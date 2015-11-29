#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <malloc.h>
#include <math.h>

#define TITLE ""
#define SCREEN_X 100
#define SCREEN_Y 100

#define VIEWPORT_X 0
#define VIEWPORT_Y 22
#define SDL_FLAGS SDL_WINDOW_SHOWN

// #define WIDTH 320
// #define HEIGHT 320
// #define VIEWPORT_WIDTH 320
// #define VIEWPORT_HEIGHT 320

#define WIDTH 500
#define HEIGHT 522
#define VIEWPORT_WIDTH 500
#define VIEWPORT_HEIGHT 500

#define BOARD_SIDEBAR_MARGIN 100
#define BOARD_WIDTH 1400
#define BOARD_HEIGHT 1400

#define SPEED_PANEL_X 0
#define SPEED_PANEL_Y 22
#define SCORE_PANEL_X 0
#define SCORE_PANEL_Y 0
// init.c
extern SDL_Window *window;
extern SDL_Renderer *renderer;
int init();
void close();
// END init.c

enum GAME_STATES { MAIN_MENU, PLAY, INSTRUCTION, GAME_OVER };
enum CHIP_TYPES { NOT_CHIP_TYPE, BLACK, WHITE };
enum MOV_STATES { STOPPED, MOVING, OUT_OF_GAME };

typedef struct {
  double x, y;
} VECTOR;

typedef struct {
  VECTOR pos, vel, acc;
  double imass;
  double radius;
  int state;
  int in_hole;
  int hole;
  int chip_type;
  int is_silent;
} MOV;

typedef struct {
  double w, h;
  SDL_Texture *sdl_texture;
} GAME_TEXTURE;

typedef struct {
  MOV mov;
  GAME_TEXTURE game_texture;
} CAMERA;

enum STRIKER_STATES { WITH_PLAYER, RELEASED };
typedef struct {
  MOV mov;
  int state;
  int square;
  double min_speed, max_speed;
  VECTOR orientation;
  GAME_TEXTURE game_texture;
} STRIKER;

typedef struct {
  MOV mov;
  GAME_TEXTURE game_texture;
} CHIP;

typedef struct {
  VECTOR pos;
  double radius;
} HOLE;

typedef struct {
  double x, y;
  VECTOR sides[4][2];
  VECTOR squares[4][2];
  HOLE holes[4];
  GAME_TEXTURE game_texture;
} BOARD;

// main.c
extern int quit;
extern int left_mouse_button_down, left_mouse_button_up, right_mouse_button_down, right_mouse_button_up;
extern double mouse_x, mouse_y;
extern SDL_Keycode keydown, keyup;
extern STRIKER striker;
extern CHIP *CHIPS[10];
extern CAMERA camera;
extern BOARD board;
extern int game_state, back_state;
extern int players;
extern int current_player;
extern int second_chance;
extern int update_score_texture[], scores[];
extern int chips_on_board;

void reset();
// END main.c

// screen.c
double COORD_X(double x);
double COORD_Y(double y);
double RCOORD_X(double x);
double RCOORD_Y(double y);
void init_camera();
SDL_Texture *create_screen_texture();
// END screen.c


// utils.c
extern unsigned int frame_start_time;
extern double elapsed_time, accumulator;
void frame_start();
unsigned int current_time();
// END utils.c

// vector.c
void vector_add1(VECTOR *v1, VECTOR *v2);
double vector_magnitude2(VECTOR *v);
double vector_magnitude(VECTOR *v);
VECTOR vector_sub(VECTOR *v1, VECTOR *v2);
VECTOR vector_limit(VECTOR *v, double max);
void vector_limit1(VECTOR *v1, double max);
VECTOR vector_normalize(VECTOR *v);
void vector_normalize1(VECTOR *v);
VECTOR vector_mult(VECTOR *v, double k);
void vector_mult1(VECTOR *v, double k);
double determinant2d(VECTOR *v1, VECTOR *v2);
double vector_dot_product(VECTOR *v1, VECTOR *v2);
// END vector.c

// physics.c
void resolve_collision_with_board(MOV *particle, BOARD *board);
void resolve_collision(MOV *particle1, MOV *particle2);
void integrate(MOV *particle);

void check_if_in_hole(MOV *particle, BOARD *board);
void resolve_collision_with_hole(MOV *particle, BOARD *board);
void resolve_penetration_with_side(VECTOR *s0, VECTOR *s1, MOV *particle);

VECTOR perpendicular(VECTOR *s0, VECTOR *s1);
// END physics.c

// img.c
int init_img();
SDL_Texture *load_img(char *path);
// END img.c

// text.c
extern TTF_Font *mono_oblique_font14, *mono_oblique_font18, *mono_font22;
int init_text();
GAME_TEXTURE text(char *str, TTF_Font *font, SDL_Color color);
void render_text(GAME_TEXTURE *game_texture, double x, double y);
// END text.c

// sound.c
void init_sound();
void play();
void play_collision_sound(double speed);
// END sound.c

// striker.c
void move_to_with_player(STRIKER *striker, int sq);
void update_striker(STRIKER *striker);
void render_striker(STRIKER *striker);
void init_striker(STRIKER *striker);
void reset_striker(STRIKER *striker);
// END striker.c

// board.c
void init_board(BOARD *board);
void render_board(BOARD *board);
// END board.c

// speed.c
void init_speed_text();
void render_speed(STRIKER *striker);
// END speed.c

//orientation.c
void init_orientation(STRIKER *striker);
void render_orientation(STRIKER *striker);
// END orientation.c

//chips.c
void reset_chips();
void init_chips();
void render_chips();
// END chips.c

//instructions.c
void init_instructions();
void render_main_instruction();
void render_instructions();
// END instructions.c

//main_menu.c
void init_main_menu();
void update_main_menu();
void render_main_menu();
//END main_menu.c

// game_states.c
void move_to_main_menu();
void move_to_play();
void move_to_instruction_state();
void move_to_state(int state);
// END game_states.c

// scores.c
void init_scores();
void render_scores();
// END scores.c

// game_over.c
void init_game_over_state();
void move_to_game_over_state();
void render_game_over_state();
// END game_over.c