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
#include <ctype.h>
#include <math.h>

#ifndef M_PI
# define M_PI           3.14159265358979323846  /* pi */
#endif

#include "renderer.h"
#include "game.h"
#include "scene.h"
#include "scene_matrix.h"

/* Digit Font */
#include "digits.h"

#define POLYCOUNT	32

#define IMAGE_TILE	1

#define ICON_RADIUS	((GLdouble)0.1)
#define ICON_HEIGHT	((GLdouble)0.3)
#define ICON_DEPTH	((GLdouble)-6.0)

#define ICON_SPHERE	10
#define ICON_CUBE	11
#define ICON_BURST	12
#define ICON_PYRAMID	13

#define SHAD_ROUND	20
#define SHAD_SQUARE	21

extern viewport cview;

static const int icon[] = {
	0,
	ICON_SPHERE,
	ICON_CUBE,
	ICON_BURST,
	ICON_PYRAMID
	};

static const int shad[] = {
	0,
	SHAD_ROUND,
	SHAD_SQUARE,
	SHAD_ROUND,
	SHAD_SQUARE
	};

void load_textures_matrix(void) {
  }

void renderer_make_tile(void) {
  glNewList(IMAGE_TILE, GL_COMPILE);

  glBegin(GL_QUADS);

  glNormal3d(-1.0,   0.0,   -1.0);
  glVertex3d(-0.25, -0.25, -0.02);
  glVertex3d(-0.25,  0.25, -0.02);
  glVertex3d(-0.23,  0.23,  0.00);
  glVertex3d(-0.23, -0.23,  0.00);

  glNormal3d( 0.0,  -1.0,   -1.0);
  glVertex3d(-0.25, -0.25, -0.02);
  glVertex3d(-0.23, -0.23,  0.00);
  glVertex3d( 0.23, -0.23,  0.00);
  glVertex3d( 0.25, -0.25, -0.02);

  glNormal3d( 1.0,   0.0,   -1.0);
  glVertex3d( 0.25, -0.25, -0.02);
  glVertex3d( 0.23, -0.23,  0.00);
  glVertex3d( 0.23,  0.23,  0.00);
  glVertex3d( 0.25,  0.25, -0.02);

  glNormal3d( 0.0,   1.0,   -1.0);
  glVertex3d(-0.25,  0.25, -0.02);
  glVertex3d( 0.25,  0.25, -0.02);
  glVertex3d( 0.23,  0.23,  0.00);
  glVertex3d(-0.23,  0.23,  0.00);

  glNormal3d( 0.0,   0.0,   -1.0);
  glVertex3d(-0.23, -0.23,  0.00);
  glVertex3d(-0.23,  0.23,  0.00);
  glVertex3d( 0.23,  0.23,  0.00);
  glVertex3d( 0.23, -0.23,  0.00);

  // No Bottom Drawn

  glEnd();

  glEndList();
  }

void renderer_make_square(void) {
  glNewList(SHAD_SQUARE, GL_COMPILE);

  glColor3f(0.0, 0.0, 0.0);

  glBegin(GL_QUADS);
  glNormal3d(0.0, 0.0, 1.0);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, 0.0);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, 0.0);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, 0.0);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, 0.0);
  glEnd();

  glEndList();
  }

void renderer_make_round(void) {
  GLUquadricObj *shadow;
  shadow = gluNewQuadric();

  glNewList(SHAD_ROUND, GL_COMPILE);
  glColor3f(0.0, 0.0, 0.0);
  gluQuadricOrientation(shadow, GLU_INSIDE);
  gluDisk(shadow, 0.0, ICON_RADIUS, 16, 1);
  glEndList();
  }

void renderer_make_sphere(void) {
  GLUquadricObj *quadObj;
  quadObj = gluNewQuadric();

  glNewList(ICON_SPHERE, GL_COMPILE);
  gluSphere(quadObj, ICON_RADIUS, POLYCOUNT, POLYCOUNT/2);
  glEndList();
  }

void renderer_make_cube(void) {
  glNewList(ICON_CUBE, GL_COMPILE);

  glColor3f(0.0, 1.0, 0.0);
	
  glBegin(GL_QUADS);

  glNormal3d(0.0, -1.0, 0.0);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);

  glNormal3d(-1.0, 0.0, 0.0);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);

  glNormal3d(0.0, 1.0, 0.0);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);

  glNormal3d(1.0, 0.0, 0.0);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, -ICON_RADIUS);
  glVertex3d(ICON_RADIUS, -ICON_RADIUS, ICON_RADIUS);
  glVertex3d(ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);

  glNormal3d(0.0, 0.0, -1.0);
  glVertex3d(-ICON_RADIUS,-ICON_RADIUS, ICON_RADIUS);
  glVertex3d(-ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d( ICON_RADIUS, ICON_RADIUS, ICON_RADIUS);
  glVertex3d( ICON_RADIUS,-ICON_RADIUS, ICON_RADIUS);

  // No Bottom Drawn

  glEnd();

  glEndList();
  }

