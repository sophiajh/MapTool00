#include "ModelCamera.h"

void ModelCamera::Frame()
{
	if (m_sMouseWheelRot)
	{
		//m_fRadius += m_nMouseWheelDelta * m_fRadius * 1.0f / 120f; //현재 떨어진 거리를 기준으로 가속도
		m_fMouseWheel += (m_sMouseWheelRot / 120.0f) * m_fMouseWheel * 0.1f;
		m_sMouseWheelRot = 0;
	}
	D3DXMATRIX matRotation = m_ViewBall.GetRotationMatrix();
	//D3DXMATRIX matWorldRot = m_WorldBall.GetRotationMatrix();
	D3DXMatrixInverse(&matRotation, NULL, &m_ViewBall.GetRotationMatrix());
	D3DXVECTOR3 vWorldUp, vWorldLook;
	D3DXVECTOR3 vLocalUp = D3DXVECTOR3(0, 1, 0);
	D3DXVECTOR3 vLocalLook = D3DXVECTOR3(0, 0, 1); //D3DXVECTOR3(0, -0.7, 0.7);
	D3DXVECTOR3 vLocalRight = D3DXVECTOR3(1, 0, 0);

	//단위백터를 회전시킨다.
	D3DXVec3TransformCoord(&vWorldUp, &vLocalUp, &matRotation);	//Local Up을 World에 위치시킴
	D3DXVec3TransformCoord(&vWorldLook, &vLocalLook, &matRotation); //Local Look을 World에 맞게
	D3DXVec3TransformCoord(&m_vRight, &vLocalRight, &matRotation);

	m_vLook = vWorldLook;
	m_vUp = vWorldUp;
	m_vPosition = m_vTarget - vWorldLook * m_fMouseWheel;
	D3DXMatrixLookAtLH(&m_MatView, &m_vPosition, &m_vTarget, &vWorldUp); //뷰행렬 생성.
	
	return UpdateVector();
}

void ModelCamera::UpdateVector()
{
	m_vLook = D3DXVECTOR3(m_MatView._13, m_MatView._23, m_MatView._33);
	m_vUp = D3DXVECTOR3(m_MatView._12, m_MatView._22, m_MatView._32);
	m_vRight = D3DXVECTOR3(m_MatView._11, m_MatView._21, m_MatView._31);
	//D3DXVECTOR3 vtmp = D3DXVECTOR3(m_MatView._11, m_MatView._12, m_MatView._13);

	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Normalize(&m_vUp, &m_vUp);
	D3DXVec3Normalize(&m_vRight, &m_vRight);
	return Update();
}

void ModelCamera::Update()
{
	D3DXMATRIX ModelLastRotInv;
	D3DXMatrixInverse(&ModelLastRotInv, NULL, &m_ModelLastRot);

	D3DXMATRIX ModelRot;
	ModelRot = m_WorldBall.GetRotationMatrix();
	m_ModelLastRot = ModelRot;

	D3DXMATRIX ViewInv;
	D3DXMatrixInverse(&ViewInv, NULL, &m_MatView);
	ViewInv._41 = ViewInv._42 = ViewInv._43 = 0;

	m_ModelRot = m_ModelRot * m_MatView * ModelLastRotInv * ModelRot * ViewInv;
	//m_ModelRot._41 = 0;
	//m_ModelRot._42 = 0;
	//m_ModelRot._43 = 0;
	//m_ModelRot._41 = m_vTarget.x;
	//m_ModelRot._42 = m_vTarget.y;
	//m_ModelRot._43 = m_vTarget.z;
	//m_MatView = m_ModelRot;
	m_matWorld = m_ModelRot;
}


ModelCamera::ModelCamera()
{
	D3DXMatrixIdentity(&m_ModelRot);
}


ModelCamera::~ModelCamera()
{
}
