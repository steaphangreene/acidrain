// *************************************************************************
// game.h
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

#ifndef GAME_H
#define GAME_H

#include "scene.h"

void panel_clicked(scene *, double x, double y, int b);
void clicked(scene *, double x, double y, int b);

void clicked_matrix(matrix_scene *, double, double, int);
void clicked_real(real_scene *, double, double, int);
void clicked_astral(astral_scene *, double, double, int);

#endif /* GAME_H */
