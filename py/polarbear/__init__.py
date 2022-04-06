import os, ctypes
from .polarbear import *

debug = False

def log(msg):
  if debug:
    print(msg)

path = "polarbear/data/_polarbear.so"
loadtype = "LoadLibrary"

if not os.path.exists(path):
  raise OSError(f"Path '{path}' does not exist.")

if loadtype == "LoadLibrary":
  lib = ctypes.cdll.LoadLibrary(path)
elif loadtype == "CDLL":
  lib = ctypes.CDLL(path)
else:
  print(f"Unknown loadtype '{loadtype}'")

lib.PB_Init()
setlib(lib)

# Constants

log("loading constants")

QUIT = ctypes.c_int.in_dll(lib, "PB_QUIT").value
KEYDOWN = ctypes.c_int.in_dll(lib, "PB_KEYDOWN").value
KEYUP = ctypes.c_int.in_dll(lib, "PB_KEYUP").value

K_a = ctypes.c_int.in_dll(lib, "PB_a").value
K_b = ctypes.c_int.in_dll(lib, "PB_b").value
K_c = ctypes.c_int.in_dll(lib, "PB_c").value
