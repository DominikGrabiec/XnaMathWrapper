#pragma once
#ifndef __MATHS_PLANE_HPP__
#define __MATHS_PLANE_HPP__

#include "Vector3.hpp"
#include "Vector4.hpp"

namespace Math
{
	class Plane : public XMFLOAT4A
	{
	public:
		//--------------------------------------------------------------------------
		// Constructors
		//

		Plane() : XMFLOAT4A()
		{
		}

		Plane(float x, float y, float z, float w)
		{ 
			XMStoreFloat4A(this, XMPlaneNormalize(XMVectorSet(x, y, z, w)));
		}

		Plane(const Vector3& point, const Vector3& normal)
		{
			// ASSUME normal is normalised
			XMStoreFloat4A(this, XMPlaneFromPointNormal(point, normal));
		}

		Plane(const Vector3& a, const Vector3& b, const Vector3& c)
		{
			XMStoreFloat4A(this, XMPlaneFromPoints(a, b, c));
		}

		explicit Plane(const float* v)
		{ 
			XMStoreFloat4A(this, XMPlaneNormalize(XMVectorSet(v[0], v[1], v[2], v[3])));
		}

		explicit Plane(FXMVECTOR v)
		{
			XMStoreFloat4A(this, XMPlaneNormalize(v));
		}

		Plane(const Plane& p) : XMFLOAT4A(p)
		{
		}

		//--------------------------------------------------------------------------
		// Assignment
		//

		Plane& operator = (FXMVECTOR v)
		{
			XMStoreFloat4A(this, XMPlaneNormalize(v));
			return *this;
		}

		Plane& operator = (const Plane& p)
		{
			x = p.x;
			y = p.y;
			z = p.z;
			w = p.w;
			return *this;
		}

		//--------------------------------------------------------------------------
		// Conversion
		//

		operator XMVECTOR () const
		{
			return XMLoadFloat4A(this);
		}

		//--------------------------------------------------------------------------
		// Comparison
		//

		bool operator == (const Plane& plane)
		{
			return x == plane.x && y == plane.y && z == plane.z && w == plane.w;
		}

		bool operator != (const Plane& plane)
		{
			return x != plane.x && y != plane.y && z != plane.z && w != plane.w;
		}

		//--------------------------------------------------------------------------
		// Computation
		//

		float dot(const Vector3& v) const;

		float dot(const Vector4& v) const;

		float dot_normal(const Vector3& v) const;

		float distance(const Vector3& v) const;

		//--------------------------------------------------------------------------
		// Constants
		//

		static const Plane XZ_PLANE;
		static const Plane XY_PLANE;
		static const Plane YZ_PLANE;
	};

} // namespace Math

#endif // __MATHS_PLANE_HPP__
