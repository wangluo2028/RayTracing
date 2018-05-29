#include "AABB.h"

bool AABB::hit(const ray& r, float tmin, float tmax)const
{
	for (int a = 0; a < 3; a++)
	{
		// Compute every axis (X,Y,Z) of AABB intersect ray separately in X,Y,Z

		float t0 = ffmin((min[a] - r.origin()[a]) / r.direction()[a], (max[a] - r.origin()[a]) / r.direction()[a]);
		float t1 = ffmax((min[a] - r.origin()[a]) / r.direction()[a], (max[a] - r.origin()[a]) / r.direction()[a]);

		// Get greater one between tmin and intersecting point's min
		tmin = ffmax(t0, tmin);

		// Get smaller one between tmax and intersecting point's max
		tmax = ffmin(t1, tmax);

		// if don't have overlap the ray don't hit the AABB
		if (tmax <= tmin)
			return false;
	}
	return true;
}



AABB SurrongdingBox(AABB box0, AABB box1)
{
	// get the vector of smaller one
	vec3 smaller(fmin(box0.Min().x(), box1.Min().x()),
		fmin(box0.Min().y(), box1.Min().y()),
		fmin(box0.Min().z(), box1.Min().z()));

	// get the vector of bigger one
	vec3 bigger(fmax(box0.Max().x(), box1.Max().x()),
		fmax(box0.Max().y(), box1.Max().y()),
		fmax(box0.Max().z(), box1.Max().z()));

	return AABB(smaller, bigger);
}