#include "Precompiled.hpp"
#include "Vector3.hpp"

namespace Math
{
	const Vector3 Vector3::ZERO(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);


	float Vector3::length() const
	{
		return XMVectorGetX(XMVector3Length(*this));
	}

	float Vector3::length_squared() const
	{
		return XMVectorGetX(XMVector3LengthSq(*this));
	}

	void Vector3::normalise()
	{
		*this = XMVector3Normalize(*this);
	}

	Vector3 Vector3::normalise() const
	{
		return Vector3(XMVector3Normalize(*this));
	}

	float Vector3::dot(const Vector3& v) const
	{
		return XMVectorGetX(XMVector3Dot(*this, v));
	}

	Vector3 Vector3::cross(const Vector3& v) const
	{
		return Vector3(XMVector3Cross(*this, v));
	}

	Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, float t)
	{
		return Vector3(XMVectorLerp(a, b, t));
	}

	Vector3 Vector3::minimise(const Vector3& a, const Vector3& b)
	{
		return Vector3(XMVectorMin(a, b));
	}

	Vector3 Vector3::maximise(const Vector3& a, const Vector3& b)
	{
		return Vector3(XMVectorMax(a, b));
	}

} // namespace Math
