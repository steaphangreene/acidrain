// *************************************************************************
// renderer.c
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

static SDL_Surface *surface = NULL;
static int videoFlags = 0;

static int xsize=0, ysize=0;
static int hgap=0, vgap=0;

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

#define SDL_TICK 13;

Uint32 tick(Uint32 t, void *data) {
  SDL_Event event;
  event.user.type = SDL_USEREVENT;
  event.user.code = SDL_TICK;
  SDL_PushEvent(&event);
  return 30;
  }

void __renderer_make_sphere(void) {
  GLUquadricObj *quadObj;

  quadObj = gluNewQuadric();

  glNewList(ICON_SPHERE, GL_COMPILE);

  glColor3f(0.0, 0.0, 1.0);
  gluSphere(quadObj, RADIUS, 32, 12);
	
  glEndList();
  }


void __renderer_make_cube(void) {
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

void __renderer_make_burst(void) {
  GLUquadricObj *quadObj;

  quadObj = gluNewQuadric();

  glNewList(ICON_BURST, GL_COMPILE);

  glColor3f(0.8, 0.8, 0.0);
  gluSphere(quadObj, RADIUS, 16, 12);
	
  glEndList();
  }


void __renderer_make_pyramid(void) {
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

int init_renderer(int xs, int ys) {
  const SDL_VideoInfo *videoInfo;
  GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat shininess[] = { 100.0 };
  GLfloat light_pos[] = { 10.0, -10.0, 4.0, 0.0 };

  xsize = xs;   ysize = ys;

  if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return 0;
    }
  atexit(SDL_Quit);

  videoInfo = SDL_GetVideoInfo();

  videoFlags = SDL_OPENGL;
  videoFlags |= SDL_GL_DOUBLEBUFFER;
  videoFlags |= SDL_HWPALETTE;
  videoFlags |= SDL_RESIZABLE;

  /* Use HW Survaces if possible */
  if(videoInfo->hw_available) videoFlags |= SDL_HWSURFACE;
  else videoFlags |= SDL_SWSURFACE;

  /* Use HW Blits if possible */
  if(videoInfo->blit_hw) videoFlags|=SDL_HWACCEL;

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  surface = SDL_SetVideoMode(xsize, ysize, 16, videoFlags);

  if(surface == NULL) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return 0;
    }

  /* Set a window title. */
  SDL_WM_SetCaption("AcidRain", "AcidRain");

  // Set the clear color to black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // Set the shading model
  glShadeModel(GL_SMOOTH);
//  glShadeModel(GL_FLAT);

  // Set the polygon mode to fill
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // Enable depth testing for hidden line removal
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  // Define material properties of specular color and degree of 
  // shininess.  Since this is only done once in this particular 
  // example, it applies to all objects.  Material properties can 
  // be set for individual objects, individual faces of the objects,
  // individual vertices of the faces, etc... 
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

  // Set the GL_AMBIENT_AND_DIFFUSE color state variable to be the
  // one referred to by all following calls to glColor
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  // Create a Directional Light Source
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Create the display lists
  __renderer_make_sphere();
  __renderer_make_cube();
  __renderer_make_burst();
  __renderer_make_pyramid();

  // Set the new viewport size
  glViewport(0, 0, (GLint)xsize, (GLint)ysize);

  // Choose the projection matrix to be the matrix 
  // manipulated by the following calls
  glMatrixMode(GL_PROJECTION);

  // Set the projection matrix to be the identity matrix
  glLoadIdentity();

  glFrustum(-0.5, -0.5+((GLdouble)xsize)/((GLdouble)ysize), 0.5, -0.5, 1.5, 20.0);

  // Choose the modelview matrix to be the matrix
  // manipulated by further calls
  glMatrixMode(GL_MODELVIEW);

  SDL_AddTimer(30, tick, NULL);

  return 1;
  }

static int phase = 0;

int __real_render_scene(real_scene *current_scene, int player) {
  return 1;
  }

int __astral_render_scene(astral_scene *current_scene, int player) {
  return 1;
  }

