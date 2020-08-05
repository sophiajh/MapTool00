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
	m_qDown = m_qNow; //�������qDown
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
	//x y�� ����ϸ� z�� ����.
	//0 ~ 800�� -1 ~ +1������ ��ȯ�Ѵ�. ȭ����ǥ�踦 ����ǥ��� ��ȯ�Ѵ�.
	//x�� +1 ~ -1�� �����Ѵ�.
	FLOAT x = -(fScreenX - m_iWidth / 2) / (m_fRadius * m_iWidth / 2); // xy��ȸ���� ������
	FLOAT y = (fScreenY - m_iHeight / 2) / (m_fRadius * m_iHeight / 2);

	//�ӽú���.
	FLOAT z = 0.0f;

	FLOAT mag = x * x + y * y; //magnitude. �Ը�.

	if (mag > 1.0f) //����ȭ�� �Ǿ����� ������� ����ȭ ����.
	{
		FLOAT scale = 1.0f / sqrtf(mag);
		x *= scale;
		y *= scale;
		//z�� 0�ϼ� �ۿ� ����.
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
	float fDot = D3DXVec3Dot(&vStart, &vEnd); //���̰�.
	D3DXVec3Cross(&vMove, &vStart, &vEnd);

	//������� �ϸ� ȸ������ 2�谡 �ȴ�. �״�� ����. (ȭ�� ���׼� ������ ������ 360�� ���ư���)
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