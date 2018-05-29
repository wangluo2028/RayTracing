#include "ConstTexture.h"

vec3 ConstTexture::Value(float u, float v, const vec3& p) const
{
	return color;
}
