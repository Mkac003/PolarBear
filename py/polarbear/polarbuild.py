import os
import sys
import json
import shutil

build_path = "polar_build"

def make_bootloader(path):
  print(f"Generating app bootloader in {path}")
  with open(path, "w") as f:
    with open("polarbear/data/bootloader.py", "r") as bf:
      f.write(bf.read())

def make_dir(path): # Creates a folder, if it does not exist
  if not os.path.exists(path):
    os.mkdir(path)

def build_linux(config_path):
  make_dir(f"{build_path}/linux/")
  
  if not os.path.exists(config_path):
    print(f"{config_path} does not exist!")
    return
  with open(config_path, "r") as f:
    config = json.loads(f.read())
  
  if "appimage" in config["build"]["platforms"]["linux"]:
    appdir = f"{build_path}/linux/appimage/{config['codename']}.AppDir"
    
    make_dir(f"{build_path}/linux/appimage")
    if os.path.exists(appdir):
      shutil.rmtree(appdir)
    make_dir(appdir)
    make_dir(f"{appdir}/usr/")
    make_dir(f"{appdir}/usr/bin/")
    make_dir(f"{appdir}/usr/bin/polarbear")
    
    print("Adding polarbear")
    shutil.copy2("polarbear", f"{appdir}/usr/bin/")
    
    for path in config["build"]["include"]:
      print(f"Including {path}")
      shutil.copy(path, f"{appdir}/usr/bin/")
    
def main(args):
  if len(args) > 0:
    if args[0] == "clear":
      print("Clearing..")
      shutil.rmtree("polar_build")
      print("removed polar_build")
    if args[0] == "init":
      with open("build.json", "w") as f:
        with open("polarbear/data/build.json", "r") as bf:
          f.write(bf.read())
      
      if not os.path.exists(build_path):
        os.mkdir(build_path)
      print("Made build.json and polar_build")
      
    if args[0] == "linux":
      build_linux(args[1])

if __name__ == "__main__":
  main(sys.argv[1:])
