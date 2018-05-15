#pragma once
#include <iostream>
#include <stdio.h>
#include "Vector3.h"
#include "Ray.h"
using namespace std;

#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning (disable:4996)

#define W 1024
#define H 1024

vec3 color(const ray& r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.f - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = W;
	int ny = H;
	FILE* image = fopen("image.pmm", "w");
	fprintf(image, "P3\n%d %d\n255\n", nx, ny);

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);



	for (int j=ny-1;j>=0;j--)
	{
		for (int i=0;i<nx;i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner.e[0] + u*horizontal,lower_left_corner.e[1] +v*vertical);
			vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			fprintf(image, "%d %d %d\n", ir, ig, ib);
		}
	}
	fclose(image);
}