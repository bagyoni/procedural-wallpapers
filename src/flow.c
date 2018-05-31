// FLOW
// Attila Bagyoni, 2018
// This is a public domain software. Do whatever you want with it.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define WID 1024
#define HEI 768

#define NUM_PARTICLES 5000
#define PATH_LEN 300

char bytes[WID * HEI * 3];
float flow[WID * HEI];
float curvature;
float frequency;
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
		bytes[i*3] = 55 + 200*flow[i]/max;
		bytes[i*3+1] = 55 + 200*flow[i]/max;
		bytes[i*3+2] = 55 + 200*flow[i]/max;
	}
}

int main(int argc, char *argv[]) {

	srand((unsigned)time(NULL));
	draw();
	
	FILE *out = fopen(argv[1], "w");
	
	fprintf(out, "P6\n");
	fprintf(out, "%d %d\n", WID, HEI);
	fprintf(out, "255\n");
	
	fwrite(bytes, 1, WID*HEI*3, out);
	fclose(out);
	return 0;
}