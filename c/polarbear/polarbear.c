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
#include <SDL2/SDL_image.h>

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
  
  return 0;
  }

// SDL functions
void PB_SDL_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

// Create a PB Surface
PB_Surface *PB_CreateSurface(int w, int h){
  PB_Surface *surface = malloc(sizeof(PB_Surface));
  surface->surf_id = 0;
  surface->surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
  return surface;
  }

PB_Surface *PB_Scale(PB_Surface *surf, int w, int h){
  SDL_Rect rect;
  SDL_Rect dst;
  
  dst.x = 0;
  dst.y = 0;
  dst.w = w;
  dst.h = h;
  
  SDL_GetClipRect(surf->surface, &rect);
  PB_Surface *new_surf = PB_CreateSurface(w, h);
  
  SDL_BlitScaled(surf->surface, &rect, new_surf->surface, &dst);
  
  return new_surf;
  }

void PB_Convert(PB_Window *window, PB_Surface *surf){
  surf->surface = SDL_ConvertSurfaceFormat(surf->surface, SDL_GetWindowPixelFormat(window->sdl_window), 0);
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
  PB_Event *event;
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

int PB_NullGetEvent(){
  return SDL_PollEvent(NULL);
  }

// Renderer functions

PB_Surface *PB_LoadImage(char *path){
  PB_Surface *surf = malloc(sizeof(PB_Surface));
  surf->surface = IMG_Load(path);
  return surf;
  }

PB_Texture *PB_LoadImageTexture(char *path){
  PB_Surface *surf = PB_LoadImage(path);
  
  
  free(path);
  }

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

PB_Pos *PB_CreatePos(int x, int y){
  PB_Pos *pos = malloc(sizeof(PB_Pos));
  SDL_Rect *sdl_rect = malloc(sizeof(SDL_Rect));
  
  sdl_rect->x = x;
  sdl_rect->y = y;
  
  pos->sdl_rect = sdl_rect;
  
  return pos;
  }

/* Free */

void PB_FreePos(PB_Pos *pos){
  free(pos->sdl_rect);
  free(pos);
  }

void PB_FreeRect(PB_Rect *rect){
  free(rect->sdl_rect);
  free(rect);
  }

void PB_FreeSurface(PB_Surface *surf){
  SDL_FreeSurface(surf->surface);
  free(surf);
  }

void PB_FreeEvent(PB_Event *event){
  free(&event->sdl_event);
  free(event);
  }

/* Drawing */

void PB_Blit(PB_Surface *src, PB_Rect *srcrect, PB_Surface *dst, PB_Pos *pos){
  SDL_BlitSurface(src->surface, srcrect->sdl_rect, dst->surface, pos->sdl_rect);
  };

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

PB_Surface *PB_FreeScale(PB_Surface *surf, int w, int h){
  SDL_Rect rect;
  SDL_Rect dst;
  
  dst.x = 0;
  dst.y = 0;
  dst.w = w;
  dst.h = h;
  
  SDL_GetClipRect(surf->surface, &rect);
  PB_Surface *new_surf = PB_CreateSurface(w, h);
  
  SDL_BlitScaled(surf->surface, &rect, new_surf->surface, &dst);
  PB_FreeSurface(surf);
  
  return new_surf;
  }

