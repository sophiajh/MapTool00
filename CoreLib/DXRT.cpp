#include "DXRT.h"

HRESULT DXRT::Create(ID3D11Device* pd3dDevice, float Width, float Height)
{
	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	td.Width = Width;
	td.Height = Height;
	td.MipLevels = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.ArraySize = 1;

	if (FAILED(hr = pd3dDevice->CreateTexture2D(&td, NULL, m_pTexture.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = pd3dDevice->CreateShaderResourceView(m_pTexture.Get(), NULL, m_pSRView.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = pd3dDevice->CreateRenderTargetView(m_pTexture.Get(), NULL, m_pRTView.GetAddressOf())))
	{
		return hr;
	}

	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	if (FAILED(hr = pd3dDevice->CreateTexture2D(&td, NULL, m_pDSTexture.GetAddressOf())))
	{
		return hr;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	if (FAILED(hr = pd3dDevice->CreateDepthStencilView(m_pDSTexture.Get(), &dsd, m_pDSView.GetAddressOf())))
	{
		return hr;
	}

	m_ViewPort.Width = Width;
	m_ViewPort.Height = Height;
	m_ViewPort.MaxDepth = 1;
	m_ViewPort.MinDepth = 0;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;

	return hr;
}

bool	DXRT::Begin(ID3D11DeviceContext* pd3dDContext)
{

	UINT ViewNum = 1;
	pd3dDContext->RSGetViewports(&ViewNum, &m_ViewPortOld);
	pd3dDContext->OMGetRenderTargets(1,m_pRTViewOld.GetAddressOf(),m_pDSViewOld.GetAddressOf());

	pd3dDContext->OMSetRenderTargets(1, m_pRTView.GetAddressOf(), m_pDSView.Get());
	pd3dDContext->RSSetViewports(1, &m_ViewPort);

	pd3dDContext->ClearRenderTargetView(m_pRTView.Get(), m_ClearColor);
	pd3dDContext->ClearDepthStencilView(m_pDSView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return true;
}

bool	DXRT::End(ID3D11DeviceContext* pd3dDContext)
{
	pd3dDContext->RSSetViewports(1, &m_ViewPortOld);
	pd3dDContext->OMSetRenderTargets(1, m_pRTViewOld.GetAddressOf(), m_pDSViewOld.Get());

	pd3dDContext->RSSetState(DX::DxState::m_pRSSolidFrame);

	m_pRTViewOld.Reset();
	m_pDSViewOld.Reset();
	return true;
}

DXRT::DXRT()
{
	m_ClearColor = D3DXVECTOR4(0, 0.5f, 0, 1);
}


DXRT::~DXRT()
{
}
