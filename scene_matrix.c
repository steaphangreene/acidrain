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
#include "scene_matrix.h"

extern scene *scene_list[];
extern SceneID csnum;

void link_nodes(SceneID id1, int x1, int y1, int c1,
		SceneID id2, int x2, int y2, int c2) {
  matrix_obj *p1, *p2;

  if(scene_list[id1] == NULL) {
    scene_list[id1] = (scene*)malloc(sizeof(scene));
    (*scene_list[id1]) = new_matrix_scene;
    }
  if(scene_list[id1]->matrix.objs[x1][y1] != NULL)
    free(scene_list[id1]->matrix.objs[x1][y1]);
  p1 = (matrix_obj*)malloc(sizeof(matrix_obj));
  p1->type = MATRIX_PORT;
  p1->stat = id2;
  p1->stat2 = COORD_ENCODE(x2, y2);
  p1->conceal = c1;
  scene_list[id1]->matrix.objs[x1][y1] = p1;

  if(scene_list[id2] == NULL) {
    scene_list[id2] = (scene*)malloc(sizeof(scene));
    (*scene_list[id2]) = new_matrix_scene;
    }
  if(scene_list[id2]->matrix.objs[x2][y2] != NULL)
    free(scene_list[id2]->matrix.objs[x2][y2]);
  p2 = (matrix_obj*)malloc(sizeof(matrix_obj));
  p2->type = MATRIX_PORT;
  p2->stat = id1;
  p2->stat2 = COORD_ENCODE(x1, y1);
  p2->conceal = c2;
  scene_list[id2]->matrix.objs[x2][y2] = p2;
  }

scene *generate_scene_matrix(SceneID id) {
  int xp, yp;
  matrix_obj *tmp;

  if(scene_list[id] == NULL) {
    scene_list[id] = (scene*)malloc(sizeof(scene));
    (*scene_list[id]) = new_matrix_scene;
    }

  if(scene_list[id]->any.init == INIT_KNOWN) return scene_list[id];

  if(scene_list[id]->matrix.node == NODE_UNKNOWN) {
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
	  link_nodes(id, xp, yp, 0, new_scene(), 1+rand()%7, 1+rand()%7, 0);
	  }
	else if(tmp->type == MATRIX_DATABIN) {
	  tmp->stat = rand()%4+1;
	  tmp->stat2 = 0;
	  scene_list[id]->matrix.objs[xp][yp] = tmp;
	  }
	else if(tmp->type == MATRIX_DATAFILE) {
	  tmp->stat = rand()%4+1;
	  tmp->stat2 = 0;
	  scene_list[id]->matrix.objs[xp][yp] = tmp;
	  }
	else if(tmp->type == MATRIX_CONTROL) {
	  tmp->stat = rand()%4+1;
	  tmp->stat2 = 0;
	  scene_list[id]->matrix.objs[xp][yp] = tmp;
	  }
	else if(tmp->type == MATRIX_FAKE) {
	  tmp->stat = rand()%4+1;
	  tmp->stat2 = 0;
	  scene_list[id]->matrix.objs[xp][yp] = tmp;
	  }
	}
      }
    }
  else if(scene_list[id]->matrix.node == NODE_LTG9) {
    int ctr, next;

    scene_list[id]->matrix.zone = ZONE_PUBLIC;

    for(ctr=0; ctr<(ltg_digits+1); ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();
	if(ltg_tp[ctr]) {
	  int rnd = rand()%ltg_digits;
	  link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 0,
	             next, ltg_xp[rnd], ltg_yp[rnd], 4);
	  scene_list[next]->matrix.node = NODE_LTG8;
	  }
	else {
	  link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 4,
	             next, 1+rand()%7, 1+rand()%7, 0);
	  scene_list[next]->matrix.zone = ZONE_WELCOME;
	  }
	}
      }
    }
  else if(scene_list[id]->matrix.node > NODE_LTG0
  		&& scene_list[id]->matrix.node < NODE_LTG9) {
    int ctr, next;

    scene_list[id]->matrix.zone = ZONE_PUBLIC;

    for(ctr=0; ctr<(ltg_digits+1); ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();
	if(ltg_tp[ctr]) {
	  int rnd = rand()%ltg_digits;
	  link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 0,
	             next, ltg_xp[rnd], ltg_yp[rnd], 4);
	  scene_list[next]->matrix.node = scene_list[id]->matrix.node-1;
	  }
	else {
	  link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 4, next, 4, 4, 0);
	  scene_list[next]->matrix.node = scene_list[id]->matrix.node+1;
	  }
	}
      }
    }
  else if(scene_list[id]->matrix.node == NODE_LTG0) {
    int ctr, next;

    scene_list[id]->matrix.zone = ZONE_PUBLIC;

    for(ctr=0; ctr<ltg_digits; ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();
	link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 4, next, 4, 4, 0);
	scene_list[next]->matrix.node = NODE_LTG1;
	}
      }
    }

  scene_list[id]->any.init = INIT_KNOWN;

  return scene_list[id];
  }

void init_scenes_matrix(void) {
  int rnd;
  matrix_obj *tmp;

  rnd = rand()%ltg_digits;

  scene_list[0] = (scene*)malloc(sizeof(scene));
  (*scene_list[0]) = new_matrix_scene;
  scene_list[0]->matrix.zone = ZONE_OWNED;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  tmp->conceal = 0;
  scene_list[0]->matrix.objs[3][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  tmp->conceal = 0;
  scene_list[0]->matrix.objs[4][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  tmp->conceal = 0;
  scene_list[0]->matrix.objs[5][6] = tmp;

  scene_list[0]->any.init = INIT_KNOWN;

  link_nodes(0, 4, 4, 0, 1, ltg_xp[rnd], ltg_yp[rnd], 0);
  scene_list[1]->matrix.node = NODE_LTG9;
  }
