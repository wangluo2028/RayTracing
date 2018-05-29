#pragma once
#include <iostream>
#include <stdio.h>
#include <float.h>
#include <windows.h>
#include <assert.h>
// custom head file 
#include "Vector/Vector3.h"
#include "Ray/Ray.h"
#include "Geometry/Sphere.h"
#include "Geometry/MovingSphere.h"
#include "Geometry/HitableList.h"
#include "Camera/Camera.h"
#include "Random/Random.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"
#include "Geometry/BVH.h"
#include "Material/Texture/CheckerTexture.h"
#include "Material/Texture/ConstTexture.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning (disable:4996)

// image's width and high
#define W 1900
#define H 1080
#define SampleNum 1024
#define DEPTH 50    // calculate how many times of scatter of one ray
#define IMAGE_NAME "MoveSphere_BVH_1080P_1024sample.ppm"

float SIN[361], COS[361];


// Camera parameter
#define LOOKAT             vec3(0,0,0)
#define LOOKFROM           vec3(13,2,3)
#define WORLDUP            vec3(0,1,0)
#define DISTTANCE_TO_FOCUS 10.f
#define APERTURE           0.2f
#define FOV                20

// the max distance of ray
#define MAXFLOAT FLT_MAX




vec3 color(const ray& r,Hitable* world,int depth)
{
	// calculate the ray hit points
	HitRecord rec;

	if (world->hit(r,0.001f,MAXFLOAT,rec))
	{
		ray scattered;
		vec3 attenuation;

		// Calculate scattered ray's color,if depth>50,we assume ray will be dark.
		if (depth<DEPTH && rec.material_ptr->scatter(r,rec,attenuation,scattered))
		{
			// Calculate once scatter,depth will plus 1
			return attenuation*color(scattered, world, depth+1);
		}
		else
		{
			return vec3(0.0,0.0,0.0);
		}
	}
	else
	{
		// if hit nothing leap the color with blue and white
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f*(unit_direction.y() + 1.f);
		return (1.f - t) * vec3(1.f, 1.f, 1.f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
	
}


Hitable* random_scene()
{
	int n = 300;
	Hitable **list = new Hitable* [n + 1];

	Texture* checker = new CheckerTexture(new ConstTexture(vec3(0.2f, 0.3f, 0.1f)), new ConstTexture(vec3(0.9f, 0.9f, 0.9f)));

	list[0] = new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(checker));
	int i = 1;
	for (int a=-3;a<3;a++)
	{
		for (int b=-3;b<3;b++)
		{
			float choose_mat = drand48();
			vec3 center(a + 0.9f * drand48(), 0.2f, b + 0.9f  *drand48());
			if ((center - vec3(4,0.2f,0)).length() > 0.9)
			{
				// diffuse sphere
				if (choose_mat < 0.8) 
				{
					list[i++] = new MovingSphere(center, center+vec3(0,0.5f * drand48(),0),0.0f,1.0f,0.2f, new Lambertian(new ConstTexture(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48()))));
				}
				// metal sphere
				else if (choose_mat < 0.95)
				{
					list[i++] = new Sphere(center, 0.2f, new Metal(vec3(0.5f * (1 + drand48()), 0.5f * (1 + drand48()), 0.5f * (1 + drand48())),drand48()));
				}
				// glass sphere
				else
				{
					list[i++] = new Sphere(center, 0.2f, new Dielectirc(1.5f));
				}
			}
		}
	}
	list[i++] = new Sphere(vec3(0, 1, 0), 1.0f, new Dielectirc(1.5f));
	list[i++] = new Sphere(vec3(-4, 1, 0), 1.0f, new Lambertian(new ConstTexture(vec3(0.4f, 0.2f,0.1f))));
	list[i++] = new Sphere(vec3(4, 1, 0), 1.0f, new Metal(vec3(0.7f, 0.6f, 0.5f), 0.0));
	assert(i < n|| i==n);
	return new Bvh_node(list, i, 0.0, 1.0);
}




int main()
{
	// get the start time
	unsigned int time = GetTickCount();

	int nx = W;
	int ny = H;
	int ns = SampleNum;

	// Initial Sin/cos looking-for table
	InitializeRadiansTable();

	FILE* image = fopen(IMAGE_NAME, "w");
	fprintf(image, "P3\n%d %d\n255\n", nx, ny);

	// Camera's distance to focus
	float dis_to_focus = DISTTANCE_TO_FOCUS;
	Camera camera(LOOKFROM, LOOKAT, WORLDUP,FOV, float(W)/float(H),APERTURE,dis_to_focus,0.0f,1.0f);

    // spawn random scene
	Hitable* world= random_scene();


	vec3 col(0.0, 0.0, 0.0);
	int ir, ig, ib;
	ray r;
	

	for (int j=ny-1;j>=0;j--)
	{
		for (int i=0;i<nx;i++)
		{
			col = vec3(0.0, 0.0, 0.0);
			for (int s=0;s<ns;s++)
			{
				float u = float(i+drand48()) / float(nx);
				float v = float(j+drand48()) / float(ny);
			    r = camera.GetRay(u, v);
				//vec3 p = r.point_at_parameter(2.0f);
				col += color(r, world,0);
			}

			col /=  float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			ir = int(255.99*col[0]);
			ig = int(255.99*col[1]);
			ib = int(255.99*col[2]);

			fprintf(image, "%d %d %d\n", ir, ig, ib);
			
		}
	}
	time = (GetTickCount() - time);
	cout << "all running time :" << time << " ms\n" << "Running time(in second):" << time/1000 << " s\n" <<"Running time(in minute)"<<time/60000<<" min"<< endl;
	fclose(image);
	return 0;
}