/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include <math.h>
#include "Sphere.h"

Sphere::Sphere()
{
	//the default sphere is centred around the origin of the world coordinate
	//default radius is 2.0

	m_centre.SetZero();
	m_radius = 2.0;
	m_primtype = PRIMTYPE_Sphere;
}

Sphere::Sphere(double x, double y, double z, double r)
{
	m_centre.SetVector(x, y, z);
	m_radius = r;
	m_primtype = PRIMTYPE_Sphere;
}

Sphere::~Sphere()
{
}

RayHitResult Sphere::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;

	double t = FARFAR_AWAY;
	Vector4D normal;
	Vector4D intersection_point;

	//TODO: Calculate the intersection between the input ray and this sphere
	// Store the parametric result in t
	// The algebraic form of a sphere is  (x - cx)^2 + (y - cy)^2 + (z - cz)^2 = r^2 where
	// (x,y,z) is a point on the sphere
	// (cx, cy, cz) is the centre of the sphere.,i.e. m_centre
	// r is the radius of the sphere
	//
	// Note, the solution to ray-sphere intersection is the root(s) of a quadratic equation
	// therefore, there will be three scenarios
	// 1. Two real roots, the ray intersects the sphere twice. In this case, we are only interested in the closest intersection
	// 2. One real root, the ray tangentially intersects the sphere
	// 3. No real root, no intersection
	
	// S-C
	Vector4D sMinusC = ray.GetRayStart() - m_centre;
	// RAY DOT PRODUCT OF S-C
	double rayDotSmC = ray.GetRay().DotProduct(sMinusC);
	// V.V
	double rayDotProd = ray.GetRay().DotProduct(ray.GetRay());
	// RADIUS SQUARED
	double radiusSquared = m_radius * m_radius;

	// First part of the vector aka determinate 
	double det = (ray.GetRay().DotProduct(sMinusC))*(ray.GetRay().DotProduct(sMinusC)) - (rayDotProd * (sMinusC.DotProduct(sMinusC) - radiusSquared));

	if (det < 0)
	{
		return result;
	}

	if (det == 0)
	{
		t = -ray.GetRay().DotProduct(sMinusC) / rayDotProd;
	}

	if (det > 0)
	{
		// Make sure to square root the damn square rest
		double t_pos = (-(rayDotSmC) + sqrt(det)) / rayDotProd; //+-
		double t_neg = (-(rayDotSmC) - sqrt(det)) / rayDotProd;

		if (t_pos < t_neg)
		{
			t = t_pos;
		}
		else
		{
			t = t_neg;
		}
	}


	//Calculate the exact location of the intersection using the result of t
	intersection_point = ray.GetRayStart() + ray.GetRay()*t;
	
	//TODO: Calculate normal
	//Normals vary across the surface of a sphere
	//You need to calculate the normal based on the location of the intersection
	normal = (intersection_point - m_centre).Normalise();

	if (t>0.0 && t < FARFAR_AWAY)
	{
		result.t = t;
		result.data = this;
		result.point = intersection_point;
		result.normal = normal;
	}

	return result;
}
