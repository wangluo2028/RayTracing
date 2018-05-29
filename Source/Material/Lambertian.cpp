#include "Lambertian.h"

#include "Texture/Texture.h"
#include "Random/Random.h"


bool Lambertian::scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered) const
{
	vec3 target = rec.point + rec.normal + random_in_unit_spere();
	scattered = ray(rec.point,target-rec.point,r_in.time());
	attenuation = albedo->Value(0,0,rec.point);
	return true;
}
