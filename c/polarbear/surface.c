#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "pbtypes.h"

#ifndef PB_SURFACE_C
#define PB_SURFACE_C

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

void PB_ConvertAlpha(PB_Surface *surf){
  SDL_Surface *newsurf = SDL_ConvertSurfaceFormat(surf->surface, SDL_PIXELFORMAT_RGBA8888, 0);
  SDL_FreeSurface(surf->surface);
  surf->surface = newsurf;
  }

PB_Surface *PB_LoadImage(char *path){
  PB_Surface *surf = malloc(sizeof(PB_Surface));
  surf->surface = IMG_Load(path);
  return surf;
  }

void PB_Blit(PB_Surface *src, PB_Surface *dst, PB_Pos *pos){
  SDL_Rect rect;
  rect.x = pos->x;
  rect.y = pos->y;
  
  SDL_BlitSurface(src->surface, NULL, dst->surface, &rect);
  }

void PB_BlitClip(PB_Surface *src, PB_Rect *srcrect, PB_Surface *dst, PB_Pos *pos){
  SDL_Rect rect;
  rect.x = pos->x;
  rect.y = pos->y;
  
  SDL_BlitSurface(src->surface, &srcrect->sdl_rect, dst->surface, &rect);
  }

void PB_FreeSurface(PB_Surface *surf){
  SDL_FreeSurface(surf->surface);
  free(surf);
  }

int PB_SurfaceGetWidth(PB_Surface *surf) {
  return surf->surface->w;
  }

int PB_SurfaceGetHeight(PB_Surface *surf) {
  return surf->surface->h;
  }

PB_Rect *PB_SurfaceGetRect(PB_Surface *surf){
  PB_Rect *rect = malloc(sizeof(PB_Rect));
  
  rect->sdl_rect.x = 0;
  rect->sdl_rect.y = 0;
  rect->sdl_rect.w = PB_SurfaceGetWidth(surf);
  rect->sdl_rect.h = PB_SurfaceGetHeight(surf);
  printf("WWW: %i\n", PB_SurfaceGetWidth(surf));

  return rect;
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

#endif
