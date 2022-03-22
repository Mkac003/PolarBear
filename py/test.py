import polarbear as pb
import time

pb.init()

window = pb.Window("PolarBear", 800, 600)
window_surface = window.get_surface()
print("1")

while True:
  print("2")
  for event in pb.get_events():
    print("3")
    print(event.type)
    print("4")
  
  window.clear((255, 255, 255))
  
  window.refresh()
