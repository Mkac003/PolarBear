#include "pbtypes.h"

#ifndef PB_DRAW_H
#define PB_DRAW_H

typedef void (*putpixelfunc)(SDL_Surface*, int, int, Uint32);

void PB_PutPixel(PB_Surface *surf, int x, int y, int r, int g, int b);
void PB_DrawFilledRectRGB(PB_Surface *surface, PB_Rect *rect, int r, int g, int b);
void PB_DrawFilledRectXYWHRGB(PB_Surface *surface, int x, int y, int w, int h, int r, int g, int b);

void PB_DrawFilledCircle(PB_Surface *surf, int x, int y, int radius, int r, int g, int b);
void PB_DrawLine(PB_Surface *surf, int x1, int y1, int x2, int y2, int r, int g, int b);

void PB_SDL_PutPixelFunc1(SDL_Surface *surface, int x, int y, Uint32 pixel);
void PB_SDL_PutPixelFunc2(SDL_Surface *surface, int x, int y, Uint32 pixel);
void PB_SDL_PutPixelFunc3_1(SDL_Surface *surface, int x, int y, Uint32 pixel);
void PB_SDL_PutPixelFunc3_2(SDL_Surface *surface, int x, int y, Uint32 pixel);
void PB_SDL_PutPixelFunc4(SDL_Surface *surface, int x, int y, Uint32 pixel);

void *PB_GetPutPixelFunc(SDL_Surface *surface);


/* AntiAliasing */


#endif
