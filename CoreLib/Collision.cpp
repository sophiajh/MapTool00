#include "Collision.h"

bool Collision::RectInPtr(RECT rt1, POINT rt2)
{
	 if (rt1.left < rt2.x && rt2.x < rt1.right)
	 {
		 if (rt1.bottom > rt2.y && rt2.y > rt1.top)
			 return true;
	 }
	return false;
}

bool Collision::RectInPtr(RECT rt1, xPoint rt2)
{
	if (rt1.left < rt2.x && rt2.x < rt1.right)
	{
		if (rt1.bottom > rt2.y && rt2.y > rt1.top)
			return true;
	}
	return false;
}

bool	Collision::VertexInPlane(D3DXVECTOR3 v3LeftTop, D3DXVECTOR3 v3RightBottom, D3DXVECTOR2 vMouse)
{
	if (vMouse.x >= v3LeftTop.x && vMouse.x <= v3RightBottom.x)
	{
		if (vMouse.y <= v3LeftTop.y && vMouse.y >= v3RightBottom.y)
		{
			return true;
		}
	}
	return false;
}

void Collision::Interrupt(xPoint& pt1, RECT rt1 , xPoint& pt2, RECT rt2) //objrt 두개 각각 + 중심점 pt 두개
{
	float intercept; //절편

	intercept = pt1.y - pt1.x;
	if (pt2.x + intercept > pt2.y)
	{
		intercept = pt1.y + pt1.x;
		if (-pt2.x + intercept > pt2.y)
		{
			pt1.y += (rt1.bottom / 2 )* g_fSecondPerFrame;//Object2가 위쪽
			pt2.y -= (rt2.bottom / 2 )* g_fSecondPerFrame;
		}
		else
		{
			pt1.x -= (rt1.right / 2)* g_fSecondPerFrame	;//Object2가오른쪽
			pt2.x += (rt2.right / 2) * g_fSecondPerFrame;
		}
	}
	else
	{
		intercept = pt1.y + pt1.x;

		if (-pt2.x + intercept > pt2.y)
		{
			pt1.x += (rt1.right / 2) * g_fSecondPerFrame;//Object2가 왼쪽
			pt2.x -= (rt2.right / 2)* g_fSecondPerFrame;
		}
		else
		{
			pt1.y -= (rt1.bottom / 2) * g_fSecondPerFrame;//Object2가 아래쪽
			pt2.y += (rt2.bottom / 2) * g_fSecondPerFrame;
		}
	}
}

bool Collision::RectInRect(RECT rt1, RECT rt2)
{
	POINT rt1center;
	POINT rt2center;
	
	rt1center.x = (rt1.right + rt1.left)/2;
	rt1center.y = (rt1.bottom + rt1.top)/2;
	rt2center.x = (rt2.right + rt2.left)/2;
	rt2center.y = (rt2.bottom + rt2.top)/2;

	POINT rt1Radius;
	POINT rt2Radius;

	rt1Radius.x = rt1.right - rt1center.x;
	rt1Radius.y = rt1.bottom - rt1center.y;
	rt2Radius.x = rt2.right - rt2center.x;
	rt2Radius.y = rt2.bottom - rt2center.y;

	POINT rtDistance;
	rtDistance.x = abs(rt2center.x - rt1center.x);
	rtDistance.y = abs(rt2center.y - rt1center.y);

	if (rtDistance.x < rt1Radius.x + rt2Radius.x) 
	{
		if (rtDistance.y < rt1Radius.y + rt2Radius.y)
		{
	
			return true;
		}
	}
	return false;
}

bool Collision::SphereInSphere(RECT rt1, RECT rt2) //좌표에 길이 받음!~
{
	POINT c0, c1;
	float r0, r1, fDistance;

	c0.x = (rt1.left + rt1.right) / 2;
	c0.y = (rt1.top + rt1.bottom) / 2;
	c1.x = (rt2.left + rt2.right) / 2;
	c1.y = (rt2.top + rt2.bottom) / 2;

	fDistance = sqrt((c0.x - c1.x) * (c0.x - c1.x) + (c0.y - c1.y) * (c0.y - c1.y));

	r0 = sqrt((rt1.right - rt1.left) * (rt1.right - rt1.left) + (rt1.bottom - rt1.top) * (rt1.bottom - rt1.top)) / 2;
	r1 = sqrt((rt2.right - rt2.left) * (rt2.right - rt2.left) + (rt2.bottom - rt2.top) * (rt2.bottom - rt2.top)) / 2;

	if (r0 + r1 > fDistance)
	{
		return true;
	}
	return false;
}

bool Collision::RayToAABB(Ray* pRay, KJHBOX* pBox)
{
	D3DXVECTOR3 vDir = pRay->Direction;
	D3DXVECTOR3 tMin;
	tMin.x = (pBox->vMin.x - pRay->Origin.x) / (vDir.x + 0.0001f);
	tMin.y = (pBox->vMin.y - pRay->Origin.y) / (vDir.y + 0.0001f);
	tMin.z = (pBox->vMin.z - pRay->Origin.z) / (vDir.z + 0.0001f);
	D3DXVECTOR3 tMax;
	tMax.x = (pBox->vMax.x - pRay->Origin.x) / (vDir.x + 0.0001f);
	tMax.y = (pBox->vMax.y - pRay->Origin.y) / (vDir.y + 0.0001f);
	tMax.z = (pBox->vMax.z - pRay->Origin.z) / (vDir.z + 0.0001f);

	D3DXVECTOR3 real_Min;
	real_Min.x = min(tMin.x, tMax.x);
	real_Min.y = min(tMin.y, tMax.y);
	real_Min.z = min(tMin.z, tMax.z);

	D3DXVECTOR3 real_Max;
	real_Max.x = max(tMin.x, tMax.x);
	real_Max.y = max(tMin.y, tMax.y);
	real_Max.z = max(tMin.z, tMax.z);

	float minmax = min(min(real_Max.x, real_Max.y), real_Max.z);
	float maxmin = max(max(real_Min.x, real_Min.y), real_Min.z);

	if (minmax >= maxmin)
	{
		return true;
	}
	return false;
}


Collision::Collision()
{
}


Collision::~Collision()
{
}
