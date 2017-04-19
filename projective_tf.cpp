#include "projective_tf.hpp"

projective_tf::projective_tf() {
	width =
	height =
	centerx = 
	centery = -1;

	tilt = .0;//4*M_PI/10;	//0 < tilt < M_PI/2
	FOV = 1.0;
}

int projective_tf::setMatPra(int w, int h) {
	width = w;
	height = h;
	centerx = w/2;
	centery = h/2;
	startx = w/4;
	starty = h/4;
	endx = 3*w/4;
	endy = 3*h/4;

	a = 
	b = 
	c = 
	d = .0;

	rm[4] = 1/cos(tilt);
	sm[5] = (1-rm[4])*centery;
	return 0;
}

int projective_tf::setRM(double ang) {
	tilt = ang;
	rm[4] = 1/cos(tilt);
	sm[5] = (1-rm[4])*centery;
	return 0;
}

int projective_tf::setFOV(double l) {
	a = (1.0 - l) / (endy - starty);
	b = -a*starty + l;
	return 0;
}

int projective_tf::culTf() { 
	double v0[3] = {.0, .0, 1.0};
	double v1[3] = {.0 ,.0, 1.0};
	double v2[3] = {.0, .0, 1.0};
	for (v0[1]=starty; v0[1]<endy; v0[1]++) {
		culFOV(v0[1]);
		for (v0[0]=startx; v0[0]<endx; v0[0]++) {
			culMt(rm, v0, v1);
			culMt(sm, v1, v2);
			setOutput(v0, v2);
		}
	}
	return 0;
}

int projective_tf::culMt(double* m, double* vi, double* vo) {
	vo[0] = m[0]*vi[0] + m[1]*vi[1] + m[2]*vi[2];
	vo[1] = m[3]*vi[0] + m[4]*vi[1] + m[5]*vi[2];
	vo[2] = m[6]*vi[0] + m[7]*vi[1] + m[8]*vi[2];
	return 0;
}

int projective_tf::culFOV(double h) {
	sm[0] = a*h + b;
	sm[2] = -sm[0]*centerx + centerx;
	return 0;
}

int projective_tf::setOutput(double* vi, double* vo) {
	if ( vo[0] < 0 || width <= vo[0] || vo[1] < 0 || height <= vo[1] )	return 1;
	out.data[3*((int)vo[0] + width*(int)vo[1])] = in.data[3*((int)vi[0] + width*(int)vi[1])];
	out.data[3*((int)vo[0] + width*(int)vo[1]) + 1] = in.data[3*((int)vi[0] + width*(int)vi[1]) + 1];
	out.data[3*((int)vo[0] + width*(int)vo[1]) + 2] = in.data[3*((int)vi[0] + width*(int)vi[1]) + 2];
	return 0;
}
