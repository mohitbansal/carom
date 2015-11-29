#include "globals.h"

unsigned int frame_start_time;
double elapsed_time = 0.01;
double accumulator;

unsigned int current_time()
{
  return SDL_GetTicks();
}

void frame_start()
{
  unsigned int c_time = current_time();
  accumulator += (c_time - frame_start_time) / 1000.0; // elapsed time in seconds instead of milliseconds
  frame_start_time = c_time;
}