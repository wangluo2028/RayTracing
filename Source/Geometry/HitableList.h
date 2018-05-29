#ifndef HITABLELISTH
#define HITABLELISTH

#include "Hitable.h"

class HitableList :public Hitable
{
public:
	
	HitableList(Hitable** l, int n) { list = l; ListSize = n; }

	bool hit(const ray& r, float tMin, float tMax, HitRecord& rec)const override;

	bool bounding_box(float t0, float t1, AABB& box)const;


	// point to the Hitable Array 
	Hitable** list;

	// keep the size of the Hitable Array
	int ListSize;
};




#endif
