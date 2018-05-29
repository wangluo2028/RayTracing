#include "MovingSphere.h"
#include <math.h>
#include "AABB.h"

bool MovingSphere::hit(const ray& r, float tmin, float tmax, HitRecord& rec) const
{
	vec3 oc = r.origin() - center(r.time());
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;

	// according the judge equation b^2-4ac < 0 or >0
	float discrimant = b*b - a*c;
	float sqrt_discriment = sqrt(discrimant);
	if (discrimant > 0)
	{
		float temp = (-b - sqrt_discriment) / a;
		if (temp <tmax && temp > tmin)
		{
			rec.t = temp;
			rec.point = r.point_at_parameter(rec.t);
			rec.normal = (rec.point - center(r.time())) / radius;
			rec.material_ptr = material;
			return true;
		}// end if

		temp = (-b + sqrt_discriment) / a;
		if (temp < tmax && temp > tmin)
		{
			rec.t = temp;
			rec.point = r.point_at_parameter(rec.t);
			rec.normal = (rec.point - center(r.time())) / radius;
			rec.material_ptr = material;
			return true;
		}// end if

	}// end if
	return false;
}

bool MovingSphere::bounding_box(float t0, float t1, AABB& box) const
{
	AABB box0(center(t0) - vec3(radius, radius, radius), center(t0) + vec3(radius, radius, radius));
	AABB box1(center(t1) - vec3(radius, radius, radius), center(t1) + vec3(radius, radius, radius));

	box = SurrongdingBox(box0,box1);

	return true;
	
}

vec3 MovingSphere::center(float time) const
{
	return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
}
