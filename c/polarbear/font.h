#include <SDL2/SDL_ttf.h>
#include "polarbear.h"

typedef struct {
  TTF_Font *sdl_font;
  } PB_Font;

void PB_FontInit();
PB_Surface *PB_FontRender(PB_Font *font, char *text, int r, int g, int b);
PB_Surface *PB_AAFontRender(PB_Font *font, char *text, int r, int g, int b);
PB_Font *PB_CreateFont(char *path, int size);
