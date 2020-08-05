#pragma once
#include "Std.h"
#include "Input.h"
#include "Camera.h"
#include "Field.h"
#include "QuadTree.h"
#include "Collision.h"

enum SelectFunc
{
	FUNC_NONE,
	FUNC_CHANGETEXTURE,
	FUNC_CHANGEHEIGHT
};

class Select
{
public:
	Ray			m_Ray;
	D3DXVECTOR3	m_Intersection;
	D3DXVECTOR3	m_PreIntersection;
	D3DXMATRIX	m_MatClick;

	D3DXMATRIX	m_MatWorld;
	D3DXMATRIX	m_MatView;
	D3DXMATRIX	m_MatProj;
public:
	void	SetMatrix(D3DXMATRIX* MatWorld, D3DXMATRIX& MatView, D3DXMATRIX& MatProj);
	void	UpdateRay();
	bool	IntersectTriangle(D3DXVECTOR3 RayOrigin, D3DXVECTOR3 RayDir,
		D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, float* u, float* v, float* t);
	bool	CheckPick(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	bool	CheckPick(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, float* flenght);

	bool	SetSelect(FieldHeight& FieldData, Camera& UserCam);
	bool	SetSelect(FieldHeight& FieldData, Camera& UserCam, QuadTree& QuadData);
	
	FieldHeight* m_DestField;
	QuadTree*	m_PartitionedField;
	Camera* m_UserCamera;
	int		m_iCurrentTexture;
	SelectFunc m_CurrFunc;
	
	float	m_fStrength;

	//	공간분할 없는 충돌 체크
	void	CollTestEveryFace();
	
	void	CollTestQuadTree();

	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();

public:
	Select();
	~Select();
};

