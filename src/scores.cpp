#include "globals.h"
char str[20];

// GAME_TEXTURE player1, player2, player3, player4;
GAME_TEXTURE score_textures[4];
void init_scores()
{

}

void render_scores()
{
  SDL_Color c = { 0, 255, 0, 255 };
  int i;
  for(i = 0; i < players; i++)
  {
    if(update_score_texture[i])
    {
      update_score_texture[i] = 0;
      if(score_textures[i].sdl_texture)
        SDL_DestroyTexture(score_textures[i].sdl_texture);
    
      sprintf(str, "Player%d: %d", i + 1, scores[i]);
      score_textures[i] = text(str, mono_oblique_font14, c);
    }
    render_text(&score_textures[i], SCORE_PANEL_X + i * 100, SCORE_PANEL_Y);
  }
}