// *************************************************************************
// renderer.h
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

#ifndef RENDERER_H
#define RENDERER_H

#include "scene.h"

int init_renderer(int, int);
int render_scene(scene *, int);
void toggle_fullscreen(void);
void resize_display(int, int);
void pixels_to_location(double *, double *);

typedef struct _viewport {
  double xoff, yoff;
  double xtarg, ytarg;
  int movet, move;
  long long data;
  double spread;
  } viewport;

/* For use internally by renderer only! */
int init_renderer_matrix();
int init_renderer_real();
int init_renderer_astral();

int render_scene_matrix(matrix_scene *, int);
int render_scene_real(real_scene *, int);
int render_scene_astral(astral_scene *, int);

#endif /* RENDERER_H */
