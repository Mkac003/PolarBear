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

print(lib.PB_a)

QUIT = lib.PB_QUIT
#  K_a = 
