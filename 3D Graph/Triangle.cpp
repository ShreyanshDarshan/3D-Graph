//AUTHOR: ShreyanshDarshan

#include"stdafx.h"
#include"render.h"
#include"Triangle.h"
#include"Vector3D.h"
#include<algorithm>
#define dbl long double

dbl Triangle::CalculateNormal()
{
	normal = (actual[1] - actual[0]).crossProduct(actual[2] - actual[0]);
	normal = normal.Unit();
	return normal.dotProduct(Vector3D(0, 0, 1));
}

void Triangle::VertexToTriangle(Vector3D** vertex, int x, int y, int type)
{
	//Triangle* faces = new Triangle[2*(sizex - 1)*(sizey - 1)]; 
	actual[0] = vertex[x][y];
	actual[1] = vertex[x + 1][y];
	actual[2] = vertex[x + 1][y + 1];
	projected[0] = Vector3D((x - 500) / 10.0, (y - 500) / 10.0, 0);
	projected[1] = Vector3D((x + 1 - 500) / 10.0, (y - 500) / 10.0, 0);
	projected[2] = Vector3D((x + type - 500) / 10.0, (y + type * 2 - 1 - 500) / 10.0, 0);

	if (CalculateNormal() < 0)
	{
		normal = normal * (-1);
	}
}

void Triangle::CalculateDistance(Camera ca)
{
	DistToCam = (ca.Location - (actual[0] + actual[1] + actual[2]) / 3).Magnitude();
}

void Triangle::show(Screen &s)
{
	//sort(projected, projected+3);
	dbl x_1, x_2;
	for (dbl i = projected[2].Y; i >= projected[0].Y; i--)
	{
		if (i > projected[1].Y)
		{
			x_1 = (projected[2].X - projected[0].X) * (i - projected[2].Y) / (projected[2].Y - projected[0].Y) + projected[2].X;
			x_2 = (projected[2].X - projected[1].X) * (i - projected[2].Y) / (projected[2].Y - projected[1].Y) + projected[2].X;
		}
		else
		{
			x_1 = (projected[2].X - projected[0].X) * (i - projected[2].Y) / (projected[2].Y - projected[0].Y) + projected[2].X;
			x_2 = (projected[0].X - projected[1].X) * (i - projected[0].Y) / (projected[0].Y - projected[1].Y) + projected[0].X;
		}
		s.draw_path(x_1, i, x_2, i, shade, shade, shade);
	}
}

void Triangle::operator = (const Triangle &a)
{
	for (int i = 0; i < 3; i++)
	{
		actual[i] = a.actual[0];
		projected[i] = a.projected[0];
	}
	normal = a.normal;
	DistToCam = a.DistToCam;
}
bool Triangle::operator < (const Triangle &a)
{
	return DistToCam < a.DistToCam;
}
bool Triangle::operator > (const Triangle &a)
{
	return DistToCam > a.DistToCam;
}