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
#include <SDL/SDL_opengl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "settings.h"
#include "renderer.h"
#include "game.h"

static SDL_Surface *surface = NULL;
static int videoFlags = 0;

static int xsize=0, ysize=0;
static int hgap=0, vgap=0;

static scene *current_scene;

viewport cview = {0.0, 0.0, 0.0, 0.0, 0, 0, 0, 1.0};

int phase = 0;

void load_textures(void) {
  }

void render_panel(scene *cscene, int player) {
  if(current_scene == NULL) return;
  else if(current_scene->type == SCENE_TYPE_MATRIX)
    render_panel_matrix(&(current_scene->matrix), player);
  else if(current_scene->type == SCENE_TYPE_REAL)
    render_panel_real(&(current_scene->real), player);
  else if(current_scene->type == SCENE_TYPE_ASTRAL)
    render_panel_astral(&(current_scene->astral), player);
  }

int init_renderer(int xs, int ys) {
  const SDL_VideoInfo *videoInfo;
  GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat shininess[] = { 100.0 };
  GLfloat light_pos[] = { 1.0, -1.0, -1.0, 0.0 };

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

  surface = SDL_SetVideoMode(xsize, ysize, 0, videoFlags);

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

  glCullFace (GL_BACK);
  glEnable (GL_CULL_FACE);

//  glEnable (GL_POLYGON_SMOOTH);
//  if(glError());
//  glHint(GL_POLYGON_SMOOTH,GL_FASTEST);

//  glEnable(GL_POINT_SMOOTH);
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
  cscene = get_current_scene();

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

  if(current_scene == NULL) return 1;

  if(antialias_level <= 1) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5, -0.5+((GLdouble)xsize)/((GLdouble)ysize), 0.5, -0.5, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);

    render_panel(current_scene, player);

    if(current_scene->type == SCENE_TYPE_MATRIX) {
      if(!render_scene_matrix(&(current_scene->matrix), player)) return 0;
      }
    else if(current_scene->type == SCENE_TYPE_REAL) {
      if(!render_scene_real(&(current_scene->real), player)) return 0;
      }
    else if(current_scene->type == SCENE_TYPE_ASTRAL) {
      if(!render_scene_astral(&(current_scene->astral), player)) return 0;
      }
    }
  else {
    int ctr;
    double xo, yo;
    glClear(GL_ACCUM_BUFFER_BIT);
    for(ctr = 0; ctr < (antialias_level*antialias_level); ++ctr) {
      xo = (-0.5+(double)(ctr%antialias_level))/(double)(ysize*antialias_level);
      yo = (-0.5+(double)(ctr/antialias_level))/(double)(ysize*antialias_level);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-0.5+xo, -0.5+((GLdouble)xsize)/((GLdouble)ysize)+xo,
		0.5+yo, -0.5+yo, 1.5, 20.0);
      glMatrixMode(GL_MODELVIEW);
      glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

      render_panel(current_scene, player);

      if(current_scene->type == SCENE_TYPE_MATRIX) {
	if(!render_scene_matrix(&(current_scene->matrix), player)) return 0;
	}
      else if(current_scene->type == SCENE_TYPE_REAL) {
	if(!render_scene_real(&(current_scene->real), player)) return 0;
	}
      else if(current_scene->type == SCENE_TYPE_ASTRAL) {
	if(!render_scene_astral(&(current_scene->astral), player)) return 0;
	}
      glAccum(GL_ACCUM, 1.0/(double)(antialias_level*antialias_level));
      glFlush();
      }
    glAccum(GL_RETURN, 1.0);
    }

  glFlush();
  SDL_GL_SwapBuffers();

  return 1;
  }

void resize_display(int xs, int ys) {
  int rx = xs, ry = ys;
  surface = SDL_SetVideoMode(rx, ry, 16, videoFlags);

  xsize = xs;   ysize = ys;

  if(xsize > (ysize*4)/3) xsize = (ysize*4)/3;
  if(ysize > (xsize*3)/4) ysize = (xsize*3)/4;

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

void load_xpm_texture(unsigned int tex, char *xpm[]) {
  int width, height, ncol, x, y;
  unsigned char *tmp;

  sscanf(xpm[0], "%d %d %d", &width, &height, &ncol);
  tmp = (unsigned char *)malloc(width*height*4);
//  memset(tmp, 0, width*height*4);
  for(y=0; y<height; ++y) {
    for(x=0; x<width; ++x) {
      if(xpm[1+ncol+y][x] == xpm[1][0]) {
	tmp[(y*width+x)*4+0] = 0;
	tmp[(y*width+x)*4+1] = 0;
	tmp[(y*width+x)*4+2] = 0;
	tmp[(y*width+x)*4+3] = 0;
	}
      else {
	tmp[(y*width+x)*4+0] = 255;
	tmp[(y*width+x)*4+1] = 255;
	tmp[(y*width+x)*4+2] = 255;
	tmp[(y*width+x)*4+3] = 255;
	}
      }
    }

  glBindTexture(GL_TEXTURE_2D, tex);

/////////
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  // when texture area is small, bilinear filter the closest mipmap
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                 GL_LINEAR_MIPMAP_NEAREST );
  // when texture area is large, bilinear filter the original
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

  // the texture wraps over at the edges (repeat)
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
/////////

  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height,
	GL_RGBA, GL_UNSIGNED_BYTE, tmp);
//  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height,
//	GL_COLOR_INDEX, GL_BITMAP, tmp);
//  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  free(tmp);
  }
