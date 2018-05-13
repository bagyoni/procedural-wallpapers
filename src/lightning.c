#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define WID 1024
#define HEI 768

#define PNUM 10000

char bytes[WID * HEI * 3];
char r, g, b;
int particles[PNUM][2];
int step;

void fgcolor(char red, char green, char blue) {
	r=red;
	g=green;
	b=blue;
}

void draw_point(int x, int y) {
	bytes[(WID*y+x)*3] = r;
	bytes[(WID*y+x)*3+1] = g;
	bytes[(WID*y+x)*3+2] = b;
}

void next_step() {
	int x = rand() % WID;
	int y = HEI - (rand() % (rand() % HEI + 1)) - 1;
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
	particles[0][0] = rand() % WID;
	particles[0][1] = 0;
	int red = rand() % 120;
	int green = rand() % 120;
	step = 1;
	while (step < PNUM) {
		fgcolor(red, green, 100+step*155/PNUM);
		next_step();
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