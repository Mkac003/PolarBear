import polarbear as pb
from polarbear import keys

pb.debug = True

import time

window = pb.Window("PolarBear", 800, 600)
window_surface = window.get_surface()

while True:
  for event in pb.get_events():
    #  print(pb.QUIT)
    if event.type == pb.QUIT:
      quit()
  
  window.clear((255, 255, 255))
  
  window.refresh()
