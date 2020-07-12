#pragma once
#include "Object.h"

struct FieldDesc
{
	int iNumCols;
	int iNumRows;
	float fCellDistance;
	float fHeightScale;
	T_STR szTextureFile;
	T_STR szShaderFile;
	T_STR szCubeFile;
};

class Field : public Object
{
public:
	int m_iNumRows;
	int m_iNumCols;
	int m_iNumCellRows;
	int m_iNumCellCols;
	int m_iNumVertices;
	int m_iNumFace;
	float m_fHeightScale;
	float m_fCellDistance;
	//
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pPattern;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pCube;
	//
	vector<D3DXVECTOR3> m_FaceNormal;
public:
	virtual float GetHeight(UINT index)
	{
		return 0.0f;
	}
	virtual D3DXVECTOR3 GetFaceNormal(UINT index)
	{
		return D3DXVECTOR3(0, 1, 0);
	}
	virtual D3DXVECTOR4 GetColor(UINT index)
	{
		return D3DXVECTOR4(1, 1, 1, 1);
	}
	D3DXVECTOR3 ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2);
	//
public:
	virtual	HRESULT CreateVertexData() override;
	virtual	HRESULT CreateIndexData() override;
	virtual bool Load(ID3D11Device* pd3Device, FieldDesc& md, const CHAR* pVertexShader, const CHAR* pPixelShader, const TCHAR* pVSFile, const TCHAR* pPSFile);
	bool	Render(ID3D11DeviceContext* pContext);

public:
	Field();
	~Field();
};

class FieldHeight : public Field
{
public:
	vector<float> m_HeightList;
public:
	void	CreateFieldHeight(ID3D11Device* pd3Device, ID3D11DeviceContext* pd3Context, const TCHAR* pMapFile);
	float	GetHeight(UINT index);
public:
	FieldHeight();
	~FieldHeight();
};