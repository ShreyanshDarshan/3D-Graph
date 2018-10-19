//defines 3d vectors, camera and triangles (which form the mesh)
//AUTHOR: ShreyanshDarshan

#pragma once
#include<cmath>
#include"render.h"
#include"Vector3D.h"
#include"Camera.h"
#define dbl long double

class Triangle
{
public:
	Vector3D actual[3];
	Vector3D projected[3];
	Vector3D normal;
	unsigned char shade;

	dbl DistToCam;

	void operator = (const Triangle &a);
	bool operator < (const Triangle &a);
	bool operator > (const Triangle &a);

	dbl CalculateNormal();
	void VertexToTriangle(Vector3D** vertex, int x, int y, int type);
	void CalculateDistance(Camera ca);
	void show(Screen &s);
};






