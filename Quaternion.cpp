#include "Precompiled.hpp"
#include "Quaternion.hpp"


namespace Math
{
	const Quaternion Quaternion::IDENTITY(0.0f, 0.0f, 0.0f, 1.0f);


	Vector3 Quaternion::transform(const Vector3& vector) const
	{
		XMVECTOR self = *this;
		return Vector3(XMQuaternionMultiply(XMQuaternionMultiply(self, vector), XMQuaternionConjugate(self)));
	}
}
