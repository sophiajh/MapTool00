#pragma once
#include "DObject.h"

enum CMPPOSITION
{
	P_FRONT, P_SPANNING, P_BACK
};

struct K_PLANE
{
	float fA, fB, fC, fD;
	bool	CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	bool	CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 vNormal);
	void	Normalization();
};
class Frusturm
{
public:
	D3DXVECTOR3	m_vFrustum[8];
	K_PLANE		m_FrustumPlane[6];
	BoxObject	m_FrustumBox;

public:
	bool	CreateFrustumObj(ID3D11Device* pDevice);
	bool	CreateFrustum(D3DXMATRIX& pView, D3DXMATRIX& pProj);
	void	SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);

	CMPPOSITION		CheckPosition(KJHBOX& Box);
	bool	CheckCollision(KJHBOX& Box);

public:
	bool	PreRender(ID3D11DeviceContext* pContext, UINT iSize);
	bool	Render(ID3D11DeviceContext* pContext);
	bool	PostRender(ID3D11DeviceContext* pContext);

public:
	Frusturm();
	virtual ~Frusturm();
};

