#ifndef BVH_H
#define BVH_H

#include "Hitable.h"
#include "AABB.h"




class Bvh_node :public Hitable
{
public:
	Bvh_node() {}
	Bvh_node(Hitable** l, int n, float time0, float time1);
	
	virtual bool hit(const ray& r, float tMin, float tMax, HitRecord& rec)const;
	virtual bool bounding_box(float t0, float t1, AABB& box)const;

	Hitable* LeftNode;
	Hitable* RightNode;
	AABB box;

};



int Box_x_compare(const void* a, const void* b);
int Box_y_compare(const void* a, const void* b);
int Box_z_compare(const void* a, const void* b);


#endif