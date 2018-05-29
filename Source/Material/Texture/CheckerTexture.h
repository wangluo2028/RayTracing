#ifndef CHECKERTEXTURE_H
#define CHECKERTEXTURE_H

#include "Texture.h"

class CheckerTexture :public Texture
{
public:
	CheckerTexture(){}
	CheckerTexture(Texture* t0,Texture* t1):even(t0),odd(t1){}

	virtual vec3 Value(float u, float v, const vec3& p)const;

	// Vec of checker's color
	Texture* odd;
	Texture* even;
};


#endif // CHECKERTEXTURE_H
