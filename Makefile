CC:=	gcc -O2 -Wall
LIBS:=	`sdl-config --libs` -L/usr/X11R6/lib -lGL -lGLU
TSTR:=	$(shell date +"%Y%m%d%H%M")

OBJS:=	main.o renderer.o input.o \
	renderer_matrix.o renderer_real.o renderer_astral.o \
	LivTyler.o

all:	acidrain

clean:	.
	rm -f acidrain *.o

tar:	archive
archive:	.
	cd .. ; tar czhvf ~/c/archive/acidrain.$(TSTR).tar.gz \
		acidrain/*.[hc] acidrain/Makefile

acidrain:	$(OBJS)
	$(CC) -s -o acidrain $(OBJS) $(LIBS)

main.o:	main.c renderer.h input.h scene.h
	$(CC) -c main.c

renderer.o:	renderer.c renderer.h scene.h gimp.h
	$(CC) -c renderer.c

renderer_matrix.o:	renderer_matrix.c renderer.h scene.h
	$(CC) -c renderer_matrix.c

renderer_real.o:	renderer_real.c renderer.h scene.h
	$(CC) -c renderer_real.c

renderer_astral.o:	renderer_astral.c renderer.h scene.h
	$(CC) -c renderer_astral.c

input.o:	input.c input.h renderer.h
	$(CC) -c input.c

LivTyler.o:	LivTyler.c gimp.h
	$(CC) -c LivTyler.c
