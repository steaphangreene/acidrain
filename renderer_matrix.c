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

#define POLYCOUNT	32

#define IMAGE_TILE	1

#define ICON_RADIUS	((GLdouble)0.1)
#define ICON_HEIGHT	((GLdouble)0.3)
#define ICON_DEPTH	((GLdouble)-6.0)

#define ICON_SPHERE	10
#define ICON_CUBE	11
#define ICON_BURST	12
#define ICON_PYRAMID	13

static const int icon[] = {0, ICON_SPHERE, ICON_CUBE, ICON_BURST, ICON_PYRAMID };

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

static matrix_scene *current_scene = NULL;

void renderer_make_tile(void) {
  glNewList(IMAGE_TILE, GL_COMPILE);

  glColor3f(0.0, 0.8, 0.8);
	
  glBegin(GL_QUADS);

  glNormal3d(-1.0,   0.0,   1.0);
  glVertex3d(-0.25, -0.25, -0.02);
  glVertex3d(-0.25,  0.25, -0.02);
  glVertex3d(-0.23,  0.23,  0.00);
  glVertex3d(-0.23, -0.23,  0.00);

  glNormal3d( 0.0,  -1.0,   1.0);
  glVertex3d(-0.25, -0.25, -0.02);
  glVertex3d( 0.25, -0.25, -0.02);
  glVertex3d( 0.23, -0.23,  0.00);
  glVertex3d(-0.23, -0.23,  0.00);

  glNormal3d( 1.0,   0.0,   1.0);
  glVertex3d( 0.25, -0.25, -0.02);
  glVertex3d( 0.25,  0.25, -0.02);
  glVertex3d( 0.23,  0.23,  0.00);
  glVertex3d( 0.23, -0.23,  0.00);

  glNormal3d( 0.0,   1.0,   1.0);
  glVertex3d(-0.25,  0.25, -0.02);
  glVertex3d( 0.25,  0.25, -0.02);
  glVertex3d( 0.23,  0.23,  0.00);
  glVertex3d(-0.23,  0.23,  0.00);

  glNormal3d( 0.0,   0.0,   1.0);
  glVertex3d(-0.23, -0.23,  0.00);
  glVertex3d( 0.23, -0.23,  0.00);
  glVertex3d( 0.23,  0.23,  0.00);
  glVertex3d(-0.23,  0.23,  0.00);

  // No Bottom Drawn

  glEnd();

  glEndList();
  }

void renderer_make_sphere(void) {
  GLUquadricObj *quadObj;
  GLUquadricObj *shadow;

  quadObj = gluNewQuadric();
  shadow = gluNewQuadric();

  glNewList(ICON_SPHERE, GL_COMPILE);

  glColor3f(0.0, 0.0, 1.0);
  gluSphere(quadObj, ICON_RADIUS, POLYCOUNT, POLYCOUNT/2);
	
  glColor3f(0.0, 0.0, 0.0);
  glTranslatef(0.0, 0.0, -ICON_HEIGHT+0.01);
  gluDisk(shadow, 0.0, ICON_RADIUS, 16, 1);

  glEndList();
  }


void renderer_make_cube(void) {
  glNewList(ICON_CUBE, GL_COMPILE);

  glColor3f(0.0, 1.0, 0.0);
	
  glBegin(GL_QUADS);

  glNormal3d(0.0, -1.0, 0.0);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);

  glNormal3d(-1.0, 0.0, 0.0);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);

  glNormal3d(0.0, 1.0, 0.0);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);

  glNormal3d(1.0, 0.0, 0.0);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);

  glNormal3d(0.0, 0.0, 1.0);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);

  // No Bottom Drawn

  // Shadow
  glColor3f(0.0, 0.0, 0.0);
  glNormal3d(0.0, 0.0, 1.0);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, -ICON_HEIGHT+0.01);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, -ICON_HEIGHT+0.01);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, -ICON_HEIGHT+0.01);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, -ICON_HEIGHT+0.01);

  glEnd();

  glEndList();
  }

