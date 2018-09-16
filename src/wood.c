// WOOD
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>
#include <math.h>

#include "lib/main.h"
#include "lib/perlin.h"

void draw() {
	generate_noise();
	int detail = rand() % (500000/HEI) + (2000000/HEI);
	int x, y;
   	for (x=0; x<WID; x++) {
		for (y=0; y<HEI; y++) {
			unsigned char depth = fractal(x/10.0, y, 0.005, 4) * detail;
			unsigned char noise = rand() & 0xFF;
			bytes[(WID*y+x)*3] = 160 + depth/4 + noise/8;
			bytes[(WID*y+x)*3+1] = 82 + depth/4 + noise/8;
			bytes[(WID*y+x)*3+2] = 45 + depth/8 + noise/16;
		}
	}
}
