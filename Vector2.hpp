#pragma once
#ifndef __MATHS_VECTOR2_HPP__
#define __MATHS_VECTOR2_HPP__

namespace Math
{
	class Vector2 : public XMFLOAT2
	{
	public:
		//--------------------------------------------------------------------------
		// Constructors
		//

		Vector2() : XMFLOAT2()
		{
		}

		Vector2(float x, float y) : XMFLOAT2(x, y)
		{
		}

		explicit Vector2(const float* v) : XMFLOAT2(v)
		{
		}

		explicit Vector2(FXMVECTOR v)
		{
			XMStoreFloat2(this, v);
		}

		Vector2(const Vector2& v) : XMFLOAT2(v)
		{
		}

		Vector2(int ix, int iy) : XMFLOAT2(static_cast<float>(ix), static_cast<float>(iy))
		{
		}

		//--------------------------------------------------------------------------
		// Assignment
		//

		Vector2& operator = (FXMVECTOR v)
		{
			XMStoreFloat2(this, v);
			return *this;
		}

		Vector2& operator = (const Vector2& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		//--------------------------------------------------------------------------
		// Conversion
		//

		operator XMVECTOR () const
		{
			return XMLoadFloat2(this);
		}

		//--------------------------------------------------------------------------
		// Comparison
		//

		bool operator == (const Vector2& v) const
		{
			return x == v.x && y == v.y;
		}

		bool operator != (const Vector2& v) const
		{
			return x != v.x || y != v.y;
		}

		bool operator < (const Vector2& v) const
		{
			return x < v.x && y < v.y;
		}

		bool operator <= (const Vector2& v) const
		{
			return x <= v.x && y <= v.y;
		}

		bool operator > (const Vector2& v) const
		{
			return x > v.x && y > v.y;
		}

		bool operator >= (const Vector2& v) const
		{
			return x >= v.x && y >= v.y;
		}

		//--------------------------------------------------------------------------
		// Computation
		//

		float length() const
		{
			return sqrtf(x * x + y * y);
		}

		float length_squared() const
		{
			return x * x + y * y;
		}

		void normalise();

		Vector2 normalise() const;

		//--------------------------------------------------------------------------
		// Arithmetic Operators
		//

		Vector2 operator + (const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}

		Vector2 operator - (const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}

		Vector2 operator * (const Vector2& v) const
		{
			return Vector2(x * v.x, y * v.y);
		}

		Vector2 operator / (const Vector2& v) const
		{
			return Vector2(x / v.x, y / v.y);
		}

		Vector2 operator - () const
		{
			return Vector2(-x, -y);
		}

		Vector2 operator * (const float n) const
		{
			return Vector2(x * n, y * n);
		}

		friend Vector2 operator * (const float n, const Vector2& v)
		{
			return Vector2(v.x * n, v.y * n);
		}

		Vector2 operator / (const float n) const
		{
			return Vector2(x / n, y / n);
		}

		Vector2& operator += (const Vector2& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vector2& operator -= (const Vector2& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		Vector2& operator *= (const Vector2& v)
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}

		Vector2& operator /= (const Vector2& v)
		{
			x /= v.x;
			y /= v.y;
			return *this;
		}

		Vector2& operator *= (const float n)
		{
			x *= n;
			y *= n;
			return *this;
		}

		Vector2& operator /= (const float n)
		{
			x /= n;
			y /= n;
			return *this;
		}

		//--------------------------------------------------------------------------
		// Auxilliary Functions
		//

		static Vector2 lerp(const Vector2& a, const Vector2& b, float t);

		static Vector2 minimise(const Vector2& a, const Vector2& b);

		static Vector2 maximise(const Vector2& a, const Vector2& b);

		//--------------------------------------------------------------------------
		// Constants
		//

		static const Vector2 ZERO;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;
	};

} // namespace Math

#endif // __MATHS_VECTOR2_HPP__
