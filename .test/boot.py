import ctypes
import os

a = 10.0

print(type(a) == int)

lib = ctypes.cdll.LoadLibrary(os.path.abspath("test.so"))
lib.main()
