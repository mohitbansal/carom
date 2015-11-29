#include "globals.h"

void move_to_main_menu()
{
  game_state = MAIN_MENU;
  reset();
}

void move_to_play()
{
  game_state = PLAY;
}

void move_to_instruction_state()
{
  if(game_state != INSTRUCTION)
    back_state = game_state;
  game_state = INSTRUCTION;
}

void move_to_state(int state)
{
  switch(state)
  {
    case MAIN_MENU:
      move_to_main_menu();
    break;
    case PLAY:
      move_to_play();
    break;
    case INSTRUCTION:
      move_to_instruction_state();
    break;
  }
}