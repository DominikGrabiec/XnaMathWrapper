#include "Precompiled.hpp"
#include "Frustum.hpp"

#include "Matrix.hpp"

namespace Math
{
	Frustum::Frustum()
	{
	}

	void Frustum::set_from(const Matrix& matrix)
	{
		const Vector4 m1 = matrix.column(0);
		const Vector4 m2 = matrix.column(1);
		const Vector4 m3 = matrix.column(2);
		const Vector4 m4 = matrix.column(3);

		mPlanes[FRUSTUM_PLANE_NEAR] = Plane(m3);
		mPlanes[FRUSTUM_PLANE_FAR] = Plane(m4 - m3);
		mPlanes[FRUSTUM_PLANE_LEFT] = Plane(m4 + m1);
		mPlanes[FRUSTUM_PLANE_TOP] = Plane(m4 - m2);
		mPlanes[FRUSTUM_PLANE_RIGHT] = Plane(m4 - m1);
		mPlanes[FRUSTUM_PLANE_BOTTOM] = Plane(m4 + m2);
	}

	const Plane& Frustum::get_plane(FrustumPlane plane_enum) const
	{
		return mPlanes[plane_enum];
	}

	template <class Object> Intersect::PlaneResult Frustum::test(const Object& object) const
	{
		uint_t inside_count = 0;

		for (uint_t plane = 0; plane < FRUSTUM_PLANE_COUNT; ++plane)
		{
			const Intersect::PlaneResult result = Intersect::test(mPlanes[plane], object);

			if (result == Intersect::OUTSIDE_PLANE) 
			{
				return Intersect::OUTSIDE_PLANE;
			}

			if (result == Intersect::INSIDE_PLANE) 
			{
				++inside_count;
			}
		}

		return (inside_count == FRUSTUM_PLANE_COUNT) ? Intersect::INSIDE_PLANE : Intersect::INTERSECTS_PLANE;
	}
}
