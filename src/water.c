// WATER
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>
#include <math.h>

#include "lib/main.h"

#define MAX_WLEN 25
#define MIN_WLEN 10

char r, g, b;
int num_waves;

void draw_wave(int cx, int cy, float amp, float wavelength) {
	int x, y;
	for (x=0; x<WID; x++) {
		for (y=0; y<HEI; y++) {
			float dist = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));
			float radius = wavelength * (rand() % 10 + 10);
			float val = amp * (1-dist/(WID+HEI)) * (1 + sin(dist/wavelength)
					* (radius > dist ? 1 : radius/dist));
			bytes[(WID*y+x)*3] += (20+val*70)/num_waves;
			bytes[(WID*y+x)*3+1] += (20+val*70)/num_waves;
			bytes[(WID*y+x)*3+2] += (120+val*70)/num_waves;
		}
	}
}

void draw() {
	num_waves = rand()%5 + 2;
	int i;
	for (i=0; i<num_waves; i++) {
		int x = rand() % WID;
		int y = rand() % HEI;
		float amp = .5 + ((float) (rand() & 0xFF)) / 0x100 / 2;
		float wavelength = rand() % (MAX_WLEN - MIN_WLEN) + MIN_WLEN;
		draw_wave(x, y, amp, wavelength);
	}
}
