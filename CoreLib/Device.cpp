#include "Device.h"

bool Device::InitDevice()
{
	CreateIDXGIFactory();
	CreateDevice();
	CreateSwapChain();
	SetRenderTargetView();
	SetViewPort();
	return true;

}
bool Device::Frame()
{
	m_DeviceTimer.Frame();
	float fTime = m_DeviceTimer.m_fAccumulation;
	float fBoundedTime = cosf(fTime)*0.5f + 0.5f;

	//D3D11_MAPPED_SUBRESOURCE MappedResource;
	//m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0,&MappedResource);
	//VertexShaderConstantBuffer* VSCB = (VertexShaderConstantBuffer*)MappedResource.pData;
	//VSCB->fTime = fTime;
	//VSCB->vColor = D3DXVECTOR4(cosf(fTime), sinf(fTime), 1.0f - cosf(fTime), 1.0f);
	//m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

	return true;
}

HRESULT Device::CreateIDXGIFactory()
{
	HRESULT hr;
	if (FAILED(hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pDXGIFactory)))
	{
		return S_FALSE;
	}
	return S_OK;
}

HRESULT Device::CreateDevice()
{
	HRESULT hr;
	m_DriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT CreateDeviceFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	D3D_FEATURE_LEVEL FeatureLevel[] = { D3D_FEATURE_LEVEL_11_0 };

	if (FAILED(hr = D3D11CreateDevice(NULL, m_DriverType, NULL,
		CreateDeviceFlag,
		FeatureLevel, 1,
		D3D11_SDK_VERSION,
		&m_pDevice,
		&m_FeatureLevel,
		&m_pDeviceContext)))
	{
		return S_FALSE;
	}
	return S_OK;
}

HRESULT Device::CreateSwapChain()
{
	HRESULT hr;
	ZeroMemory(&m_SwapChainDesc, sizeof(m_SwapChainDesc));
	m_SwapChainDesc.BufferDesc.Width = g_rtClient.right;
	m_SwapChainDesc.BufferDesc.Height = g_rtClient.bottom;
	m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	m_SwapChainDesc.SampleDesc.Count = 1;
	m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_SwapChainDesc.BufferCount = 1;
	m_SwapChainDesc.OutputWindow = m_hWnd;
	m_SwapChainDesc.Windowed = true;

	if (FAILED(hr = m_pDXGIFactory->CreateSwapChain(m_pDevice, &m_SwapChainDesc, &m_pSwapChain)))
	{
		return S_FALSE;
	}
	return S_OK;
}

HRESULT Device::SetRenderTargetView()
{
	HRESULT hr;
	ID3D11Texture2D* pBackBuffer;
	if (FAILED(hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
	{
		return false;
	}
	//ID3D11RenderTargetViewA render-target-view interface identifies the render-target subresources that can be accessed during rendering.
	if (FAILED(hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView)))
	{
		return false;
	}
	//CreateRenderTargetView = Creates a render-target view for accessing resource data.
	pBackBuffer->Release();
	
	ID3D11Texture2D* pDepthStencilTexture = NULL;
	D3D11_TEXTURE2D_DESC DescDepth;
	ZeroMemory(&DescDepth, sizeof(D3D11_TEXTURE2D_DESC));
	DescDepth.Width = m_SwapChainDesc.BufferDesc.Width;
	DescDepth.Height = m_SwapChainDesc.BufferDesc.Height;
	DescDepth.MipLevels = 1;
	DescDepth.ArraySize = 1;
	DescDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DescDepth.SampleDesc.Count = 1;
	DescDepth.SampleDesc.Quality = 0;
	DescDepth.Usage = D3D11_USAGE_DEFAULT;
	DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//DescDepth.CPUAccessFlags = 0;
	//DescDepth.MiscFlags = 0;

	if (FAILED(hr = m_pDevice->CreateTexture2D(&DescDepth, NULL, &pDepthStencilTexture)))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilDesc;
	ZeroMemory(&DepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	DepthStencilDesc.Format = DescDepth.Format;
	DepthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//DepthStencilDesc.Texture2D.MipSlice = 0;

	if (FAILED(hr = m_pDevice->CreateDepthStencilView(pDepthStencilTexture, &DepthStencilDesc, &m_pDSView)))
	{
		return false;
	}
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDSView);
	pDepthStencilTexture->Release();
	return S_OK;
}

HRESULT Device::SetViewPort()
{
	HRESULT hr;
//#if defined (_DEBUG)

	iRectWidth = g_rtClient.right/ 3;
	iRectHeight = g_rtClient.bottom / 3;

	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Height = g_rtClient.bottom ;
	m_ViewPort.Width = g_rtClient.right ;
	m_ViewPort.MaxDepth = 1;
	m_ViewPort.MinDepth = 0;

	m_pDeviceContext->RSSetViewports(1, &m_ViewPort);
	
//#endif // _DEBUG

	return S_OK;
}

bool Device::PreRender()
{
	float clearColor[] = { 0.0f,0.5f,0.5f,1 };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDSView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);

	return true;
}

