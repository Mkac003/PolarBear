#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "polarbear.h"
#include "font.h"

void PB_FontInit(){
  if (TTF_Init() == -1){
    printf("TTF Init Error: %s\n", SDL_GetError());
    }
  }

PB_Font *PB_CreateFont(char *path, int size){
  PB_Font *font = malloc(sizeof(PB_Font));
  TTF_Font *ttf_font = TTF_OpenFont(path, size);
  font->sdl_font = ttf_font;
  return font;
  }

PB_Surface *PB_FontRender(PB_Font *font, char *text, int r, int g, int b){
  PB_Surface *surf = malloc(sizeof(PB_Surface));
  SDL_Color color = {r, g, b};
  
  SDL_Surface *rendered = TTF_RenderText_Solid(font->sdl_font, text, color); 
  
  surf->surface = rendered;
  
  return surf;
  }

PB_Surface *PB_AAFontRender(PB_Font *font, char *text, int r, int g, int b){
  PB_Surface *surf = malloc(sizeof(PB_Surface));
  SDL_Color color = {r, g, b};
  
  SDL_Surface *rendered = TTF_RenderText_Blended(font->sdl_font, text, color); 
  
  surf->surface = rendered;
  
  return surf;
  }
