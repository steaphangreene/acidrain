// *************************************************************************
// renderer_matrix.c
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

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "renderer.h"

#define RADIUS ((GLdouble)0.1)

#define ICON_SPHERE	1
#define ICON_CUBE	2
#define ICON_BURST	3
#define ICON_PYRAMID	4

static int icon[] = {0, ICON_SPHERE, ICON_CUBE, ICON_BURST, ICON_PYRAMID };

static double xoff=0.0, yoff=0.0, xtarg=0.0, ytarg=0.0;
static int move = -1;

const double moves[] = {
	1.0/100.0,
	3.0/99.0,
	6.0/96.0,
	15.0/90.0,
	25.0/75.0,
	25.0/50.0,
	15.0/25.0,
	6.0/10.0,
	3.0/4.0,
	1.0/1.0
	};

void renderer_make_sphere(void) {
  GLUquadricObj *quadObj;

  quadObj = gluNewQuadric();

  glNewList(ICON_SPHERE, GL_COMPILE);

  glColor3f(0.0, 0.0, 1.0);
  gluSphere(quadObj, RADIUS, 32, 12);
	
  glEndList();
  }


void renderer_make_cube(void) {
  glNewList(ICON_CUBE, GL_COMPILE);

  glColor3f(0.0, 1.0, 0.0);
	
  glBegin(GL_QUADS);

  glNormal3d(0.0, -1.0, 0.0);
  glVertex3d(RADIUS, -RADIUS, -RADIUS);
  glVertex3d(RADIUS, -RADIUS, RADIUS);
  glVertex3d(-RADIUS, -RADIUS, RADIUS);
  glVertex3d(-RADIUS, -RADIUS, -RADIUS);

  glNormal3d(-1.0, 0.0, 0.0);
  glVertex3d(-RADIUS, -RADIUS, -RADIUS);
  glVertex3d(-RADIUS, -RADIUS, RADIUS);
  glVertex3d(-RADIUS, RADIUS, RADIUS);
  glVertex3d(-RADIUS, RADIUS, -RADIUS);

  glNormal3d(0.0, 1.0, 0.0);
  glVertex3d(-RADIUS, RADIUS, -RADIUS);
  glVertex3d(-RADIUS, RADIUS, RADIUS);
  glVertex3d(RADIUS, RADIUS, RADIUS);
  glVertex3d(RADIUS, RADIUS, -RADIUS);

  glNormal3d(1.0, 0.0, 0.0);
  glVertex3d(RADIUS, RADIUS, -RADIUS);
  glVertex3d(RADIUS, RADIUS, RADIUS);
  glVertex3d(RADIUS, -RADIUS, RADIUS);
  glVertex3d(RADIUS, -RADIUS, -RADIUS);

  glNormal3d(0.0, 0.0, 1.0);
  glVertex3d(-RADIUS, -RADIUS, RADIUS);
  glVertex3d(RADIUS, -RADIUS, RADIUS);
  glVertex3d(RADIUS, RADIUS, RADIUS);
  glVertex3d(-RADIUS, RADIUS, RADIUS);

  // No Bottom Drawn

  glEnd();

  glEndList();
  }

void renderer_make_burst(void) {
  GLUquadricObj *quadObj;

  quadObj = gluNewQuadric();

  glNewList(ICON_BURST, GL_COMPILE);

  glColor3f(0.8, 0.8, 0.0);
  gluSphere(quadObj, RADIUS, 16, 12);
	
  glEndList();
  }


void renderer_make_pyramid(void) {
  glNewList(ICON_PYRAMID, GL_COMPILE);

  glColor3f(1.0, 0.0, 0.0);

  // Draw the sides of the cube (No Base Needed)
  glBegin(GL_TRIANGLES);

  glNormal3d(-1.0, 0.0, 0.5);
  glVertex3d(0.0, 0.0, RADIUS);
  glVertex3d(-RADIUS, -RADIUS, -RADIUS);
  glVertex3d(-RADIUS, RADIUS, -RADIUS);

  glNormal3d(0.0, 1.0, 0.5);
  glVertex3d(0.0, 0.0, RADIUS);
  glVertex3d(-RADIUS, RADIUS, -RADIUS);
  glVertex3d(RADIUS, RADIUS, -RADIUS);

  glNormal3d(1.0, 0.0, 0.5);
  glVertex3d(0.0, 0.0, RADIUS);
  glVertex3d(RADIUS, RADIUS, -RADIUS);
  glVertex3d(RADIUS, -RADIUS, -RADIUS);

  glNormal3d(0.0, -1.0, 0.5);
  glVertex3d(0.0, 0.0, RADIUS);
  glVertex3d(RADIUS, -RADIUS, -RADIUS);
  glVertex3d(-RADIUS, -RADIUS, -RADIUS);
  glEnd();
  glEndList();
  }

int init_renderer_matrix() {
  // Create the display lists
  renderer_make_sphere();
  renderer_make_cube();
  renderer_make_burst();
  renderer_make_pyramid();

  return 1;
  }

static int phase = 0;

int render_scene_matrix(matrix_scene *current_scene, int player) {
  matrix_obj *tmp = current_scene->objs;

  ++phase;

  if(move >= 0) {
    xoff += (double)(xtarg-xoff)*(double)moves[move];
    yoff += (double)(ytarg-yoff)*(double)moves[move];
    ++move;
    if(move >= 10) move = -1;
    }

  while(tmp != NULL) {
    int tp = tmp->type, fac=1, ang;
    double xpos = 0.5*(tmp->xp-4)-xoff;
    double ypos = 0.5*(tmp->yp-4)-yoff;

    if(tp == MATRIX_FAKE) { tp = tmp->stat; fac=-1; }

    while(xpos < -2.25) xpos += 4.5;
    while(ypos < -2.25) ypos += 4.5;
    while(xpos > 2.25) xpos -= 4.5;
    while(ypos > 2.25) ypos -= 4.5;

    ang = (phase*5%360)*fac;
    glLoadIdentity();
    glTranslatef(xpos, ypos, -6.0);
    glRotatef((double)ang, 0.0, 0.0, 1.0);
    glCallList(icon[tp]);
    tmp = tmp->next;
    }

  glFlush();
  SDL_GL_SwapBuffers();

  return 1;
  }

void clicked_matrix(double x, double y, int b) {
  if(move == -1 && b == 3) {
    x*=8;  x+=9.5;
    y*=8;  y+=9.5;
    if(((int)x & 1) == 1 && ((int)y & 1) == 1) {
      int ix = ((int)x)/2;
      int iy = ((int)y)/2;
      xtarg += 4.5;  xoff += 4.5;
      ytarg += 4.5;  yoff += 4.5;
      xtarg += ((double)ix-4)/2.0;
      ytarg += ((double)iy-4)/2.0;
      while(xtarg > 4.5) { xtarg -= 4.5; xoff -= 4.5; }
      while(ytarg > 4.5) { ytarg -= 4.5; yoff -= 4.5; }
      if(xtarg != xoff || ytarg != yoff) move = 0;
      }
    }
  if(b == 4) {
    ytarg -= 0.5;
    move = 0;
    }
  if(b == 5) {
    ytarg += 0.5;
    move = 0;
    }
  }
