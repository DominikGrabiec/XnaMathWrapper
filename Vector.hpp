#pragma once
#ifndef __MATHS_VECTOR_HPP__
#define __MATHS_VECTOR_HPP__

namespace Math
{
	class Vector2 : public XMFLOAT2
	{
	public:
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

		operator XMVECTOR () const
		{
			return XMLoadFloat2(this);
		}
	};

	class Vector3 : public XMFLOAT3
	{
	public:
		Vector3() : XMFLOAT3()
		{
		}

		Vector3(float x, float y, float z) : XMFLOAT3(x, y, z)
		{
		}

		explicit Vector3(const float* v) : XMFLOAT3(v)
		{
		}

		explicit Vector3(FXMVECTOR v)
		{
			XMStoreFloat3(this, v);
		}

		Vector3(const Vector3& v) : XMFLOAT3(v)
		{
		}

		Vector3& operator = (FXMVECTOR v)
		{
			XMStoreFloat3(this, v);
			return *this;
		}

		Vector3& operator = (const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			return *this;
		}

		operator XMVECTOR () const
		{
			return XMLoadFloat3(this);
		}
	};

	class Vector4 : public XMFLOAT4
	{
	public:
		Vector4() : XMFLOAT4()
		{
		}

		Vector4(float x, float y, float z, float w) : XMFLOAT4(x, y, z, w)
		{
		}

		explicit Vector4(const float* v) : XMFLOAT4(v)
		{
		}

		explicit Vector4(FXMVECTOR v)
		{
			XMStoreFloat4(this, v);
		}

		Vector4(const Vector4& v) : XMFLOAT4(v)
		{
		}

		Vector4& operator = (FXMVECTOR v)
		{
			XMStoreFloat4(this, v);
			return *this;
		}

		Vector4& operator = (const Vector4& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = v.w;
			return *this;
		}

		operator XMVECTOR () const
		{
			return XMLoadFloat4(this);
		}
	};

} // namespace Math

#endif // __MATHS_VECTOR_HPP__
