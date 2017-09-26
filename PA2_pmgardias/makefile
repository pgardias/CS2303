# makefile -- Przemek Gardias (pmgardias)
#
# This makefile is used as follows to regenerate files for the sinewave program:
#   make game.o   --  Regenerates game.o by compiling
#   make life.o   --  Regenerates life.o by compiling
#   make life     --  Regenerates the executable life file by compiling
#   make              --  Same as "make life"
#

CFLAGS = -g

all: life

life: game.o life.o
	gcc $(CFLAGS) -Wall life.o game.o -o life

game.o: life.h game.c
	gcc $(CFLAGS) -Wall -c game.c
	
life.o: life.h life.c
	gcc $(CFLAGS) -Wall -c life.c

clean:
	rm -f life.o game.o life