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

#include "renderer.h"
#include "input.h"
#include "scene.h"

int main(int argc, char **argv) {
  int player_number = 1, ctr;
  scene current_scene = new_matrix_scene;

  srand(time(NULL));

//  if(!init_renderer(1024, 768)) {
  if(!init_renderer(832, 624)) {
    fprintf(stderr, "Renderer failed to initialize!\n");
    exit(1);
    }

  for(ctr=0; ctr<81; ++ctr) {
    matrix_obj *tmp;
    int rn = rand()%19;
    if(rn > 4) continue;

    tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
    tmp->type = rn+1;
    tmp->xp = ctr%9;	tmp->yp = ctr/9;
    tmp->stat = rand()%4+1;
    tmp->stat2 = 0;
    tmp->next = current_scene.matrix.objs;
    current_scene.matrix.objs = tmp;
    }

  while(!user_quit) {
    if(!render_scene(&current_scene, player_number)) {
      fprintf(stderr, "Render of scene failed!\n");
      exit(1);
      }

    if(!input_process(player_number)) {
      fprintf(stderr, "Input processing failed!\n");
      exit(1);
      }

    }

  exit(0);
  return 0;
  }
