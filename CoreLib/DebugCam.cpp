#include "DebugCam.h"

void DebugCam::Frame()
{
	if (m_sMouseWheelRot)
	{
		m_vPosition -= m_vLook * m_sMouseWheelRot / 120.0f * 10.0f * m_fSpeed;
		m_sMouseWheelRot = 0;
	}

	D3DXMATRIX matRotation;
	D3DXMatrixInverse(&matRotation, NULL, &m_ViewBall.GetRotationMatrix());

	D3DXQUATERNION qRotationYawPitch;
	D3DXQuaternionRotationYawPitchRoll(&qRotationYawPitch, m_ViewBall.m_vEulerAngle.x, m_ViewBall.m_vEulerAngle.y, 0.0f);
	//m_ViewBall.m_vEulerAngle = 마우스 클릭하고 이동한 거리를 radian으로 변경
	D3DXMatrixAffineTransformation(&m_MatView, 1.0f, NULL, &qRotationYawPitch, &m_vPosition);
	D3DXMatrixInverse(&m_MatView, NULL, &m_MatView);

	return UpdateVector();
} 

void DebugCam::UpdateVector()
{
	m_vLook = D3DXVECTOR3(m_MatView._13, m_MatView._23, m_MatView._33);
	m_vUp = D3DXVECTOR3(m_MatView._12, m_MatView._22, m_MatView._32);
	m_vRight = D3DXVECTOR3(m_MatView._11, m_MatView._21, m_MatView._31);
	
	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Normalize(&m_vUp, &m_vUp);
	D3DXVec3Normalize(&m_vRight, &m_vRight);

	m_Frustum.CreateFrustum(m_MatView, m_matProj);
}

DebugCam::DebugCam()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_MatView);
	D3DXMatrixIdentity(&m_matProj);
}


DebugCam::~DebugCam()
{
}
