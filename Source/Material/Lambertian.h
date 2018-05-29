#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Texture;


class Lambertian:public Material
{
public:
	Lambertian(Texture* texture):albedo(texture){}

	// Calculate the material's scattered rays
	virtual bool scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered)const;

	// albedo of the material
	Texture* albedo;

};

#endif