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

void draw_point(complex float z) {
	float re = crealf(z);
	float im = cimagf(z);
	int x = (int)re + WID/2;
	int y = (int)im + HEI/2;
	if (x>0 && x<WID && y>0 && y<HEI) {
		bytes[(WID*y+x)*3] = r;
		bytes[(WID*y+x)*3+1] = g;
		bytes[(WID*y+x)*3+2] = b;
	}
}

void draw_horiz(float im, float re1, float re2) {
	float re;
	for (re=re1; re<re2; re+=0.5f) {
		draw_point(f(re + I*im));
	}
}

void draw_vert(float re, float im1, float im2) {
	float im;
	for (im=im1; im<im2; im+=0.5f) {
		draw_point(f(re + I*im));
	}
}

void draw() {

	gen_poly(poly1);
	gen_poly(poly2);
	fgcolor(rand(), rand(), rand());
	draw_horiz(-200.5f, -600.f, 600.f);
	draw_horiz(-150.5f, -600.f, 600.f);
	draw_horiz(-100.5f, -600.f, 600.f);
	draw_horiz(-50.5f, -600.f, 600.f);
	draw_horiz(0.5f, -600.f, 600.f);
	draw_horiz(50.5f, -600.f, 600.f);
	draw_horiz(100.5f, -600.f, 600.f);
	draw_horiz(150.5f, -600.f, 600.f);
	draw_horiz(200.5f, -600.f, 600.f);
	fgcolor(rand(), rand(), rand());
	draw_vert(-150.5f, -600.f, 600.f);
	draw_vert(-100.5f, -600.f, 600.f);
	draw_vert(-50.5f, -600.f, 600.f);
	draw_vert(0.5f, -600.f, 600.f);
	draw_vert(50.5f, -600.f, 600.f);
	draw_vert(100.5f, -600.f, 600.f);
	draw_vert(150.5f, -600.f, 600.f);
	
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