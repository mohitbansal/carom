#include "globals.h"

double COORD_X(double x)
{
  return x - camera.mov.pos.x;
}

double COORD_Y(double y)
{
  return camera.game_texture.h + camera.mov.pos.y - y; 
}


double RCOORD_X(double x)
{
  double X = x - VIEWPORT_X;
  return camera.game_texture.w * X / VIEWPORT_WIDTH;
}

double RCOORD_Y(double y)
{
  double Y = y - VIEWPORT_Y;
  Y = VIEWPORT_HEIGHT - Y;
  return camera.game_texture.h * Y / VIEWPORT_HEIGHT;
}

SDL_Texture *create_screen_texture()
{
  SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, camera.game_texture.w, camera.game_texture.h);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
  return texture;
}


void set_camera_height(double height)
{
  if(height > 10)
  {
    if(camera.game_texture.sdl_texture)
      SDL_DestroyTexture(camera.game_texture.sdl_texture);
    camera.game_texture.h = height;
    camera.game_texture.w = VIEWPORT_WIDTH * height / VIEWPORT_HEIGHT;
    camera.game_texture.sdl_texture = create_screen_texture();
  }
}

void init_camera()
{
  camera.mov.pos = { 0, 0 };
  set_camera_height(BOARD_HEIGHT);
}