/*
 * PolarBear Styling guide:
 *  main color: #281811
 *  secondary color: #FFFFFF
 *  
 *  font: Manjari regular
 * 
 * */

#include "pbtypes.h"
// #include "pbdefs.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "font.h"

// Init
int PB_Init(){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    // Error
    printf("SDL Init Error: %s\n", SDL_GetError());
    }
  
  if (!IMG_Init(IMG_INIT_PNG)){
    // Error
    printf("SDL_Image Init Error: %s\n", SDL_GetError());
    }
  
  PB_FontInit();
  
  return 0;
  }

int PB_GetEvent(PB_Event *pb_event){
  SDL_Event event;
  
  int ret = SDL_PollEvent(&event);
  
  pb_event->sdl_event = event;
  pb_event->key = event.key.keysym.sym;
  pb_event->type = event.type;
  
  return ret;
  }

PB_Event *PB_CreateEvent(){
  PB_Event *event = malloc(sizeof(PB_Event));
  return event;
  }

PB_Event PB_CreateNoPtrEvent(){
  PB_Event event;
  return event;
  }

/* For the python wrapper */
int PB_GetEventType(PB_Event *event){
  return event->type;
  }

int PB_GetKey(PB_Event *event){
  return event->key;
  }

int PB_NullGetEvent(){
  return SDL_PollEvent(NULL);
  }

// Renderer functions

PB_Rect *PB_CreateRect(int x, int y, int w, int h){
  PB_Rect *rect = malloc(sizeof(PB_Rect));
  
  rect->sdl_rect.x = x;
  rect->sdl_rect.y = y;
  rect->sdl_rect.w = w;
  rect->sdl_rect.h = h;
 
  return rect;
  }

PB_Pos *PB_CreatePos(int x, int y){
  PB_Pos *pos = malloc(sizeof(PB_Pos));
  
  pos->x = x;
  pos->y = y;
  
  return pos;
  }

/* Free */

void PB_FreePos(PB_Pos *pos){
  free(pos);
  }

void PB_FreeRect(PB_Rect *rect){
  free(rect);
  }

void PB_FreeEvent(PB_Event *event){
  // free(event->sdl_event);
  free(event);
  }

/* Drawing */

void PB_Clear(PB_Window *window, int r, int g, int b){
  SDL_FillRect(SDL_GetWindowSurface(window->sdl_window), NULL, SDL_MapRGB(SDL_GetWindowSurface(window->sdl_window)->format, r, g, b));
  }

void PB_Refresh(PB_Window *window){
  SDL_UpdateWindowSurface(window->sdl_window);
  }

/* Window */

PB_Window *PB_CreateWindow(char *title, int width, int height, Uint32 flags){
  PB_Window *window = malloc(sizeof(PB_Window));
  
  window->sdl_window = SDL_CreateWindow(title, 0, 0, width, height, 0);
  // window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, -1, flags);
  
  window->fps = -1;
  window->frame_counter = 0;
  window->frame_next = 1;
  
  return window;
  }

void PB_DestroyWindow(PB_Window *window){
  SDL_DestroyWindow(window->sdl_window);
  }

void PB_SetWindowPosition(PB_Window *window, int x, int y){
  SDL_SetWindowPosition(window->sdl_window, x, y);
  }

PB_Surface *PB_GetWindowSurface(PB_Window *window){
  PB_Surface *surf = malloc(sizeof(PB_Surface));
  surf->surface = SDL_GetWindowSurface(window->sdl_window);
  surf->surf_id = 0;
  return surf;
  }

void PB_SetWindowTitle(PB_Window *window, char *title){
  SDL_SetWindowTitle(window->sdl_window, title);
  }

void PB_ConsoleDisableBuffering(){
  setbuf(stdout, NULL);
  }

float PB_GetFps(PB_Window *window){
  return window->fps;
  }

void PB_LimitFps(PB_Window *window, float fps){
  // Calculate FPS
  window->frame_counter ++;
  if(SDL_GetTicks() > window->frame_next){
    window->frame_next = SDL_GetTicks()+ 1000;
    window->fps = window->frame_counter;
    window->frame_counter = 0;
    }
  
  // Cap FPS
  if(fps > 0){
    SDL_Delay(1000/fps);
    }
  }

void PB_Quit(PB_Window *window){
  SDL_DestroyWindow(window->sdl_window);
  SDL_Quit();
  free(window);
  }

int PB_GetMousePosX(){
  int x;
  SDL_GetMouseState(&x, NULL);
  return x;
  }

int PB_GetMousePosY(){
  int y;
  SDL_GetMouseState(NULL, &y);
  return y;
  }

void PB_SetFullScreen(PB_Window *window, int fullscreen){
  if (fullscreen){
    if (SDL_SetWindowFullscreen(window->sdl_window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0){
      printf("FullScreen Error (setting to on): %s\n", SDL_GetError());
      }
    } else {
      if (SDL_SetWindowFullscreen(window->sdl_window, 0) < 0){
        printf("FullScreen Error (setting to off): %s\n", SDL_GetError());
        }
      }
  }