void renderer_make_burst(void) {
  GLUquadricObj *quadObj, *quadObj2;
  GLUquadricObj *shadow;

  quadObj = gluNewQuadric();
  quadObj2 = gluNewQuadric();
  shadow = gluNewQuadric();

  glNewList(ICON_BURST, GL_COMPILE);

  glColor3f(0.9, 0.9, 0.0);
  glTranslatef(0.0, 0.0, -ICON_RADIUS);
  gluCylinder(quadObj, ICON_RADIUS, 0.0, ICON_RADIUS*2.0, 16, 1);

  glTranslatef(0.0, 0.0, ICON_RADIUS*2.0);
//  gluDisk(quadObj2, 0.0, ICON_RADIUS, POLYCOUNT, 1);

  glColor3f(0.0, 0.0, 0.0);
  glTranslatef(0.0, 0.0, -ICON_RADIUS-ICON_HEIGHT+0.01);
  gluDisk(shadow, 0.0, ICON_RADIUS, POLYCOUNT, 1);

  glEndList();
  }


void renderer_make_pyramid(void) {
  glNewList(ICON_PYRAMID, GL_COMPILE);

  glColor3f(1.0, 0.0, 0.0);

  // Draw the sides of the cube (No Base Needed)
  glBegin(GL_TRIANGLES);

  glNormal3d(-1.0, 0.0, 0.5);
  glVertex3d(0.0, 0.0, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);

  glNormal3d(0.0, 1.0, 0.5);
  glVertex3d(0.0, 0.0, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);

  glNormal3d(1.0, 0.0, 0.5);
  glVertex3d(0.0, 0.0, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);

  glNormal3d(0.0, -1.0, 0.5);
  glVertex3d(0.0, 0.0, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glEnd();

  // Shadow
  glBegin(GL_QUADS);
  glColor3f(0.0, 0.0, 0.0);
  glNormal3d(0.0, 0.0, 1.0);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, -ICON_HEIGHT+0.01);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, -ICON_HEIGHT+0.01);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, -ICON_HEIGHT+0.01);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, -ICON_HEIGHT+0.01);
  glEnd();

  glEndList();
  }

int init_renderer_matrix() {
  // Create the display lists
  renderer_make_tile();

  renderer_make_sphere();
  renderer_make_cube();
  renderer_make_burst();
  renderer_make_pyramid();

  return 1;
  }

extern int phase;

int render_scene_matrix(matrix_scene *cscene, int player) {
  int ctr;
  matrix_obj *tmp = cscene->objs;

  current_scene = cscene;

  if(current_scene->move >= 0) {
    current_scene->xoff +=
	(double)(current_scene->xtarg-current_scene->xoff)*(double)moves[current_scene->move];
    current_scene->yoff +=
	(double)(current_scene->ytarg-current_scene->yoff)*(double)moves[current_scene->move];
    ++current_scene->move;
    if(current_scene->move >= 10) current_scene->move = -1;
    }

  for(ctr=0; ctr<100; ++ctr) {
    double xpos = 0.5*((ctr%10)-4)-(current_scene->xoff);
    double ypos = 0.5*((ctr/10)-4)-(current_scene->yoff);

    while(xpos < -2.5) xpos += 5.0;
    while(ypos < -2.5) ypos += 5.0;
    while(xpos > 2.5) xpos -= 5.0;
    while(ypos > 2.5) ypos -= 5.0;

    glLoadIdentity();
    glTranslatef(xpos, ypos, ICON_DEPTH-ICON_HEIGHT);
    glCallList(IMAGE_TILE);
    }

  while(tmp != NULL) {
    int tp = tmp->type, fac=1, ang;
    double xpos = 0.5*(tmp->xp-4)-(current_scene->xoff);
    double ypos = 0.5*(tmp->yp-4)-(current_scene->yoff);

    if(tp == MATRIX_FAKE) { tp = tmp->stat; fac=-1; }

    while(xpos < -2.25) xpos += 4.5;
    while(ypos < -2.25) ypos += 4.5;
    while(xpos > 2.25) xpos -= 4.5;
    while(ypos > 2.25) ypos -= 4.5;

    ang = (phase*5%360)*fac;
    glLoadIdentity();
    glTranslatef(xpos, ypos, ICON_DEPTH);
    glRotatef((double)ang, 0.0, 0.0, 1.0);
    glCallList(icon[tp]);
    tmp = tmp->next;
    }

  glFlush();
  SDL_GL_SwapBuffers();

  return 1;
  }
