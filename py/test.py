import polarbear as pb
from polarbear import keys

pb.debug = True

import time

window = pb.Window("PolarBear", 800, 600)
window_surface = window.get_surface()
w = 0

while True:
  for event in pb.get_events():
    if event.type == pb.QUIT:
      quit()
    if event.type == pb.KEYDOWN:
      if event.key == pb.K_w:
        w += 10
        window.set_position(w, w)
        print("Key 'A' was pressed")
  
  window.clear((255, 255, 255))
  
  window.refresh()
