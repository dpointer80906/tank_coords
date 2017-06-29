# Makefile for tank_coords.c

all: tank_coords

tank_coords: tank_coords.c
	gcc -o tank_coords tank_coords.c -lm

clean:
	rm -f tank_coords.o tank_coords *~
