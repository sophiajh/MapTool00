#pragma once
#include <Windows.h>
#include <math.h>

namespace DX
{
#define ErrorRange ((float)0.001f)
#define PIValue		((float)3.141592654f)
#define RadianToDegree(radian) (radian*(180.0f/PIValue))
#define DegreeToRadian(degree) (degree*(PIValue/180.0f))

	struct float2
	{
		union
		{
			struct { float x, y; };
			float v[2];
		};
	};

	struct float3
	{
		union
		{
			struct { float x, y, z; };
			float v[3];
		};
	};

	struct float4
	{
		union
		{
			struct { float x, y, z, w; };
			float v[4];
		};
	};

	class Vector2 : public float2
	{
	public:
		Vector2(const Vector2& v);
		Vector2(float fx, float fy);
	public:
		Vector2();
		~Vector2();
	};

	class Vector3 : public float3
	{
	public:
		Vector3(const Vector3& v);
		Vector3(float fx, float fy, float fz);
	public:
		Vector3 operator + (Vector3 const &v);
		Vector3 operator - (Vector3 const &v);
		Vector3 operator * (float const &fScalar);
		Vector3 operator / (float const &fScalar);
		float	operator | (Vector3 const &v); //내적
		Vector3 operator ^ (Vector3 const &v); //외적
		bool	operator == (Vector3 const &v);

		float	Length();
		float	LengthSquared();
		Vector3 Normal();
		float	Angle(Vector3& v);
	public:
		Vector3();
		~Vector3();
	};

	class Vector4 : public float4
	{
	public:
		Vector4(const Vector4& v);
		Vector4(float fx, float fy, float fz, float fw);
	public:
		Vector4();
		~Vector4();
	};

}