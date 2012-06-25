#pragma once
#ifndef __MATHS_QUATERNION_HPP__
#define __MATHS_QUATERNION_HPP__

#include "Vector3.hpp"
#include "Vector4.hpp"

namespace Math
{

	class Quaternion : public XMFLOAT4A
	{
	public:
		//--------------------------------------------------------------------------
		// Constructors
		//

		Quaternion()
		{
			XMStoreFloat4A(this, XMQuaternionIdentity());
		}

		Quaternion(float x, float y, float z, float w) : XMFLOAT4A(z, y, z, w) 
		{
		}

		Quaternion(float yaw, float pitch, float roll)
		{
			XMStoreFloat4A(this, XMQuaternionRotationRollPitchYaw(pitch, yaw, roll));
		}

		Quaternion(const Vector3& axis, float angle)
		{
			XMStoreFloat4A(this, XMQuaternionRotationAxis(axis, angle));
		}

		explicit Quaternion(const float* values) : XMFLOAT4A(values) 
		{
		}

		explicit Quaternion(FXMVECTOR v) 
		{
			XMStoreFloat4A(this, v);
		}

		Quaternion(const Quaternion& q) : XMFLOAT4A(q) 
		{
		}

		//--------------------------------------------------------------------------
		// Assignment
		//

		Quaternion& operator = (FXMVECTOR v)
		{
			XMStoreFloat4A(this, v);
			return *this;
		}

		Quaternion& operator = (const Quaternion& q)
		{
			x = q.x;
			y = q.y;
			z = q.z;
			w = q.w;
			return *this;
		}

		//--------------------------------------------------------------------------
		// Conversion
		//

		operator XMVECTOR () const
		{
			return XMLoadFloat4A(this);
		}

		//--------------------------------------------------------------------------
		// Comparison
		//

		bool operator == (const Quaternion& q) const
		{
			return x == q.x && y == q.y && z == q.z && w == q.w;
		}

		bool operator != (const Quaternion& q) const
		{
			return x != q.x || y != q.y || z != q.z || w != q.w;
		}

		//--------------------------------------------------------------------------
		// Inspection
		//

		bool is_identity() const
		{
			return XMQuaternionIsIdentity(*this) == TRUE;
		}

		//--------------------------------------------------------------------------
		// Computation
		//

		void from_axis_angle(const Vector3& axis, float angle)
		{
			XMStoreFloat4A(this, XMQuaternionRotationAxis(axis, angle));
		}

		void to_axis_angle(Vector3& axis, float& angle) const
		{
			XMVECTOR a;
			XMQuaternionToAxisAngle(&a, &angle, *this);
			axis = a;
		}

		float dot(const Quaternion& q) const
		{
			return XMVectorGetX(XMQuaternionDot(*this, q));
		}

		float length() const
		{
			return XMVectorGetX(XMQuaternionLength(*this));
		}

		float length_squared() const
		{
			return XMVectorGetX(XMQuaternionLengthSq(*this));
		}

		void normalise()
		{
			XMStoreFloat4A(this, XMQuaternionNormalize(*this));
		}

		Quaternion conjugate() const
		{
			return Quaternion(XMQuaternionConjugate(*this));
		}

		Quaternion inverse() const
		{
			return Quaternion(XMQuaternionInverse(*this));
		}

		Quaternion exp() const
		{
			return Quaternion(XMQuaternionExp(*this));
		}

		Quaternion ln() const
		{
			return Quaternion(XMQuaternionLn(*this));
		}

		Quaternion slerp(const Quaternion& q, float t) const
		{
			return Quaternion(XMQuaternionSlerp(*this, q, t));
		}

		Vector3 transform(const Vector3& v) const;

		//--------------------------------------------------------------------------
		// Constants
		//

		static const Quaternion IDENTITY;
	};

} // namespace Math

#endif // __MATHS_QUATERNION_HPP__
