#ifndef RENDERER_H
#define RENDERER_H

#include "scene.h"

int init_renderer(int, int);
int render_scene(scene *, int);
void toggle_fullscreen(void);
void resize_display(int, int);
void pixels_to_location(double *, double *);
void clicked(double, double, int);

#endif /* RENDERER_H */
