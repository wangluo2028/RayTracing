#include "Dielectric.h"
#include "Random/Random.h"

bool Dielectirc::scatter(const ray& r_in, const HitRecord& rec, vec3& attenuation, ray& scattered) const
{
	vec3 outward_normal;

	vec3 reflected = reflect(r_in.direction(), rec.normal);

	// The ratio of internal refractive index to external index
	float ni_over_nt;

	attenuation = vec3(1.0, 1.0, 1.0);

	// the ray refracted
	vec3 refracted;

	float reflect_prob;
	float cosine;

	// Calculate two situation, air's refractive index is 1.0 =n1,dielectric materials refractive index is n2 > 1.0.
	// First situation,rays comes out of  geometry, n1/n2= RefractiveIndex
	// Second situation, rays pass into  geometry, n1/n2 = 1.0 / RefractiveInde
	if (dot(r_in.direction(),rec.normal)>0)
	{
		outward_normal = -rec.normal;
		ni_over_nt = RefractiveIndex;
		cosine = RefractiveIndex* dot(r_in.direction(), rec.normal) / r_in.direction().length();
	}
	else
	{
		outward_normal = rec.normal;
		ni_over_nt = 1.f / RefractiveIndex;
		cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
	}// end if

	if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
	{
		reflect_prob = Schlick(cosine, RefractiveIndex);
	}
	else
	{
		scattered = ray(rec.point, reflected);
		reflect_prob = 1.0;
	}

	if (drand48() < reflect_prob)
	{
		scattered = ray(rec.point, reflected);
	}
	else
	{
		scattered = ray(rec.point, refracted);
	}
	return true;
}

