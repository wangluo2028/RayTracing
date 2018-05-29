#include "Random.h"




void InitializeRadiansTable()
{
	for (int i=0;i<361;i++)
	{
		float radian = DegreeToRadian((float)i);
		//COS[i] = cosf(radian);
		SIN[i] = sinf(radian);
	}
}

float drand48()
{
	return (float)(rand() / (RAND_MAX + 1.0));
}

// random a new point in a unit sphere
vec3 random_in_unit_spere()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.f);
	return p;
}

// Calculate total reflectivity angle
float Schlick(float consine, float refractivity)
{
	float r0 = (1 - refractivity) / (1 + refractivity);
	r0 = r0*r0;
	return r0 + (1 - r0)*pow((1 - consine), 5);
}