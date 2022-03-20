import ctypes
import os
import sys

a = 10.0

print(type(a) == int)

if getattr(sys, 'frozen', True):
  lib = ctypes.cdll.LoadLibrary(os.path.join(sys._MEIPASS, "test.so"))
#  else:
  #  lib = ctypes.cdll.LoadLibrary(os.path.abspath("test.so"))

lib.main()
