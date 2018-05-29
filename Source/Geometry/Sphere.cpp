#include "Sphere.h"
#include "AABB.h"


bool Sphere::hit(const ray& r, float tMin, float tMax, HitRecord& rec)const
{
	vec3 oc = r.origin() - SphereCenter;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float disriminant = b*b - a*c;
	float sqrt_disriminant = sqrt(disriminant);

	// test  whether there are two or one real solution 
	if (disriminant > 0)
	{
		float temp = (-b - sqrt_disriminant) / a;
		if (temp < tMax && temp > tMin)
		{
			rec.t = temp;
			rec.point = r.point_at_parameter(rec.t);
			rec.normal = (rec.point - SphereCenter) / radius;
			rec.material_ptr = material;
			return true;
		}
		temp = (-b + sqrt_disriminant) / a;
		if (temp < tMax && temp > tMin)
		{
			rec.t = temp;
			rec.point = r.point_at_parameter(rec.t);
			rec.normal = (rec.point - SphereCenter) / radius;
			rec.material_ptr = material;
			return true;
		}
	}
	return false;
}

bool Sphere::bounding_box(float t0, float t1, AABB& box) const
{
	box = AABB(SphereCenter - vec3(radius, radius, radius), SphereCenter + vec3(radius, radius, radius));
	return true;
}
