// *************************************************************************
// scene.c
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

scene *scene_list[MAX_SCENES];
SceneID csnum = 0;

void set_current_scene(SceneID id) {
  csnum = id;
  }

scene *get_current_scene(void) {
  return get_scene(csnum);
  }

scene *generate_scene(SceneID id) {
  if(scene_list[id] != NULL) {
    if(scene_list[id]->type == SCENE_TYPE_MATRIX)
      return generate_scene_matrix(id);
    else if(scene_list[id]->type == SCENE_TYPE_REAL)
      return generate_scene_real(id);
    else if(scene_list[id]->type == SCENE_TYPE_ASTRAL)
      return generate_scene_astral(id);
    }

  if(scene_list[id] == NULL) 
    return generate_scene_matrix(id);

  if(scene_list[csnum]->type == SCENE_TYPE_MATRIX)
    return generate_scene_matrix(id);
  else if(scene_list[csnum]->type == SCENE_TYPE_REAL)
    return generate_scene_real(id);
  else if(scene_list[csnum]->type == SCENE_TYPE_ASTRAL)
    return generate_scene_astral(id);

  
  fprintf(stderr, "Error generating scene of unknown type!\n");
  exit(1);

  return NULL;
  }

scene *get_scene(SceneID id) {
  if(scene_list[id] == NULL || scene_list[id]->any.init != INIT_KNOWN)
    return generate_scene(id);

  return scene_list[id];
  }

void init_scenes(void) {
  int ctr;

  for(ctr=0; ctr<MAX_SCENES; ++ctr) scene_list[ctr] = NULL;

  init_scenes_matrix();
  init_scenes_real();
  init_scenes_astral();
  }

int scene_visited(SceneID id) {
  if(scene_list[id] != NULL && scene_list[id]->any.init == INIT_KNOWN)
    return 1;
  return 0;
  }

SceneID new_scene(void) {
  SceneID ret = 0;
  while(scene_list[ret] != NULL) {
    ++ret;
    if(ret == MAX_SCENES) {
      fprintf(stderr, "Out of scene IDs, AARRGGHH!!\n");
      exit(1);
      }
    }
  return ret;
  }
