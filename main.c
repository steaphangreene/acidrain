// *************************************************************************
// main.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <SDL/SDL.h>

#include "settings.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"

int main(int argc, char **argv) {
  int ixs=832, iys=624;
  int player_number = 1;
  scene *current_scene = NULL;

  srand(time(NULL));

  if(argc == 2 && (!strcmp(argv[1], "--fullscreen"))) {
    fullscreen_mode = 1;
    ixs = 1024;
    iys = 768;
    }

  if(!init_renderer(ixs, iys)) {
    fprintf(stderr, "Renderer failed to initialize!\n");
    exit(1);
    }

  init_scenes();

  while(!user_quit) {
    current_scene = get_current_scene();

    if(!render_scene(current_scene, player_number)) {
      fprintf(stderr, "Render of scene failed!\n");
      exit(1);
      }

    if(!input_process(current_scene, player_number)) {
      fprintf(stderr, "Input processing failed!\n");
      exit(1);
      }

    }

  exit(0);
  return 0;
  }
