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

const int ltg_xp[] = {2, 3, 4, 5, 6, 2, 3, 4, 5, 6, 4};
const int ltg_yp[] = {6, 6, 6, 6, 6, 2, 2, 2, 2, 2, 4};
const int ltg_tp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

scene *generate_scene_matrix(SceneID id) {
  int xp, yp;
  matrix_obj *tmp;

  if(scene_list[id] == NULL) {
    scene_list[id] = (scene*)malloc(sizeof(scene));
    (*scene_list[id]) = new_matrix_scene;
    }

  if(scene_list[id]->any.init == SCENE_UNKNOWN) {
    if(scene_list[id]->matrix.zone == ZONE_UNKNOWN) {
      scene_list[id]->matrix.zone = ZONE_PRIVATE;
      }
    for(xp=0; xp<MATRIX_X; ++xp) {
      for(yp=0; yp<MATRIX_Y; ++yp) {
	int rn;

	if(scene_list[id]->matrix.objs[xp][yp] != NULL) continue;

	rn = rand()%19;
	if(rn > 4) continue;

	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = rn+1;
	if(tmp->type == MATRIX_PORT) {
	  matrix_obj *other;
	  int nxp, nyp;

	  nxp = 1+rand()%7;  nyp = 1+rand()%7;
	  tmp->stat = new_scene();
	  tmp->stat2 = COORD_ENCODE(nxp, nyp);

	  scene_list[tmp->stat] = (scene*)malloc(sizeof(scene));
	  (*scene_list[tmp->stat]) = new_matrix_scene;
	  scene_list[tmp->stat]->any.init = SCENE_UNKNOWN;

	  other = (matrix_obj*)malloc(sizeof(matrix_obj));
	  other->type = MATRIX_PORT;
	  other->stat = id;
	  other->stat2 = COORD_ENCODE(xp, yp);
	  scene_list[tmp->stat]->matrix.objs[nxp][nyp] = other;

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
    }
  else if(scene_list[id]->any.init == NODE_LTG9) {
    int ctr;
    SceneID next, nxp, nyp;

    scene_list[id]->matrix.zone = ZONE_PUBLIC;

    for(ctr=0; ctr<11; ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();

	scene_list[next] = (scene*)malloc(sizeof(scene));
	(*scene_list[next]) = new_matrix_scene;
	if(ltg_tp[ctr]) {
	  int rnd = rand()%10;
	  nxp = ltg_xp[rnd];  nyp = ltg_yp[rnd];
	  scene_list[next]->any.init = scene_list[id]->any.init-1;
	  }
	else {
	  nxp = 1+rand()%7;  nyp = 1+rand()%7;
	  scene_list[next]->any.init = SCENE_UNKNOWN;
	  scene_list[next]->matrix.zone = ZONE_WELCOME;
	  }

	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = MATRIX_PORT;
	tmp->stat = next;
	tmp->stat2 = COORD_ENCODE(nxp, nyp);
	scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] = tmp;

	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = MATRIX_PORT;
	tmp->stat = id;
	tmp->stat2 = COORD_ENCODE(ltg_xp[ctr], ltg_yp[ctr]);
	scene_list[next]->matrix.objs[nxp][nyp] = tmp;
	}
      }
    }
  else if(scene_list[id]->any.init > NODE_LTG0
  		&& scene_list[id]->any.init < NODE_LTG9) {
    int ctr;
    SceneID next, nxp, nyp;

    scene_list[id]->matrix.zone = ZONE_PUBLIC;

    for(ctr=0; ctr<11; ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();

	scene_list[next] = (scene*)malloc(sizeof(scene));
	(*scene_list[next]) = new_matrix_scene;
	if(ltg_tp[ctr]) {
	  int rnd = rand()%10;
	  nxp = ltg_xp[rnd];  nyp = ltg_yp[rnd];
	  scene_list[next]->any.init = scene_list[id]->any.init-1;
	  }
	else {
	  nxp = 4;  nyp = 4;
	  scene_list[next]->any.init = scene_list[id]->any.init+1;
	  }

	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = MATRIX_PORT;
	tmp->stat = next;
	tmp->stat2 = COORD_ENCODE(nxp, nyp);
	scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] = tmp;

	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = MATRIX_PORT;
	tmp->stat = id;
	tmp->stat2 = COORD_ENCODE(ltg_xp[ctr], ltg_yp[ctr]);
	scene_list[next]->matrix.objs[nxp][nyp] = tmp;
	}
      }
    }
  else if(scene_list[id]->any.init == NODE_LTG0) {
    int ctr;
    SceneID next, nxp, nyp;

    scene_list[id]->matrix.zone = ZONE_PUBLIC;

    for(ctr=0; ctr<10; ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();

	scene_list[next] = (scene*)malloc(sizeof(scene));
	(*scene_list[next]) = new_matrix_scene;
	scene_list[next]->any.init = scene_list[id]->any.init+1;
	nxp = 4;  nyp = 4;

	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = MATRIX_PORT;
	tmp->stat = next;
	tmp->stat2 = COORD_ENCODE(nxp, nyp);
	scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] = tmp;

	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = MATRIX_PORT;
	tmp->stat = id;
	tmp->stat2 = COORD_ENCODE(ltg_xp[ctr], ltg_yp[ctr]);
	scene_list[next]->matrix.objs[nxp][nyp] = tmp;
	}
      }
    }

  scene_list[id]->any.init = SCENE_KNOWN;

  return scene_list[id];
  }

void init_scenes_matrix(void) {
  int rnd;
  matrix_obj *tmp;

  rnd = rand()%10;

  scene_list[0] = (scene*)malloc(sizeof(scene));
  (*scene_list[0]) = new_matrix_scene;
  scene_list[0]->matrix.zone = ZONE_OWNED;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 1;
  tmp->stat2 = COORD_ENCODE(ltg_xp[rnd], ltg_yp[rnd]);
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

  scene_list[0]->any.init = SCENE_KNOWN;


  scene_list[1] = (scene*)malloc(sizeof(scene));
  (*scene_list[1]) = new_matrix_scene;
  scene_list[1]->any.init = NODE_LTG9;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_PORT;
  tmp->stat = 0;
  tmp->stat2 = COORD_ENCODE(4, 4);
  scene_list[1]->matrix.objs[ltg_xp[rnd]][ltg_yp[rnd]] = tmp;
  }
