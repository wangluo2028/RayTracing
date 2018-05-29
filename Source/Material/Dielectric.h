#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

class Dielectirc :public Material 
{
public:
	Dielectirc(float refractive_index):RefractiveIndex(refractive_index){}

	virtual bool scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered)const;

	float RefractiveIndex;
};

#endif