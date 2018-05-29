#include "HitableList.h"
#include "AABB.h"


bool HitableList::hit(const ray& r, float tMin, float tMax, HitRecord& rec)const
{
	HitRecord TempRec;
	bool HitAnything = false;
	double ClosetSoFar = tMax;

	for (int i = 0; i < ListSize; i++)
	{
		if (list[i]->hit(r, tMin, (float) ClosetSoFar, TempRec))
		{
			HitAnything = true;
			ClosetSoFar = TempRec.t;
			rec = TempRec;
		}
	}
	return HitAnything;

}

bool HitableList::bounding_box(float t0, float t1, AABB& box) const
{
	if (ListSize<1)
	{
		return false;
	}

	AABB temp_box;

	bool first_true = list[0]->bounding_box(t0, t1, temp_box);

	// Create the first bounding box
	if (!first_true)
	{
		return false;
	}
	else
		box = temp_box;

	// Traverse all the geometry and create the biggest bounding box
	for (int i=1;i < ListSize ; i++)
	{
		if (list[0]->bounding_box(t0, t1, temp_box))
		{
			box = SurrongdingBox(box, temp_box);
		}
		else
			return false;
	}
	return true;



}

