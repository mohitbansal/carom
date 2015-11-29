#include "globals.h"

Mix_Chunk *collision_sound;
void init_sound()
{
  if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
  {
    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    return;
  }

  collision_sound = Mix_LoadWAV("data/sound/low_collision.wav");
  if(!collision_sound)
  {
    printf("Failed to load collision sound: %s\n", Mix_GetError());
    return;
  }
}

void play_chunk(Mix_Chunk *chunk)
{
  Mix_PlayChannel(-1, chunk, 0);
}

void play_collision_sound(double speed)
{
  int volume = (speed / striker.max_speed) * MIX_MAX_VOLUME;
  Mix_Volume(-1, volume);
  play_chunk(collision_sound);
}


