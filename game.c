// *************************************************************************
// game.c
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
#include "game.h"

int roll(int ndice, int targ) {
  int ret = 0, ctr;
  for(ctr=0; ctr<ndice; ++ctr) {
    int val = 1+(rand()%6);
    while((val%6) == 0) val += (1+rand()%6);
    if(val > 1 && val >= targ) ++ret;
    }
  return ret;
  }

void panel_clicked(scene *current_scene, double x, double y, int b) {
  if(current_scene == NULL) return;
  else if(current_scene->type == SCENE_TYPE_MATRIX)  
    panel_clicked_matrix(&(current_scene->matrix), x, y, b);
  else if(current_scene->type == SCENE_TYPE_REAL)
    panel_clicked_real(&(current_scene->real), x, y, b);
  else if(current_scene->type == SCENE_TYPE_ASTRAL)
    panel_clicked_astral(&(current_scene->astral), x, y, b);  
  }

void clicked(scene *current_scene, double x, double y, int b) {
  if(current_scene == NULL) return;
  if(x >= 1.0) panel_clicked(current_scene, x, y, b);
  else if(current_scene->type == SCENE_TYPE_MATRIX)  
    clicked_matrix(&(current_scene->matrix), x, y, b);
  else if(current_scene->type == SCENE_TYPE_REAL)
    clicked_real(&(current_scene->real), x, y, b);
  else if(current_scene->type == SCENE_TYPE_ASTRAL)
    clicked_astral(&(current_scene->astral), x, y, b);  
  }

void update_viewport(scene *current_scene) {
  if(current_scene == NULL) return;
  else if(current_scene->type == SCENE_TYPE_MATRIX)  
    update_viewport_matrix(&(current_scene->matrix));
  else if(current_scene->type == SCENE_TYPE_REAL)
    update_viewport_real(&(current_scene->real));
  else if(current_scene->type == SCENE_TYPE_ASTRAL)
    update_viewport_astral(&(current_scene->astral));
  }

void keypressed(scene *current_scene, int k) {
  if(current_scene == NULL) return;
  else if(current_scene->type == SCENE_TYPE_MATRIX)  
    keypressed_matrix(&(current_scene->matrix), k);
  else if(current_scene->type == SCENE_TYPE_REAL)
    keypressed_real(&(current_scene->real), k);
  else if(current_scene->type == SCENE_TYPE_ASTRAL)
    keypressed_astral(&(current_scene->astral), k);
  }

