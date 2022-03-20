#include <SDL2/SDL.h>

#ifndef PB_TYPES_H
#define PB_TYPES_H

#define PB_QUIT SDL_QUIT
#define PB_KEYDOWN SDL_KEYDOWN
#define PB_KEYUP SDL_KEYUP

#define PB_RENDERER_ACCELERATED SDL_RENDERER_ACCELERATED

typedef int PB_Bool;
#define PB_True 1;
#define PB_False 0;

typedef struct {
  SDL_Event sdl_event;
  int type;
  int key;
  } PB_Event;

typedef struct {
  SDL_Surface *surface;
  int surf_id;
  } PB_Surface;

typedef struct {
  SDL_Window *sdl_window;
  // SDL_Renderer *sdl_renderer;
  
  float fps;
  int frame_counter;
  int frame_next;
  
  } PB_Window;

typedef struct {
  SDL_Rect *sdl_rect;
  } PB_Rect;

typedef struct {
  SDL_Rect *sdl_rect;
  } PB_Pos;

typedef struct {
  SDL_Texture *sdl_tex;
  } PB_Texture;

#endif