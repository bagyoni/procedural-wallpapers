// TANGLES
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>
#include <string.h>

#include "lib/main.h"

char bytes[WID * HEI * 3];

void draw_rect(int maxsize, int r, int g, int b) {
	int w = rand()%maxsize;
	int h = maxsize-w;
	int x0 = rand()%(WID-w);
	int y0 = rand()%(HEI-h);
	
	int x, y;
   	for (x=x0; x<x0+w; x++) {
		for (y=y0; y<y0+h; y++) {
			bytes[(WID*y+x)*3] = r;
			bytes[(WID*y+x)*3+1] = g;
			bytes[(WID*y+x)*3+2] = b;
		}
	}
}

void draw() {
	memset(bytes, 230, WID*HEI*3);
	int r = 128+(rand()%128);
	int g = 128+(rand()%128);
	int b = 128+(rand()%128);
	int m = 240 + (rand()%16);
	int rnd = rand()%3;
	switch(rnd) {
		case 0:
			r = m;
			break;
		case 1:
			g = m;
			break;
		case 2:
			b = m;
			break;
	}
	int i;
	for (i=1; i<25; i++) {
		draw_rect(HEI - i*HEI/40, r - i*5, g - i*5, b - i*5);
	}
}
