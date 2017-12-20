#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define WID 1024
#define HEI 768

char *bytes;

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
		draw_rect(HEI-i*20, r-i*5, g-i*5, b-i*5);
	}
}

int main(int argc, char **argv) {

	srand((unsigned)time(NULL));
	bytes = malloc(WID*HEI*3);
	memset(bytes, 255, WID*HEI*3);
	draw();
	
	FILE *out = fopen(argv[1], "w");
	
	fprintf(out, "P6\n");
	fprintf(out, "%d %d\n", WID, HEI);
	fprintf(out, "255\n");
	
	fwrite(bytes, 1, WID*HEI*3, out);
	fclose(out);
	return 0;
}