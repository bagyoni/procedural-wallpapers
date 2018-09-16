// MESH
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>
#include <complex.h>

#include "lib/main.h"
#include "lib/basicdrawing.h"
#include "lib/randomcomplex.h"

void draw_complex_point(complex float z) {
	float re = crealf(z);
	float im = cimagf(z);
	int x = (int)re + WID/2;
	int y = (int)im + HEI/2;
	draw_point(x, y);
}

void draw_horiz(float im, float re1, float re2) {
	float re;
	for (re=re1; re<re2; re+=0.5f) {
		draw_complex_point(f(re + I*im));
	}
}

void draw_vert(float re, float im1, float im2) {
	float im;
	for (im=im1; im<im2; im+=0.5f) {
		draw_complex_point(f(re + I*im));
	}
}

void draw() {
	generate_f();
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
