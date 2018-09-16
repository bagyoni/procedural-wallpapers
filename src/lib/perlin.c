// Perlin noise/fractal noise generator
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>
#include <math.h>

#include "main.h"

float gradient[WID][HEI][2];

void generate_noise() {
	int x, y;
	for (x=0; x<WID; x++) {
		for (y=0; y<HEI; y++) {
			int rnd = rand() & 0xFFF;
			gradient[x][y][0] = sin(rnd);
			gradient[x][y][1] = cos(rnd);
		}
	}
}

float inter(float x, float y, float weight) {
	float yweight= weight * weight * (2-weight);
	return x * (1 - yweight) + y * yweight;
}

float distance_along_gradient(float x, float y, int gridx, int gridy) {
	return (x - gridx) * gradient[gridx][gridy][0]
		+ (y - gridy) * gradient[gridx][gridy][1];
}

float perlin(float x, float y) {
	float d1 = distance_along_gradient(x, y, x,   y);
	float d2 = distance_along_gradient(x, y, x+1, y);
	float d3 = distance_along_gradient(x, y, x,   y+1);
	float d4 = distance_along_gradient(x, y, x+1, y+1);
	float i1 = inter(d1, d2, x - (int) x);
	float i2 = inter(d3, d4, x - (int) x);
	return inter(i1, i2, y - (int) y);
}

float fractal(float x, float y, float freq, int depth) {
	if (depth == 0) {
		return 0;
	}
	return perlin(x*freq, y*freq) + fractal(x, y, freq*2, depth-1) / 2;
}
