#include "Precompiled.hpp"
#include "Plane.hpp"

namespace Math
{
	const Plane Plane::XZ_PLANE(Vector3::ZERO, Vector3::UNIT_Y);
	const Plane Plane::XY_PLANE(Vector3::ZERO, Vector3::UNIT_Z);
	const Plane Plane::YZ_PLANE(Vector3::ZERO, Vector3::UNIT_X);


	float Plane::dot(const Vector3& v) const
	{
		return XMVectorGetX(XMPlaneDotCoord(*this, v));
	}

	float Plane::dot(const Vector4& v) const
	{
		return XMVectorGetX(XMPlaneDot(*this, v));
	}

	float Plane::dot_normal(const Vector3& v) const
	{
		return XMVectorGetX(XMPlaneDotNormal(*this, v));
	}

	float Plane::distance(const Vector3& v) const
	{
		return XMVectorGetX(XMPlaneDotCoord(*this, v));
	}
}
