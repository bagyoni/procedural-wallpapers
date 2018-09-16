// ISLANDS
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include "lib/main.h"
#include "lib/perlin.h"

#define LEVEL(in, c1, c2, c3)   in>195 ? c1 : (in>190 ? c2 : c3)

void draw_horiz_dashed(int y) {
	int x;
	for (x=0; x<WID; x++) {
		if (x%20 < 10) {
			bytes[(WID*y+x)*3]   = 100;
			bytes[(WID*y+x)*3+1] = 96;
			bytes[(WID*y+x)*3+2] = 82;
		}
	}
}

void draw_vert_dashed(int x) {
	int y;
	for (y=0; y<HEI; y++) {
		if (y%20 < 10) {
			bytes[(WID*y+x)*3]   = 100;
			bytes[(WID*y+x)*3+1] = 96;
			bytes[(WID*y+x)*3+2] = 82;
		}
	}
}

void draw() {
	generate_noise();
	int x, y;
   	for (x=0; x<WID; x++) {
		for (y=0; y<HEI; y++) {
			unsigned char val = 170+(char)(fractal(x, y, 0.006, 6)*80);
			bytes[(WID*y+x)*3]   = LEVEL(val, 202*val/255, 154, (198+val)/2);
			bytes[(WID*y+x)*3+1] = LEVEL(val, 168*val/255, 115, (151+val)/2);
			bytes[(WID*y+x)*3+2] = LEVEL(val, 131*val/255, 82,  ( 63+val)/2);
		}
	}
	draw_horiz_dashed(HEI*1/6);
	draw_horiz_dashed(HEI*3/6);
	draw_horiz_dashed(HEI*5/6);
	draw_vert_dashed(WID*1/6);
	draw_vert_dashed(WID*2/6);
	draw_vert_dashed(WID*3/6);
	draw_vert_dashed(WID*4/6);
	draw_vert_dashed(WID*5/6);
}