bool Device::Render()
{
	
	return true;
}

bool Device::PostRender()
{

	m_pSwapChain->Present(0, 0);

	return true;
}

HRESULT Device::DeleteDXResource()
{
	return S_OK;
}

HRESULT Device::CreateDXResource()
{
	return S_OK;
}

bool Device::ResizeDevice(UINT Width, UINT Height)
{
	if (m_pDevice == nullptr) return true;

	DeleteDXResource();

	m_pDeviceContext->OMSetRenderTargets(0, NULL, NULL);	//·»´õÅ¸°Ù ÇØÁ¦‰Î.
	m_pRenderTargetView->Release();							//ÇØÁ¦µÈ ·»´õÅ¸°Ù ºä Á¦°Å.

	HRESULT hr;

	
	if (FAILED(hr = m_pSwapChain->ResizeBuffers(m_SwapChainDesc.BufferCount, Width, Height, m_SwapChainDesc.BufferDesc.Format, m_SwapChainDesc.Flags)))
	{
		return false;
	}
	if (FAILED(hr = m_pSwapChain->GetDesc(&m_SwapChainDesc)))
	{
		return false;
	}
	
	g_rtClient.right = Width;
	g_rtClient.bottom = Height;

	SetRenderTargetView();
	SetViewPort();
	 
	CreateDXResource();
	return true;
}

bool Device::Release()
{
	////////////////////////////
	//if (m_pVertexBuffer) m_pVertexBuffer->Release();
	//if (m_pVertexShader) m_pVertexShader->Release();
	//if (m_pPixelShader) m_pPixelShader->Release();
	//if (m_pInputLayout) m_pInputLayout->Release();
	//if (m_pIndexBuffer) m_pIndexBuffer->Release();
	//if (m_pConstantBuffer) m_pConstantBuffer->Release();
	//if (m_pSRV[0]) m_pSRV[0]->Release();
	//if (m_pSRV[1]) m_pSRV[0]->Release();

	//m_pVertexBuffer = 0;
	//m_pVertexShader = 0;
	//m_pPixelShader = 0;
	//m_pInputLayout = 0;
	//m_pIndexBuffer = 0;
	//m_pConstantBuffer = 0;
	//m_pSRV[0] = 0;
	//m_pSRV[1] = 0;
	m_pRenderTargetView->Release();
	m_pDevice->Release();
	m_pDeviceContext->Release();
	m_pSwapChain->Release();	
	
	//////////////////////////
	//if (m_pBlendState) m_pBlendState->Release();
	//m_pBlendState = 0;
	
	return true;
}

bool Device::ReleaseDevice()
{
	return true;
}

Device::Device()
{
	//////////////////////
	//m_pVertexBuffer = 0;
	//m_pVertexShader = 0;
	//m_pPixelShader = 0;
	//m_pInputLayout = 0;
	//m_pIndexBuffer = 0;
	//m_pConstantBuffer = 0;
	/////////////////////////
	//m_pBlendState = 0;

}

Device::~Device()
{
}
