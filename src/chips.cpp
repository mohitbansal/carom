#include "globals.h"

void init_chips()
{
  CHIPS[0] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[0]->game_texture.sdl_texture = load_img("data/images/white_chip_80x80.png");
  CHIPS[0]->game_texture.w = CHIPS[0]->game_texture.h = 80;
  CHIPS[0]->mov.radius = 40;
  CHIPS[0]->mov.imass = 1;
  CHIPS[0]->mov.chip_type = WHITE;

  CHIPS[1] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[1]->game_texture.sdl_texture = load_img("data/images/black_chip_80x80.png");
  CHIPS[1]->game_texture.w = CHIPS[1]->game_texture.h = 80;
  CHIPS[1]->mov.radius = 40;
  CHIPS[1]->mov.imass = 1;
  CHIPS[1]->mov.chip_type = BLACK;

  CHIPS[2] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[2]->game_texture.sdl_texture = load_img("data/images/black_chip_80x80.png");
  CHIPS[2]->game_texture.w = CHIPS[2]->game_texture.h = 80;
  CHIPS[2]->mov.radius = 40;
  CHIPS[2]->mov.imass = 1;
  CHIPS[2]->mov.chip_type = BLACK;

  CHIPS[3] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[3]->game_texture.sdl_texture = load_img("data/images/black_chip_80x80.png");
  CHIPS[3]->game_texture.w = CHIPS[3]->game_texture.h = 80;
  CHIPS[3]->mov.radius = 40;
  CHIPS[3]->mov.imass = 1;
  CHIPS[3]->mov.chip_type = BLACK;

  CHIPS[4] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[4]->game_texture.sdl_texture = load_img("data/images/white_chip_80x80.png");
  CHIPS[4]->game_texture.w = CHIPS[4]->game_texture.h = 80;
  CHIPS[4]->mov.radius = 40;
  CHIPS[4]->mov.imass = 1;
  CHIPS[4]->mov.chip_type = WHITE;

  CHIPS[5] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[5]->game_texture.sdl_texture = load_img("data/images/white_chip_80x80.png");
  CHIPS[5]->game_texture.w = CHIPS[5]->game_texture.h = 80;
  CHIPS[5]->mov.radius = 40;
  CHIPS[5]->mov.imass = 1;
  CHIPS[5]->mov.chip_type = WHITE;


  CHIPS[6] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[6]->game_texture.sdl_texture = load_img("data/images/white_chip_80x80.png");
  CHIPS[6]->game_texture.w = CHIPS[6]->game_texture.h = 80;
  CHIPS[6]->mov.radius = 40;
  CHIPS[6]->mov.imass = 1;
  CHIPS[6]->mov.chip_type = WHITE;

  CHIPS[7] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[7]->game_texture.sdl_texture = load_img("data/images/white_chip_80x80.png");
  CHIPS[7]->game_texture.w = CHIPS[7]->game_texture.h = 80;
  CHIPS[7]->mov.radius = 40;
  CHIPS[7]->mov.imass = 1;
  CHIPS[7]->mov.chip_type = WHITE;

  CHIPS[8] = (CHIP *)malloc(sizeof(CHIP));
  CHIPS[8]->game_texture.sdl_texture = load_img("data/images/white_chip_80x80.png");
  CHIPS[8]->game_texture.w = CHIPS[8]->game_texture.h = 80;
  CHIPS[8]->mov.radius = 40;
  CHIPS[8]->mov.imass = 1;
  CHIPS[8]->mov.chip_type = WHITE;

}

void reset_chips()
{
  chips_on_board = 9;
  CHIPS[0]->mov.pos = { 700, 700 };
  CHIPS[1]->mov.pos = { 700, 780 };
  CHIPS[2]->mov.pos = { 700, 620 };
  CHIPS[3]->mov.pos = { 620, 700 };
  CHIPS[4]->mov.pos = { 780, 700 };
  CHIPS[5]->mov.pos = { 780, 780 };
  CHIPS[6]->mov.pos = { 620, 780 };
  CHIPS[7]->mov.pos = { 620, 620 };
  CHIPS[8]->mov.pos = { 780, 620 };

  int i;
  for(i = 0; CHIPS[i]; i++)
  {
    CHIPS[i]->mov.vel = CHIPS[i]->mov.acc = { 0, 0 };
    CHIPS[i]->mov.state = STOPPED;
    CHIPS[i]->mov.in_hole = 0;
  }
}

void render_chips()
{
  int i;
  for(i = 0; CHIPS[i]; i++)
  {
    if(CHIPS[i]->mov.state != OUT_OF_GAME)
    {
      SDL_Rect dest_rect = { COORD_X(CHIPS[i]->mov.pos.x - CHIPS[i]->mov.radius), COORD_Y(CHIPS[i]->mov.pos.y + CHIPS[i]->mov.radius), CHIPS[i]->game_texture.w, CHIPS[i]->game_texture.h };
      SDL_RenderCopy(renderer, CHIPS[i]->game_texture.sdl_texture, NULL, &dest_rect);
    }
  }
}