#ifndef METAL_H
#define METAL_H

#include "Material.h"
class Metal :public Material
{
public:
	Metal(const vec3& a,float in_fuzz) :albedo(a),fuzz(in_fuzz){ }

	// Calculate mirror reflecting rays
	virtual bool scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered)const;


	vec3 albedo;
	float fuzz;
};

#endif // METAL_H
