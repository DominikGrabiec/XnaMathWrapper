#include "Precompiled.hpp"
#include "BoundingSphere.hpp"
#include "Intersect.hpp"
#include "Line.hpp"

namespace Math
{

	BoundingSphere BoundingSphere::compute_containing_sphere(const BoundingSphere& a, const BoundingSphere& b)
	{
		Intersect::VolumeResult result = Intersect::test(a, b);

		if (result == Intersect::VOLUME_CONTAINS) // A contains B
		{
			return a;
		}

		if (result == Intersect::VOLUME_CONTAINED) // B contains A
		{
			return b;
		}

		Line line(a.center(), b.center());
		line.extend(a.radius(), b.radius());
		return BoundingSphere(line.mid_point(), line.length() / 2);
	}
}
