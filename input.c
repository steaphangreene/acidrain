#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "input.h"
#include "renderer.h"

int user_quit = 0;

int input_process(int player_number) {
  SDL_Event event;

  while(SDL_WaitEvent(&event)) {
    switch (event.type) {
      case(SDL_USEREVENT): {
	if(event.user.code == 13) return 1;
	} break;
      case(SDL_KEYDOWN): {
	if (event.key.keysym.sym == SDLK_ESCAPE) {
	  user_quit = 1;
	  }
	else if (event.key.keysym.sym == SDLK_RETURN
		&& ((event.key.keysym.mod & KMOD_LALT)
		|| (event.key.keysym.mod & KMOD_RALT))) {
	  toggle_fullscreen();
	  }
	} break;
      case(SDL_QUIT): {
	user_quit = 1;
	} break;
      case(SDL_VIDEORESIZE): {
	resize_display(event.resize.w, event.resize.h);
	} break;
      case(SDL_MOUSEBUTTONDOWN): {
	double x, y;
	x = (double)event.button.x;  y = (double)event.button.y;
	pixels_to_location(&x, &y);
	clicked(x, y, event.button.button);
	} break;
      }
    }

  return 1;
  }
