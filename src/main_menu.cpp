#include "globals.h"

GAME_TEXTURE item1, item2, item3, item4, item5;
static double x, y;

void init_main_menu()
{
  SDL_Color c = { 0, 255, 0, 255 };
  item1 = text("1. Single player", mono_oblique_font18, c);
  item2 = text("2. Two players", mono_oblique_font18, c);
  item3 = text("3. Three players", mono_oblique_font18, c);
  item4 = text("4. Four players", mono_oblique_font18, c);
  item5 = text("Press 1, 2, 3, 4", mono_oblique_font18, c);

  double h = item1.h + item2.h + item3.h + item4.h + 30;
  y = (VIEWPORT_HEIGHT - h) / 2;

  x = (VIEWPORT_WIDTH - item1.w) / 2;

}

void update_main_menu()
{
  switch(keydown)
  {
    case SDLK_1:
      players = 1;
    break;
    case SDLK_2:
      players = 2;
    break;
    case SDLK_3:
      players = 3;
    break;
    case SDLK_4:
      players = 4;
    break;
  }
  
  if(players > 0)
    move_to_play();
}

void render_main_menu()
{
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
  SDL_Rect rect = { 0, 0, WIDTH, HEIGHT };
  SDL_RenderFillRect(renderer, &rect);

  render_text(&item1, x, y);
  render_text(&item2, x, y + item1.h + 10);
  render_text(&item3, x, y + item1.h + 10 + item2.h + 10);
  render_text(&item4, x, y + item1.h + 10 + item2.h + 10 + item3.h + 10);
  render_text(&item5, x, y + item1.h + 10 + item2.h + 10 + item3.h + 10 + item4.h + 20);
}