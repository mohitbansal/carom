#include "globals.h"

TTF_Font *mono_oblique_font14, *mono_oblique_font18, *mono_font22;

int init_text()
{
  TTF_Init();
  mono_oblique_font14 = TTF_OpenFont("data/fonts/FreeMonoBoldOblique.ttf", 14);
  mono_oblique_font18 = TTF_OpenFont("data/fonts/FreeMonoBoldOblique.ttf", 18);
  mono_font22 = TTF_OpenFont("data/fonts/FreeMono.ttf", 22);

  if(!(mono_oblique_font14 && mono_oblique_font18))
  {
    printf("Could not initialize font %s\n", TTF_GetError());
    return 0;
  }
  return 1;
}

GAME_TEXTURE text(char *str, TTF_Font *font, SDL_Color color)
{
  SDL_Surface *surface = TTF_RenderText_Solid(font, str, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  GAME_TEXTURE game_texture;
  game_texture.sdl_texture = texture;
  
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  game_texture.w = w;
  game_texture.h = h;
  
  return game_texture;
}

void render_text(GAME_TEXTURE *game_texture, double x, double y) // x and y are based on sdl coordinates
{
  SDL_SetRenderTarget(renderer, NULL);
  SDL_Rect dest_rect = { x, y, game_texture->w, game_texture->h };
  SDL_RenderCopy(renderer, game_texture->sdl_texture, NULL, &dest_rect);
}