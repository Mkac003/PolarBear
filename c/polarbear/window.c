#include "pbtypes.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"
#include "font.h"

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
