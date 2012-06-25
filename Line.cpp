#include "Precompiled.hpp"
#include "Line.hpp"

namespace Math
{
	float Line::length() const
	{
		return XMVectorGetX(XMVector3Length(XMVectorSubtract(end_point, start_point)));
	}

	float Line::length_squared() const
	{
		return XMVectorGetX(XMVector3LengthSq(XMVectorSubtract(end_point, start_point)));
	}

	Vector3 Line::direction() const
	{
		return Vector3(XMVector3Normalize(XMVectorSubtract(end_point, start_point)));
	}

	Vector3 Line::mid_point() const
	{
		static const float HALF = 0.5f;
		return Vector3(XMVectorMultiply(XMVectorSubtract(end_point, start_point), XMVectorReplicate(HALF)));
	}

	void Line::extend(float start_amount, float end_amount)
	{
		XMVECTOR start = start_point;
		XMVECTOR end = end_point;
		XMVECTOR dir = XMVector3Normalize(XMVectorSubtract(end, start));
		start_point = XMVectorSubtract(start, XMVectorMultiply(dir, XMVectorReplicate(start_amount)));
		end_point = XMVectorAdd(end, XMVectorMultiply(dir, XMVectorReplicate(end_amount)));
	}
}
