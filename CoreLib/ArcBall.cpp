#include "ArcBall.h"

bool	ArcBall::Init()
{
	SetWindow(float(g_rtClient.right), float(g_rtClient.bottom), 0.9);
	return true;
}

void	ArcBall::SetWindow(INT nWidth, INT nHeight, FLOAT fRadius)
{
	m_iWidth = nWidth;
	m_iHeight = nHeight;
	m_fRadius = fRadius;
}

void	ArcBall::OnBegin(int nX, int nY)
{
	m_bDrag = true;
	m_vDragPt.x = nX;
	m_vDragPt.y = nY;
	m_qDown = m_qNow; //현재시작qDown
	m_vDownPt = ScreenToVector((float)nX, (float)nY);
}

void	ArcBall::OnMove(int nX, int nY)
{
	if (m_bDrag == true)
	{
		m_vDragAngle.x = nX - m_vDragPt.x;
		m_vDragAngle.y = nY - m_vDragPt.y;
		m_vDragPt.x = nX;
		m_vDragPt.y = nY;
		m_vEulerAngle.x += D3DXToRadian(m_vDragAngle.x);
		m_vEulerAngle.y += D3DXToRadian(m_vDragAngle.y);
		
		
		m_vCurrPt = ScreenToVector((float)nX, (float)nY);
		m_qNow = m_qDown * QuaternionFromPt(m_vDownPt, m_vCurrPt);
	}
	
}
void	ArcBall::OnEnd(int nX, int nY)
{
	m_bDrag = false;
}

//D3DXMATRIX ArcBall::GetRotationMatrix()
//{
//	D3DXMatrixRotationYawPitchRoll(&m_matRotation, m_vEulerAngle.x, m_vEulerAngle.y, 0.0f);
//	return m_matRotation;
//}

D3DXMATRIX ArcBall::GetRotationMatrix()
{
	return *D3DXMatrixRotationQuaternion(&m_matRotation, &m_qNow);
	/*D3DXMATRIX tmp = *D3DXMatrixRotationQuaternion(&m_matRotation, &m_qNow);
	tmp._31 = 0.0f;
	tmp._32 = 0.0f;
	tmp._33 = 1.0f;
	return tmp;*/
}

D3DXVECTOR3 ArcBall::ScreenToVector(float fScreenX, float fScreenY)
{
	//x y만 계산하면 z값 나옴.
	//0 ~ 800을 -1 ~ +1범위로 변환한다. 화면좌표계를 구좌표계로 변환한다.
	//x는 +1 ~ -1로 변경한다.
	FLOAT x = -(fScreenX - m_iWidth / 2) / (m_fRadius * m_iWidth / 2); // xy축회전에 음수값
	FLOAT y = (fScreenY - m_iHeight / 2) / (m_fRadius * m_iHeight / 2);

	//임시변수.
	FLOAT z = 0.0f;

	FLOAT mag = x * x + y * y; //magnitude. 규모.

	if (mag > 1.0f) //정규화가 되어있지 않은경우 정규화 수행.
	{
		FLOAT scale = 1.0f / sqrtf(mag);
		x *= scale;
		y *= scale;
		//z는 0일수 밖에 없다.
	}
	else
	{
		z = sqrtf(1.0f - mag);
	}

	return D3DXVECTOR3(x, y, z);
}

D3DXQUATERNION ArcBall::QuaternionFromPt(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd)
{
	D3DXVECTOR3 vMove;
	//
	//vEnd.z = vStart.z;
	//
	float fDot = D3DXVec3Dot(&vStart, &vEnd); //사이각.
	D3DXVec3Cross(&vMove, &vStart, &vEnd);

	//사원수로 하면 회전각이 2배가 된다. 그대로 수행. (화면 끝네서 끝으로 돌리면 360도 돌아간다)
	return D3DXQUATERNION(vMove.x, vMove.y, vMove.z, fDot); 
	//return D3DXQUATERNION(vMove.x, vMove.y, 0, fDot);
}

ArcBall::ArcBall()
{
	D3DXQuaternionIdentity(&m_qNow);
	D3DXQuaternionIdentity(&m_qDown);
	D3DXMatrixIdentity(&m_matRotation);
}


ArcBall::~ArcBall()
{
}

/////////////////copy//////////////////

//D3DXMATRIX ArcBall::GetRotationMatrix()
//{
//	return *D3DXMatrixRotationQuaternion(&m_matRotation, &m_qNow);
//}
//
//void	ArcBall::OnMove(int nX, int nY)
//{
//	if (m_bDrag == true)
//	{
//		m_vDragAngle.x = nX - m_vDragPt.x;
//		m_vDragAngle.y = nY - m_vDragPt.y;
//		m_vDragPt.x = nX;
//		m_vDragPt.y = nY;
//		m_vEulerAngle.x += D3DXToRadian(m_vDragAngle.x);
//		m_vEulerAngle.y += D3DXToRadian(m_vDragAngle.y);
//
//
//	}
//}