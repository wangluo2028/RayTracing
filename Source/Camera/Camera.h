#ifndef CAMERA_H
#define CAMERA_H

#include "Ray/Ray.h"

#define M_PI 3.14159265359

vec3 random_in_unit_disk();



class Camera
{
public:
	Camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspectRatio,float aperture,float focus_dist,float t0,float t1)
	{
		time0 = t0;
		time1 = t1;
		lens_radius = aperture / 2;
		float theta = vfov* (float)M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = half_height*aspectRatio;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);	
		lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
		horizontal = 2 * half_width * focus_dist * u;
		vertical = 2 * half_height * focus_dist * v;
	}

	ray GetRay(float u, float v);

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;

	// for shutter open / close times
	float time0, time1;

	// the radius of camera's lens
	float lens_radius;
};

#endif