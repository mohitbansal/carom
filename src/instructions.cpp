#include "globals.h"

static GAME_TEXTURE inst[7], main_instruction;
static double x, y;

void init_instructions()
{
  SDL_Color c = { 0, 255, 0, 255 };
  inst[0] = text("Use keys a, s to move striker.", mono_oblique_font18, c);
  inst[1] = text("Hold Right click to increase speed.", mono_oblique_font18, c);
  inst[2] = text("Press Left click to release striker.", mono_oblique_font18, c);
  inst[3] = text("", mono_oblique_font18, c);
  inst[4] = text("White chips earn 20 points", mono_oblique_font18, c);
  inst[5] = text("Black chips earn 10 points", mono_oblique_font18, c);
  inst[6] = text("Press any key to resume", mono_oblique_font18, c);

  main_instruction = text("Press h for help", mono_oblique_font18, c);

  y = inst[0].h * 7  +  60;
  y = (HEIGHT - y) / 2;
  x = 10;
}

void render_main_instruction()
{
  render_text(&main_instruction, SPEED_PANEL_X + 270, SPEED_PANEL_Y);
}

void render_instructions()
{ 

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 150);
  SDL_Rect rect = { 0, 0, WIDTH, HEIGHT };
  SDL_RenderFillRect(renderer, &rect);

  int i;
  for(i = 0; i < 7; i++)
  {
    render_text(&inst[i], x, y + inst[i].h * i);
  }
}