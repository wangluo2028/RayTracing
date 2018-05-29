#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray/Ray.h"
#include "Geometry/Hitable.h"


// Abstract class
// Interface to calculate the scattered rays
class Material
{
public:
	virtual bool scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered)const = 0;
};



#endif