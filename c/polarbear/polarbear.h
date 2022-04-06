// PolarBear is a library for making cross-platform games and GUIs.

#include <stdlib.h>
#include <SDL2/SDL.h>
#include "pbtypes.h"
#include "surface.h"
#include "window.h"

#ifndef POLARBEAR_H
#define POLARBEAR_H

int PB_Init();
void PB_Quit(PB_Window *window);

void PB_ShowMouse();
void PB_HideMouse();
void PB_SetMouseVisible(int visible);

int PB_GetEvent(PB_Event *event);
int PB_NullGetEvent();

PB_Event PB_CreateNoPtrEvent();
PB_Event *PB_CreateEvent();

int PB_GetEventType(PB_Event *event);
int PB_GetKey(PB_Event *event);

void PB_Clear(PB_Window *window, int r, int g, int b);
void PB_Refresh(PB_Window *window);
void PB_LimitFps(PB_Window *window, float fps);


PB_Rect *PB_CreateRect(int x, int y, int w, int h);
void PB_FreeRect(PB_Rect *rect);
void PB_DrawFilledRectRGB(PB_Surface *surface, PB_Rect *rect, int r, int g, int b);
void PB_DrawFilledRectXYWHRGB(PB_Surface *surface, int x, int y, int w, int h, int r, int g, int b);

void PB_FreePos(PB_Pos *pos);
void PB_FreeEvent(PB_Event *event);

// Other
void PB_ConsoleDisableBuffering();
float PB_GetFps(PB_Window *window);
double PB_GetDelta(PB_Window *window);

int PB_GetMousePosX();
int PB_GetMousePosY();

// int PB_GetMousePosX();

void PB_SetFullScreen(PB_Window *window, int fullscreen);

#endif

