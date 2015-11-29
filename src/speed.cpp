#include "globals.h"

GAME_TEXTURE speed_text_texture;
void init_speed_text()
{
  SDL_Color c = { 0, 255, 0, 255 };
  speed_text_texture = text("Speed", mono_oblique_font14, c); 
}

void render_speed(STRIKER *striker)
{
  render_text(&speed_text_texture, SPEED_PANEL_X + 4, SPEED_PANEL_Y);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_Rect rect = { SPEED_PANEL_X + 4 + speed_text_texture.w + 10, SPEED_PANEL_Y + 5, 200, 15 };
  SDL_RenderDrawRect(renderer, &rect);

  double per = vector_magnitude(&striker->mov.vel) * 200 / striker->max_speed;
  rect.w = per;
  SDL_RenderFillRect(renderer, &rect);
}