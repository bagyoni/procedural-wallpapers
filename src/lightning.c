// LIGHTNING
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>

#include "lib/main.h"
#include "lib/basicdrawing.h"

#define PNUM ((int) WID*10)

int particles[PNUM][2];
int step;
int distribution;

void generate_distribution() {
	distribution = rand() % 4;
}

void place_charge(int* x, int* y) {
	switch (distribution) {
	case 0:
		*x = rand() % WID;
		*y = HEI - (rand() % (rand() % (HEI - 1) + 1)) - 2;
		break;
	case 1:
		*x = rand() % WID;
		*y = rand() % (rand() % (HEI - 1) + 1);
		break;
	case 2:
		*x = WID - (rand() % (rand() % WID + 1)) - 1;
		*y = rand() % (HEI - 1);
		break;
	case 3:
		*x = rand() % (rand() % WID + 1);
		*y = rand() % (HEI - 1);
		break;
	
	}
}

void next_step() {
	int x, y;
	place_charge(&x, &y);
	int nearest;
	int nearest_d_sq = WID*WID + HEI*HEI;
	int i;
	for (i=0; i<step; i++) {
		int dist_sq = (particles[i][0] - x) * (particles[i][0] - x)
				+ (particles[i][1] - y) * (particles[i][1] - y);
		if (dist_sq < nearest_d_sq) {
			nearest_d_sq = dist_sq;
			nearest = i;
		}
	}
	int dx = particles[nearest][0] < x ? 1 : -1;
	int dy = particles[nearest][1] < y ? 1 : -1;
	if (dx * (x - particles[nearest][0]) > 3 * dy * (y - particles[nearest][1])) {
		dy = 0;
	} else if (dy * (y - particles[nearest][1]) > 3 * dx * (x - particles[nearest][0])) {
		dx = 0;
	}
	particles[step][0] = particles[nearest][0] + dx;
	particles[step][1] = particles[nearest][1] + dy;
	draw_point(particles[step][0], particles[step][1]);
	draw_point(particles[step][0], particles[step][1]+1);
	step++;
}

void draw() {
	generate_distribution();
	particles[0][0] = rand() % WID;
	particles[0][1] = 0;
	int red = rand() % 120;
	int green = rand() % 120;
	step = 1;
	while (step < PNUM) {
		if (step % 2000 == 0) {
			generate_distribution();
		}
		fgcolor(
			red + (200-red)*(PNUM-step)/PNUM,
			green + (200-green)*(PNUM-step)/PNUM,
			255);
		next_step();
	}
}
