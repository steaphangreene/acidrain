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

#define MAX_SCENES	1024

#define SCENE_TYPE_MATRIX	1
#define SCENE_TYPE_REAL		2
#define SCENE_TYPE_ASTRAL	3

#define MATRIX_PORT	1
#define MATRIX_DATAFILE	2
#define MATRIX_DATABIN	3
#define MATRIX_CONTROL	4
#define MATRIX_FAKE	5

#define MATRIX_X	9
#define MATRIX_Y	9
#define MATRIX_CONVXD(x)	(( (int)((double)(MATRIX_X)*3.5+((x)*2.0)) )%MATRIX_X)
#define MATRIX_CONVYD(y)	(( (int)((double)(MATRIX_Y)*3.5+((y)*2.0)) )%MATRIX_Y)

#define COORD_ENCODE(x, y)	(((y&65535)<<16)|(x&65535))
#define COORD_DECODEX(c)	(c&65535)
#define COORD_DECODEY(c)	((c>>16)&65535)

#define SCENE_UNKNOWN	0
#define SCENE_KNOWN	1
#define NODE_LTG0	100
#define NODE_LTG1	101
#define NODE_LTG2	102
#define NODE_LTG3	103
#define NODE_LTG4	104
#define NODE_LTG5	105
#define NODE_LTG6	106
#define NODE_LTG7	107
#define NODE_LTG8	108
#define NODE_LTG9	109

#define MOVE_NONE	0
#define MOVE_RECENTER	1
#define MOVE_TRAVEL1	2
#define MOVE_TRAVEL2	3

#include <stdio.h> // for NULL

typedef struct _matrix_obj {
  int type;
  int stat, stat2;
  } matrix_obj;

typedef struct _matrix_scene {
  int type;
  int init;
  matrix_obj *objs[MATRIX_X][MATRIX_Y];
  } matrix_scene;

typedef struct _real_scene {
  int type;
  int init;
  } real_scene;

typedef struct _astral_scene {
  int type;
  int init;
  } astral_scene;

typedef struct _any_scene {
  int type;
  int init;
  } any_scene;

typedef union _scene {
  int type;
  any_scene any;
  matrix_scene matrix;
  real_scene real;
  astral_scene astral;
  } scene;

const static scene new_matrix_scene = { matrix: {
	SCENE_TYPE_MATRIX, SCENE_UNKNOWN,
	{{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }},
	} };

const static scene new_astral_scene = { astral: {
	SCENE_TYPE_ASTRAL, 0
	} };

const static scene new_real_scene = { real: {
	SCENE_TYPE_REAL, 0
	} };

typedef unsigned long long SceneID;


void init_scenes(void);
void set_current_scene(SceneID id);
scene *get_current_scene();
scene *get_scene(SceneID id);
int scene_visited(SceneID id);
SceneID new_scene(void);

// Internal use ONLY!
scene *generate_scene(SceneID id);
scene *generate_scene_matrix(SceneID id);
scene *generate_scene_real(SceneID id);
scene *generate_scene_astral(SceneID id);
void init_scenes_matrix(void);
void init_scenes_real(void);
void init_scenes_astral(void);

#endif /* SCENE_H */
