typedef struct _gimage {
  unsigned int   width;
  unsigned int   height;
  unsigned int   bytes_per_pixel; /* 3:RGB, 4:RGBA */
  char          *comment;
  unsigned char  pixel_data[200 * 600 * 3 + 1];
} gimage;

extern gimage LivTyler;
