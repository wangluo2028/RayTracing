#include "Camera/Camera.h"
#include "Random/Random.h"


ray Camera::GetRay(float ScreenU, float ScreenV)
{
	vec3 rd = lens_radius * random_in_unit_disk();
	vec3 offset = u * rd.x() + v * rd.y();
	float time = time0 + drand48() * (time1 -time0);
	return ray(origin +offset, lower_left_corner + ScreenU*horizontal + ScreenV*vertical - origin - offset,time);
}


vec3 random_in_unit_disk()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
	} while (dot(p, p) >= 1.0);
	return p;
}