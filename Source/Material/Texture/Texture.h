#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vector/Vector3.h"

class Texture
{
public:
	virtual vec3 Value(float u, float v, const vec3& p)const = 0;

};


#endif