import json

def load():
  with open("boot.json", "r") as f:
    boot = json.loads(f.read())
    main = __import__(boot["path"])
    main.main()

load()
