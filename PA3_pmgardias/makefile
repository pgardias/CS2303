# makefile -- Przemek Gardias (pmgardias)
#
# This makefile is used as follows to regenerate files for the tree program:
#   make input.o   --  Regenerates input.o by compiling
#	make output.o  --  Regenerates output.o by compiling
#   make tree.o    --  Regenerates tree.o by compiling
#   make tree      --  Regenerates the executable tree file by compiling
#   make           --  Same as "make tree"
#

CFGLAGS = -g -Wall

all: tree

tree: input.o output.o tree.o
	gcc $(CFLAGS) input.o output.o tree.o -o tree
	
input.o: input.c input.h output.h tree.h
	gcc $(CFLAGS) -c input.c
	
output.o: output.c output.h tree.h
	gcc $(CFLAGS) -c output.c
	
tree.o: tree.c tree.h input.h output.h
	gcc $(CFLAGS) -c tree.c
	
clean:
	rm -f input.o output.o tree.o tree