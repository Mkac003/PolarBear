#include "polarbear/polarbear.h"
#include "polarbear/draw.h"
#include "polarbear/pbdefs.h"
#include "polarbear/font.h"

#include <stdlib.h>

int main(){
  PB_Init();
  
  PB_Window *window = PB_CreateWindow("Polar Bear", 1920, 1080, PB_RENDERER_ACCELERATED);
  PB_SetFullScreen(window, 1);
  
  PB_Bool running = PB_True;
  long int timer = 0;
  PB_Event event;
  
  PB_Surface *window_surface = PB_GetWindowSurface(window);
  PB_Surface *image = PB_LoadImage("cat.jpg");
  
  image = PB_FreeScale(image, 50, 100);
  // PB_Convert(window, image);
  
  printf("WIDTH: %i\n", PB_SurfaceGetWidth(image));
  
  PB_Rect *imagerect = PB_SurfaceGetRect(image);
  printf("IMAGE WIDTH %i\n", imagerect->sdl_rect.w);
  PB_Pos *pos = PB_CreatePos(0, 0);
  
  PB_Font *font = PB_CreateFont("font.ttf", 100);
  PB_Surface *text = PB_AAFontRender(font, "This is a test", 0, 0, 0);
  // PB_Convert(window, text);
  
  char title[50];
  printf("%i\n", PB_QUIT);
  while (running){
    
    while(PB_GetEvent(&event)){
      if (event.type==PB_QUIT){
        PB_Quit(window);
        return 0;
        }
      }
    
    timer ++;
    if (timer>10) {
      timer = 0;
      sprintf(title, "FPS: %f", PB_GetFps(window));
      PB_SetWindowTitle(window, title);
      }
    
    PB_Clear(window, 255, 255, 255);
    
    pos->x = PB_GetMousePosX()-PB_SurfaceGetWidth(text)/2;
    pos->y = PB_GetMousePosY()-PB_SurfaceGetHeight(text)/2;
    
    PB_Blit(text, window_surface, pos);
    
    PB_Refresh(window);
    
    PB_LimitFps(window, -1);
    }
  
  PB_FreePos(pos);
  PB_FreeSurface(image);
  PB_FreeEvent(&event);
  
  PB_Quit(window);
  PB_FreeSurface(window_surface);
  
  return 0;
  }
