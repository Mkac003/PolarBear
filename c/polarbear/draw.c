#include "polarbear.h"
#include <SDL2/SDL.h>

#ifndef PB_DRAW_C
#define PB_DRAW_C

void PB_SDL_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
  /* Use PB_PutPixel - this is here for speed and eff. reasons*/
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
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
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

void PB_PutPixel(PB_Surface *surf, int x, int y, int r, int g, int b){
  Uint32 color = SDL_MapRGB(surf->surface->format, r, g, b);
  
  if (SDL_MUSTLOCK(surf->surface)){
    if(SDL_LockSurface(surf->surface) < 0){
      printf("SDL LockSurface Error: %s\n", SDL_GetError());
      }
    }
  
  PB_SDL_putpixel(surf->surface, x, y, color);
  
  if (SDL_MUSTLOCK(surf->surface)) {
    SDL_UnlockSurface(surf->surface);
    }
  }

void PB_DrawFilledRectRGB(PB_Surface *surface, PB_Rect *rect, int r, int g, int b){
  SDL_FillRect(surface->surface, &rect->sdl_rect, SDL_MapRGB(surface->surface->format, r, g, b));
  }


void PB_DrawFilledRectXYWHRGB(PB_Surface *surface, int x, int y, int w, int h, int r, int g, int b){
  SDL_Rect sdl_rect;
  sdl_rect.x = x;
  sdl_rect.y = y;
  sdl_rect.w = w;
  sdl_rect.h = h;
  
  SDL_FillRect(surface->surface, &sdl_rect, SDL_MapRGB(surface->surface->format, r, g, b));
  }

void PB_DrawFilledCircle(PB_Surface *surf, int x, int y, int radius, int r, int g, int b){
  if (SDL_MUSTLOCK(surf->surface)){
    if(SDL_LockSurface(surf->surface) < 0){
      printf("SDL LockSurface Error: %s\n", SDL_GetError());
      }
    }
  
  Uint32 color = SDL_MapRGB(surf->surface->format, r, g, b);
  
  for (int w = 0; w < radius * 2; w++) {
    for (int h = 0; h < radius * 2; h++) {
      int dx = radius - w;
      int dy = radius - h;
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        PB_SDL_putpixel(surf->surface, x+dx, y+dy, color);
      }
    }
  }
  
  if (SDL_MUSTLOCK(surf->surface)) {
    SDL_UnlockSurface(surf->surface);
    }
  }

void PB_DrawLine(PB_Surface *surf, int x1, int y1, int x2, int y2, int r, int g, int b){
  if (SDL_MUSTLOCK(surf->surface)){
    if(SDL_LockSurface(surf->surface) < 0){
      printf("SDL LockSurface Error: %s\n", SDL_GetError());
      }
    }
  
  Uint32 color = SDL_MapRGB(surf->surface->format, r, g, b);
  
  
  
  
  if (SDL_MUSTLOCK(surf->surface)) {
    SDL_UnlockSurface(surf->surface);
    }
  }

void PB_QuickDrawLine(PB_Surface *surf, int x1, int y1, int x2, int y2, int s, int r, int g, int b){
  if (SDL_MUSTLOCK(surf->surface)){
    if(SDL_LockSurface(surf->surface) < 0){
      printf("SDL LockSurface Error: %s\n", SDL_GetError());
      }
    }
  
  Uint32 color = SDL_MapRGB(surf->surface->format, r, g, b);
  
  int x;
  int y;
  
  for(float i=0; i<1; i += s){
    x = x1 + (y2 - x1)*i;
    y = y1 + (y2 - y1)*i;
    
    PB_SDL_putpixel(surf->surface, x, y, color);
    }
  
  if (SDL_MUSTLOCK(surf->surface)) {
    SDL_UnlockSurface(surf->surface);
    }
  }

#endif
