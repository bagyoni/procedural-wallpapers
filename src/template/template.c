#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define WID 1024
#define HEI 768

char bytes[WID * HEI * 3];
char r, g, b;

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

void draw() {
	
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