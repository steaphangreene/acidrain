// *************************************************************************
// scene.h
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

#ifndef SCENE_H
#define SCENE_H

#define SCENE_TYPE_MATRIX	1
#define SCENE_TYPE_REAL		2
#define SCENE_TYPE_ASTRAL	3

#define MATRIX_PORT	1
#define MATRIX_DATABIN	2
#define MATRIX_DATAFILE	3
#define MATRIX_CONTROL	4
#define MATRIX_FAKE	5

typedef struct _matrix_obj {
  int type;
  int xp, yp;
  int stat, stat2;
  struct _matrix_obj *next;
  } matrix_obj;

typedef struct _matrix_scene {
  int type;
  matrix_obj *objs;
  } matrix_scene;

typedef struct _real_scene {
  int type;
  } real_scene;

typedef struct _astral_scene {
  int type;
  } astral_scene;

typedef union _scene {
  int type;
  matrix_scene matrix;
  real_scene real;
  astral_scene astral;
  } scene;

#endif /* SCENE_H */
