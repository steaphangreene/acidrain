// *************************************************************************
// input.c
// This is a component of Acid Rain, Pre ALPHA non-distribution version
//
// -By Insomnia (Steaphan Greene)   (Copyright 2002 Steaphan Greene)
//                   (stea@core.binghamton.edu)
//      No waranty stated or implied, I am not responsible for any damage
// caused directly or indirectly by this software.
//      Permision granted for use/distribution/modification by anyone,
// provided this header remains intact, and modified versions are marked
// as so immediately below this header.
//      Products utilizing the code or methods within may be distributed
// freely along with this licence, but any sales for profit of such products
// must have the author's permission, and may be subject to a royaltee fee.
// *************************************************************************

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "input.h"
#include "settings.h"
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "digits.h"

int user_quit = 0;

int fucked = 0;

int input_process(scene *current_scene, int player_number) {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case(SDL_KEYDOWN): {
	if (event.key.keysym.sym == SDLK_ESCAPE) {
	  user_quit = 1;
	  }
	else if (event.key.keysym.sym == SDLK_SCROLLOCK) {
	  fucked = !fucked;
	  }
	else if (event.key.keysym.sym == SDLK_PRINT) {
	  toggle_render_fonts();
	  }
	else if (event.key.keysym.sym == SDLK_PAUSE) {
	  toggle_antialiasing();
	  }
	else if (event.key.keysym.sym == SDLK_RETURN
		&& ((event.key.keysym.mod & KMOD_LALT)
		|| (event.key.keysym.mod & KMOD_RALT))) {
	  toggle_fullscreen();
	  }
	else {
	  keypressed(current_scene, event.key.keysym.sym);
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
	clicked(current_scene, x, y, event.button.button);
	} break;
      }
    }

  return 1;
  }
