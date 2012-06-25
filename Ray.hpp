#pragma once
#ifndef __MATHS_RAY_HPP__
#define __MATHS_RAY_HPP__

#include "Vector3.hpp"

namespace Math
{

	class Ray
	{
	private:
		// The values are private because we want to keep the direction vector normalised
		Vector3 mOrigin;
		Vector3 mDirection;

	public:
		Ray() :	mDirection(Vector3::UNIT_Z)
		{
		}

		Ray(const Vector3& origin, const Vector3& direction) : 
			mOrigin(origin),
			mDirection(direction)
		{
			mDirection.normalise();
		}

		Ray(const Ray& ray) :
			mOrigin(ray.mOrigin),
			mDirection(ray.mDirection)
		{
		}

		
		Ray& operator = (const Ray& ray)
		{
			mOrigin = ray.mOrigin;
			mDirection = ray.mDirection;
			return *this;
		}


		bool operator == (const Ray& ray) const
		{
			return mOrigin == ray.mOrigin && mDirection == ray.mDirection;
		}

		bool operator != (const Ray& ray) const
		{
			return mOrigin != ray.mOrigin || mDirection != ray.mDirection;
		}


		Vector3 point_at(float t) const
		{
			return mOrigin + mDirection * t;
		}

		Vector3 operator * (float t) const
		{
			return mOrigin + mDirection * t;
		}

		friend Vector3 operator * (float t, const Ray& ray)
		{
			return ray.mOrigin + ray.mDirection * t;
		}


		void origin(const Vector3& o)
		{
			mOrigin = o;
		}

		const Vector3& origin() const
		{
			return mOrigin;
		}


		void direction(const Vector3& d)
		{
			mDirection = d;
			mDirection.normalise();
		}

		const Vector3& direction() const
		{
			return mDirection;
		}
	};

} // namespace Math

#endif // __MATHS_RAY_HPP__
