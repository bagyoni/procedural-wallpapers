// FLOW
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>
#include <math.h>

#include "lib/main.h"
#include "lib/perlin.h"

#define NUM_PARTICLES 5000
#define PATH_LEN 300

float flow[WID * HEI];
float curvature;
float frequency;
int signum;

void make_single_path() {
	float x = rand() % WID;
	float y = rand() % HEI;
	int i = 0;
	while (i<PATH_LEN && x>0 && x<WID && y>0 && y<HEI) {
		int xi = x;
		int yi = y;
		flow[(WID*yi+xi)] += ((float) (PATH_LEN-i)) / PATH_LEN;
		float angle = 2 * M_PI * (fractal(x, y, frequency, 6) - 0.5) * curvature;
		x += cos(angle);
		y += sin(angle);
		i++;
	}
}

void draw() {
	generate_noise();
	signum = rand() & 1 ? 1 : -1;
	curvature = 0.3 + 0.1 * ((float) (rand() & 0xFF)) / 0xFF;
	frequency = 0.003 + 0.003 * ((float) (rand() & 0xFF)) / 0xFF;
	int i;
	for (i=0; i<NUM_PARTICLES; i++) {
		make_single_path();
	}
	float max;
	for (i=0; i<WID*HEI; i++) {
		max = flow[i] > max ? flow[i] : max;
	}
	for (i=0; i<WID*HEI; i++) {
		unsigned char val = 256 + signum * (55 + 200*flow[i]/max);
		bytes[i*3] = val;
		bytes[i*3+1] = val;
		bytes[i*3+2] = val;
	}
}
