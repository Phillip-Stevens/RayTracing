/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#pragma once
#include "Primitive.h"
#include "Vector4D.h"
#include "Ray.h"

class Sphere : public Primitive
{
	private:
		Vector4D				m_centre;
		double				m_radius;

	public:
		Sphere();
		Sphere(double x, double y, double z, double r);
		~Sphere();

		inline Vector4D&		GetCentre()
		{
			return m_centre;
		}

		inline double		GetRadius()
		{
			return m_radius;
		}

		RayHitResult		IntersectByRay(Ray& ray);
};

