#include "globals.h"

int init_img()
{
  int img_flags = IMG_INIT_PNG;
  if(!(IMG_Init(img_flags) & img_flags))
  {
    printf("could not initialize img %s", IMG_GetError());
    return 0;
  }
  return 1;
}

SDL_Texture *load_img(char *path)
{
  SDL_Surface *surface = IMG_Load(path);
  if(!surface)
  {
    printf("could not load image %s", IMG_GetError());
    return 0;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if(!texture)
  {
    printf("could not load load texture %s", SDL_GetError());
    return 0;
  }
  // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);

  SDL_FreeSurface(surface);
  return texture;
}