void renderer_make_burst(void) {
  GLUquadricObj *quadObj;

  quadObj = gluNewQuadric();

  glNewList(ICON_BURST, GL_COMPILE);

  glColor3f(0.9, 0.9, 0.0);
  glTranslatef(0.0, 0.0, -ICON_RADIUS);
  gluQuadricOrientation(quadObj, GLU_INSIDE);
  gluCylinder(quadObj, ICON_RADIUS, 0.0, ICON_RADIUS*2.0, 16, 4);

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

  glEndList();
  }

int init_renderer_matrix() {
  // Create the display lists
  renderer_make_tile();

  renderer_make_sphere();
  renderer_make_cube();
  renderer_make_burst();
  renderer_make_pyramid();

  renderer_make_round();
  renderer_make_square();

  load_textures_matrix();

  return 1;
  }

extern int phase;

void draw_dialog(int complete) {
  glLoadIdentity();
  glNormal3d( 0.0,  0.0,  -1.0);

  glBegin(GL_QUADS);
  glColor3f(0.0, 0.0, 0.0);
  glVertex3d( 1.00, -0.15, -4.50);
  glVertex3d(-1.00, -0.15, -4.50);
  glVertex3d(-1.00,  0.15, -4.50);
  glVertex3d( 1.00,  0.15, -4.50);
  glEnd();

  if(complete)
    glColor3f(0.0, 1.0, 0.0);
  else
    glColor3f(1.0, 0.0, 0.0);

  glBegin(GL_QUADS);
  glVertex3d( 1.01, -0.16, -4.51);
  glVertex3d(-1.01, -0.16, -4.51);
  glVertex3d(-1.01,  0.16, -4.51);
  glVertex3d( 1.01,  0.16, -4.51);
  glEnd();
  }

void render_panel_matrix(matrix_scene *cscene, int player) {
//  glBindTexture(GL_TEXTURE_2D, tex_panel);
  glLoadIdentity();
  glColor3d(1.0, 1.0, 1.0);
  glNormal3d(0.0, 0.0, -1.0);
  glBegin(GL_QUADS);
//  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(1.5, -1.5, -4.5);
//  glTexCoord2f(0.0f, 1.0f);
  glVertex3d(1.5, 1.5, -4.5);
//  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(2.5, 1.5, -4.5);
//  glTexCoord2f(1.0f, 0.0f);
  glVertex3d(2.5, -1.5, -4.5);
  glEnd();

  { int ctr;
    double ys, xs, yp = -1.45, xp = 1.55;
    char *mes = "Generic Node";

    if(cscene->name != NULL) mes = cscene->name;
    if(mes[0] == ':') ++mes;

    xs = 0.9 / (double)(strlen(mes));
    ys = xs * 1.5;

    glColor3d(0.0, 1.0, 1.0);

    for(ctr=0; ctr<strlen(mes); ++ctr) {
      glTranslatef(xp, yp, -4.49);
      glScalef(xs, ys, 1.0);
      render_digit(mes[ctr]);
      glLoadIdentity();
      xp += xs;
      }
    }
  }

