#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#include "renderer.h"
#include "input.h"
#include "scene.h"

int main(int argc, char **argv) {
  struct timeval tv;
  int player_number = 1, ctr;
  scene current_scene;
  current_scene.matrix.type = SCENE_TYPE_MATRIX;
  current_scene.matrix.objs = NULL;

  gettimeofday(&tv, NULL);
  srandom(tv.tv_usec);

// if(!init_renderer(1024, 768)) {
  if(!init_renderer(800, 600)) {
    fprintf(stderr, "Renderer failed to initialize!\n");
    exit(1);
    }

  for(ctr=0; ctr<81; ++ctr) {
    matrix_obj *tmp;
    int rn = random()%19;
    if(rn > 3) continue;

    tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
    tmp->type = rn+1;
    tmp->xp = ctr%9;	tmp->yp = ctr/9;
    tmp->stat = 0;	tmp->stat2 = 0;
    tmp->next = current_scene.matrix.objs;
    current_scene.matrix.objs = tmp;
    }

  while(!user_quit) {
    if(!render_scene(&current_scene, player_number)) {
      fprintf(stderr, "Renderer failed to render!\n");
      exit(1);
      }
    if(!input_process(player_number)) {
      fprintf(stderr, "Input processing failed!\n");
      exit(1);
      }
//    SDL_Delay(40);
    }

  exit(0);
  return 0;
  }
