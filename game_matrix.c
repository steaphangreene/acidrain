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
#include "game.h"

void clicked_matrix(matrix_scene *current_scene, double x, double y, int b) {
  if(current_scene->move == -1 && b == 3) {
    x*=4;  x+=4.5;
    y*=4;  y+=4.5;
    { int ix = ((int)x);
      int iy = ((int)y);
      current_scene->xtarg += 4.5;  current_scene->xoff += 4.5;
      current_scene->ytarg += 4.5;  current_scene->yoff += 4.5;
      current_scene->xtarg += ((double)ix-4)/2.0;
      current_scene->ytarg += ((double)iy-4)/2.0;
      while(current_scene->xtarg > 4.5) {
        current_scene->xtarg -= 4.5;
        current_scene->xoff -= 4.5;
        }
      while(current_scene->ytarg > 4.5) {
        current_scene->ytarg -= 4.5;
        current_scene->yoff -= 4.5;
        }
      if(current_scene->xtarg != current_scene->xoff
                || current_scene->ytarg != current_scene->yoff)
        current_scene->move = 0;
      }
    }
  if(b == 4) {
    current_scene->ytarg -= 0.5;
    current_scene->move = 0;
    }
  if(b == 5) {
    current_scene->ytarg += 0.5;
    current_scene->move = 0;
    }
  }
