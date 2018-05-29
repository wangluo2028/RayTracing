#include "CheckerTexture.h"
#include "Random/Random.h"

vec3 CheckerTexture::Value(float u, float v, const vec3& p) const
{
	float sines =(float)SIN[RadianToDegree(10 * p.x())]*SIN[RadianToDegree(10 * p.y())]*SIN[RadianToDegree(10 * p.z())];
	//float sines = sin(5 * p.x())*sin(5 * p.y())*sin(5 * p.z());
	if (sines < 0)
	{
		return odd->Value(u, v, p);
	}
	else
		return even->Value(u, v, p);
	
}
