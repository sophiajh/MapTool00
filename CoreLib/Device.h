#pragma once
#include "Window.h"
#include "Timer.h"

class Device : public Window
{
public:
	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pDeviceContext;
	IDXGISwapChain*			m_pSwapChain;
	//An IDXGISwapChain interface implements one or more surfaces for storing rendered data before presenting it to an output.

	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
	ID3D11RenderTargetView*	m_pRenderTargetView;
	D3D11_VIEWPORT			m_ViewPort;
	ID3D11DepthStencilState*m_pDSState;
	ID3D11DepthStencilView*	m_pDSView;

	D3D_DRIVER_TYPE			m_DriverType;
	D3D_FEATURE_LEVEL		m_FeatureLevel;

	Timer					m_DeviceTimer;
	IDXGIFactory*			m_pDXGIFactory;
public:
	
	bool InitDevice();
	HRESULT CreateIDXGIFactory();
	HRESULT CreateDevice();
	HRESULT CreateSwapChain();
	HRESULT SetRenderTargetView();
	HRESULT SetViewPort();
	
	UINT iRectWidth;
	UINT iRectHeight;

	bool ReleaseDevice();
	
	bool ResizeDevice(UINT Width, UINT Height);

	virtual HRESULT DeleteDXResource();
	virtual HRESULT CreateDXResource();
	
public:
	//bool Init();
	bool Frame();
	bool PreRender();
	bool Render();
	bool PostRender();
	bool Release();
	
public:
	Device();
	~Device();
};