#include <ctype.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "renderer.h"
#include "digits.h"
#include "digits_xpm.h"
#include "digits_seg.h"

#define LED_SIZE 0.2
#define LED_EDGE 0.05

static int render_fonts = 1;

static unsigned int tex_digit[128];

static int rendered_initialized = 0;
static int nonrendered_initialized = 0;

static GLuint base_digit = 0;

void toggle_render_fonts(void) {
  render_fonts = !render_fonts;
  }

void create_digit_tex(unsigned int *tx, char *xpm[]) {
  glGenTextures(1, tx);
  load_xpm_texture(*tx, xpm);
  }

void init_digits(void) {
  if(!render_fonts) {
    create_digit_tex(tex_digit+'0', digit0_xpm);
    create_digit_tex(tex_digit+'1', digit1_xpm);
    create_digit_tex(tex_digit+'2', digit2_xpm);
    create_digit_tex(tex_digit+'3', digit3_xpm);
    create_digit_tex(tex_digit+'4', digit4_xpm);
    create_digit_tex(tex_digit+'5', digit5_xpm);
    create_digit_tex(tex_digit+'6', digit6_xpm);
    create_digit_tex(tex_digit+'7', digit7_xpm);
    create_digit_tex(tex_digit+'8', digit8_xpm);
    create_digit_tex(tex_digit+'9', digit9_xpm);

    create_digit_tex(tex_digit+'A', digitA_xpm);
    create_digit_tex(tex_digit+'B', digitB_xpm);
    create_digit_tex(tex_digit+'C', digitC_xpm);
    create_digit_tex(tex_digit+'D', digitD_xpm);
    create_digit_tex(tex_digit+'E', digitE_xpm);
    create_digit_tex(tex_digit+'F', digitF_xpm);
    create_digit_tex(tex_digit+'G', digitG_xpm);
    create_digit_tex(tex_digit+'H', digitH_xpm);
    create_digit_tex(tex_digit+'I', digitI_xpm);
    create_digit_tex(tex_digit+'J', digitJ_xpm);
    create_digit_tex(tex_digit+'K', digitK_xpm);
    create_digit_tex(tex_digit+'L', digitL_xpm);
    create_digit_tex(tex_digit+'M', digitM_xpm);
    create_digit_tex(tex_digit+'N', digitN_xpm);
    create_digit_tex(tex_digit+'O', digitO_xpm);
    create_digit_tex(tex_digit+'P', digitP_xpm);
    create_digit_tex(tex_digit+'Q', digitQ_xpm);
    create_digit_tex(tex_digit+'R', digitR_xpm);
    create_digit_tex(tex_digit+'S', digitS_xpm);
    create_digit_tex(tex_digit+'T', digitT_xpm);
    create_digit_tex(tex_digit+'U', digitU_xpm);
    create_digit_tex(tex_digit+'V', digitV_xpm);
    create_digit_tex(tex_digit+'W', digitW_xpm);
    create_digit_tex(tex_digit+'X', digitX_xpm);
    create_digit_tex(tex_digit+'Y', digitY_xpm);
    create_digit_tex(tex_digit+'Z', digitZ_xpm);

    create_digit_tex(tex_digit+'a', digitA_xpm);
    create_digit_tex(tex_digit+'b', digitB_xpm);
    create_digit_tex(tex_digit+'c', digitC_xpm);
    create_digit_tex(tex_digit+'d', digitD_xpm);
    create_digit_tex(tex_digit+'e', digitE_xpm);
    create_digit_tex(tex_digit+'f', digitF_xpm);
    create_digit_tex(tex_digit+'g', digitG_xpm);
    create_digit_tex(tex_digit+'h', digitH_xpm);
    create_digit_tex(tex_digit+'i', digitI_xpm);
    create_digit_tex(tex_digit+'j', digitJ_xpm);
    create_digit_tex(tex_digit+'k', digitK_xpm);
    create_digit_tex(tex_digit+'l', digitL_xpm);
    create_digit_tex(tex_digit+'m', digitM_xpm);
    create_digit_tex(tex_digit+'n', digitN_xpm);
    create_digit_tex(tex_digit+'o', digitO_xpm);
    create_digit_tex(tex_digit+'p', digitP_xpm);
    create_digit_tex(tex_digit+'q', digitQ_xpm);
    create_digit_tex(tex_digit+'r', digitR_xpm);
    create_digit_tex(tex_digit+'s', digitS_xpm);
    create_digit_tex(tex_digit+'t', digitT_xpm);
    create_digit_tex(tex_digit+'u', digitU_xpm);
    create_digit_tex(tex_digit+'v', digitV_xpm);
    create_digit_tex(tex_digit+'w', digitW_xpm);
    create_digit_tex(tex_digit+'x', digitX_xpm);
    create_digit_tex(tex_digit+'y', digitY_xpm);
    create_digit_tex(tex_digit+'z', digitZ_xpm);

    glBindTexture(GL_TEXTURE_2D, 0);

    nonrendered_initialized = 1;
    }
  else {
    int ctr;
    base_digit = glGenLists(128);

    for(ctr=0; ctr<128; ++ctr) {
      glNewList(base_digit+ctr, GL_COMPILE);

      if(digit_segs[ctr] & 0x0001) {
	glBegin(GL_QUADS);
	glVertex3d(LED_EDGE, -1.0, 0.0);
	glVertex3d(LED_SIZE+LED_EDGE, -1.0+LED_SIZE, 0.0);
	glVertex3d(1.0-LED_SIZE-LED_EDGE, -1.0+LED_SIZE, 0.0);
	glVertex3d(1.0, -1.0, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0002) {
	glBegin(GL_QUADS);
	glVertex3d(0.0, -1.0+LED_EDGE, 0.0);
	glVertex3d(0.0, 0.0-LED_EDGE, 0.0);
	glVertex3d(0.0+LED_SIZE, 0.0-LED_SIZE/2.0-LED_EDGE, 0.0);
	glVertex3d(0.0+LED_SIZE, -1.0+LED_SIZE+LED_EDGE, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0004) {
	glBegin(GL_QUADS);
	glVertex3d(1.0-LED_SIZE, -1.0+LED_SIZE+LED_EDGE, 0.0);
	glVertex3d(1.0-LED_SIZE, 0.0-LED_SIZE/2.0-LED_EDGE, 0.0);
	glVertex3d(1.0, 0.0-LED_EDGE, 0.0);
	glVertex3d(1.0, -1.0+LED_EDGE, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0008) {
	glBegin(GL_POLYGON);
	glVertex3d(0.0+LED_EDGE, 0.0, 0.0);
	glVertex3d(0.0+LED_SIZE+LED_EDGE, LED_SIZE/2.0, 0.0);
	glVertex3d(0.5-LED_SIZE/2.0-LED_EDGE, LED_SIZE/2.0, 0.0);
	glVertex3d(0.5-LED_EDGE, 0.0, 0.0);
	glVertex3d(0.5-LED_SIZE/2.0-LED_EDGE, -LED_SIZE/2.0, 0.0);
	glVertex3d(0.0+LED_SIZE+LED_EDGE, -LED_SIZE/2.0, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0010) {
	glBegin(GL_POLYGON);
	glVertex3d(0.5+LED_EDGE, 0.0, 0.0);
	glVertex3d(0.5+LED_SIZE/2.0+LED_EDGE, LED_SIZE/2.0, 0.0);
	glVertex3d(1.0-LED_SIZE-LED_EDGE, LED_SIZE/2.0, 0.0);
	glVertex3d(1.0-LED_EDGE, 0.0, 0.0);
	glVertex3d(1.0-LED_SIZE-LED_EDGE, -LED_SIZE/2.0, 0.0);
	glVertex3d(0.5+LED_SIZE/2.0+LED_EDGE, -LED_SIZE/2.0, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0020) {
	glBegin(GL_QUADS);
	glVertex3d(0.0, 0.0+LED_EDGE, 0.0);
	glVertex3d(0.0, 1.0-LED_EDGE, 0.0);
	glVertex3d(0.0+LED_SIZE, 1.0-LED_SIZE-LED_EDGE, 0.0);
	glVertex3d(0.0+LED_SIZE, 0.0+LED_SIZE/2.0+LED_EDGE, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0040) {
	glBegin(GL_QUADS);
	glVertex3d(1.0-LED_SIZE, 0.0+LED_SIZE/2.0+LED_EDGE, 0.0);
	glVertex3d(1.0-LED_SIZE, 1.0-LED_SIZE-LED_EDGE, 0.0);
	glVertex3d(1.0, 1.0-LED_EDGE, 0.0);
	glVertex3d(1.0, 0.0+LED_EDGE, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0080) {
	glBegin(GL_QUADS);
	glVertex3d(LED_SIZE+LED_EDGE, 1.0-LED_SIZE, 0.0);
	glVertex3d(LED_EDGE, 1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0-LED_SIZE-LED_EDGE, 1.0-LED_SIZE, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0100) {
	glBegin(GL_POLYGON);
	glVertex3d( 0.5-LED_SIZE/2.0, -1.0+LED_SIZE+LED_EDGE, 0.0);
	glVertex3d( 0.5-LED_SIZE/2.0, 0.0-LED_SIZE/2.0-LED_EDGE, 0.0);
	glVertex3d( 0.5, 0.0-LED_EDGE, 0.0);
	glVertex3d( 0.5+LED_SIZE/2.0, 0.0-LED_SIZE/2.0-LED_EDGE, 0.0);
	glVertex3d( 0.5+LED_SIZE/2.0, -1.0+LED_SIZE+LED_EDGE, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0200) {
	glBegin(GL_POLYGON);
	glVertex3d( 0.5-LED_SIZE/2.0, 0.0+LED_SIZE/2.0+LED_EDGE, 0.0);
	glVertex3d( 0.5-LED_SIZE/2.0, 1.0-LED_SIZE-LED_EDGE, 0.0);
	glVertex3d( 0.5+LED_SIZE/2.0, 1.0-LED_SIZE-LED_EDGE, 0.0);
	glVertex3d( 0.5+LED_SIZE/2.0, 0.0+LED_SIZE/2.0+LED_EDGE, 0.0);
	glVertex3d( 0.5, 0.0+LED_EDGE, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0400) {
	glBegin(GL_QUADS);
	glVertex3d( 0.25, 0.25, 0.0);
	glVertex3d( 0.25, 0.30, 0.0);
	glVertex3d( 0.40, 0.40, 0.0);
	glVertex3d( 0.40, 0.35, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x0800) {
	glBegin(GL_QUADS);
	glVertex3d( 0.60, 0.35, 0.0);
	glVertex3d( 0.60, 0.40, 0.0);
	glVertex3d( 0.85, 0.30, 0.0);
	glVertex3d( 0.85, 0.25, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x1000) {
	glBegin(GL_QUADS);
	glVertex3d( 0.25, 0.80, 0.0);
	glVertex3d( 0.25, 0.85, 0.0);
	glVertex3d( 0.40, 0.60, 0.0);
	glVertex3d( 0.40, 0.55, 0.0);
	glEnd();
	}
      if(digit_segs[ctr] & 0x2000) {
	glBegin(GL_QUADS);
	glVertex3d( 0.60, 0.55, 0.0);
	glVertex3d( 0.60, 0.60, 0.0);
	glVertex3d( 0.85, 0.85, 0.0);
	glVertex3d( 0.85, 0.80, 0.0);
	glEnd();
	}

      glEndList();
      }

    rendered_initialized = 1;
    }
  }

void render_digit(int chr) {
  if(!render_fonts) {
    if(!nonrendered_initialized) init_digits();

    if(tex_digit[chr] == 0) return;
    glBindTexture(GL_TEXTURE_2D, tex_digit[chr]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(-0.5,-0.5, 0.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-0.5, 0.5, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d( 0.5, 0.5, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d( 0.5,-0.5, 0.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    }
  else {
    if(!rendered_initialized) init_digits();
    glTranslatef(-0.5, 0.0, 0.0);
    glScalef(1.0, 0.5, 1.0);
    glCallList(base_digit+chr);
    }
  }
