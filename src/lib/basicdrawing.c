// Basic drawing utilities
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include "main.h"

char r, g, b;

void fgcolor(char red, char green, char blue) {
	r = red;
	g = green;
	b = blue;
}

void draw_point(int x, int y) {
	if (x>0 && x<WID && y>0 && y<HEI) {
		bytes[(WID*y+x)*3] = r;
		bytes[(WID*y+x)*3+1] = g;
		bytes[(WID*y+x)*3+2] = b;
	}
}
