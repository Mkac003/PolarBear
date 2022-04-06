## Note: Yes, I know that according to PEP 8 and the Python standards,
## I should use tabs instead of spaces. idc.. makes it more readable for me and I am used to spaces.

# This is the official PolarBear ctypes wrapper

import ctypes
import os

def setlib(clib):
  global lib
  lib = clib

def quit(window):
  global lib
  lib.PB_Quit(window)

def get_events():
  events = []
  event = lib.PB_CreateEvent();
  
  now = 1
  while now:
    now = lib.PB_GetEvent(event)
    yield _Event(event, key=now)
  
  lib.PB_FreeEvent(event)

class draw:
  def rect(surface, color, rect):
    lib.PB_DrawRect()

class mouse:
  def get_pos():
    return (lib.PB_GetMousePosX().value, lib.PB_GetMousePosY().value)

class _Event:
  def __init__(self, c_event, key=None):
    # Creates an Event from a ctypes event
    
    self.type = lib.PB_GetEventType(c_event)
    self.key = lib.PB_GetKey(c_event)
  
class Surface:
  def __init__(self, width=50, height=50, surf=None):
    if surf is not None:
      self.surface = surf
    else:
      self.surface = lib.PB_CreateSurface(ctypes.c_int(width), ctypes.c_int(height))
  
  def get_width(self):
    return lib.PB_SurfaceGetWidth(self.surf).value
  
  def get_height(self):
    return lib.PB_SurfaceGetHeight(self.surf).value
  
  def __del__(self):
    lib.PB_FreeSurface(self.surface)

# The Rectangle Class
class Rect:
  def __init__(self, x, y, w, h):
    self.rect = lib.PB_CreateRect(ctypes.c_int(x), ctypes.c_int(y), ctypes.c_int(w), ctypes.c_int(h))
  
  def __del__(self):
    lib.PB_FreeRect(self.rect)
  
# The Window class
class Window:
  def __init__(self, title, width, height, flags=None):
    title_char = ctypes.c_char_p(bytes(str(title), encoding="utf-8")) # Create a char pointer from a string (char *)
    
    self.window = lib.PB_CreateWindow(title_char, ctypes.c_int(width), ctypes.c_int(height), flags)
  
  def refresh(self):
    lib.PB_Refresh(self.window)
  
  def clear(self, color):
    lib.PB_Clear(self.window, color[0], color[1], color[2])
  
  def destroy(self):
    lib.PB_DestroyWindow(self.window)
  
  def set_position(self, x, y):
    lib.PB_SetWindowPosition(self.window, ctypes.c_int(x), ctypes.c_int(y))
  
  def set_title(self, title):
    title_char = ctypes.c_char_p(bytes(str(title), encoding="utf-8")) # Create a char pointer from a string (char *)
    lib.PB_SetWindowTitle(self.window, title_char)
  
  def get_surface(self):
    return Surface(surf=lib.PB_GetWindowSurface(self.window))
