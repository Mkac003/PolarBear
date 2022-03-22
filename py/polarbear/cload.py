# Load C or C++ .so files as extensions in python

import ctypes
import os

class Lib:
  def __init__(self, lib):
    self._pb_lib = lib
  
  def __contains__(self, name):
    return hasattr(self._pb_lib, name) is not None
  
  def call(self, name, types=None, *args):
    if hasattr(self._pb_lib, name):
      if types is not None: # The types are set, now just convert
        cargs = []
        i = 0
        for arg in args:
          var = None
          if types[i] == "int":
            var = cargs.append(ctypes.c_int(arg))
          elif types[i] == "pint":
            var = cargs.append(ctypes.c_int_p(arg))
          else:
            var = arg # no c comparison found ^
          cargs.append(var)
            
          i += 1
      else:
        cargs = []
        for arg in args: # Convert Python args to C args
          if type(arg) == int:
            cargs.append(ctypes.c_int(arg))
      
      getattr(self._pb_lib, name)(*cargs) # call it
      
    return AttributeError("Attribute Not Found")
    
  def fastcall(self, name, *args):
    return getattr(self._pb_lib, name)(*args)
  
def load(path, abspath=True):
  lib = Lib(ctypes.cdll.LoadLibrary(os.path.abspath(path)))
  
  return lib
