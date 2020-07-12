#pragma once
#include "Vector.h"

namespace DX
{
	struct float4X4
	{
		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};
	};
	class Matrix : public float4X4
	{
	public:
		Matrix ObjectLookAt(
			Vector3& Eye,
			Vector3& At,
			Vector3& Up);
		Matrix ViewLookAt(
			Vector3& Eye,
			Vector3& At,
			Vector3& Up);
		void Identity()
		{
			_11 = _12 = _13 = _14 = 0.0f;
			_21 = _22 = _23 = _24 = 0.0f;
			_31 = _32 = _33 = _34 = 0.0f;
			_41 = _42 = _43 = _44 = 0.0f;
			_11 = _22 = _33 = _44 = 1.0f;
		}
		void Translation(const Vector3& v);
		void Scale(const Vector3& v);
		void XRotation(float fRadian);
		void YRotation(float fRadian);
		void ZRotation(float fRadian);
		Matrix Transpose();

		Matrix();
		~Matrix();
	};
}
