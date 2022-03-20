#include "polarbear/polarbear.h"
#include "polarbear/draw.h"

#include <stdlib.h>

int main(){
  PB_Init();
  
  PB_Window *window = PB_CreateWindow("Polar Bear", 643, 638, PB_RENDERER_ACCELERATED);
    
  PB_Bool running = PB_True;
  long int timer = 0;
  PB_Event event;
  
  PB_Surface *window_surface = PB_GetWindowSurface(window);
  PB_Surface *image = PB_LoadImage("cat.jpg");
  PB_Convert(window, image);
  
  PB_Rect *imagerect = PB_CreateRect(0, 0, 643, 638);
  PB_Pos *pos = PB_CreatePos(0, 0);
  // PB_DrawFilledCircle(image, 100, 100, 50, 255, 255, 255);
  
  char title[50];
  
  while (running){
    
    while(PB_GetEvent(&event)){
      if (event.type==PB_QUIT){
        PB_Quit(window);
        return 0;
        }
      }
    
    // PB_Clear(window, 255, 255, 255);
    
    timer ++;
    if (timer>10) {
      timer = 0;
      sprintf(title, "FPS: %f", PB_GetFps(window));
      PB_SetWindowTitle(window, title);
      }
    
    PB_Blit(image, imagerect, window_surface, pos);
    
    // PB_SetColor(window, 255, 255, 255);
    PB_Refresh(window);
    
    PB_LimitFps(window, -1);
    }
  
  PB_FreeSurface(image);
  
  return 0;
  }
