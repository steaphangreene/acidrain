TSTR:=	$(shell date +"%Y%m%d%H%M")

CC:=	gcc -O2 -Wall
LIBS:=	`sdl-config --libs` -L/usr/X11R6/lib -lGL -lGLU
OBJS:=	main.o renderer.o input.o scene.o \
	game.o game_matrix.o game_real.o game_astral.o \
	renderer_matrix.o renderer_real.o renderer_astral.o

WCC:=	cross-gcc.sh -O2 -Wall
WLIBS:=	`cross-exec.sh sdl-config --libs` -lopengl32 -lglu32
WOBJS:=	main.obj renderer.obj input.obj scene.obj \
	game.obj game_matrix.obj game_real.obj game_astral.obj \
	renderer_matrix.obj renderer_real.obj renderer_astral.obj

all:	acidrain

win:	acidrain.exe

clean:	.
	rm -f acidrain acidrain.exe *.o *.obj

tar:	archive
archive:	.
	cd .. ; tar czhvf ~/c/archive/acidrain.$(TSTR).tar.gz \
		acidrain/*.[hc] acidrain/Makefile

acidrain:	$(OBJS)
	$(CC) -s -o acidrain $(OBJS) $(LIBS)

acidrain.exe:	$(WOBJS)
	$(WCC) -s -o acidrain.exe $(WOBJS) $(WLIBS)

main.o:	main.c renderer.h scene.h input.h
	$(CC) -c main.c

main.obj:	main.c renderer.h scene.h input.h
	$(WCC) -c main.c -o main.obj

renderer.o:	renderer.c renderer.h scene.h game.h
	$(CC) -c renderer.c

renderer.obj:	renderer.c renderer.h scene.h game.h
	$(WCC) -c renderer.c -o renderer.obj

renderer_matrix.o:	renderer_matrix.c renderer.h scene.h
	$(CC) -c renderer_matrix.c

renderer_matrix.obj:	renderer_matrix.c renderer.h scene.h
	$(WCC) -c renderer_matrix.c -o renderer_matrix.obj

renderer_real.o:	renderer_real.c renderer.h scene.h
	$(CC) -c renderer_real.c

renderer_real.obj:	renderer_real.c renderer.h scene.h
	$(WCC) -c renderer_real.c -o renderer_real.obj

renderer_astral.o:	renderer_astral.c renderer.h scene.h
	$(CC) -c renderer_astral.c

renderer_astral.obj:	renderer_astral.c renderer.h scene.h
	$(WCC) -c renderer_astral.c -o renderer_astral.obj

input.o:	input.c input.h scene.h renderer.h game.h
	$(CC) -c input.c

input.obj:	input.c input.h scene.h renderer.h game.h
	$(WCC) -c input.c -o input.obj

scene.o:	scene.c scene.h
	$(CC) -c scene.c

scene.obj:	scene.c scene.h
	$(WCC) -c scene.c -o scene.obj

game.o:	game.c scene.h game.h
	$(CC) -c game.c

game.obj:	game.c scene.h game.h
	$(WCC) -c game.c -o game.obj

game_matrix.o:	game_matrix.c scene.h game.h
	$(CC) -c game_matrix.c

game_matrix.obj:	game_matrix.c scene.h game.h
	$(WCC) -c game_matrix.c -o game_matrix.obj

game_real.o:	game_real.c game.h scene.h
	$(CC) -c game_real.c

game_real.obj:	game_real.c game.h scene.h
	$(WCC) -c game_real.c -o game_real.obj

game_astral.o:	game_astral.c game.h scene.h
	$(CC) -c game_astral.c

game_astral.obj:	game_astral.c game.h scene.h
	$(WCC) -c game_astral.c -o game_astral.obj
