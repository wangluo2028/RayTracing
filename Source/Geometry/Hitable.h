#ifndef HITABLEH 
#define HITABLEH

#include "Ray/Ray.h"

class Material;
class AABB;



// Used to record the hit point include
// ray's t,hit point'vec3,hit point's normal,the material of hit surface
struct HitRecord
{
	// t of a ray expression (origin + t* direction)
	float t;

	// Hit position
	vec3 point;

	// Normalized vector
	vec3 normal;

	// Material of hit point of geometry
	Material* material_ptr;
};

// Abstract class
// Every geometry inherit the class to calculate the hit message
class Hitable {
public:
	    // Calculate the ray and geometry intersection
		virtual bool hit(const ray& r, float tMin, float tMax, HitRecord& rec)const =0 ;

		// Create geometry's AABB
		virtual bool bounding_box(float t0, float t1, AABB& box)const = 0;


};

#endif // 
