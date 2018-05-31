// ISLANDS
// Attila Bagyoni, 2018
// This is a public domain software. Do whatever you want with it.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define WID 1024
#define HEI 768
#define LEVEL(in, c1, c2, c3)   in>195 ? c1 : (in>190 ? c2 : c3)

char bytes[WID * HEI * 3];
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
	draw_horiz_dashed(200);
	draw_horiz_dashed(400);
	draw_horiz_dashed(600);
	draw_vert_dashed(200);
	draw_vert_dashed(400);
	draw_vert_dashed(600);
	draw_vert_dashed(800);
	draw_vert_dashed(1000);
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