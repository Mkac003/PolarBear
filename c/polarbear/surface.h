#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

#ifndef PB_SURFACE_H
#define PB_SURFACE_H

PB_Surface *PB_LoadImage(char *path);
void PB_SDL_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

PB_Surface *PB_Scale(PB_Surface *surf, int w, int h);
PB_Surface *PB_FreeScale(PB_Surface *surf, int w, int h);
PB_Pos *PB_CreatePos(int x, int y);
void PB_Convert(PB_Window *window, PB_Surface *surf);
void PB_ConvertAlpha(PB_Surface *surf);

PB_Surface *PB_CreateSurface(int w, int h);
void PB_Blit(PB_Surface *src, PB_Surface *dst, PB_Pos *pos);
void PB_BlitClip(PB_Surface *src, PB_Rect *srcrect, PB_Surface *dst, PB_Pos *pos);

int PB_SurfaceGetWidth(PB_Surface *surf);
int PB_SurfaceGetHeight(PB_Surface *surf);
PB_Rect *PB_SurfaceGetRect(PB_Surface *surf);

void PB_FreeSurface(PB_Surface *surf);

#endif
