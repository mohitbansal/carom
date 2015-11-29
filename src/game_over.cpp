#include "globals.h"

static GAME_TEXTURE winner_texture, inst;
static double x, y;

void init_game_over_state()
{
  SDL_Color c = { 0, 255, 0, 255 };
  inst = text("Press Esc", mono_oblique_font18, c);
  x = 170; y = 200;
}

int winning_player()
{
  int i;
  int max_score = 0, winner;
  for(i = 0; i < players; i++)
  {
    if(scores[i] > max_score)
    {
      max_score = scores[i];
      winner = i;
    }
  }
  return winner;
}

void move_to_game_over_state()
{
  game_state = GAME_OVER;
  if(winner_texture.sdl_texture)
  {
    SDL_DestroyTexture(winner_texture.sdl_texture);
  }


  char str[20];
  sprintf(str, "PLAYER%d WINS", winning_player() + 1);

  SDL_Color c = { 0, 255, 0, 255 };
  winner_texture = text(str, mono_font22, c);
}

void render_game_over_state()
{
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
  SDL_Rect rect = { 0, 0, WIDTH, HEIGHT };
  SDL_RenderFillRect(renderer, &rect);

  render_text(&winner_texture, x, y);
  render_text(&inst, x + 50, y + 50);
}