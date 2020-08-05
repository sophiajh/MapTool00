#pragma once
#include "DObject.h"
#include "DXRT.h"

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

struct FIELD_CONSTANT_BUFFER
{
	D3DXVECTOR4	Coord;
	float		etc[4];
	FIELD_CONSTANT_BUFFER() {};
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

	float m_ftxOffSetU;
	float m_ftxOffSetV;

	float m_fHeightScale;
	float m_fCellDistance;
	//
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pPattern;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pCube;
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pDestAlphaTexture;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pSrcAlphaTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pAlphaSRV;

	ID3D11ShaderResourceView* m_pSplattingPatternList[3];
	
	vector<D3DXVECTOR3> m_FaceNormal;
	int*			m_pNormalLookupTable;
	D3DXVECTOR3*	m_pFaceNormal;
	//
	DXRT			m_FieldRT;
	void			RTSplatting(D3DXVECTOR3 vSelectedCoord3, int iTexNum);
	FIELD_CONSTANT_BUFFER	m_FieldCstData;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_pFieldCstBuffer;
	PlaneObject		m_FieldBrush;
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

	//	1�� vertex�� normal�� ������ 6���� face���� normal�� ����Ѵ�.
	void	CreateNormalLookupTable();
	
	//	m_pFaceNormal�� ���̽� ������ŭ (0,1,0)���� �ʱ�ȭ�Ѵ�.
	void	CreateFaceNormal();

	//	���� ��ü�� ���̽� �븻 ���. m_pFaceNormal ����.
	void	CalculateFaceNormal();

	//	���� ��ü�� ���ؽ� �븻 ���. 
	void	CalculateVertexNormalFastLookup();

	//	���̽��븻 ���� - �븻��� ���̺� ���� - ���� ��ü ���ؽ� �븻 ���
	//	���� ���� �� �ε��� ������ ���� �� ȣ���. 
	void	GenerateVertexNormal();
	
	//	iVertex�� ������ facenormal�� �ݿ��� ���ؽ� �븻 ������Ʈ.
	void	CalculateRelatedFace(int iVertex);
public:
	virtual	HRESULT CreateVertexData() override;
	virtual	HRESULT CreateIndexData() override;
	virtual bool Load(ID3D11Device* pd3Device, FieldDesc& md, const CHAR* pVertexShader, const CHAR* pPixelShader, const TCHAR* pVSFile, const TCHAR* pPSFile);

	bool	Init();
	bool	Render(ID3D11DeviceContext* pContext);
	void	Splatting(D3DXVECTOR3 vSelectedCoord3, int iTexNum);
	bool	Release();
public:
	Field();
	virtual ~Field();
};

class FieldHeight : public Field
{
public:
	vector<float> m_HeightList;
public:
	void	CreateFieldHeight(ID3D11Device* pd3Device, ID3D11DeviceContext* pd3Context, const TCHAR* pMapFile);
	float	GetHeight(UINT index);
	bool	SetFieldHeightData(const TCHAR* pMapFile);

	bool Load(ID3D11Device* pd3Device, FieldDesc& md, const CHAR* pVertexShader, const CHAR* pPixelShader, const TCHAR* pVSFile, const TCHAR* pPSFile);

private:
	const TCHAR* m_pMapFile;

public:
	FieldHeight();
	~FieldHeight();
};