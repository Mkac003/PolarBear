/*
 * PolarBear Styling guide:
 *  main color: #281811
 *  secondary color: #FFFFFF
 *  
 *  font: Manjari regular
 * 
 * */

#include "pbtypes.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

// Init
int PB_Init(){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
    // Error
    printf("SDL Init Error: %s\n", SDL_GetError());
    }
  return 0;
  }

// Uninit and free window
void PB_Quit(PB_Window *window){
  // SDL_DestroyRenderer(window->sdl_renderer);
  SDL_DestroyWindow(window->sdl_window);
  SDL_Quit();
  free(window);
  }

// Create a PB Surface
PB_Surface *PB_CreateSurface(int w, int h){
  PB_Surface *surface = malloc(sizeof(PB_Surface));
  surface->surf_id = 0;
  surface->surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
  return surface;
  }

void PB_FreeSurface(PB_Surface *surface){
  free(surface->surface);
  free(surface);
  }

int PB_GetEvent(PB_Event *pb_event){
  SDL_Event event;
  
  int ret = SDL_PollEvent(&event);
  
  pb_event->sdl_event = event;
  pb_event->key = event.key.keysym.sym;
  pb_event->type = event.type;
  
  return ret;
  }

int PB_NullGetEvent(){
  return SDL_PollEvent(NULL);
  }

// Renderer functions

// void PB_SetBGRenderColorRGB(PB_Window *window, int r, int g, int b){
  // SDL_SetRenderDrawColor(window->sdl_renderer, r, g, b, 255);
  // }

// void PB_SetBGRenderColorRGBA(PB_Window *window, int r, int g, int b, int a){
  // SDL_SetRenderDrawColor(window->sdl_renderer, r, g, b, a);
  // }

void PB_Clear(PB_Window *window, int r, int g, int b){
  SDL_FillRect(SDL_GetWindowSurface(window->sdl_window), NULL, SDL_MapRGB(SDL_GetWindowSurface(window->sdl_window)->format, r, g, b));
  }

void PB_Refresh(PB_Window *window){
  SDL_UpdateWindowSurface(window->sdl_window);
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

// Drawing

// void PB_SetColor(PB_Window *window, Uint8 r, Uint8 g, Uint8 b){
  // SDL_SetRenderDrawColor(window->sdl_renderer, r, g, b, 255);
  // }

// void PB_SetColorRGBA(PB_Window *window, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
  // SDL_SetRenderDrawColor(window->sdl_renderer, r, g, b, a);
  // }

PB_Rect *PB_CreateRect(int x, int y, int w, int h){
  PB_Rect *rect = malloc(sizeof(PB_Rect));
  SDL_Rect *sdl_rect = malloc(sizeof(SDL_Rect));
  
  sdl_rect->x = x;
  sdl_rect->y = y;
  sdl_rect->w = w;
  sdl_rect->h = h;
  
  rect->sdl_rect = sdl_rect;
  return rect;
  }

void PB_FreeRect(PB_Rect *rect){
  free(rect);
  }

void PB_DrawFilledRectRGB(PB_Surface *surface, PB_Rect *rect, int r, int g, int b){
  SDL_Rect *sdl_rect = rect->sdl_rect;
  SDL_FillRect(surface->surface, sdl_rect, SDL_MapRGB(surface->surface->format, r, g, b));
  }

void PB_DrawFilledRectXYWHRGB(PB_Surface *surface, int x, int y, int w, int h, int r, int g, int b){
  SDL_Rect sdl_rect;
  sdl_rect.x = x;
  sdl_rect.y = y;
  sdl_rect.w = w;
  sdl_rect.h = h;
  
  SDL_FillRect(surface->surface, &sdl_rect, SDL_MapRGB(surface->surface->format, r, g, b));
  }

PB_Surface *PB_GetWindowSurface(PB_Window *window){
  PB_Surface *surf = malloc(sizeof(PB_Surface));
  surf->surface = SDL_GetWindowSurface(window->sdl_window);
  surf->surf_id = 0;
  return surf;
  }

// Window

// Creates a new window and SDL_Renderer
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
  // SDL_DestroyRenderer(window->sdl_renderer);
  }

void PB_SetWindowPosition(PB_Window *window, int x, int y){
  SDL_SetWindowPosition(window->sdl_window, x, y);
  }

void PB_SetWindowTitle(PB_Window *window, char *title){
  SDL_SetWindowTitle(window->sdl_window, title);
  }

// Misc

void PB_ConsoleDisableBuffering(){
  setbuf(stdout, NULL);
  }

float PB_GetFps(PB_Window *window){
  return window->fps;
  }
