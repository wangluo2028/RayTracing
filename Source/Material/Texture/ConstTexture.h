#ifndef CONSTTEXTURE_H
#define CONSTTEXTURE_H

#include "Texture.h"

class ConstTexture :public Texture
{
public:
	ConstTexture() {}
	ConstTexture(vec3 c):color(c){}

	virtual vec3 Value(float u, float v, const vec3& p)const;

	vec3 color;
};



#endif