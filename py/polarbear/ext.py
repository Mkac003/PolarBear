# Utilities for makeing applicatons with PolarBear

import sys

def get_platform():
  # Computer Platforms
  if sys.platform.startswith("linux"):
    return "linux"
  elif sys.platform.startswith("aix"):
    return "aix"
  elif sys.platform.startswith("win32") or sys.platform.startswith("cygwin"):
    return "win"
  elif sys.platform.startswith("freebsd"):
    return "freebsd"
  elif sys.platform.startswith("darwin"):
    return "mac"
  # Mobile platforms
  if sys.platform.startswith("android"):
    return "android"

def get_storage_path():
  if getattr(sys, "frozen", False): # If built with polarbuild-pyinstaller
    return sys._MEIPASS
  return "./"


def debug_message():
  print("Using PolarBear.")
