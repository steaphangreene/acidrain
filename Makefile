TSTR:=	$(shell date +"%Y%m%d%H%M")

CC:=	gcc `sdl-config --cflags` -O2 -Wall
LIBS:=	`sdl-config --libs` -L/usr/X11R6/lib -lGL -lGLU
OBJS:=	main.o input.o digits.o settings.o \
	game.o game_matrix.o game_real.o game_astral.o \
	scene.o scene_matrix.o scene_real.o scene_astral.o \
	renderer.o renderer_matrix.o renderer_real.o renderer_astral.o

WCC:=	win32-gcc `win32-exec sdl-config --cflags` -O2 -Wall
WLIBS:=	`win32-exec sdl-config --libs` -lopengl32 -lglu32
WOBJS:=	$(shell echo $(OBJS) | sed 's-\.o-.win32_o-g')

basic:	x86

all:	x86 win

x86:	acidrain

win:	acidrain.exe

clean:	.
	rm -f acidrain acidrain.* *.o *.win32_o

upload:	all
	scp acidrain warp:public_html/acidrain/i386/
	scp acidrain.exe warp:public_html/acidrain/win32/

backup:	tar
	scp ~/c/archive/acidrain.$(TSTR).tar.gz stea@reactor:backup/
	scp ~/c/archive/acidrain.$(TSTR).tar.gz stea@megatron:backup/
	scp ~/c/archive/acidrain.$(TSTR).tar.gz stea@opal:backup/

tar:	archive
archive:	.
	cd .. ; tar czhvf ~/c/archive/acidrain.$(TSTR).tar.gz \
		acidrain/*.[hc] acidrain/Makefile \
		acidrain/xpms acidrain/*.raw

acidrain:	$(OBJS)
	$(CC) -s -o acidrain $(OBJS) $(LIBS)

acidrain.exe:	$(WOBJS)
	$(WCC) -s -o acidrain.exe $(WOBJS) $(WLIBS)

%.o:	%.c
	$(CC) -c $<

%.win32_o:	%.c %.o
	$(WCC) -c $< -o $@

#AUTO-GENERATED DEPS BELOW (gcc -MM *.c to regen)
digits.o: digits.c settings.h renderer.h scene.h digits.h digits_xpm.h \
 xpms/digit0.xpm xpms/digit1.xpm xpms/digit2.xpm xpms/digit3.xpm \
 xpms/digit4.xpm xpms/digit5.xpm xpms/digit6.xpm xpms/digit7.xpm \
 xpms/digit8.xpm xpms/digit9.xpm xpms/digitA.xpm xpms/digitB.xpm \
 xpms/digitC.xpm xpms/digitD.xpm xpms/digitE.xpm xpms/digitF.xpm \
 xpms/digitG.xpm xpms/digitH.xpm xpms/digitI.xpm xpms/digitJ.xpm \
 xpms/digitK.xpm xpms/digitL.xpm xpms/digitM.xpm xpms/digitN.xpm \
 xpms/digitO.xpm xpms/digitP.xpm xpms/digitQ.xpm xpms/digitR.xpm \
 xpms/digitS.xpm xpms/digitT.xpm xpms/digitU.xpm xpms/digitV.xpm \
 xpms/digitW.xpm xpms/digitX.xpm xpms/digitY.xpm xpms/digitZ.xpm \
 digits_seg.h
game.o: game.c scene.h game.h
game_astral.o: game_astral.c game.h scene.h
game_matrix.o: game_matrix.c scene.h scene_matrix.h game.h renderer.h
game_real.o: game_real.c game.h scene.h
input.o: input.c input.h scene.h settings.h renderer.h game.h digits.h
main.o: main.c renderer.h scene.h input.h
renderer.o: renderer.c settings.h renderer.h scene.h game.h
renderer_astral.o: renderer_astral.c renderer.h scene.h
renderer_matrix.o: renderer_matrix.c renderer.h scene.h game.h \
 scene_matrix.h digits.h
renderer_real.o: renderer_real.c renderer.h scene.h
scene.o: scene.c scene.h
scene_astral.o: scene_astral.c scene.h
scene_matrix.o: scene_matrix.c scene.h scene_matrix.h
scene_real.o: scene_real.c scene.h
settings.o: settings.c

