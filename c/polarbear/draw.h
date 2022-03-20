#include "pbtypes.h"

#ifndef PB_DRAW_H
#define PB_DRAW_H


void PB_PutPixel(PB_Surface *surf, int x, int y, int r, int g, int b);
void PB_DrawFilledRectRGB(PB_Surface *surface, PB_Rect *rect, int r, int g, int b);
void PB_DrawFilledRectXYWHRGB(PB_Surface *surface, int x, int y, int w, int h, int r, int g, int b);

void PB_DrawFilledCircle(PB_Surface *surf, int x, int y, int radius, int r, int g, int b);

#endif
