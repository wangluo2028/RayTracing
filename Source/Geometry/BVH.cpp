#include "BVH.h"
#include "AABB.h"

#include "Random/Random.h"
#include <math.h>




// Create BVH Binary Search Tree


Bvh_node::Bvh_node(Hitable** ptrInlist, int ListNum, float time0, float time1)
{

	// Use random number to sort every sub-tree's node  by (X,Y,Z) values
	// to let 
	int axis = int(3 * drand48());
	if (axis==0)
	{
		qsort(ptrInlist, ListNum, sizeof(Hitable*), Box_x_compare);
	}
	else if (axis==1)
	{
		qsort(ptrInlist, ListNum, sizeof(Hitable*), Box_y_compare);
	}
	else 
	{
		qsort(ptrInlist, ListNum, sizeof(Hitable*), Box_z_compare);
	}

	// Recursion end condition,when the last ListNum = 1 or 2
	if (ListNum==1)
	{
		// Right and left are point to the same node
		// Do this to keep Binary Tree balance
		LeftNode = RightNode = ptrInlist[0];
	}
	else if (ListNum==2)
	{
		// left and right leaves is different node
		LeftNode = ptrInlist[0];
		RightNode = ptrInlist[1];
	}
	else
	{
		// Recursing to Create balance sub-tree
		LeftNode = new Bvh_node(ptrInlist,ListNum/2, time0, time1);
		RightNode = new Bvh_node(ptrInlist + ListNum/2 , ListNum - ListNum / 2, time0, time1);
	}
	AABB BoxLeft, BoxRight;
	if (!LeftNode->bounding_box(time0,time1,BoxLeft)||!RightNode->bounding_box(time0,time1,BoxRight))
	{
		std::cerr << "no bounding box in bvh_node constructor\n";
	}
	box = SurrongdingBox(BoxLeft, BoxRight);
}



// Surface-Area-heuristic,The SAH minimizes: SUM_left_right number_of_children_in_subtree * surface_area_of_bounding_box_of_subtree
/*
Bvh_node::Bvh_node(Hitable** ptrInlist, int ListNum, float time0, float time1)
{
	AABB* boxes = new AABB[ListNum];
	float* LeftArea = new float[ListNum];
	float* RightArea = new float[ListNum];

	AABB MainBox;
	
	bool dummy = ptrInlist[0]->bounding_box(time0, time1, MainBox);

	AABB NewBox;
	for (int i=1;i < ListNum;i++)
	{
		
		bool dummy = ptrInlist[i]->bounding_box(time0, time1, NewBox);
		MainBox = SurrongdingBox(MainBox, NewBox);
	}// end for

	int axis = MainBox.LongestAxis();
	
	if (axis == 0)
	{
		qsort(ptrInlist, ListNum, sizeof(Hitable*), Box_x_compare());
	}
	else if (axis == 1)
	{
		qsort(ptrInlist, ListNum, sizeof(Hitable*), Box_y_compare());
	}
	else
		qsort(ptrInlist, ListNum, sizeof(Hitable*), Box_y_compare());

	for (int i=0;i<ListNum;i++)
	{
		bool dummy = ptrInlist[i]->bounding_box(time0, time1, boxes[i]);
	}
	LeftArea[0] = boxes[0].area();
	AABB LeftBox = boxes[0];

	for (int i=1;i<ListNum-1;i++)
	{
		LeftBox = SurrongdingBox(LeftBox, boxes[i]);
		LeftArea[i] = LeftBox.area();
	}
	RightArea[ListNum - 1] = boxes[ListNum - 1].area();
	AABB RightBox = boxes[ListNum - 1];

	for (int i=ListNum-2;i>0;i--)
	{
		RightBox = SurrongdingBox(RightBox, boxes[i]);
		RightArea[i] = RightBox.area();
	}

	float minSAH = FLT_MAX;
	int minSAHIndex;

	for (int i=0;i<ListNum-1;i++)
	{
		float SAH = ListNum*LeftArea[i] + (ListNum - i - 1)*RightArea[i + 1];
		if (SAH < minSAH)
		{
			minSAHIndex = i;
			minSAH = SAH;
		}
	}

	if (minSAHIndex == 0)
	{
		left = ptrInlist[0];
	}
	else
		left = new Bvh_node(1, minSAHIndex + 1, time0, time1);
	if (minSAHIndex == ListNum - 2)
	{
		right = ListNum[minSAHIndex + 1];
	}
	else
		right = new Bvh_node(1 + minSAHIndex + 1, n - minSAHIndex - 1, time0, time1);

	box = MainBox;
}
*/


// Calculate the Ray intersect with bounding box and final intersect at the geometry of bottom of tree 
bool Bvh_node::hit(const ray& r, float tMin, float tMax, HitRecord& rec) const
{
	// First,test whether or not hit the biggest bounding box (Tree's root have the biggest AABB)
	// Then test whether or not hit the sub-leaves-bounding box until to find correction Geometry(Sphere)
	if (box.hit(r, tMin, tMax))
	{
		HitRecord LeftRecord, RightRecord;
		bool bHitLeft = LeftNode->hit(r, tMin, tMax, LeftRecord);
		bool bHitRight = RightNode->hit(r, tMin, tMax, RightRecord);

		// Test whether or not hit in left and right sub-tree 
		// According the return boolean to chose  closest Hit_Record 
		if (bHitLeft && bHitRight)
		{
			if (LeftRecord.t < RightRecord.t)
			{
				rec = LeftRecord;
			}
			else
				rec = RightRecord;
			return true;
		}
		else if (bHitLeft)
		{
			rec = LeftRecord;
			return true;
		}
		else if (bHitRight)
		{
			rec = RightRecord;
			return true;
		}
		else
			return false;

	}
	else
		return false;
}

bool Bvh_node::bounding_box(float t0, float t1, AABB& In_box) const
{
	In_box = box;
	return true;
}


int Box_x_compare(const void* a, const void* b)
{
	AABB BoxLeft, BoxRight;
	Hitable* ah = *(Hitable**)a;
	Hitable* bh = *(Hitable**)b;

	if (!ah->bounding_box(0,0,BoxLeft)||!bh->bounding_box(0,0,BoxRight))
	{
		std::cerr << "no bounding box in bvh_node constructor\n";
	}

	if ( (BoxLeft.Min().x() - BoxRight.Min().x()) < 0.0)
	{
		return -1;
	}
	else
		return 1;
}


int Box_y_compare(const void* a, const void* b)
{
	AABB BoxLeft, BoxRight;
	Hitable* ah = *(Hitable**)a;
	Hitable* bh = *(Hitable**)b;

	if (!ah->bounding_box(0, 0, BoxLeft) || !bh->bounding_box(0, 0, BoxRight))
	{
		std::cerr << "no bounding box in bvh_node constructor\n";
	}

	if ( ( BoxLeft.Min().y() - BoxRight.Min().y() ) < 0.0)
	{
		return -1;
	}
	else
		return 1;
}

int Box_z_compare(const void* a, const void* b)
{
	AABB BoxLeft, BoxRight;
	Hitable* ah = *(Hitable**)a;
	Hitable* bh = *(Hitable**)b;

	if (!ah->bounding_box(0, 0, BoxLeft) || !bh->bounding_box(0, 0, BoxRight))
	{
		std::cerr << "no bounding box in bvh_node constructor\n";
	}

	if ( BoxLeft.Min().z() - BoxRight.Min().z()  < 0.0)
	{
		return -1;
	}
	else
		return 1;
}
