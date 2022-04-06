#include <stdlib.h>
#include <SDL2/SDL.h>
#include "surface.h"

#ifndef PB_WINDOW_H
#define PB_WINDOW_H

PB_Window *PB_CreateWindow(char *title, int width, int height, Uint32 flags);

void PB_DestroyWindow(PB_Window *window);
void PB_SetWindowPosition(PB_Window *window, int x, int y);
void PB_SetWindowTitle(PB_Window *window, char *title);
PB_Surface *PB_GetWindowSurface(PB_Window *window);

#endif
