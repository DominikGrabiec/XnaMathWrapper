#include "Precompiled.hpp"
#include "Vector4.hpp"

namespace Math
{
	const Vector4 Vector4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
	const Vector4 Vector4::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);
	const Vector4 Vector4::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);


	float Vector4::length() const
	{
		return XMVectorGetX(XMVector4Length(*this));
	}

	float Vector4::length_squared() const
	{
		return XMVectorGetX(XMVector4LengthSq(*this));
	}

	void Vector4::normalise()
	{
		*this = XMVector4Normalize(*this);
	}

	Vector4 Vector4::normalise() const
	{
		return Vector4(XMVector4Normalize(*this));
	}

	float Vector4::dot(const Vector4& v) const
	{
		return XMVectorGetX(XMVector4Dot(*this, v));
	}

	Vector4 Vector4::cross(const Vector4& a, const Vector4& b) const
	{
		return Vector4(XMVector4Cross(*this, a, b));
	}

	Vector4 Vector4::lerp(const Vector4& a, const Vector4& b, float t)
	{
		return Vector4(XMVectorLerp(a, b, t));
	}

	Vector4 Vector4::minimise(const Vector4& a, const Vector4& b)
	{
		return Vector4(XMVectorMin(a, b));
	}

	Vector4 Vector4::maximise(const Vector4& a, const Vector4& b)
	{
		return Vector4(XMVectorMax(a, b));
	}

} // namespace Math
