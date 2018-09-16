// CLOUDS
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>
#include <math.h>

#include "lib/main.h"
#include "lib/perlin.h"

float sigmoid(float x) {
	return tanh(tanh(2*x-0.5)*2);
}

void draw() {
	generate_noise();
	float freq = 0.002 * (rand() & 0xFF) / 0xFF + 0.003;
	int x, y;
   	for (x=0; x<WID; x++) {
		for (y=0; y<HEI; y++) {
			float val = 0.5 * sigmoid(fractal(x, y, freq, 7)) + 0.5;
			bytes[(WID*y+x)*3] = val*230 + 25;
			bytes[(WID*y+x)*3+1] = val*255;
			bytes[(WID*y+x)*3+2] = 255;
		}
	}
}
