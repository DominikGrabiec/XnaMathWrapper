#pragma once
#ifndef __MATHS_MATRIX_HPP__
#define __MATHS_MATRIX_HPP__

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Quaternion.hpp"

namespace Math
{
	class Matrix : public XMMATRIX
	{
	public:
		//--------------------------------------------------------------------------
		// Constructors
		//

		Matrix() : XMMATRIX() 
		{
		}

		Matrix(XMVECTOR _1, XMVECTOR _2, XMVECTOR _3, XMVECTOR _4) : XMMATRIX(_1, _2, _3, _4)
		{
		}

		Matrix(float _11, float _12, float _13, float _14,
			   float _21, float _22, float _23, float _24,
			   float _31, float _32, float _33, float _34,
			   float _41, float _42, float _43, float _44) : XMMATRIX(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44)
		{
		}

		explicit Matrix(const float* v) : XMMATRIX(v) 
		{
		}

		explicit Matrix(CXMMATRIX m) : XMMATRIX(m) 
		{
		}

		Matrix(const Matrix& matrix) : XMMATRIX(matrix)
		{
		}

		//--------------------------------------------------------------------------
		// Assignment
		//

		Matrix& operator = (CXMMATRIX m)
		{
			if (&m != this)
			{
				*static_cast<XMMATRIX*>(this) = m;
			}
			return *this;
		}

		Matrix& operator = (const Matrix& m)
		{
			if (&m != this)
			{
				*static_cast<XMMATRIX*>(this) = m;
			}
			return *this;
		}

		//--------------------------------------------------------------------------
		// Accessors
		//

		float& operator () (int row, int column)
		{
			return m[row][column];
		}

		float operator () (int row, int column) const
		{
			return m[row][column];
		}

		Vector4 row(uint_t i) const;

		Vector4 column(uint_t i) const;

		//--------------------------------------------------------------------------
		// Arithmetic Operators
		//

		Matrix operator * (const Matrix& m) const
		{
			return static_cast<Matrix>(XMMatrixMultiply(*this, m));
		}

		Matrix operator *= (const Matrix& m)
		{
			*this = (XMMatrixMultiply(*this, m));
			return *this;
		}

		//--------------------------------------------------------------------------
		// Computation
		//

		float determinant() const
		{
			return XMVectorGetX(XMMatrixDeterminant(*this));
		}

		bool decompose(Quaternion& rotation, Vector3& translation, Vector3& scale);

		void invert(float* determinant = nullptr)
		{
			XMVECTOR det;
			*this = XMMatrixInverse(&det, *this);
			if (determinant)
			{
				*determinant = XMVectorGetX(det);
			}
		}

		Matrix inverse(float* determinant = nullptr) const
		{
			XMVECTOR det;
			XMMATRIX mat = XMMatrixInverse(&det, *this);
			if (determinant)
			{
				*determinant = XMVectorGetX(det);
			}
			return static_cast<Matrix>(mat);
		}

		void transpose()
		{
			*this = XMMatrixTranspose(*this);
		}

		Matrix transpose() const
		{
			return static_cast<Matrix>(XMMatrixTranspose(*this));
		}

		Vector3 transform(const Vector3& v) const
		{
			return Vector3(XMVector3Transform(v, *this));
		}

		Vector4 transform(const Vector4& v) const
		{
			return Vector4(XMVector4Transform(v, *this));
		}

		bool is_identity() const
		{
			return XMMatrixIsIdentity(*this) == TRUE;
		}

		//--------------------------------------------------------------------------
		// Constants
		//

		static const Matrix IDENTITY;

		//--------------------------------------------------------------------------
		// Auxilliary Functions
		//

		static Matrix rotation_axis(const Vector3& axis, float angle)
		{
			return static_cast<Matrix>(XMMatrixRotationAxis(axis, angle));
		}

		static Matrix rotation_roll_pitch_yaw(float pitch, float yaw, float roll)
		{
			return static_cast<Matrix>(XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
		}

		static Matrix rotation_quaternion(const Quaternion& q)
		{
			return static_cast<Matrix>(XMMatrixRotationQuaternion(q));
		}

		static Matrix scaling(float x, float y, float z)
		{
			return static_cast<Matrix>(XMMatrixScaling(x, y, z));
		}

		static Matrix scaling(const Vector3& v)
		{
			return static_cast<Matrix>(XMMatrixScalingFromVector(v));
		}

		static Matrix translation(float x, float y, float z)
		{
			return static_cast<Matrix>(XMMatrixTranslation(x, y, z));
		}

		static Matrix translation(const Vector3& v)
		{
			return static_cast<Matrix>(XMMatrixTranslationFromVector(v));
		}

		static Matrix affine_transformation(const Vector3& translation, const Quaternion& rotation)
		{
			return static_cast<Matrix>(XMMatrixAffineTransformation(XMVectorSplatOne(), XMVectorZero(), rotation, translation));
		}

		static Matrix affine_transformation(const Vector3& translation, const Quaternion& rotation, const Vector3& scale, const Vector3& rotation_centre = Vector3::ZERO)
		{
			return static_cast<Matrix>(XMMatrixAffineTransformation(scale, rotation_centre, rotation, translation));
		}

		static Matrix look_at(const Vector3& position, const Vector3& target, const Vector3& up)
		{
			return static_cast<Matrix>(XMMatrixLookAtLH(position, target, up));
		}

		static Matrix orthographic(float width, float height, float nearZ, float farZ)
		{
			return static_cast<Matrix>(XMMatrixOrthographicLH(width, height, nearZ, farZ));
		}

		static Matrix perspective(float width, float height, float nearZ, float farZ)
		{
			return static_cast<Matrix>(XMMatrixPerspectiveLH(width, height, nearZ, farZ));
		}

		static Matrix perspective_fov(float fov, float aspect, float nearZ, float farZ)
		{
			return static_cast<Matrix>(XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ));
		}
	};

} // namespace Math

#endif // __MATHS_MATRIX_HPP__
