import sys
import tools

ver = "1.0dev"

args = tools.parse_args(sys.argv)
path = args[0]

if "init" in args:
  print(f"PolarBuild {ver} - Init")
  os.mkdir("polar_build")
  os.mkdir("polar_build/logs")
  
  with open("polar_build/logs/build.sett", "w") as f:
    f.write(tools.build_sett_deaf)

if "all" in args:
  
