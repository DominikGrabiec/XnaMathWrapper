#pragma once
#ifndef __MATHS_BOUNDINGSPHERE_HPP__
#define __MATHS_BOUNDINGSPHERE_HPP__

#include "Vector3.hpp"

#include <type_traits>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

namespace Math
{

	class BoundingSphere
	{
	private:
		Vector3 mCenter;
		float mRadius;

	public:
		//--------------------------------------------------------------------------
		// Constructors
		//

		BoundingSphere() : mRadius(0.0f)
		{
		}

		BoundingSphere(const Vector3& center, float radius) : mCenter(center), mRadius(std::abs(radius))
		{
		}

		BoundingSphere(const BoundingSphere& sphere) : mCenter(sphere.mCenter), mRadius(sphere.mRadius)
		{
		}

		//--------------------------------------------------------------------------
		// Assignment
		//

		BoundingSphere& operator = (const BoundingSphere& sphere)
		{
			mCenter = sphere.mCenter;
			mRadius = sphere.mRadius;
			return *this;
		}

		//--------------------------------------------------------------------------
		// Comparison
		//

		bool operator == (const BoundingSphere& sphere) const
		{
			return mCenter == sphere.mCenter && mRadius == sphere.mRadius;
		}

		bool operator != (const BoundingSphere& sphere) const
		{
			return mCenter != sphere.mCenter || mRadius != sphere.mRadius;
		}

		bool contains(const Vector3& point) const
		{
			return Vector3(mCenter - point).length_squared() <= mRadius * mRadius;
		}

		bool is_empty()
		{
			return mRadius <= FLT_EPSILON;
		}

		//--------------------------------------------------------------------------
		// Accessors
		//

		void set(const Vector3& center, float radius)
		{
			mCenter = center;
			mRadius = std::abs(radius);
		}

		void center(const Vector3& center)
		{
			mCenter = center;
		}

		const Vector3& center() const
		{
			return mCenter;
		}

		void radius(float radius)
		{
			mRadius = std::abs(radius);
		}

		float radius() const
		{
			return mRadius;
		}

		static BoundingSphere compute_containing_sphere(const BoundingSphere& a, const BoundingSphere& b);

		template <class Iterator>
		typename std::enable_if<std::is_same<typename std::iterator_traits<Iterator>::value_type, BoundingSphere>::value, BoundingSphere>::type 
			static compute_containing_sphere(Iterator begin, Iterator end)
		{
			if (begin != end)
			{
				BoundingSphere bounds = *begin++;
				return std::accumulate(begin, end, bounds, std::ptr_fun(&compute_containing_sphere));
			}

			return BoundingSphere();
		}
	};

} // namespace Math

#endif // __MATHS_BOUNDINGSPHERE_H__
