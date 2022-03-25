import select
import socket
import json
from typing import Callable


class Client:

    class Mode:
        TEXT = 't'
        BINARY = 'b'
        CALL = 'c'

    class Proxy:
        def __init__(self, conn):
            self._conn = conn

        def __getattr__(self, name):
            def method(*args, **varargs):
                self._conn.send_call(name, args, varargs)
            return method

    def __init__(
            self,
            mode: Mode = Mode.TEXT,
            idle_beat: float = 0.2,
            on_idle: Callable = None,
            on_close: Callable = None,
            on_data: Callable = None,
            recv_buffer_len: int = 1024,
            raw: bool = False,
            target: object = None
    ):
        self.mode = mode
        self.idle_beat = idle_beat
        self.idle_callback = on_idle
        self.close_callback = on_close
        self.recv_callback = on_data
        self.recv_buffer_len = recv_buffer_len
        self.queue = []
        self.buffer = bytearray()
        self.header_len = 4
        self.raw = raw
        self.call = Client.Proxy(self)

        self.close_callback = None
        self.socket = None
        self.target = target

    def connect(self, host='localhost', port=6666):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((host, port))
        self.socket.setblocking(False)
        self.socket.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)

    def on_data(self, fn: Callable):
        self.recv_callback = fn

    def on_close(self, fn: Callable):
        self.close_callback = fn

    def on_idle(self, fn: Callable):
        self.idle_callback = fn

    def close(self):
        if callable(self.close_callback):
            self.close_callback()
        self.socket.close()
        self.socket = None

    def loop(self):
        while True:
            self.check(self.idle_beat)
            if callable(self.idle_callback):
                self.idle_callback()

    def check(self, beat=0.0, limit=1000):
        count = 0
        idle = False
        while not idle and count < limit:
            readable, writable, error = select.select([self.socket],
                                                      [self.socket] if len(self.queue) else [],
                                                      [self.socket],
                                                      beat)
            idle = True
            for s in readable:
                self.on_data_received(s)
                idle = False
            for s in writable:
                self.on_can_write(s)
                idle = False
            for s in error:
                self.on_disconnected(s)
                idle = False
            count += 1

    def on_data_received(self, s):
        packet = s.recv(self.recv_buffer_len)
        if self.mode == Client.Mode.TEXT:
            packet = packet.decode('utf-8', 'ignore') if not self.raw else packet
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
                packet = packet.decode('utf-8', 'ignore') if not self.raw else packet
                if self.mode == Client.Mode.BINARY:
                    if callable(self.recv_callback):
                        self.recv_callback(packet)
                elif self.mode == Client.Mode.CALL:
                    try:
                        packet = json.loads(packet)
                        method = packet[0]
                        args = packet[1]
                        varargs = packet[2]
                        getattr(self.target, method)(*args, **varargs)
                    except Exception as e:
                        print(f"{e}\nreceived unknown message: {packet}")

    def on_can_write(self, s):
        if len(self.queue):
            s.send(self.queue.pop(0))

    def on_disconnected(self, s):
        self.close()

    def send(self, data, raw=False):
        packet = data.encode('utf-8', 'ignore') if not raw else data
        if self.mode != Client.Mode.TEXT:
            packet = len(packet).to_bytes(self.header_len, byteorder='little') + packet
        self.queue.append(packet)
        self.check()

    def send_call(self, name, args, varargs):
        self.send(json.dumps([name, args, varargs], default='str'))

    def set_mode(self, mode: Mode, target: object = None):
        self.mode = mode
        self.target = target

    def set_raw(self, raw: bool):
        self.raw = raw
