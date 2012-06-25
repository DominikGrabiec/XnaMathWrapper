#include "Precompiled.hpp"
#include "Matrix.hpp"

namespace Math
{
	const Matrix Matrix::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
								  0.0f, 1.0f, 0.0f, 0.0f,
								  0.0f, 0.0f, 1.0f, 0.0f,
								  0.0f, 0.0f, 0.0f, 1.0f);

	bool Matrix::decompose(Quaternion& rotation, Vector3& translation, Vector3& scale)
	{
		XMVECTOR s;
		XMVECTOR r;
		XMVECTOR t;
		const bool result = XMMatrixDecompose(&s, &r, &t, *this) == TRUE;
		rotation = r;
		translation = t;
		scale = s;
		return result;
	}

	Vector4 Matrix::row(uint_t i) const
	{
		XMASSERT(i < 4);
		return Vector4(m[i][0], m[i][1], m[i][2], m[i][3]);
	}

	Vector4 Matrix::column(uint_t i) const
	{
		XMASSERT(i < 4);
		return Vector4(m[0][i], m[1][i], m[2][i], m[3][i]);
	}
}
