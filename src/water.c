// WATER
// Attila Bagyoni, 2018
// This is a public domain software. Do whatever you want with it.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define WID 1024
#define HEI 768

char bytes[WID * HEI * 3];
char r, g, b;
int num_waves;

void draw_wave(int cx, int cy, float amp, float wavelength) {
	int x, y;
	for (x=0; x<WID; x++) {
		for (y=0; y<HEI; y++) {
			float dist = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));
			float val = amp * (1-dist/(WID+HEI)) * (1 + sin(dist/wavelength));
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
		float wavelength = rand() % 20 + 5;
		draw_wave(x, y, amp, wavelength);
	}
}

int main(int argc, char **argv) {

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