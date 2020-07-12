#pragma once
#include "Std.h"

class ArcBall
{
public:
	INT		m_iWidth;
	INT		m_iHeight;
	FLOAT	m_fRadius;

	bool	m_bDrag;
	D3DXVECTOR2	m_vDragPt;
	D3DXVECTOR2	m_vDragAngle;
	D3DXVECTOR2 m_vEulerAngle;
	D3DXMATRIX	m_matRotation;

	//
	D3DXQUATERNION m_qNow;
	D3DXQUATERNION m_qDown;
	D3DXVECTOR3		m_vDownPt;
	D3DXVECTOR3		m_vCurrPt;
	//
public:
	void	OnBegin(int nX, int nY);
	void	OnMove(int nX, int nY);
	void	OnEnd(int nX, int nY);
	D3DXMATRIX GetRotationMatrix();

	bool	Init();
	void	SetWindow(INT nWidth, INT nHeight, FLOAT fRadius);

	//���콺 2d��ǥ�� 3d��ǥ�� �ٲ��ִ� �Լ�.
	D3DXVECTOR3 ScreenToVector(float fScreenX, float fScreenY);
	
	D3DXQUATERNION QuaternionFromPt(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd);
	//

public:
	ArcBall();
	~ArcBall();
};

//���ʹϾ��� ����� ȸ���� ������ ���е��� ����.