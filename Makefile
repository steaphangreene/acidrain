CC:=	gcc -O2 -Wall
LIBS:=	`sdl-config --libs` -L/usr/X11R6/lib -lGL -lGLU
TSTR:=	$(shell date +"%Y%m%d%H%M")

all:	acidrain

clean:	.
	rm -f acidrain *.o

tar:	archive
archive:	.
	cd .. ; tar czhvf ~/c/archive/acidrain.$(TSTR).tar.gz \
		acidrain/*.[hc] acidrain/Makefile

acidrain:	main.o renderer.o input.o
	$(CC) -o acidrain main.o renderer.o input.o $(LIBS)

main.o:	main.c renderer.h input.h scene.h
	$(CC) -c main.c

renderer.o:	renderer.c renderer.h scene.h
	$(CC) -c renderer.c

input.o:	input.c input.h
	$(CC) -c input.c

