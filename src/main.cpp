#include "globals.h"

int quit;
double mouse_x, mouse_y;
int left_mouse_button_down, left_mouse_button_up, right_mouse_button_down, right_mouse_button_up;
SDL_Keycode keydown, keyup;
STRIKER striker;
CHIP *CHIPS[10];
BOARD board;
CAMERA camera;
int game_state, back_state; // As of now, back_state is only used to move out of instruction state.
int players;
int current_player;
int second_chance; // if current player holes a chip, then striker should not pass to next player. current player should be given second chance.
int update_score_texture[4], scores[4]; // update_score_texture is used to prevent creating new textures for rendering. cause for memory corruption
int chips_on_board; // when chips_on_board becomes zero, then move to game over and declare winner.

void increment_current_player()
{
  if(!second_chance)
  {
    current_player++;
    current_player = current_player % players;
  }
}

void handle_events()
{
  // left_mouse_button_down = left_mouse_button_up = right_mouse_button_down = right_mouse_button_up = 0;
  keydown = keyup = 0;
  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    if(e.type == SDL_QUIT)
    {
      quit = 1;
      return;
    }

    if(e.type == SDL_KEYDOWN )
    {
      keydown = e.key.keysym.sym;
    }

    if(e.type == SDL_KEYUP)
    {
      keyup = e.key.keysym.sym;
    }

    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
      if(e.button.button == SDL_BUTTON_LEFT)
      {
        left_mouse_button_up = 0;
        left_mouse_button_down = 1;
      }

      if(e.button.button == SDL_BUTTON_RIGHT)
      {
        right_mouse_button_up = 0;
        right_mouse_button_down = 1;
      }
    }

    if(e.type == SDL_MOUSEBUTTONUP)
    {
      if(e.button.button == SDL_BUTTON_LEFT)
      {
        left_mouse_button_down = 0;
        left_mouse_button_up = 1;
      }

      if(e.button.button == SDL_BUTTON_RIGHT)
      {
        right_mouse_button_down = 0;
        right_mouse_button_up = 1;
      }
    }

    if(e.type == SDL_MOUSEMOTION)
    {
      mouse_x = e.motion.x;
      mouse_y = e.motion.y;
    }
  }
}

void update()
{
  if(quit)
    return;
  
  if(game_state != INSTRUCTION)
    if(keydown == SDLK_ESCAPE)
    {
      move_to_main_menu();
      return;
    }

  if(keydown == SDLK_h)
  {
    move_to_instruction_state();
    return;
  }

  switch(game_state)
  {
    case MAIN_MENU:
      update_main_menu();
    break;

    case PLAY:
    {
        if(striker.state == RELEASED)
        {
          update_striker(&striker);

          int i;
          for(i = 0; CHIPS[i]; i++)
            if(CHIPS[i]->mov.state != OUT_OF_GAME)
              integrate(&CHIPS[i]->mov);

          for(i = 0; CHIPS[i]; i++)
            if(CHIPS[i]->mov.state != OUT_OF_GAME)
              resolve_collision(&striker.mov, &CHIPS[i]->mov);

          int j;
          for(i = 0; CHIPS[i]; i++)
          {
            if(CHIPS[i]->mov.state != OUT_OF_GAME)
            {
              for(j = i + 1; CHIPS[j]; j++)
              {
                if(CHIPS[j]->mov.state != OUT_OF_GAME)
                  resolve_collision(&CHIPS[i]->mov, &CHIPS[j]->mov);
              }
            }
          }

          for(i = 0; CHIPS[i]; i++)
          {
            if(CHIPS[i]->mov.state != OUT_OF_GAME)
            {
              resolve_collision_with_hole(&CHIPS[i]->mov, &board);
              resolve_collision_with_board(&CHIPS[i]->mov, &board);
            }
          }
          
          resolve_collision_with_hole(&striker.mov, &board);
          resolve_collision_with_board(&striker.mov, &board);

          if(!chips_on_board)
          {
            move_to_game_over_state();
            return;
          }

          int all_stopped = 1;
          for(i = 0; CHIPS[i]; i++)
          {
            if(CHIPS[i]->mov.state == MOVING)
            {
              all_stopped = 0;
              break;
            }
          }

          if(striker.mov.state == MOVING)
            all_stopped = 0;

          if(all_stopped)
          {
            // calculate score
            // assign striker to square
            if(striker.mov.in_hole)
            {
              second_chance = 0;
            }
            increment_current_player();
            move_to_with_player(&striker, current_player);
          }
        } else {
          update_striker(&striker);
        }
    }
    break;

    case INSTRUCTION:
      if(keydown || left_mouse_button_down)
        move_to_state(back_state);
    break;
  }
}

void render_orientation_text(STRIKER *striker)
{
  char *str = (char *)malloc(sizeof(char)*30);
  sprintf(str, "%s %f %f", "Orientation: ", striker->orientation.x, striker->orientation.y);
  SDL_Color c = { 0, 255, 0, 255 };
  GAME_TEXTURE game_texture = text(str, mono_oblique_font14, c);
  render_text(&game_texture, 100, 0);
}

void render()
{
  if(quit)
    return;
  //clear renderer
  SDL_SetRenderTarget(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  //clear camera
  SDL_SetRenderTarget(renderer, camera.game_texture.sdl_texture);
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderClear(renderer);

  render_board(&board);
  render_striker(&striker);
  render_chips();

  if(game_state == PLAY && striker.state == WITH_PLAYER)
  {
    render_orientation(&striker);
  }


  //render camera in viewport
  SDL_SetRenderTarget(renderer, NULL);
  SDL_Rect dest_rect = { VIEWPORT_X, VIEWPORT_Y, VIEWPORT_HEIGHT, VIEWPORT_WIDTH };
  SDL_RenderCopy(renderer, camera.game_texture.sdl_texture, NULL, &dest_rect);
  

  if(game_state == MAIN_MENU)
  {
    render_main_menu();
  }

  if(game_state == INSTRUCTION)
  {
    render_instructions();
  }

  if(game_state == GAME_OVER)
  {
    render_game_over_state();
  }

  if(game_state == PLAY && striker.state == WITH_PLAYER)
  {
    render_speed(&striker);
    // render_orientation_text(&striker);
  }

  if(game_state == PLAY)
  {
    render_main_instruction();
  }

  render_scores();
  SDL_RenderPresent(renderer);
}


int main()
{
  if(chdir(PKGDATADIR) != 0)
  {
    printf("data directory %s not found.", PKGDATADIR);
  }

  init();

  init_camera();
  init_board(&board);
  init_striker(&striker);
  init_chips();
  init_orientation(&striker);
  init_instructions();
  init_speed_text();
  init_main_menu();
  init_scores();
  init_game_over_state();

  move_to_main_menu();

  while(!quit)
  {
    frame_start();

    while(!quit && accumulator >= elapsed_time)
    {
      handle_events();
      update();
      render();
      accumulator -= elapsed_time;
    }
  }

  close();
}

void reset()
{
  players = 0;
  current_player = 0;
  int i;
  for(i = 0; i < 4; i++)
  {
    scores[i] = 0;
    update_score_texture[i] = 1;
  }

  reset_chips();
  reset_striker(&striker);
}