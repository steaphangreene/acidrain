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
#include "game.h"
#include "scene.h"
#include "scene_matrix.h"

#define POLYCOUNT	32

#define IMAGE_TILE	1

#define ICON_RADIUS	((GLdouble)0.1)
#define ICON_HEIGHT	((GLdouble)0.3)
#define ICON_DEPTH	((GLdouble)-6.0)

#define ICON_VSPHERE	10
#define ICON_SPHERE	11
#define ICON_CUBE	12
#define ICON_BURST	13
#define ICON_PYRAMID	14

extern viewport cview;

static const int icon[] = {
	0,
	ICON_SPHERE,
	ICON_CUBE,
	ICON_BURST,
	ICON_PYRAMID
	};

void renderer_make_tile(void) {
  glNewList(IMAGE_TILE, GL_COMPILE);

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

void renderer_make_vsphere(void) {
  GLUquadricObj *quadObj;
  GLUquadricObj *shadow;

  quadObj = gluNewQuadric();
  shadow = gluNewQuadric();

  glNewList(ICON_VSPHERE, GL_COMPILE);

  glColor3f(0.8, 0.0, 0.8);
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
  renderer_make_vsphere();
  renderer_make_cube();
  renderer_make_burst();
  renderer_make_pyramid();

  return 1;
  }

extern int phase;

int render_scene_matrix(matrix_scene *cscene, int player) {
  int ctr, xp, yp;

  for(ctr=0; ctr<100; ++ctr) {
    double xpos = 0.5*((ctr%10)-4)-(cview.xoff);
    double ypos = 0.5*((ctr/10)-4)-(cview.yoff);

    while(xpos < -2.5) xpos += 5.0;
    while(ypos < -2.5) ypos += 5.0;
    while(xpos > 2.5) xpos -= 5.0;
    while(ypos > 2.5) ypos -= 5.0;

    xpos *= cview.spread;
    ypos *= cview.spread;

    glLoadIdentity();
    glTranslatef(xpos, ypos, ICON_DEPTH-ICON_HEIGHT);
    if(cscene->zone == ZONE_OWNED) {
      glColor3f(1.0, 1.0, 1.0);
      }
    else if(cscene->zone == ZONE_PUBLIC) {
      glColor3f(0.0, 0.9, 0.0);
      }
    else if(cscene->zone == ZONE_WELCOME) {
      glColor3f(0.0, 0.8, 0.8);
      }
    else if(cscene->zone == ZONE_PRIVATE) {
      glColor3f(0.3, 0.3, 0.3);
      }
    else if(cscene->zone == ZONE_PROTECTED) {
      glColor3f(0.8, 0.4, 0.0);
      }
    else if(cscene->zone == ZONE_SECURE) {
      glColor3f(0.8, 0.0, 0.0);
      }
    glCallList(IMAGE_TILE);
    }

  for(xp=0; xp<MATRIX_X; ++xp) {
    for(yp=0; yp<MATRIX_Y; ++yp) {
      if(cscene->objs[xp][yp] != NULL) {
	int tp = cscene->objs[xp][yp]->type, fac=1, ang;
	double xpos = 0.5*(xp-4)-(cview.xoff);
	double ypos = 0.5*(yp-4)-(cview.yoff);

	if(tp == MATRIX_FAKE) {
	  tp = cscene->objs[xp][yp]->stat; fac=-1;
	  }
	else if(cscene->objs[xp][yp]->conceal != 0) {
	  if(cscene->objs[xp][yp]->conceal < 0) continue;
	  if(roll(6, cscene->objs[xp][yp]->conceal) < 1) {
	    cscene->objs[xp][yp]->conceal = -(cscene->objs[xp][yp]->conceal);
	    continue;
	    }
	  cscene->objs[xp][yp]->conceal = 0;
	  }

	while(xpos < -2.25) xpos += 4.5;
	while(ypos < -2.25) ypos += 4.5;
	while(xpos > 2.25) xpos -= 4.5;
	while(ypos > 2.25) ypos -= 4.5;

	xpos *= cview.spread;
	ypos *= cview.spread;

	ang = (phase*5%360)*fac;
	glLoadIdentity();
	glTranslatef(xpos, ypos, ICON_DEPTH);
	glRotatef((double)ang, 0.0, 0.0, 1.0);
	if(cscene->objs[xp][yp]->type == MATRIX_PORT
		&& scene_visited(cscene->objs[xp][yp]->stat))
	  glCallList(ICON_VSPHERE);
	else
	  glCallList(icon[tp]);
	}
      }
    }

  if(cview.movet >= MOVE_RUN_DIAL00 && cview.movet <= MOVE_RUN_DIAL10) {
    int ctr;

    glLoadIdentity();
    glNormal3d( 0.0,  0.0,  1.0);
    glBegin(GL_QUADS);

    glColor3f(0.0, 0.0, 0.0);
    glVertex3d( 1.01, -0.16, -4.51);
    glVertex3d( 1.01,  0.16, -4.51);
    glVertex3d(-1.01,  0.16, -4.51);
    glVertex3d(-1.01, -0.16, -4.51);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3d( 1.00, -0.15, -4.50);
    glVertex3d( 1.00,  0.15, -4.50);
    glVertex3d(-1.00,  0.15, -4.50);
    glVertex3d(-1.00, -0.15, -4.50);

    if(cview.movet != MOVE_RUN_DIAL10)
      glColor3f(1.0, 0.0, 0.0);
    else
      glColor3f(0.0, 1.0, 0.0);
    for(ctr = 0; ctr < cview.movet-MOVE_RUN_DIAL00; ++ctr) {
      double basex = -1.0 + 0.20*(double)ctr;
      glVertex3d( basex+0.02, -0.1, -4.49);
      glVertex3d( basex+0.02,  0.1, -4.49);
      glVertex3d( basex+0.18,  0.1, -4.49);
      glVertex3d( basex+0.18, -0.1, -4.49);
      }

    glEnd();
    }

  if(cview.movet == MOVE_RUN_SCAN) {
    GLdouble prog;

    prog = -2.25 + (0.025 * (GLdouble)(cview.move));

    glLoadIdentity();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glNormal3d(0.0, -1.0, 0.0);
    glVertex3d(-5.0, prog, -7.0);
    glVertex3d(-5.0, prog, -5.0);
    glVertex3d( 5.0, prog, -5.0);
    glVertex3d( 5.0, prog, -7.0);

    glEnd();
    }

  glFlush();
  SDL_GL_SwapBuffers();

  return 1;
  }

