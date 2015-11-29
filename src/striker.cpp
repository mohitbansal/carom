#include "globals.h"

static void move(STRIKER *striker, int dir)
{
  VECTOR v;
  if(dir == -1)
  {
    v = vector_sub(&board.squares[striker->square][0], &striker->mov.pos);
  } else {
    v = vector_sub(&board.squares[striker->square][1], &striker->mov.pos);
  }

  vector_limit1(&v, 50);
  vector_add1(&striker->mov.pos, &v);
}

static void orient(STRIKER *striker, double rad)
{
  VECTOR v1 = { cos(rad), sin(rad) };
  VECTOR v2 = { -sin(rad), cos(rad) };
  vector_mult1(&v1, striker->orientation.x);
  vector_mult1(&v2, striker->orientation.y);
  vector_add1(&v1, &v2);
  striker->orientation = v1;
}

static void set_orientation_based_on_mouse(STRIKER *striker)
{
  VECTOR m = { RCOORD_X(mouse_x), RCOORD_Y(mouse_y) };
  VECTOR v = vector_sub(&m, &striker->mov.pos);
  vector_normalize1(&v);
  striker->orientation = v;
}

static void move_left(STRIKER *striker)
{
  move(striker, -1);
}

static void move_right(STRIKER *striker)
{
  move(striker, 1);
}

static void orient_left(STRIKER *striker)
{
  orient(striker, -22.0 / (7.0 * 180));
}

static void orient_right(STRIKER *striker)
{
  orient(striker, 22.0 / (7.0 * 180));
}

static void move_to_released(STRIKER *striker)
{
  striker->state = RELEASED;
}

void move_to_with_player(STRIKER *striker, int sq)
{
  second_chance = 0;
  striker->state = WITH_PLAYER;
  striker->mov.in_hole = 0;
  striker->mov.vel = striker->mov.acc = { 0, 0 };
  striker->orientation = { 0, 1 };

  striker->square = sq;
  striker->mov.pos = board.squares[sq][0];
}

void update_striker(STRIKER *striker)
{
  switch(striker->state)
  {
    case RELEASED:
      integrate(&striker->mov);
    break;

    case WITH_PLAYER:
    // handle keys and mouse movement for position and velocity update;
      set_orientation_based_on_mouse(striker);
      if(right_mouse_button_down)
      {
        double speed = vector_magnitude(&striker->mov.vel);
        speed += 50;
        if(speed < striker->min_speed)
          speed = striker->min_speed;
        if(speed > striker->max_speed)
          speed = striker->max_speed;
        striker->mov.vel = vector_mult(&striker->orientation, speed);        
      }

      if(right_mouse_button_up)
      {
        striker->mov.vel = { 0, 0 };
        striker->mov.acc = { 0, 0 };
      }

      if(left_mouse_button_down)
      {
        move_to_released(striker);
      }

      switch(keydown)
      {
        case SDLK_a:
          move_left(striker);
        break;
        
        case SDLK_s:
          move_right(striker);
        break;

        // case SDLK_j:
        //   orient_right(striker);
        // break;

        // case SDLK_k:
        //   orient_left(striker);
        // break;

        // case SDLK_LSHIFT:
        // case SDLK_SPACE:
        //   {
        //     double speed = vector_magnitude(&striker->mov.vel);
        //     speed += 100;
        //     if(speed < striker->min_speed)
        //       speed = striker->min_speed;
        //     if(speed > striker->max_speed)
        //       speed = striker->max_speed;
        //     striker->mov.vel = vector_mult(&striker->orientation, speed);
        //   }
        // break;

        // case SDLK_RETURN:
        //   move_to_released(striker);
        // break;

        default:
        break;
      }

      // if(keyup == SDLK_SPACE)
      // {
      //   striker->mov.vel = { 0, 0 };
      //   striker->mov.acc = { 0, 0 };
      // }
    break;
  }
}

void render_striker(STRIKER *striker)
{
  SDL_Rect dest_rect = { COORD_X(striker->mov.pos.x - striker->mov.radius), COORD_Y(striker->mov.pos.y + striker->mov.radius), striker->game_texture.w, striker->game_texture.h };
  SDL_RenderCopy(renderer, striker->game_texture.sdl_texture, NULL, &dest_rect);
}

void init_striker(STRIKER *striker)
{
  striker->game_texture.sdl_texture = load_img("data/images/striker_80x80.png");
  striker->game_texture.w = striker->game_texture.h = 80;
  striker->mov.radius = 40;
  striker->mov.imass = 1;
  striker->min_speed = 1400;
  striker->max_speed = 10000;
}

void reset_striker(STRIKER *striker)
{
  move_to_with_player(striker, current_player);
}