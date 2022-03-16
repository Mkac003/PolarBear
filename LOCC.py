# Lines Of Code Counter
# Count lines of code in your project
import os

include = [".c", ".py", ".h"]

lines = 0

for root, subdirs, files in os.walk("./"):
  for f in files:
    for ending in include:
      if f.endswith(ending) and f != "LOCC.py" and not f.startswith("test"):
        path = os.path.join(root, f)
        print(path)
        with open(path) as io:
          lines += len(io.readlines())
          

print(lines)
