#include "Matrix.h"

namespace DX
{
	Matrix Matrix::ObjectLookAt(Vector3& Eye, Vector3& At, Vector3& Up)
	{
		Matrix Mat;

		Vector3 vLook = (At - Eye).Normal();
		Vector3 vRight = (vLook ^ Up).Normal();
		Vector3 vUp = (vRight ^ vLook).Normal();

		Mat._11 = vRight.x;
		Mat._12 = vRight.y;
		Mat._13 = vRight.z;
		Mat._21 = vUp.x;
		Mat._22 = vUp.y;
		Mat._23 = vUp.z;
		Mat._31 = vLook.x;
		Mat._32 = vLook.y;
		Mat._33 = vLook.z;

		return Mat;
	}
	Matrix Matrix::ViewLookAt(Vector3& Eye, Vector3& At, Vector3& Up)
	{
		Matrix Mat;
		Vector3 vLook = (At - Eye).Normal();

		float fDot = vLook | Up;
		Vector3 vUp = (Up - ( vLook * fDot )).Normal();
		Vector3 vRight = (vUp ^ vLook).Normal();

		_11 = vRight.x; _12 = vUp.x; _13 = vLook.x;
		_21 = vRight.y; _22 = vUp.y; _23 = vLook.y;
		_31 = vRight.z; _32 = vUp.z; _33 = vLook.z;
		_41 = -(Eye | vRight);
		_42 = -(Eye | vUp);
		_43 = -(Eye | vLook);

		return Mat;
	}
	void Matrix::Translation(const Vector3& v)
	{
		_41 = v.x;
		_42 = v.y;
		_43 = v.z;
	}
	void Matrix::Scale(const Vector3& v)
	{
		_11 = v.x;
		_22 = v.y;
		_33 = v.z;
	}
	void Matrix::XRotation(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);

		_22 = fCos;		_23 = fSin;
		_32 = -fSin;	_33 = fCos;
	}
	void Matrix::YRotation(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);

		_11 = fCos;		_13 = -fSin;
		_31 = fSin;		_33 = fCos;
	}
	void Matrix::ZRotation(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);

		_11 = fCos;		_12 = fSin;
		_21 = -fSin;	_22 = fCos;
	}
	Matrix Matrix::Transpose()
	{
		Matrix Mat;
		Mat._11 = _11; Mat._12 = _21; Mat._13 = _31; Mat._14 = _41;
		Mat._21 = _12; Mat._22 = _22; Mat._23 = _32; Mat._24 = _42;
		Mat._31 = _13; Mat._32 = _23; Mat._33 = _33; Mat._34 = _43;
		Mat._41 = _14; Mat._42 = _24; Mat._43 = _34; Mat._44 = _44;
		return Mat;

	}
	Matrix::Matrix()
	{ 
		Identity(); 
	}
	Matrix::~Matrix()
	{
	}
}