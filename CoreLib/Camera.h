#pragma once
#include "Std.h"
#include "ArcBall.h"
#include "Frusturm.h"
class Camera
{
public:
	ArcBall			m_ViewBall;
	ArcBall			m_WorldBall;
	Frusturm		m_Frustum;
public:

	D3DXMATRIX		m_MatView;
	
	D3DXVECTOR3		m_vLook;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3		m_vRight;
	D3DXVECTOR3		m_vPosition;
	D3DXVECTOR3		m_vTarget;

	D3DXMATRIX		m_ModelRot;
	D3DXMATRIX		m_ModelLastRot;
public:
	D3DXMATRIX		m_matWorld;
	D3DXMATRIX		m_matProj;

	short m_sMouseWheelRot;
	float m_fMouseWheel;
	float m_fSpeed;

public:	
	void CreateViewMatrix(D3DXVECTOR3 Position, D3DXVECTOR3 Target, D3DXVECTOR3 Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	void CreateProjMatrix();
	void CreateProjMatrix(float fFov, float fAspect, float fNear, float fFar);
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	void Forward();
	void Backward();
	void Left();
	void Right();

	bool Init();
	virtual void Frame();
	void SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	virtual void Render(ID3D11DeviceContext* pContext);
	virtual void Update() {};
	virtual void UpdateVector();

public:
	Camera();
	virtual ~Camera();
};