int render_scene_matrix(matrix_scene *cscene, int player) {
  int ctr, xp, yp;

  if(cscene->zone == ZONE_OWNED) {
    glColor3f(0.7, 0.7, 0.7);
    }
  else if(cscene->zone == ZONE_PUBLIC) {
    glColor3f(0.0, 0.6, 0.0);
    }
  else if(cscene->zone == ZONE_WELCOME) {
    glColor3f(0.0, 0.6, 0.6);
    }
  else if(cscene->zone == ZONE_PRIVATE) {
    glColor3f(0.3, 0.3, 0.3);
    }
  else if(cscene->zone == ZONE_PROTECTED) {
    glColor3f(0.6, 0.3, 0.0);
    }
  else if(cscene->zone == ZONE_SECURE) {
    glColor3f(0.6, 0.0, 0.0);
    }
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
    glCallList(IMAGE_TILE);
    }

  for(xp=0; xp<MATRIX_X; ++xp) {
    for(yp=0; yp<MATRIX_Y; ++yp) {
      if(cscene->objs[xp][yp] != NULL) {
	int tp = cscene->objs[xp][yp]->type;
	double xpos = 0.5*(xp-4)-(cview.xoff);
	double ypos = 0.5*(yp-4)-(cview.yoff);
	int fake = 0;

	if(cscene->objs[xp][yp]->conceal != 0) {
	  if(cscene->objs[xp][yp]->conceal < 0) continue;
	  if(roll(6, cscene->objs[xp][yp]->conceal) < 1) {
	    cscene->objs[xp][yp]->conceal = -(cscene->objs[xp][yp]->conceal);
	    continue;
	    }
	  cscene->objs[xp][yp]->conceal = 0;
	  }
	if(tp == MATRIX_FAKE) {
	  tp = cscene->objs[xp][yp]->stat;
	  if(cscene->objs[xp][yp]->stat2 == 0) {
	    fake = 1;
	    }
	  else if(cscene->objs[xp][yp]->stat2 < 0) {
	    }
	  else if(roll(6, cscene->objs[xp][yp]->stat2) < 1) {
	    cscene->objs[xp][yp]->stat2 = -(cscene->objs[xp][yp]->stat2);
	    }
	  else {
	    fake = 1;
	    cscene->objs[xp][yp]->stat2 = 0;
	    }
	  }

	while(xpos < -2.25) xpos += 4.5;
	while(ypos < -2.25) ypos += 4.5;
	while(xpos > 2.25) xpos -= 4.5;
	while(ypos > 2.25) ypos -= 4.5;

	xpos *= cview.spread;
	ypos *= cview.spread;

	{ int ang = (phase*5%360);
	  GLdouble sc = 0.7 + 0.3*(cos(M_PI * 0.05 * (double)(phase)));

	  glLoadIdentity();
	  glTranslatef(xpos, ypos, (ICON_DEPTH-ICON_HEIGHT)+0.01);
	  glRotatef((double)ang, 0.0, 0.0, 1.0);
	  glPushMatrix();
	  if(fake) glScaled(sc, sc, sc);
	  /* Draw Shadow */
	  glCallList(shad[tp]);

	  glPopMatrix();
	  glTranslatef(0.0, 0.0, ICON_HEIGHT-0.01);
	  if(fake) glScaled(sc, sc, sc);
	  /* Draw Icon */
	  if(cscene->objs[xp][yp]->type == MATRIX_PORT
		&& scene_visited(cscene->objs[xp][yp]->stat))
	    glColor3f(1.0, 0.0, 1.0);
	  else
	    glColor3f(0.0, 0.0, 1.0);
	  glCallList(icon[tp]);
	  }
	}
      }
    }

  if(cview.movet == MOVE_RUN_DIAL) {
    int ctr; 
    long long base = LTG_DIGITS*LTG_DIGITS*LTG_DIGITS*LTG_DIGITS*LTG_DIGITS
                               *LTG_DIGITS*LTG_DIGITS*LTG_DIGITS*LTG_DIGITS;

    for(ctr=10; ctr>cview.move; --ctr) base /= LTG_DIGITS;

    draw_dialog(cview.move == 10);

    for(ctr = 0; ctr < cview.move; ++ctr) {
      double basex = -1.0 + 0.20*(double)ctr;
      int digit = (cview.data/base)%LTG_DIGITS;

      if(digit<10)	digit += '0';
      else		digit += 'A'-10;

      glTranslatef(basex+0.02, -0.1, -4.49);
      glScalef(0.16, 0.2, 1.0);
      render_digit(digit);
      glLoadIdentity();

      base /= LTG_DIGITS;
      }
    }
  else if(cview.data != 0) {
    int ctr; 
    char *mes = "CONNECTING";

    draw_dialog(cscene->node > NODE_LTG9 || cscene->node < NODE_LTG0);

    for(ctr = 0; ctr < strlen(mes); ++ctr) {
      double basex = -1.0 + 0.20*(double)ctr;

      glTranslatef(basex+0.02, -0.1, -4.49);
      glScalef(0.16, 0.2, 1.0);
      render_digit(mes[ctr]);
      glLoadIdentity();
      }
    }

  if(cview.movet == MOVE_RUN_SCAN) {
    GLdouble prog;

    prog = -2.25 + (0.025 * (GLdouble)(cview.move));

    glLoadIdentity();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    if(cview.move < 90) {
      glNormal3d(0.0, -1.0, 0.0);
      glVertex3d(-5.0, prog, -7.0);
      glVertex3d( 5.0, prog, -7.0);
      glVertex3d( 5.0, prog, -5.0);
      glVertex3d(-5.0, prog, -5.0);
      }
    else {
      glNormal3d(0.0, -1.0, 0.0);
      glVertex3d(-5.0, prog, -7.0);
      glVertex3d(-5.0, prog, -5.0);
      glVertex3d( 5.0, prog, -5.0);
      glVertex3d( 5.0, prog, -7.0);
      }
    glEnd();
    }

  glFlush();
  SDL_GL_SwapBuffers();

  return 1;
  }

