#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "input.h"

int user_quit = 0;

int input_process(int player_number) {
  SDL_Event event;

  if(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN: {
	if (event.key.keysym.sym == SDLK_ESCAPE) {
	  user_quit = 1;
	  }
	} break;
      case SDL_QUIT: {
	user_quit = 1;
	} break;
      }
    }

  return 1;
  }
