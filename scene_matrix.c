// *************************************************************************
// scene_matrix.c
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

#include "scene.h"

extern scene *scene_list[];
extern SceneID csnum;

scene *generate_scene_matrix(SceneID id) {
  int xp, yp;

  if(scene_list[id] == NULL) 
    scene_list[id] = (scene*)malloc(sizeof(scene));
  (*scene_list[id]) = new_matrix_scene;

  for(xp=0; xp<MATRIX_X; ++xp) {
    for(yp=0; yp<MATRIX_Y; ++yp) {
      matrix_obj *tmp;
      int rn;

      if(scene_list[id]->matrix.objs[xp][yp] != NULL) continue;

      rn = rand()%19;
      if(rn > 4) continue;

      tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
      tmp->type = rn+1;
      if(tmp->type == MATRIX_PORT) {
	tmp->stat = rand()%MAX_SCENES;
	tmp->stat2 = 0;
	}
      else if(tmp->type == MATRIX_DATABIN) {
	tmp->stat = rand()%4+1;
	tmp->stat2 = 0;
	}
      else if(tmp->type == MATRIX_DATAFILE) {
	tmp->stat = rand()%4+1;
	tmp->stat2 = 0;
	}
      else if(tmp->type == MATRIX_CONTROL) {
	tmp->stat = rand()%4+1;
	tmp->stat2 = 0;
	}
      else if(tmp->type == MATRIX_FAKE) {
	tmp->stat = rand()%4+1;
	tmp->stat2 = 0;
	}
      scene_list[id]->matrix.objs[xp][yp] = tmp;
      }
    }

  scene_list[id]->matrix.init = 1;

  return scene_list[id];
  }

void init_scenes_matrix(void) {
  matrix_obj *tmp;

  scene_list[0] = (scene*)malloc(sizeof(scene));
  (*scene_list[0]) = new_matrix_scene;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 1;
  scene_list[0]->matrix.objs[4][4] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  scene_list[0]->matrix.objs[3][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  scene_list[0]->matrix.objs[4][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  scene_list[0]->matrix.objs[5][6] = tmp;

  scene_list[0]->matrix.init = 1;


  scene_list[1] = (scene*)malloc(sizeof(scene));
  (*scene_list[1]) = new_matrix_scene;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 0;
  scene_list[1]->matrix.objs[4][4] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[3][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[4][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[5][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[6][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[6][5] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[6][4] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[6][3] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[6][2] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[5][2] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[4][2] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[3][2] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[2][2] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[2][3] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[2][4] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[2][5] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 2+(rand()%(MAX_SCENES-2));
  scene_list[1]->matrix.objs[2][6] = tmp;

  scene_list[1]->matrix.init = 1;
  }
