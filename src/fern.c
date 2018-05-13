//Mutated Barnsley fern

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define WID 1024
#define HEI 768

char bytes[WID * HEI * 3];
char r, g, b;
float coeffs[4][6] = {
	{0,	0,	0,	0.16,	0,	0},
	{0.20,	-0.26,	0.23,	0.22,	0,	1.60},
	{-0.15,	0.28,	0.26,	0.24,	0,	0.44},
	{0.85,	0.04,	-0.04,	0.85,	0,	1.60}
};
float dist[4] = {0.01, 0.08, 0.15, 1};
float brush_x, brush_y;

void fgcolor(char red, char green, char blue) {
	r=red;
	g=green;
	b=blue;
}

void draw_point(int x, int y) {
	if (x>0 && x<WID && y>0 && y<HEI) {
		bytes[(WID*y+x)*3] = r;
		bytes[(WID*y+x)*3+1] = g;
		bytes[(WID*y+x)*3+2] = b;
	}
}

void mutate() {
	int mutation = rand()%7;
	switch(mutation) {
	case 0:
		coeffs[3][1] = 0.2 * ((float) (rand() & 0xFF))/256 - 0.1;
		break;
	case 1:
		coeffs[1][0] = 0.5 * ((float) (rand() & 0xFF))/256 + 0.1;
		break;
	case 2:
		coeffs[1][0] = -0.1 * ((float) (rand() & 0xFF))/256 - 0.1;
		break;
	case 3:
		coeffs[2][0] = 0.1 * ((float) (rand() & 0xFF))/256 + 0.1;
		break;
	case 4:
		coeffs[2][0] = -0.3 * ((float) (rand() & 0xFF))/256 - 0.1;
		break;
	case 5:
		coeffs[1][1] = -0.1 * ((float) (rand() & 0xFF))/256 - 0.1;
		break;
	case 6:
		coeffs[2][1] = 0.2 * ((float) (rand() & 0xFF))/256 + 0.1;
		break;
	}
}

void next_step() {
	float rnd = ((float) (rand() & 0xFF))/256;
	int i = 0;
	while (dist[i] < rnd) {
		i++;
	}
	brush_x = coeffs[i][0] * brush_x + coeffs[i][1] * brush_y + coeffs[i][4];
	brush_y = coeffs[i][2] * brush_x + coeffs[i][3] * brush_y + coeffs[i][5];
	draw_point(brush_x * 60 + WID / 2, -brush_y * 60 + HEI);
}

void draw() {
	mutate();
	mutate();
	mutate();
	mutate();
	mutate();
	brush_x = 0;
	brush_y = 0;
	int i;
	fgcolor(0, 140, 70);
	for (i=0; i<80000; i++) {
		next_step();
	}
	fgcolor(100, 220, 20);
	for (i=0; i<5000; i++) {
		next_step();
	}
}

int main(int argc, char **argv) {

	srand((unsigned) time(NULL));
	draw();
	
	FILE *out = fopen(argv[1], "w");
	
	fprintf(out, "P6\n");
	fprintf(out, "%d %d\n", WID, HEI);
	fprintf(out, "255\n");
	
	fwrite(bytes, 1, WID*HEI*3, out);
	fclose(out);
	
	return 0;
}