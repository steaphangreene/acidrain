int antialias_level = 0;
int render_fonts = 1;

void toggle_render_fonts(void) {
  render_fonts = !render_fonts;
  }

void toggle_antialiasing(void) {
  if(antialias_level) antialias_level = 0;
  else                antialias_level = 3;
  }
