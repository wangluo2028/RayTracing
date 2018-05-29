#ifndef AABB_H
#define AABB_H

#include "Ray/Ray.h"


//
inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }


// BVH axis_align bounding box for geometry
class AABB
{
public:
	AABB() {}
	AABB(const vec3& a, const vec3& b) { min = a; max = b; }

	vec3 Min()const { return min; }
	vec3 Max()const { return max; }

	bool hit(const ray& r, float tmin, float tmax)const;




	vec3 min;
	vec3 max;
};


AABB SurrongdingBox(AABB box0, AABB box1);

#endif