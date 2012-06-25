#pragma once
#ifndef __FRUSTUM_HPP__
#define __FRUSTUM_HPP__

#include "Plane.hpp"
#include "Intersect.hpp"

namespace Math
{
	class Matrix;
	class BoundingSphere;

	class Frustum
	{
	public:
		enum FrustumPlane : uint_t
		{
			FRUSTUM_PLANE_NEAR,
			FRUSTUM_PLANE_FAR,
			FRUSTUM_PLANE_LEFT,
			FRUSTUM_PLANE_TOP,
			FRUSTUM_PLANE_RIGHT,
			FRUSTUM_PLANE_BOTTOM,

			FRUSTUM_PLANE_COUNT
		};

	private:
		Plane mPlanes[FRUSTUM_PLANE_COUNT];

	public:
		Frustum();

		void set_from(const Matrix& matrix);

		const Plane& get_plane(FrustumPlane plane_enum) const;

		// BoundingBox, BoundingSphere
		template <class Object> Intersect::PlaneResult test(const Object& object) const;
	};

} // namespace Math


#endif // __FRUSTUM_HPP__
