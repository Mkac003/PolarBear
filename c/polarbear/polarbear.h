// PolarBear is a library for making cross-platform games and GUIs.

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "pbtypes.h"


#ifndef POLARBEAR_H
#define POLARBEAR_H

// Keys

#define PB_KEY_a SDLK_a
#define PB_KEY_b SDLK_b

#define PB_a SDLK_a
#define PB_b SDLK_b
#define PB_c SDLK_c
#define PB_d SDLK_d
#define PB_e SDLK_e
#define PB_f SDLK_f
#define PB_g SDLK_g
#define PB_h SDLK_h
#define PB_i SDLK_i
#define PB_j SDLK_j
#define PB_k SDLK_k
#define PB_l SDLK_l
#define PB_m SDLK_m
#define PB_n SDLK_n
#define PB_o SDLK_o
#define PB_p SDLK_p
#define PB_q SDLK_q
#define PB_r SDLK_r
#define PB_s SDLK_s
#define PB_t SDLK_t
#define PB_u SDLK_u
#define PB_v SDLK_v
#define PB_w SDLK_w
#define PB_x SDLK_x
#define PB_y SDLK_y
#define PB_z SDLK_z
#define PB_0 SDLK_0
#define PB_1 SDLK_1
#define PB_2 SDLK_2
#define PB_3 SDLK_3
#define PB_4 SDLK_4
#define PB_5 SDLK_5
#define PB_6 SDLK_6
#define PB_7 SDLK_7
#define PB_8 SDLK_8
#define PB_9 SDLK_9
#define PB_F0 SDLK_F0
#define PB_F1 SDLK_F1
#define PB_F2 SDLK_F2
#define PB_F3 SDLK_F3
#define PB_F4 SDLK_F4
#define PB_F5 SDLK_F5
#define PB_F6 SDLK_F6
#define PB_F7 SDLK_F7
#define PB_F8 SDLK_F8
#define PB_F9 SDLK_F9
#define PB_F10 SDLK_F10
#define PB_F11 SDLK_F11
#define PB_F12 SDLK_F12

// Init
int PB_Init();
// Uninit and free window
void PB_Quit(PB_Window *window);

// Create a PB Surface
PB_Surface *PB_CreateSurface(int w, int h);
void PB_Blit(PB_Surface *src, PB_Rect *srcrect, PB_Surface *dst, PB_Pos *pos);

void PB_FreeSurface(PB_Surface *surface);
int PB_GetEvent(PB_Event *event);
int PB_NullGetEvent();

void PB_Clear(PB_Window *window, int r, int g, int b);
void PB_Refresh(PB_Window *window);
void PB_LimitFps(PB_Window *window, float fps);

// Drawing

// Image
PB_Surface *PB_LoadImage(char *path);
PB_Texture *PB_LoadImageTexture(char *path);
void PB_SDL_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

PB_Surface *PB_Scale(PB_Surface *surf, int w, int h);
PB_Pos *PB_CreatePos(int x, int y);
void PB_Convert(PB_Window *window, PB_Surface *surf);

// Rect
PB_Rect *PB_CreateRect(int x, int y, int w, int h);
void PB_FreeRect(PB_Rect *rect);
void PB_DrawFilledRectRGB(PB_Surface *surface, PB_Rect *rect, int r, int g, int b);
void PB_DrawFilledRectXYWHRGB(PB_Surface *surface, int x, int y, int w, int h, int r, int g, int b);

// Window

// Creates a new window and SDL_Renderer
PB_Window *PB_CreateWindow(char *title, int width, int height, Uint32 flags);

void PB_DestroyWindow(PB_Window *window);
void PB_SetWindowPosition(PB_Window *window, int x, int y);
void PB_SetWindowTitle(PB_Window *window, char *title);
PB_Surface *PB_GetWindowSurface(PB_Window *window);

// Other
void PB_ConsoleDisableBuffering();
float PB_GetFps(PB_Window *window);
double PB_GetDelta(PB_Window *window);

#endif
