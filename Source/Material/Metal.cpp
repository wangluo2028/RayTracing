#include "Metal.h"

#include "Random/Random.h"

bool Metal::scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered) const
{
	vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.point, reflected+fuzz*random_in_unit_spere());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}
