// *************************************************************************
// game_matrix.c
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

#include "scene.h"
#include "scene_matrix.h"
#include "game.h"
#include "renderer.h"

extern viewport cview;

void clicked_matrix(matrix_scene *cscene, double x, double y, int b) {
  if(cview.movet == MOVE_NONE && b == 1) {
    int xp = MATRIX_CONVXD(cview.xoff + (x*2.0));
    int yp = MATRIX_CONVXD(cview.yoff + (y*2.0));
    matrix_obj *tmp = cscene->objs[xp][yp];

    if(tmp != NULL) {
      int xo = MATRIX_CONVXD((x*2.0));
      int yo = MATRIX_CONVXD((y*2.0));
      cview.xtarg += 4.5;  cview.xoff += 4.5;
      cview.ytarg += 4.5;  cview.yoff += 4.5;
      cview.xtarg += ((double)xo-4)/2.0;
      cview.ytarg += ((double)yo-4)/2.0;
      while(cview.xtarg >= 4.5) {
	cview.xtarg -= 4.5;
	cview.xoff -= 4.5;
	}
      while(cview.ytarg >= 4.5) {
	cview.ytarg -= 4.5;
	cview.yoff -= 4.5;
	}
      if(cview.xtarg != cview.xoff || cview.ytarg != cview.yoff) {
	cview.movet = MOVE_TARGET;
	cview.move = 0;
	}	
      else {
	cview.movet = MOVE_TARGET;
	cview.move = 9;
	}
      }
    }
  if(cview.movet == MOVE_NONE && b == 3) {
    x*=4;  x+=4.5;
    y*=4;  y+=4.5;
    { int ix = ((int)x);
      int iy = ((int)y);
      cview.xtarg += 4.5;  cview.xoff += 4.5;
      cview.ytarg += 4.5;  cview.yoff += 4.5;
      cview.xtarg += ((double)ix-4)/2.0;
      cview.ytarg += ((double)iy-4)/2.0;
      while(cview.xtarg >= 4.5) {
	cview.xtarg -= 4.5;
	cview.xoff -= 4.5;
	}
      while(cview.ytarg >= 4.5) {
	cview.ytarg -= 4.5;
	cview.yoff -= 4.5;
	}
      if(cview.xtarg != cview.xoff || cview.ytarg != cview.yoff)
	cview.move = 0;
	cview.movet = MOVE_RECENTER;
      }
    }
  if(b==4 && (cview.movet == MOVE_NONE || cview.movet == MOVE_RECENTER)) {
    cview.ytarg -= 0.5;
    cview.move = 0;
    cview.movet = MOVE_RECENTER;
    }
  if(b==5 && (cview.movet == MOVE_NONE || cview.movet == MOVE_RECENTER)) {
    cview.ytarg += 0.5;
    cview.move = 0;
    cview.movet = MOVE_RECENTER;
    }
  }


void update_viewport_matrix(matrix_scene *cscene) {
  if(cview.movet == MOVE_RECENTER || cview.movet == MOVE_TARGET) {
    cview.xoff += (double)(cview.xtarg-cview.xoff)*moves[cview.move];
    cview.yoff += (double)(cview.ytarg-cview.yoff)*moves[cview.move];
    ++cview.move;
    if(cview.move >= 10) {
      if(cview.movet == MOVE_RECENTER) {
        cview.movet = MOVE_NONE;
        }
      else if(cview.movet == MOVE_TARGET) {
	int xp = MATRIX_CONVXD(cview.xoff);
	int yp = MATRIX_CONVXD(cview.yoff);
	matrix_obj *tmp = cscene->objs[xp][yp];

	if(tmp->type == MATRIX_PORT) {
	  cview.movet = MOVE_PORT1;
	  cview.move = 0;
	  }
	else {
	  cview.movet = MOVE_NONE;
	  cview.move = 0;
	  }
        }
      }
    }

  else if(cview.movet == MOVE_PORT1) {
    cview.spread = spreads[cview.move];
    ++cview.move;
    if(cview.move >= 10) {
      int xp = MATRIX_CONVXD(cview.xoff);
      int yp = MATRIX_CONVXD(cview.yoff);
      matrix_obj *tmp = cscene->objs[xp][yp];

      cview.movet = MOVE_PORT2;
      cview.move = 9;

      cview.xtarg = 0.5*(double)(COORD_DECODEX(tmp->stat2)-4);
      cview.ytarg = 0.5*(double)(COORD_DECODEY(tmp->stat2)-4);
      cview.xoff = 0.5*(double)(COORD_DECODEX(tmp->stat2)-4);
      cview.yoff = 0.5*(double)(COORD_DECODEY(tmp->stat2)-4);
      set_current_scene(tmp->stat);
      }
    }

  else if(cview.movet == MOVE_PORT2) {
    cview.spread = spreads[cview.move];
    --cview.move; 
    if(cview.move < 0) {
      cview.spread = 1.0;
      cview.movet = MOVE_NONE;
      }
    }
  }
