#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "digits.h"
#include "renderer.h"

int antialias_level = 0;
int render_fonts = 0;
int fullscreen_mode = 0;

void toggle_render_fonts(void) {
  render_fonts = !render_fonts;
  }

void toggle_antialiasing(void) {
  if(antialias_level) antialias_level = 0;
  else                antialias_level = 3;
  }

void render_settings_window(void) {
  glColor3d(1.0, 1.0, 1.0);
  glNormal3d(0.0, 0.0, -1.0);
  glBegin(GL_QUADS);
  glVertex3d(-1.0, -1.0, 0.0);
  glVertex3d(-1.0,  1.0, 0.0);
  glVertex3d( 1.0,  1.0, 0.0);
  glVertex3d( 1.0, -1.0, 0.0);
  glEnd();

  glNormal3d(0.0, 0.0, -1.0);
  glTranslated(0.0, 0.0, 0.01);

  if(fullscreen_mode) glColor3d(0.0, 0.0, 1.0);
  else                glColor3d(0.0, 0.0, 0.0);

  glPushMatrix();
  glTranslated(-0.6, -0.95, 0.0);
  glScaled(0.4, 0.1, 0.0);
  render_digits("Fullscreen Mode");
  glPopMatrix();

  if(render_fonts) glColor3d(0.0, 0.0, 1.0);
  else             glColor3d(0.0, 0.0, 0.0);

  glPushMatrix();
  glTranslated(-0.6, -0.85, 0.0);
  glScaled(0.4, 0.1, 0.0);
  render_digits("Rendered Fonts");
  glPopMatrix();

  if(antialias_level) glColor3d(0.0, 0.0, 1.0);
  else                glColor3d(0.0, 0.0, 0.0);

  glPushMatrix();
  glTranslated(-0.6, -0.75, 0.0);
  glScaled(0.4, 0.1, 0.0);
  render_digits("Antialiasing");
  glPopMatrix();

  glColor3d(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslated(-0.6, -0.55, 0.0);
  glScaled(0.4, 0.1, 0.0);
  render_digits(getenv("HOME"));
  glPopMatrix();

  glColor3d(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslated(-0.6, -0.45, 0.0);
  glScaled(0.4, 0.1, 0.0);
  render_digits(getenv("TEMP"));
  glPopMatrix();

  glColor3d(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslated(-0.6, -0.35, 0.0);
  glScaled(0.4, 0.1, 0.0);
  render_digits(getenv("TMP"));
  glPopMatrix();
  }

void clicked_settings(double x, double y, int b) {
  if(x < -0.2 && y < -0.9) {
    toggle_fullscreen();
    }
  else if(x < -0.2 && y < -0.8) {
    toggle_render_fonts();
    }
  else if(x < -0.2 && y < -0.7) {
    toggle_antialiasing();
    }
  }
