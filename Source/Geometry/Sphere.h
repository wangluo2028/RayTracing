#ifndef SPHEREH
#define SPHEREH

#include "Hitable.h"
#include "Material/Material.h"


class Sphere :public Hitable
{
public:
	Sphere(){}
	Sphere(vec3& center, float r,Material* Omaterial) :SphereCenter(center),radius(r),material(Omaterial){}

	// Compute intersection between sphere and Ray
	virtual bool hit(const ray& r, float tMin, float tMax, HitRecord& rec)const;

	// create Sphere's AABB Box
	virtual bool bounding_box(float t0, float t1, AABB& box) const;

	//  Geometric parameters of sphere
	//  Center position of sphere
	vec3 SphereCenter;

	// radius of sphere
	float radius;

	// Material's ptr of this sphere
	Material* material;
};


#endif
