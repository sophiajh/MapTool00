#pragma once
#include "Object.h"

class DXRT
{
public:
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pTexture;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pDSTexture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_pRTView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_pDSView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>m_pSRView;
	D3D11_VIEWPORT	m_ViewPort;

	D3D11_VIEWPORT	m_ViewPortOld;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_pRTViewOld;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_pDSViewOld;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>m_pSRViewOld;

	D3DXVECTOR4 m_ClearColor;
public:
	HRESULT Create(ID3D11Device* pd3dDevice, float Width, float Height);
	bool	Begin(ID3D11DeviceContext* pd3dDContext);
	bool	End(ID3D11DeviceContext* pd3dDContext);
public:
	DXRT();
	~DXRT();
};

