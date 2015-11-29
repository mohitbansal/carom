#include "globals.h"

void render_board(BOARD *board)
{
  SDL_Rect dest_rect = { COORD_X(board->x), COORD_Y(board->y + board->game_texture.h), board->game_texture.w, board->game_texture.h };
  SDL_RenderCopy(renderer, board->game_texture.sdl_texture, NULL, &dest_rect);
}

void set_board_positions(BOARD *board)
{
  board->x = board->y = 0;



  board->sides[0][0]  = { board->x + BOARD_SIDEBAR_MARGIN, board->y + BOARD_SIDEBAR_MARGIN };
  board->sides[0][1]  = { board->x + BOARD_SIDEBAR_MARGIN, board->y + BOARD_HEIGHT - BOARD_SIDEBAR_MARGIN };
                    
  board->sides[1][0] = { board->x + BOARD_SIDEBAR_MARGIN, board->y + BOARD_HEIGHT - BOARD_SIDEBAR_MARGIN };
  board->sides[1][1] = { board->x + BOARD_WIDTH - BOARD_SIDEBAR_MARGIN, board->y + BOARD_HEIGHT - BOARD_SIDEBAR_MARGIN };

  board->sides[2][0] = { board->x + BOARD_WIDTH - BOARD_SIDEBAR_MARGIN, board->y + BOARD_HEIGHT - BOARD_SIDEBAR_MARGIN };
  board->sides[2][1] = { board->x + BOARD_WIDTH - BOARD_SIDEBAR_MARGIN, board->y + BOARD_SIDEBAR_MARGIN };

  board->sides[3][0] = { board->x + BOARD_WIDTH - BOARD_SIDEBAR_MARGIN, board->y + BOARD_SIDEBAR_MARGIN };
  board->sides[3][1] = { board->x + BOARD_SIDEBAR_MARGIN, board->y + BOARD_SIDEBAR_MARGIN };
                    


  // board->squares = { 
board->squares[0][0] = { board->sides[0][0].x + 200, board->sides[0][0].y + 280 };
board->squares[0][1] = { board->sides[0][0].x + 200, board->sides[0][0].y + 920 };

// board->squares[1] = { 
board->squares[1][0] = { board->sides[0][0].x + 280, board->sides[0][0].y + 1000 }; 
board->squares[1][1] = { board->sides[0][0].x + 920, board->sides[0][0].y + 1000 };
// };
// board->sqaures[2] = { 
board->squares[2][0] = { board->sides[0][0].x + 1000, board->sides[0][0].y + 920 }; 
board->squares[2][1] = { board->sides[0][0].x + 1000, board->sides[2][1].y + 280 }; 
// };
// board->squares[3] = { 
board->squares[3][0] = { board->sides[0][0].x + 920, board->sides[0][0].y + 200 }; 
board->squares[3][1] = { board->sides[0][0].x + 280, board->sides[0][0].y + 200 };
                   // };

board->holes[0].pos = { board->sides[0][0].x + 50, board->sides[0][0].y + 50 };
board->holes[0].radius = 50;

board->holes[1].pos = { board->sides[0][0].x + 50, board->sides[0][0].y + 1150 };
board->holes[1].radius = 50;

board->holes[2].pos = { board->sides[0][0].x + 1150, board->sides[0][0].y + 1150 };
board->holes[2].radius = 50;

board->holes[3].pos = { board->sides[0][0].x + 1150, board->sides[0][0].y + 50 };
board->holes[3].radius = 50;
}

void init_board(BOARD *board)
{
  board->game_texture.sdl_texture = load_img("data/images/board_1400x1400.png");
  board->game_texture.w = BOARD_WIDTH;
  board->game_texture.h = BOARD_HEIGHT;

  set_board_positions(board);
}