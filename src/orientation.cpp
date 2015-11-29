#include "globals.h"

STRIKER guide;

void init_orientation(STRIKER *striker)
{
  guide = *striker;
  guide.mov.is_silent = 1;
  guide.game_texture.sdl_texture = load_img("data/images/orientation_80x80.png");
}

void render_orientation(STRIKER *striker)
{
  int i;
  guide.mov.pos = striker->mov.pos;
  guide.mov.vel = striker->orientation;
  vector_mult1(&guide.mov.vel, 20);
  for(i = 0; i < 40; i++)
  {
    vector_add1(&guide.mov.pos, &guide.mov.vel);
    resolve_collision_with_board(&guide.mov, &board);
    render_striker(&guide);
  }
}