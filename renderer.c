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
#include "game.h"

static SDL_Surface *surface = NULL;
static int videoFlags = 0;

static int xsize=0, ysize=0;
static int hgap=0, vgap=0;

static scene *current_scene;

viewport cview = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};

int phase = 0;

//static unsigned int tex_panel = 0;

void load_textures(void) {
//  glGenTextures(1, &tex_panel);
//  glBindTexture(GL_TEXTURE_2D, tex_panel);
//  gluBuild2DMipmaps(GL_TEXTURE_2D, 3,
//	panel_matrix_grap.width, panel_matrix_grap.height,
//	GL_RGB, GL_UNSIGNED_BYTE, panel_matrix_grap.pixel_data);
//  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  }

void render_panel(scene *cscene, int player) {
  current_scene = cscene;
//  glBindTexture(GL_TEXTURE_2D, tex_panel);
  glLoadIdentity();
  glColor3d(1.0, 1.0, 1.0);
  glNormal3d(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
//  glTexCoord2f(0.0f, 0.0f);
  glVertex3d(1.5, -1.5, -4.5);
//  glTexCoord2f(1.0f, 0.0f);
  glVertex3d(2.5, -1.5, -4.5);
//  glTexCoord2f(1.0f, 1.0f);
  glVertex3d(2.5, 1.5, -4.5);
//  glTexCoord2f(0.0f, 1.0f);
  glVertex3d(1.5, 1.5, -4.5);
  glEnd();
  }

int init_renderer(int xs, int ys) {
  const SDL_VideoInfo *videoInfo;
  GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat shininess[] = { 100.0 };
  GLfloat light_pos[] = { 10.0, -10.0, 4.0, 0.0 };

  xsize = xs;   ysize = ys;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    return 0;
    }
  atexit(SDL_Quit);

  videoInfo = SDL_GetVideoInfo();

  videoFlags = SDL_OPENGL;
  videoFlags |= SDL_GL_DOUBLEBUFFER;
  videoFlags |= SDL_HWPALETTE;
  videoFlags |= SDL_RESIZABLE;
//  videoFlags |= SDL_FULLSCREEN;

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
  glEnable(GL_TEXTURE_2D);

//  glCullFace (GL_BACK);
//  glEnable (GL_CULL_FACE);
//  glEnable (GL_POLYGON_SMOOTH);

//  glEnable(GL_LINE_SMOOTH);
//  glEnable(GL_BLEND);
//  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

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

  if(!init_renderer_matrix()) {
    fprintf(stderr, "Matrix Renderer Init Failed!\n");
    return 0;
    }
  if(!init_renderer_real()) {
    fprintf(stderr, "Real-World Renderer Init Failed!\n");
    return 0;
    }
  if(!init_renderer_astral()) {
    fprintf(stderr, "Astral Renderer Init Failed!\n");
    return 0;
    }

  load_textures();

  return 1;
  }

extern int fucked;

int render_scene(scene *cscene, int player) {
  static Uint32 lasttick = 0;
  Uint32 difftick = SDL_GetTicks()-lasttick;

  ++phase;

  if(lasttick == 0) {
    lasttick = SDL_GetTicks();
    difftick = 30;
    }
  else lasttick += 30;

  update_viewport(cscene);

  if(difftick < 0 || difftick >= 1000000) {
    int d = (int)difftick;
    SDL_Delay(-d);
    }

  if(difftick > 60 && difftick < 1000000) {
    return -1;
    }

  if(fucked) SDL_Delay(100);

  current_scene = cscene;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  render_panel(current_scene, player);

  if(current_scene == NULL) return 1;
  else if(current_scene->type == SCENE_TYPE_MATRIX)
    return render_scene_matrix(&(current_scene->matrix), player);
  else if(current_scene->type == SCENE_TYPE_REAL)
    return render_scene_real(&(current_scene->real), player);
  else if(current_scene->type == SCENE_TYPE_ASTRAL)
    return render_scene_astral(&(current_scene->astral), player);
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
