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
#include <string.h>

#include "scene.h"
#include "scene_matrix.h"

extern scene *scene_list[];
extern SceneID csnum;

const char * ltg_nm[LTG_DIGITS+1] = {
	"0", "1", "2", "3", "4", "5", "6",
	"7", "8", "9",      "A", "B", "C",
	"D", "E",                "F", "G",
	"H",                          "I",
	"J", "K",                "L", "M",
	"N", "O", "P",      "Q", "R", "S",
	"T", "U", "V", "W", "X", "Y", "Z",
	"`Back"
	};

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
  p1->name = NULL;
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
  p2->name = NULL;
  scene_list[id2]->matrix.objs[x2][y2] = p2;
  }

scene *generate_scene_matrix(SceneID id) {
  int xp, yp;
  matrix_obj *tmp;
  static char name_buf[64];

  if(scene_list[id] == NULL) {
    scene_list[id] = (scene*)malloc(sizeof(scene));
    (*scene_list[id]) = new_matrix_scene;
    }

  if(scene_list[id]->any.init == INIT_KNOWN) return scene_list[id];

  if(scene_list[id]->matrix.node == NODE_UNKNOWN) {
    int rnd = rand()%3;
    if(rnd == 0) scene_list[id]->matrix.node = NODE_BANK;
    else if(rnd == 1) scene_list[id]->matrix.node = NODE_LIBRARY;
    else scene_list[id]->matrix.node = NODE_RANDOM;
    }

  if(scene_list[id]->matrix.node == NODE_RANDOM) {
    if(scene_list[id]->matrix.zone == ZONE_UNKNOWN) {
      scene_list[id]->matrix.zone = ZONE_PRIVATE;
      scene_list[id]->matrix.name = ":Private Node";
      }
    else {
      scene_list[id]->matrix.name = ":Welcome Node";
      }
    for(xp=0; xp<MATRIX_X; ++xp) {
      for(yp=0; yp<MATRIX_Y; ++yp) {
	int rn;

	if(scene_list[id]->matrix.objs[xp][yp] != NULL) continue;

	rn = rand()%19;
	if(rn > 4) continue;

	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->name = NULL;
	tmp->type = rn+1;
	if(tmp->type == MATRIX_PORT) {
	  int next = new_scene();
	  link_nodes(id, xp, yp, 0, next, 1+rand()%7, 1+rand()%7, 0);
	  scene_list[next]->matrix.node = NODE_RANDOM;
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
	  tmp->stat2 = rand()%5+4;
	  scene_list[id]->matrix.objs[xp][yp] = tmp;
	  }
	}
      }
    }
  else if(scene_list[id]->matrix.node == NODE_LTG9) {
    int ctr, next;

    scene_list[id]->matrix.funcs |= FUNC_DIAL;
    scene_list[id]->matrix.zone = ZONE_PUBLIC;

    for(ctr=0; ctr<(LTG_DIGITS+1); ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();
	if(ltg_tp[ctr]) {
	  int rnd = rand()%LTG_DIGITS;
	  link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 0,
	             next, ltg_xp[rnd], ltg_yp[rnd], 4);
	  scene_list[next]->matrix.node = NODE_LTG8;
	  scene_list[next]->matrix.objs[ltg_xp[rnd]][ltg_yp[rnd]]->name
		= (char *)ltg_nm[rnd];
	  scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]]->name
		= (char *)ltg_nm[ctr];
	  }
	else {
	  link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 4, next, 4, 4, 0);
	  scene_list[next]->matrix.zone = ZONE_WELCOME;
	  scene_list[next]->matrix.funcs = FUNC_DIAL;
	  scene_list[next]->matrix.objs[4][4]->name
		= (char *)ltg_nm[LTG_DIGITS];
	  scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]]->name
		= (char *)ltg_nm[ctr];
	  }
	}
      }
    sprintf(name_buf, "LTG: %9d-", 607729016);
    scene_list[id]->matrix.name = (char *)malloc(strlen(name_buf)+1);
    strcpy(scene_list[id]->matrix.name, name_buf);
    }
  else if(scene_list[id]->matrix.node > NODE_LTG0
  		&& scene_list[id]->matrix.node < NODE_LTG9) {
    int ctr, next;

    scene_list[id]->matrix.zone = ZONE_PUBLIC;
    scene_list[id]->matrix.funcs |= FUNC_DIAL;

    for(ctr=0; ctr<(LTG_DIGITS+1); ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();
	if(ltg_tp[ctr]) {
	  int rnd = rand()%LTG_DIGITS;
	  link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 0,
	             next, ltg_xp[rnd], ltg_yp[rnd], 4);
	  scene_list[next]->matrix.node = scene_list[id]->matrix.node-1;
	  scene_list[next]->matrix.objs[ltg_xp[rnd]][ltg_yp[rnd]]->name
		= (char *)ltg_nm[rnd];
	  scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]]->name
		= (char *)ltg_nm[ctr];
	  }
	else {
	  link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 4, next, 4, 4, 0);
	  scene_list[next]->matrix.node = scene_list[id]->matrix.node+1;
	  scene_list[next]->matrix.objs[4][4]->name
		= (char *)ltg_nm[LTG_DIGITS];
	  scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]]->name
		= (char *)ltg_nm[ctr];
	  }
	}
      }
    }
  else if(scene_list[id]->matrix.node == NODE_LTG0) {
    int ctr, next;

    scene_list[id]->matrix.zone = ZONE_PUBLIC;
    scene_list[id]->matrix.funcs |= FUNC_DIAL;

    for(ctr=0; ctr<LTG_DIGITS; ++ctr) {
      if(scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]] == NULL) {
	next = new_scene();
	link_nodes(id, ltg_xp[ctr], ltg_yp[ctr], 4, next, 4, 4, 0);
	scene_list[next]->matrix.node = NODE_LTG1;
	  scene_list[next]->matrix.objs[4][4]->name
		= (char *)ltg_nm[LTG_DIGITS];
	scene_list[id]->matrix.objs[ltg_xp[ctr]][ltg_yp[ctr]]->name
		= (char *)ltg_nm[ctr];
	}
      }
    }

  else if(scene_list[id]->matrix.node == NODE_BANK) {
    int next, ctr;
    int vault = rand()%5;
    int dec1 = rand()%4;
    int dec2 = rand()%3;
    int dec3 = rand()%2;
    if(dec1 >= vault) ++dec1;
    if(dec2 >= vault) ++dec2;
    if(dec2 >= dec1) ++dec2;
    if(dec3 >= vault) ++dec3;
    if(dec3 >= dec1) ++dec3;
    if(dec3 >= dec2) ++dec3;

    tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
    tmp->type = MATRIX_DATAFILE;
    tmp->stat = 0;
    tmp->stat2 = 0;
    tmp->conceal = 0;
    tmp->name = NULL;
    scene_list[id]->matrix.objs[5][4] = tmp;
    scene_list[id]->matrix.zone = ZONE_WELCOME;

    for(ctr=0; ctr<5; ++ctr) {
      next = new_scene();
      link_nodes(id, 2+ctr, 2, 4, next, 4, 4, 0);

      scene_list[next]->matrix.node = NODE_BANK;
      if(ctr == dec1) scene_list[id]->matrix.objs[2+ctr][2]->conceal = 4;
      else if(ctr == dec2) scene_list[id]->matrix.objs[2+ctr][2]->conceal = 10;
      else scene_list[id]->matrix.objs[2+ctr][2]->conceal = 12;

      if(ctr == vault) {
	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = MATRIX_DATAFILE;
	tmp->stat = 0;
	tmp->stat2 = 0;
	tmp->conceal = 12;
	tmp->name = NULL;
	scene_list[next]->matrix.objs[4][2] = tmp;
	scene_list[next]->matrix.zone = ZONE_PROTECTED;
	}
      else if(ctr == dec3) {
	tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
	tmp->type = MATRIX_FAKE;
	tmp->stat = MATRIX_DATAFILE;
	tmp->stat2 = 12;
	tmp->conceal = 8;
	tmp->name = NULL;
	scene_list[next]->matrix.objs[4][2] = tmp;
	scene_list[next]->matrix.zone = ZONE_PROTECTED;
	}
      else {
	scene_list[next]->matrix.zone = ZONE_SECURE;
	}
      scene_list[next]->matrix.init = INIT_KNOWN;
      }
    }

  else if(scene_list[id]->matrix.node == NODE_LIBRARY) {
    }

  scene_list[id]->any.init = INIT_KNOWN;

  return scene_list[id];
  }

