// The common main method for all wallpaper generators in this project
// Attila Bagyoni, 2018
// This software is public domain. Do whatever you want with it.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "main.h"

int main(int argc, char *argv[]) {

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
