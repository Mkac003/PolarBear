# This is the official PolarBear ctypes wrapper

import ctypes
import os

def init(path="polarbear/data/polarbear.so", loadtype="LoadLibrary"):
  """
    args:
      str path - sets the path to .so polarbear file. Deafults to 'polarbear/data/polarbear.so'
      
      str loadtype - defines the way to load the library. This can be 'LoadLibrary' or 'CDLL'. Deafults to 'LoadLibrary'
    
    Loads the library into a global variable lib and call PB_Init().
    Needs to be called at the start before calling
    any functions or creating any classes.
  """
  
  global lib
  
  if not os.path.exists(path):
    print(f"Path '{path}' does not exist.")
    return False
  
  if loadtype == "LoadLibrary":
    lib = ctypes.cdll.LoadLibrary(path)
  elif loadtype == "CDLL":
    lib = ctypes.CDLL(path)
  else:
    print(f"Unknown loadtype '{loadtype}'")
  
  lib.PB_Init()

# The Surface Class
class Surface:
  """
    The surface class implements a wrapper for PB_Surface (SDL_Surface).
  """
  
  def __init__(self, width=50, height=50, surf=None):
    """
      args:
        int width - The desired width of the surface in pixels
        int height - The desired height of the surface in pixels
        
        PB_Surface *surf - the surf to fill the wrapper with, deafults to None
      Creates a new surface.
    """
    
    if surf is not None:
      self.surface = surf
    else:
      self.surface = lib.PB_CreateSurface(ctypes.c_int(width), ctypes.c_int(height))
  
  def __del__(self):
    """
      Frees the surface associated with this instance.
      This function is called automatically by the python GC.
    """
    
    lib.PB_FreeSurface(self.surface)

# The Rectangle Class
class Rect:
  def __init__(self, x, y, w, h):
    """
      args:
        int x - the X coordinate
        int y - the Y coordinate
        
        int w - the desired width of the rectangle
        int h - the desired height of the rectangle
      
      Creates a new Rectangle.
    """
    self.rect = lib.PB_CreateRect(ctypes.c_int(x), ctypes.c_int(y), ctypes.c_int(w), ctypes.c_int(h))
  
  def __del__(self):
    """
      Frees the rectangle associated with this instance.
      This function is called automatically by the python GC.
    """
    
    lib.PB_FreeRect(self.rect)
  
# The Window class
class Window:
  """
    Window class manages all the communications with the WM (Window Manager).
    It implements methods like set_title and set_size.
  """
  
  def __init__(self, title, width, height, flags=None):
    """
      args:
        str title - the desired title
        
        int width - the desired width of the window
        
        int height - the desired height of the window
                
      Initializes the window by calling PB_CreateWindow
    """
    
    title_char = ctypes.c_char_p(bytes(str(title), encoding="utf-8")) # Create a char pointer from a string (char *)
    
    self.window = lib.PB_CreateWindow(title_char, ctypes.c_int(width), ctypes.c_int(height), flags)
  
  def refresh(self):
    """
      Updates contents of the window
    """
    
    lib.PB_Refresh(self.window)
  
  def clear(self, color):
    """
      args:
        tuple/list color - a list or a tuple of 3 RGB colors.
        
      Fills the window with a specified color.
    """
    
    lib.PB_Clear(self.window, color[0], color[1], color[2])
  
  def destroy(self):
    """
      Destroys the window by calling PB_DestroyWindow.
    """
    lib.PB_DestroyWindow(self.window)
  
  def set_position(self, x, y):
    """
      args:
        int x - the X coordinate
        
        int y - the Y coordinate
      Sets the position of the window relative to the top-left of the screen.
    """
    lb.PB_SetWindowPosition(self.window, ctypes.c_int(x), ctypes.c_int(y))
  
  def set_title(self, title):
    """
      args:
        str title - the title you want to switch to
      Sets the title (caption) of the window by calling PB_SetWindowTitle
    """
    title_char = ctypes.c_char_p(bytes(str(title), encoding="utf-8")) # Create a char pointer from a string (char *)
    lib.PB_SetWindowTitle(self.window, title_char)
  
  def get_surface(self):
    return Surface(surf=lib.PB_GetWindowSurface(self.window))
  