int __matrix_render_scene(matrix_scene *current_scene, int player) {
  matrix_obj *tmp = current_scene->objs;

  if(move >= 0) {
    xoff += (double)(xtarg-xoff)*(double)moves[move];
    yoff += (double)(ytarg-yoff)*(double)moves[move];
    ++move;
    if(move >= 10) move = -1;
    }

  while(tmp != NULL) {
    double xpos = 0.5*(tmp->xp-4)-xoff;
    double ypos = 0.5*(tmp->yp-4)-yoff;

    while(xpos < -2.25) xpos += 4.5;
    while(ypos < -2.25) ypos += 4.5;
    while(xpos > 2.25) xpos -= 4.5;
    while(ypos > 2.25) ypos -= 4.5;

    glLoadIdentity();
    glTranslatef(xpos, ypos, -6.0);
    glRotatef((45+phase*5)%360, 0.0, 0.0, 1.0);
    glCallList(icon[tmp->type]);
    tmp = tmp->next;
    }

  glFlush();
  SDL_GL_SwapBuffers();

  return 1;
  }

void __render_panel(scene *current_scene, int player) {
  glLoadIdentity();
  glColor3f(6.0, 6.0, 6.0);
  glNormal3d(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
  glVertex3d(1.5, -1.5, -4.5);
  glVertex3d(2.5, -1.5, -4.5);
  glVertex3d(2.5, 1.5, -4.5);
  glVertex3d(1.5, 1.5, -4.5);
  glEnd();
  }

int render_scene(scene *current_scene, int player) {
  ++phase;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  __render_panel(current_scene, player);

  if(current_scene == NULL) return 1;
  else if(current_scene->type == SCENE_TYPE_MATRIX)
    return __matrix_render_scene(&(current_scene->matrix), player);
  else if(current_scene->type == SCENE_TYPE_REAL)
    return __real_render_scene(&(current_scene->real), player);
  else if(current_scene->type == SCENE_TYPE_ASTRAL)
    return __astral_render_scene(&(current_scene->astral), player);
  return 1;
  }

void resize_display(int xs, int ys) {
  int rx = xs, ry = ys;
  surface = SDL_SetVideoMode(rx, ry, 16, videoFlags);

  xsize = xs;   ysize = ys;

  if(xsize > (ysize*4)/3) xsize = (ysize*4)/3;
  if(ysize > (xsize*3)/4) ysize = (xsize*3)/4;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-0.5, -0.5+((GLdouble)xsize)/((GLdouble)ysize), 0.5, -0.5, 1.5, 20.0);
  glMatrixMode(GL_MODELVIEW);

  hgap = (rx-xsize)/2;  vgap = (ry-ysize)/2;
  glViewport(hgap, vgap, (GLint)xsize, (GLint)ysize);
  }

static int oldmodex = 0, oldmodey = 0;

void toggle_fullscreen(void) {
  if(oldmodex != 0) {
    resize_display(oldmodex, oldmodey);
    oldmodex = 0;  oldmodey = 0;
    }
  else {
    oldmodex = surface->w;
    oldmodey = surface->h;
    if(oldmodex <= 640 && oldmodey <= 480) resize_display(640, 480);
    else if(oldmodex <= 800 && oldmodey <= 600) resize_display(800, 600);
    else if(oldmodex <= 1024 && oldmodey <= 768) resize_display(1024, 768);
    else if(oldmodex <= 1280 && oldmodey <= 1024) resize_display(1280, 1024);
    else if(oldmodex <= 1600 && oldmodey <= 1200) resize_display(1600, 1200);
    }
  SDL_WM_ToggleFullScreen(surface);
  videoFlags ^= SDL_FULLSCREEN;
  }

void pixels_to_location(double *x, double *y) {
  (*x) -= (double)hgap;
  (*y) -= (double)vgap;

  if((*x) < 0.0) (*x)=-10.0, (*y)=-10.0;
  else if((*y) < 0.0) (*x)=-10.0, (*y)=-10.0;
  else if((*x) >= (double)xsize) (*x)=-10.0, (*y)=-10.0;
  else if((*y) >= (double)ysize) (*x)=-10.0, (*y)=-10.0;
  else {
    (*x) /= (double)ysize;  // INTENTIONAL - Divide by YSIZE, not XSIZE!
    (*y) /= (double)ysize;
    (*x) *= 2.0;  (*x) -= 1.0;
    (*y) *= 2.0;  (*y) -= 1.0;
    }
  }

void clicked(double x, double y, int b) {
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
