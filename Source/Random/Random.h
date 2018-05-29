#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <math.h>
#include "Vector/Vector3.h"
#define PI 3.1415926f


extern float SIN[361], COS[361];

inline float DegreeToRadian(float degree)
{
	return degree / 180 * (float)PI;
}
inline int RadianToDegree(float Radian)
{
	float r= Radian / PI * 180;
	while (r > 360 || r < 0)
	{
		if (r > 360)
			r -= 360;
		else
			r+=360;
	}
	return (int)(r+0.5f);
}

void InitializeRadiansTable();

// random float  in 0 to 1
float drand48();

// random a new point in a unit sphere
vec3 random_in_unit_spere();

// simple polynomials approximation by Christophe Schlick  to calculate total reflected critical angle.
float Schlick(float consine, float refractivity);


#endif