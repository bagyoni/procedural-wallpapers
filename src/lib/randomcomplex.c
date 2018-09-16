// Random complex function generator
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <complex.h>
#include <stdlib.h>

#include "randomcomplex.h"
#include "main.h"

complex float poly1[5], poly2[5];

void generate_poly(complex float * poly) {
	poly[1] = ((int)(rand()&255) - 128)/100. + ((int)(rand()&255) - 128)/100.*I;
	poly[2] = ((int)(rand()&255) - 128)/100000. + ((int)(rand()&255) - 128)/100000.*I;
	poly[3] = ((int)(rand()&255) - 128)/100000000. + ((int)(rand()&255) - 128)/100000000.*I;
	poly[4] = ((int)(rand()&255) - 128)/10000000000. + ((int)(rand()&255) - 128)/10000000000.*I;
}

void generate_f() {
	generate_poly(poly1);
	generate_poly(poly2);
}

complex float p1(complex float z) {
	return poly1[4]*z*z*z*z + poly1[3]*z*z*z + poly1[2]*z*z + poly1[1]*z;
}

complex float p2(complex float z) {
	return poly2[4]*z*z*z*z + poly2[3]*z*z*z + poly2[2]*z*z + poly2[1]*z;
}

complex float f(complex float z) {
	return cpow(2*I, p1(z-50)/200)*100 + p2(z);
}
