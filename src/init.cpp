#include "globals.h"

SDL_Window *window;
SDL_Renderer *renderer;

int init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printf("could not initialize sdl %s", SDL_GetError());
    return 0;
  }

  window = SDL_CreateWindow(TITLE, SCREEN_X, SCREEN_Y, WIDTH, HEIGHT, SDL_FLAGS);
  if(!window)
  {
    printf("could not create window %s\n", SDL_GetError());
    return 0;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(!renderer)
  {
    printf("could not create renderer %s\n", SDL_GetError());
    return 0;
  }

  if(!init_img())
    return 0;

  if(!init_text())
    return 0;

  init_sound();

  return 1;
}

void close()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}