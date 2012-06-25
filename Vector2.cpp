#include "Precompiled.hpp"
#include "Vector2.hpp"

namespace Math
{
	const Vector2 Vector2::ZERO(0.0f, 0.0f);
	const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
	const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);

	void Vector2::normalise()
	{
		*this = XMVector2Normalize(*this);
	}

	Vector2 Vector2::normalise() const
	{
		return Vector2(XMVector2Normalize(*this));
	}

	Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(XMVectorLerp(a, b, t));
	}

	Vector2 Vector2::minimise(const Vector2& a, const Vector2& b)
	{
		return Vector2(XMVectorMin(a, b));
	}

	Vector2 Vector2::maximise(const Vector2& a, const Vector2& b)
	{
		return Vector2(XMVectorMax(a, b));
	}

} // namespace Math
