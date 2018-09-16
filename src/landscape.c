//Code stolen from https://tyrellrummage.github.io/landscape/

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lib/main.h"

double *points;
int points_len;

void generate_points(double steepness) {

	//first create a new array and set the initial point
	double newArray[points_len*2-1];
	newArray[0] = points[0];

	//then, loop through the original points array starting from the first one (to correct off by one error)
	int i;
	for(i = 1; i < points_len; i++){

		//get the average between the two points
		double avg = (points[i] + points[i - 1]) / 2;

		//get an offset
		double offsetAm = (double)HEI / ((points_len - 1) * 20/steepness);

		//make the offset random and able to be negative
		int rnd = rand()%((int)offsetAm*2+1)-(int)offsetAm;

		//add the randomness to the average (displace the point)
		avg += rnd;

		//push the displaced point as well as the original point
		newArray[2*i-1] = avg;
		newArray[2*i] = points[i];
	}
	//finally, copy the new array into points
	points_len = points_len*2-1;
	points = malloc(points_len*sizeof(double));
	memcpy(points, newArray, points_len*sizeof(double));
}

void generate_layer(double level, double steepness, char r, char g, char b) {
	double init_points[2] = {level, level};
	points = init_points;
	points_len = 2;
	int iters = log(WID) / log(2) + 1;
	int i;
	for (i=0; i<iters; i++) {
		generate_points(steepness);
	}
	for (i=0; i<points_len; i++) {
		int pt = (int)points[i];
		int ii;
		for (ii=pt; ii<HEI; ii++) {
			if (ii>=0) {
				bytes[(WID*ii+i)*3] = r;
				bytes[(WID*ii+i)*3+1] = g;
				bytes[(WID*ii+i)*3+2] = b;
			}
		}
	}
}

void draw() {
	memset(bytes, 240, WID*HEI*3);
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
	generate_layer(HEI*1/5, 7, r, g, b);
	generate_layer(HEI*2/5, 7, r-20, g-20, b-20);
	generate_layer(HEI*3/5, 5, r-50, g-50, b-50);
	generate_layer(HEI*4/5, 5, r-100, g-100, b-100);
}
