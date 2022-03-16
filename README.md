# PolarBear
PolarBear is a library for making 2D games with python and/or C++ &amp; C

## Examples - Hello Rectangle

### Python
This example will be using the PolarBear python wrapper.
```python
# imports the polarbear library
import polarbear as pb

# Inits all modules
pb.init()

# Creates a new window
window = pb.Window("My App", 800, 600)

# Gets the surface of the window
window_surface = window.get_surface() 

while True:
  # Fill the window with white
  window.clear((255, 255, 255))
  
  # Draw a red rectangle on X: 100 Y: 100 and W:100 H: 100
  pb.draw.rect(window_surface, (255, 0, 0), (100, 100, 100, 100))
  
  # Updates the window
  window.refresh()
  
```
