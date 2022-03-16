#include "polarbear.h"
#include <stdlib.h>

int main(){
  PB_ConsoleDisableBuffering();
  
  PB_Init();
  
  PB_Window *window = PB_CreateWindow("Polar Bear", 800, 600, PB_RENDERER_ACCELERATED);
  PB_SetWindowPosition(window, 100, 50);
  PB_SetWindowTitle(window, "Hello");
  
  PB_Bool running = PB_True;
  long int timer = 0;
  PB_Event event;
  
  PB_Surface *window_surface = PB_GetWindowSurface(window);
  
  int x = 0;
  
  char title[50];
  
  while (running){
    
    while(PB_GetEvent(&event)){
      if (event.type==PB_QUIT){
        PB_Quit(window);
        return 0;
        }
      if (event.type==PB_KEYDOWN){
        if (event.key==PB_d){
          x = x+50;
          }
        if (event.key==PB_a){
          x = x-50;
          }
        }
      }
    
    PB_Clear(window, 255, 255, 255);
    
    timer ++;
    if (timer>10) {
      timer = 0;
      sprintf(title, "FPS: %f", PB_GetFps(window));
      PB_SetWindowTitle(window, title);
      }
      
    // PB_DrawFilledRectXYWHRGB(window_surface, x, 100, 100, 100, 255, 0, 0);
    
    // PB_SetColor(window, 255, 255, 255);
    PB_Refresh(window);
    
    PB_LimitFps(window, -1);
    }
  
  return 0;
  }