void init_scenes_matrix(void) {
  int rnd;
  matrix_obj *tmp;

  rnd = rand()%LTG_DIGITS;

  scene_list[0] = (scene*)malloc(sizeof(scene));
  (*scene_list[0]) = new_matrix_scene;
  scene_list[0]->matrix.zone = ZONE_OWNED;
  scene_list[0]->matrix.funcs = FUNC_DIAL;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  tmp->conceal = 0;
  tmp->name = NULL;
  scene_list[0]->matrix.objs[3][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  tmp->conceal = 0;
  tmp->name = NULL;
  scene_list[0]->matrix.objs[4][6] = tmp;

  tmp = (matrix_obj*)malloc(sizeof(matrix_obj));
  tmp->type = MATRIX_DATAFILE;
  tmp->stat = 1;
  tmp->conceal = 0;
  tmp->name = NULL;
  scene_list[0]->matrix.objs[5][6] = tmp;

  scene_list[0]->any.init = INIT_KNOWN;

  link_nodes(0, 4, 4, 0, 1, ltg_xp[rnd], ltg_yp[rnd], 0);
  scene_list[0]->matrix.objs[4][4]->name = (char *)ltg_nm[LTG_DIGITS];
  scene_list[1]->matrix.objs[ltg_xp[rnd]][ltg_yp[rnd]]->name
	= (char *)ltg_nm[rnd];
  scene_list[1]->matrix.node = NODE_LTG9;
  }
