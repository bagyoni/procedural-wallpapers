#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <complex.h>

#define WID 1024
#define HEI 768

char bytes[WID * HEI * 3];
float complex poly1[5], poly2[5];
char r, g, b;

void fgcolor(char red, char green, char blue) {
	r=red;
	g=green;
	b=blue;
}

float complex p1(float complex z) {
	return poly1[4]*z*z*z*z + poly1[3]*z*z*z + poly1[2]*z*z + poly1[1]*z;
}

float complex p2(float complex z) {
	return poly2[4]*z*z*z*z + poly2[3]*z*z*z + poly2[2]*z*z + poly2[1]*z;
}

float complex f(float complex z) {
	return cpow(2*I, p1(z-50)/200)*100 + p2(z);
}

void gen_poly(float complex * poly) {
	poly[1] = ((int)(rand()&255) - 128)/100. + ((int)(rand()&255) - 128)/100.*I;
	poly[2] = ((int)(rand()&255) - 128)/100000. + ((int)(rand()&255) - 128)/100000.*I;
	poly[3] = ((int)(rand()&255) - 128)/100000000. + ((int)(rand()&255) - 128)/100000000.*I;
	poly[4] = ((int)(rand()&255) - 128)/10000000000. + ((int)(rand()&255) - 128)/10000000000.*I;
}

void draw_point(int x, int y) {
	bytes[(WID*y+x)*3] = r;
	bytes[(WID*y+x)*3+1] = g;
	bytes[(WID*y+x)*3+2] = b;
}

void draw() {
	fgcolor(150, 150, 150);
	gen_poly(poly1);
	gen_poly(poly2);	
	int x, y;
	for (x=0; x<WID; x++) {
		for (y=0; y<HEI; y++) {
			char re = (char) crealf(f(x - WID/2 + I*(y - HEI/2)));
			if (re < 0) {
				draw_point(x, y);
			}
		}
	}
}

int main(int argc, char **argv) {

	srand((unsigned)time(NULL));
	memset(bytes, 230, WID*HEI*3);
	draw();
	
	FILE *out = fopen(argv[1], "w");
	
	fprintf(out, "P6\n");
	fprintf(out, "%d %d\n", WID, HEI);
	fprintf(out, "255\n");
	
	fwrite(bytes, 1, WID*HEI*3, out);
	fclose(out);
	return 0;
}