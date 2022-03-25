import select
import socket
import signal
from typing import Callable
import uuid
import json


class Server:

    class Mode:
        TEXT = 't'
        BINARY = 'b'
        CALL = 'c'

    class Proxy:
        def __init__(self, method: Callable):
            self._method = method

        def __getattr__(self, name):
            def method(*args, **varargs):
                self._method(name, args, varargs)
            return method

    class Connection:
        def __init__(self, sock, server):
            self.socket = sock
            self.server = server
            self.queue = []
            self.is_closing = False
            self.id = uuid.uuid1().hex
            self.tags = set()
            self.recv_callback = None
            self.close_callback = None
            self.buffer = bytearray()
            self.header_len = 4
            self.call = Server.Proxy(self.send_call)
            self.call_all = Server.Proxy(self.send_call_all)
            self.call_others = Server.Proxy(self.send_call_others)
            self.worker = None

        def send_call(self, name, args, varargs):
            self.send(json.dumps([name, args, varargs], default='str'))

        def send_call_all(self, name, args, varargs):
            data = json.dumps([name, args, varargs], default='str')
            for client in self.server.clients.values():
                client.send(data)

        def send_call_others(self, name, args, varargs):
            data = json.dumps([name, args, varargs], default='str')
            for client in self.server.clients.values():
                if client is not self:
                    client.send(data)

        def on_data(self, fn: Callable):
            self.recv_callback = fn

        def on_close(self, fn: Callable):
            self.close_callback = fn

        def send(self, data):
            packet = data.encode('utf-8', 'ignore') if not self.server.raw else data
            if self.server.mode != Server.Mode.TEXT:
                packet = len(packet).to_bytes(self.header_len, byteorder='little') + packet
            self.queue.append(packet)
            self.server.append_to_outputs(self.socket)

        def recv(self, data):
            packet = data
            if self.server.mode == Server.Mode.TEXT:
                packet = packet.decode('utf-8', 'ignore') if not self.server.raw else packet
                if callable(self.recv_callback):
                    self.recv_callback(packet)
            else:
                self.buffer += packet
                while True:
                    buffer_len = len(self.buffer)
                    if buffer_len < self.header_len:
                        return
                    packet_len = int.from_bytes(self.buffer[0:self.header_len], byteorder='little')
                    if buffer_len < self.header_len + packet_len:
                        return
                    packet = self.buffer[self.header_len:self.header_len + packet_len]
                    self.buffer = self.buffer[self.header_len + packet_len:]
                    packet = packet.decode('utf-8', 'ignore') if not self.server.raw else packet
                    if self.server.mode == Server.Mode.BINARY:
                        if callable(self.recv_callback):
                            self.recv_callback(packet)
                    elif self.server.mode == Server.Mode.CALL:
                        try:
                            packet = json.loads(packet)
                            method = packet[0]
                            args = packet[1]
                            varargs = packet[2]
                            getattr(self.worker, method)(*args, **varargs)
                        except Exception as e:
                            print(f"{e}\nreceived unknown message: {packet}")

        def broadcast(self, data, tag=None):
            for client in self.server.clients.values():
                if client is not self:
                    if tag is None or tag in client.tags:
                        client.send(data)

        def tag(self, tag: str):
            self.tags += set(tag)

        def untag(self, tag: str):
            self.tags -= set(tag)

        def close(self):
            self.server.close(self.socket)
            pass

    def __init__(
            self,
            host: str = '0.0.0.0',
            port: int = 6666,
            worker_class: object = None,
            mode: Mode = Mode.TEXT,
            listen_backlog: int = 5,
            idle_beat: float = 0.2,
            on_idle: Callable = None,
            on_connect: Callable = None,
            on_disconnect: Callable = None,
            recv_buffer_len: int = 1024,
            raw: bool = False
    ):
        self.host = host
        self.port = port
        self.worker_class = worker_class
        self.mode = mode
        self.listen_backlog = listen_backlog
        self.idle_beat = idle_beat
        self.idle_callback = on_idle
        self.connect_callback = on_connect
        self.disconnect_callback = on_disconnect
        self.recv_buffer_len = recv_buffer_len
        self.raw = raw

        self.socket = None
        self.inputs = []
        self.outputs = []
        self.clients = {}
        self.workers = {}

        def handler(signum, frame):
            self.quit("received signal " + str(signum) + ", frame " + str(frame))

        signal.signal(signal.SIGINT, handler)
        signal.signal(signal.SIGTERM, handler)

    def worker(self, worker_class: object):
        self.worker_class = worker_class

    def quit(self, msg):
        print("Server shutting down (" + msg + ")\n")
        for s in self.inputs:
            if s is not self.socket:
                s.close()
        self.socket.close()

    def append_to_outputs(self, s):
        if s not in self.outputs:
            self.outputs.append(s)

    def _listen(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(False)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.socket.bind((self.host, self.port))
        self.socket.listen(self.listen_backlog)
        self.inputs.append(self.socket)

    def start(self):
        print(f"Server starting, host {self.host}, port {str(self.port)}\n")
        self._listen()
        while self.inputs:
            readable, writable, error = select.select(self.inputs, self.outputs, self.inputs, self.idle_beat)
            for s in readable:
                if s is self.socket:
                    self.on_new_connection()
                else:
                    self.on_data_received(s)
            for s in writable:
                self.on_can_write(s)
            for s in error:
                self.on_disconnected(s)
            self.on_idle()

    def on_new_connection(self):
        sock, client_address = self.socket.accept()
        sock.setblocking(False)
        sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        self.inputs.append(sock)
        self.clients[sock] = Server.Connection(sock, self)
        if callable(self.connect_callback):
            self.connect_callback(self.clients[sock])
        if self.worker_class is not None:
            self.workers[sock] = self.worker_class(self.clients[sock])
            self.clients[sock].worker = self.workers[sock]

    def on_data_received(self, s):
        data = s.recv(self.recv_buffer_len)
        if data:
            self.clients[s].recv(data)
        else:
            self.close(s)

    def on_can_write(self, s):
        if len(self.clients[s].queue):
            s.send(self.clients[s].queue.pop(0))
        if not len(self.clients[s].queue):
            self.outputs.remove(s)
            if self.clients[s].is_closing:
                self.close(s)

    def on_disconnected(self, s):
        self.close(s)

    def close(self, s):
        if callable(self.disconnect_callback):
            self.disconnect_callback(self.clients[s])
        if s in self.outputs:
            self.outputs.remove(s)
        self.inputs.remove(s)
        if callable(self.clients[s].close_callback):
            self.clients[s].close_callback()
        s.close()
        del self.clients[s]
        if s in self.workers:
            del self.workers[s]

    def on_idle(self):
        if callable(self.idle_callback):
            self.idle_callback()
        pass

    def set_mode(self, mode: Mode):
        self.mode = mode

    def set_raw(self, raw: bool):
        self.raw = raw
