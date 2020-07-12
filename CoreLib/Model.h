#pragma once

#include "DxHelperEx.h"
#include "Texture.h"
#include "Matrix.h"

struct P3VERTEX
{
	float x; float y; float z;
	float u; float v;
};
struct PNCT_VERTEX
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR4 Color;
	D3DXVECTOR2 Texture;
	PNCT_VERTEX() {};
	PNCT_VERTEX(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR4 v2, D3DXVECTOR2 v3)
	{
		Position = v0,	Normal = v1, Color = v2, Texture = v3;
	}
};
struct PNCTIW_VERTEX
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR4 Color;
	D3DXVECTOR2 Texture;
	D3DXVECTOR4 Index;
	D3DXVECTOR4 Weight;
};
struct EssCB
{
	D3DXMATRIX MatWorld;
	D3DXMATRIX MatView;
	D3DXMATRIX MatProj;
	float color[4];
	float etc[4];
};
struct KJHBOX
{
	D3DXVECTOR3 vCenter;
	D3DXVECTOR3 vMin;
	D3DXVECTOR3 vMax;
	D3DXVECTOR3 vAxis[3];
	float		fExtent[3];
};
class Model
{
public:
	D3DXMATRIX	m_MatWorld;
	D3DXMATRIX	m_MatView;
	D3DXMATRIX	m_MatProj;

	EssCB					m_ConstBuffer;
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pDeviceContext;
	DX::DxHelperEx			m_DxHelper;
	vector< PNCT_VERTEX >	m_VertexList;
	vector< DWORD >			m_IndexList;
	ID3D11Texture2D*		m_pDepthStencilBuffer;

	FILE*					m_pStream;
public:
	virtual bool Init();
	virtual bool Frame() ;
	virtual bool PreRender(ID3D11DeviceContext* pContext);
	virtual bool Render(ID3D11DeviceContext* pContext) ;
	virtual bool PostRender(ID3D11DeviceContext* pContext);
	virtual bool Release() ;
	bool Load(ID3D11Device* pDevice, T_STR filename, const TCHAR* pVSFilename, const TCHAR* pPSFilename, const TCHAR* pLoadTextureFile, const CHAR* pVertexShader, const CHAR* pPixelShader);

	bool Create(ID3D11Device* pd3dDevice, const TCHAR* pVSFilename, const TCHAR* pPSFilename, const TCHAR* pLoadTextureFile, const CHAR* pVertexShader, const CHAR* pPixelShader);
		//셰이더 로드, 레이아웃 설정, 버텍스/인덱스 버퍼/데이터 생성, 상수 버퍼 생성, 텍스쳐 로드, 버퍼 업데이트, 리소스 생성, 충돌데이터
	virtual HRESULT LoadShaderFile(const TCHAR* pVSFilename, const TCHAR* pPSFilename, const CHAR* pVertexShader, const CHAR* pPixelShader);
	virtual HRESULT SetInputLayout();
	virtual HRESULT CreateVertexData(); //Obj에서 설정.
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexData();	//Obj에서 설정.
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT LoadTexture(const TCHAR* pTextureFile);
	virtual bool UpdateBuffer();
	virtual HRESULT CreateResource();
	void SetCollisionData();
	void SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);

public:
	Model();
	virtual ~Model();
};

//Model을 포함해서 Line, Plane생성. vertex와 Index 정보만 다르게 입력.
