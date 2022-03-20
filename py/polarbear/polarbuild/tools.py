import time

build_sett_deaf = """
name = MyApp

version = 1.0
"""

def parse_args(args):
  args.pop(0)
  return args

# Does the same thing as loadsettstr, but it is pretty :-) ... and up to 8 times slower
def _loadsettstr(string):
  defs = {} # All the definitions
  
  # Split the file into lines
  for line in string.split("\n"):
    # Remove whitespace at the start and at the end of the line
    line = line.strip()
    
    # Continue if the line is not a comment
    if not line.startswith("#"):
      # Divide the list on every '='
      divided = line.split("=")
      
      # The first item is always the name, remove unnecessary whitespace
      name = divided[0].strip()
      
      # Join all the items that are not the name (list[1:] returns the list without the first element) by '=' that we removed earlier
      value = "=".join(divided[1:])
      
      # Remove unnecessary whitespace
      value = value.strip()
      
      # Set the name as the value in definitions.
      defs[name] = value
  
  # Remove empty strings, if there are any.
  # Passing None to defs[] will do nothing.
  del defs["" if "" in defs else None]
  
  # And return our output
  return defs
  
def loadsettstr(string):
  defs = {}
  
  for line in string.split("\n"):
    if not line.strip().startswith("#"):
      defs[str(line.split("=")[0].strip())] = "=".join(line.split("=")[1:]).strip()
    
  del defs["" if "" in defs else None]
  
  return defs

def loadsett(path):
  with open(path, "r") as f:
    string = f.read()
    return loadsettstr(string)

if __name__ == "__main__":
  
  s = time.time()
  loadsettstr(build_sett_deaf)
  print(f"F1: {time.time()-s}")
  
  s = time.time()
  _loadsettstr(build_sett_deaf) # up to 8x slower
  print(f"F2: {time.time()-s}")
