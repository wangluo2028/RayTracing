#ifndef MOVINGSHPERE_H
#define MOVINGSPHERE_H

#include "HitableList.h"

class MovingSphere :public Hitable
{
public:
	MovingSphere(){}
	MovingSphere(vec3 cen0,vec3 cen1,float t0,float t1,float r,Material* material_ptr):center0(cen0),center1(cen1),time0(t0),time1(t1),radius(r),material(material_ptr){}

	virtual bool hit(const ray& r, float tmin, float tmax, HitRecord& rec)const;

	virtual bool bounding_box(float t0, float t1, AABB& box) const;

	// Calculate linearly sphere's center between time0 and time1
	vec3 center(float time)const;

	// 
	vec3 center0, center1;
	float time0, time1;
	float radius;
	Material* material;
};


#endif