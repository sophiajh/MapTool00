#pragma once
#include "DObject.h"
class CubeMap: public BoxObject
{
public:
	BoxObject	m_Box;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pFaceTex;
public:
	///HRESULT CreateVertexData()	override;

	HRESULT	LoadTextureArray(const TCHAR* pTextureFile);
	bool	Render(ID3D11DeviceContext* pd3dDeviceContext) override;

public:
	CubeMap();
	~CubeMap();
};

