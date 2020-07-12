#pragma once
//#include "Std.h"
#include "Object.h"

class Collision
{
public:
	static bool RectInPtr(RECT rt, POINT pt);
	static bool RectInPtr(RECT rt, xPoint pt);
	static bool	VertexInPlane(D3DXVECTOR3 v3LeftTop, D3DXVECTOR3 v3RightBottom, D3DXVECTOR2 vMouse);

	static bool RectInRect(RECT rt1, RECT rt2);
	static bool SphereInSphere(RECT rt1, RECT rt2);

	static void	Interrupt(xPoint&, RECT, xPoint&, RECT /*Object Objrt, Object Objrt2*/);

public:
	Collision();
	~Collision();
};

