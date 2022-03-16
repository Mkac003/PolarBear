import polarbear as pb
import time

pb.init()

window = pb.Window("PolarBear", 800, 600)
window_surface = window.get_surface()

while True:
  window.clear((255, 255, 255))
  
  window.refresh()
