/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
* 
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include "Triangle.h"

Triangle::Triangle()
{
	m_vertices[0] = Vector4D(-1.0, 0.0, -5.0);
	m_vertices[1] = Vector4D(0.0, 1.0, -5.0);
	m_vertices[2] = Vector4D(1.0, 0.0, -5.0);
	m_normal = Vector4D(0.0, 0.0, 1.0);
	m_primtype = PRIMTYPE_Triangle;
}

Triangle::Triangle(Vector4D pos1, Vector4D pos2, Vector4D pos3)
{
	SetTriangle(pos1, pos2, pos3);

	m_primtype = PRIMTYPE_Triangle;
}


Triangle::~Triangle()
{
}

void Triangle::SetTriangle(Vector4D v0, Vector4D v1, Vector4D v2)
{
	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;

	//Calculate Normal
	Vector4D NormalA = m_vertices[1] - m_vertices[0];
	Vector4D NormalB = m_vertices[2] - m_vertices[0];
	Vector4D Norm = NormalA.CrossProduct(NormalB);
	Norm.Normalise();
	m_normal = Norm;
}


RayHitResult Triangle::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;
	double t = FARFAR_AWAY;
	Vector4D intersection_point;

	Vector4D P = ray.GetRayStart() + ray.GetRay();
	double D = -(m_vertices[0]).DotProduct(m_normal);

	// TODO: Calculate the intersection between in the input ray and this triangle
	// If you have implemented ray-plane intersection, you have done half the work for ray-triangle intersection.
	// The remaining test is to check if the intersection point is inside the triangle
	//
	// Similar to the plane case, you should check if the ray is parallel to the triangle
	// and check if the ray intersects the triangle from the front or the back
	
	// Create Vert calculations
	Vector4D Vert0 = m_vertices[0] - P;
	Vector4D Vert1 = m_vertices[1] - P;
	Vector4D Vert2 = m_vertices[2] - P;

	// Vector Cross Product results (then normalize them)
	Vector4D N0 = Vert1.CrossProduct(Vert0);
	Vector4D N1 = Vert2.CrossProduct(Vert1);
	Vector4D N2 = Vert0.CrossProduct(Vert2);

	N0.Normalise();
	N1.Normalise();
	N2.Normalise();

	double D0 = -ray.GetRayStart().DotProduct(N0);
	double D1 = -ray.GetRayStart().DotProduct(N1);
	double D2 = -ray.GetRayStart().DotProduct(N2);

	if ((P.DotProduct(N0) + D0) < 0)
	{
		return result;
	}

	if ((P.DotProduct(N1) + D1) < 0)
	{
		return result;
	}

	if ((P.DotProduct(N2) + D2) < 0)
	{
		return result;
	}

	// Calculate t
	t = -(ray.GetRayStart().DotProduct(m_normal) + D) / ray.GetRay().DotProduct(m_normal);

	//Calculate the exact location of the intersection using the result of t
	intersection_point = ray.GetRayStart() + ray.GetRay()*t;

	if (t > 0 && t < FARFAR_AWAY) { //ray intersection
		result.t = t;
		result.normal = this->m_normal;
		result.point = intersection_point;
		result.data = this;
		return result;
	}
	
	return result;
}
