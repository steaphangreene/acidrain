TSTR:=	$(shell date +"%Y%m%d%H%M")

CC:=	gcc -O2 -Wall
LIBS:=	`sdl-config --libs` -L/usr/X11R6/lib -lGL -lGLU
OBJS:=	main.o input.o \
	game.o game_matrix.o game_real.o game_astral.o \
	scene.o scene_matrix.o scene_real.o scene_astral.o \
	renderer.o renderer_matrix.o renderer_real.o renderer_astral.o

WCC:=	win32-gcc -O2 -Wall
WLIBS:=	`win32-exec sdl-config --libs` -lopengl32 -lglu32
WOBJS:=	$(shell echo $(OBJS) | sed 's-\.o-.win32_o-g')

basic:	x86

all:	x86 win

x86:	acidrain

win:	acidrain.exe

clean:	.
	rm -f acidrain acidrain.* *.o *.win32_o

upload:	all
	scp acidrain acidrain.exe warp:public_html/acidrain/

backup:	tar
	scp ~/c/archive/acidrain.$(TSTR).tar.gz stea@reactor:backup/
	scp ~/c/archive/acidrain.$(TSTR).tar.gz stea@megatron:backup/
	scp ~/c/archive/acidrain.$(TSTR).tar.gz stea@opal:backup/

tar:	archive
archive:	.
	cd .. ; tar czhvf ~/c/archive/acidrain.$(TSTR).tar.gz \
		acidrain/*.[hc] acidrain/Makefile

acidrain:	$(OBJS)
	$(CC) -s -o acidrain $(OBJS) $(LIBS)

acidrain.exe:	$(WOBJS)
	$(WCC) -s -o acidrain.exe $(WOBJS) $(WLIBS)

%.o:	%.c
	$(CC) -c $<

%.win32_o:	%.c %.o
	$(WCC) -c $< -o $@

#AUTO-GENERATED DEPS BELOW (gcc -MM *.c to regen)
game.o: game.c scene.h game.h
game_astral.o: game_astral.c game.h scene.h
game_matrix.o: game_matrix.c scene.h scene_matrix.h game.h renderer.h
game_real.o: game_real.c game.h scene.h
input.o: input.c input.h scene.h renderer.h game.h
main.o: main.c renderer.h scene.h input.h
renderer.o: renderer.c renderer.h scene.h game.h
renderer_astral.o: renderer_astral.c renderer.h scene.h
renderer_matrix.o: renderer_matrix.c xpms/digit0.xpm xpms/digit1.xpm \
 xpms/digit2.xpm xpms/digit3.xpm xpms/digit4.xpm xpms/digit5.xpm \
 xpms/digit6.xpm xpms/digit7.xpm xpms/digit8.xpm xpms/digit9.xpm \
 renderer.h scene.h game.h scene_matrix.h
renderer_real.o: renderer_real.c renderer.h scene.h
scene.o: scene.c scene.h
scene_astral.o: scene_astral.c scene.h
scene_matrix.o: scene_matrix.c scene.h scene_matrix.h
scene_real.o: scene_real.c scene.h

