#include "Camera.h"

LRESULT Camera::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_LBUTTONDOWN)
	{
		int iMouseX = LOWORD(lParam);
		int iMouseY = HIWORD(lParam);
		//m_ViewBall.OnBegin(iMouseX, iMouseY);
		m_WorldBall.OnBegin(iMouseX, iMouseY);

	}
	if (msg == WM_RBUTTONDOWN)
	{
		int iMouseX = LOWORD(lParam);
		int iMouseY = HIWORD(lParam);
		//m_WorldBall.OnBegin(iMouseX, iMouseY);
		m_ViewBall.OnBegin(iMouseX, iMouseY);

	}
	if (msg == WM_MOUSEMOVE)
	{
		int iMouseX = LOWORD(lParam);
		int iMouseY = HIWORD(lParam);
		m_ViewBall.OnMove(iMouseX, iMouseY);
		m_WorldBall.OnMove(iMouseX, iMouseY);
	}
	if (msg == WM_LBUTTONUP || msg == WM_RBUTTONUP)
	{
		int iMouseX = LOWORD(lParam);
		int iMouseY = HIWORD(lParam);
		m_ViewBall.OnEnd(iMouseX, iMouseY);
		m_WorldBall.OnEnd(iMouseX, iMouseY);
	}
	if (msg == WM_MOUSEWHEEL)
	{
		m_sMouseWheelRot += HIWORD(wParam);
	}
	return 1;
}

bool Camera::Init()
{
	m_ViewBall.Init();
	m_WorldBall.Init(); 
	return true;
}

void Camera::CreateViewMatrix(D3DXVECTOR3 Position, D3DXVECTOR3 Target, D3DXVECTOR3 Up)
{
	m_vPosition = Position;
	m_vTarget = Target;
	m_vUp = Up;

	D3DXMatrixLookAtLH(&m_MatView, &Position, &Target, &Up);

	return UpdateVector();

}

void Camera::CreateProjMatrix()
{
	D3DXMATRIX MatProj;
	D3DXMatrixPerspectiveFovLH(&MatProj, D3DX_PI / 4, (float)g_rtClient.right / (float)g_rtClient.bottom, 1.0f, 4000.0f);
	m_matProj = MatProj;
	//D3DXMatrixPerspectiveFovLH(출력 행렬, y방향 fov(라디안), aspect ratio 너비 / 높이, near plane, far plane)
}
void Camera::CreateProjMatrix(float fFov, float fAspect, float fNear, float fFar)
{
	D3DXMatrixPerspectiveFovLH(&m_matProj, fFov, fAspect, fNear, fFar);
}
void Camera::UpdateVector()
{
	m_vRight = D3DXVECTOR3(m_MatView._11, m_MatView._21, m_MatView._31);
	m_vUp = D3DXVECTOR3(m_MatView._12, m_MatView._22, m_MatView._32);
	m_vLook = D3DXVECTOR3(m_MatView._13, m_MatView._23, m_MatView._33);

	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Normalize(&m_vUp, &m_vUp);
	D3DXVec3Normalize(&m_vRight, &m_vRight);
	
	m_Frustum.CreateFrustum(m_MatView, m_matProj);
}
void Camera::Forward()
{
	m_vPosition = m_vPosition + m_vLook * g_fSecondPerFrame * 50.0f * m_fSpeed;
}

void Camera::Backward()
{
	m_vPosition = m_vPosition - m_vLook * g_fSecondPerFrame * 50.0f * m_fSpeed;
}

void Camera::Left()
{
	m_vPosition = m_vPosition - m_vRight * g_fSecondPerFrame * 50.0f * m_fSpeed;
}

void Camera::Right()
{
	m_vPosition = m_vPosition + m_vRight * g_fSecondPerFrame * 50.0f * m_fSpeed;
}

void Camera::Frame()
{
	CreateViewMatrix(m_vPosition, m_vTarget, m_vUp);
	return UpdateVector();
}

void Camera::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	m_Frustum.m_FrustumBox.SetMatrix(pWorld, pView, pProj);
}
void Camera::Render(ID3D11DeviceContext* pContext)
{
	DX::ApplyBS(pContext, DX::DxState::m_pAlphaBlend);
	DX::ApplyDSS(pContext, DX::DxState::m_pDepthEnable);
	m_Frustum.Render(pContext);
	DX::ApplyDSS(pContext, DX::DxState::m_pDepthDisable);
	DX::ApplyBS(pContext, DX::DxState::m_pAlphaBlendDisable);
}
Camera::Camera()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_MatView);
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_ModelLastRot);

	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	m_vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_fMouseWheel = 5.0f;
	m_sMouseWheelRot = 0;
	m_fSpeed = 1.0f;
}


Camera::~Camera()
{
}
