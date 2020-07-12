#include "DxWrite.h"

bool DxWrite::Set(IDXGISurface1* pBackBuffer)
{
	CreateDeviceResource(pBackBuffer);
	return true;
}

bool DxWrite::CreateDeviceResource(IDXGISurface1* pBackBuffer)
{
	HRESULT hr;
	//------------------------------------------------
	if (FAILED(hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory)))
	{
		return false;
	}
	m_pD2DFactory->GetDesktopDpi(&m_fDPIX, &m_fDPIY);

	m_fDPIscaleX = m_fDPIX / 96.0f;
	m_fDPIscaleY = m_fDPIY / 96.0f;

	if (FAILED(hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_pWriteFactory)))
	{
		return false;
	}
	if (FAILED(hr = m_pWriteFactory->CreateTextFormat(L"°íµñ", NULL,
		DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		20, L"ko-kr", &m_pWriteFormat)))
	{
		return false;
	}
	

	//------------------------------------------device independent resource

	//------------------------------------------------------
	D2D1_RENDER_TARGET_PROPERTIES RT_prop;
	//D2D1_RENDER_TARGET_TYPE type;
	//D2D1_PIXEL_FORMAT pixelFormat;
	//FLOAT dpiX;
	//FLOAT dpiY;
	//D2D1_RENDER_TARGET_USAGE usage;
	//D2D1_FEATURE_LEVEL minLevel;
	RT_prop.dpiX = m_fDPIX;
	RT_prop.dpiY = m_fDPIY;
	RT_prop.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
	RT_prop.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	RT_prop.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	RT_prop.usage = D2D1_RENDER_TARGET_USAGE_NONE;

	if (FAILED(hr = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &RT_prop, &m_pRenderTarget)))
	{
		return false;
	}

	if (FAILED(hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush)))
	{
		return false;
	}
	//-------------------------------------------device dependent resource
	textdata = L"Å×½ºÆ®";

	rt_text.top = 50;
	rt_text.left = 50;
	rt_text.right = 800 - 50;
	rt_text.bottom = 600 - 50;

	return true;
}

bool DxWrite::DiscardDeviceResource()
{
	HRESULT hr;

	if (m_pD2DFactory) m_pD2DFactory->Release();
	if (m_pWriteFactory) m_pWriteFactory->Release();
	if (m_pWriteFormat) m_pWriteFormat->Release();

	if (m_pRenderTarget) m_pRenderTarget->Release();
	if (m_pBrush) m_pBrush->Release();

	return true;
}
bool DxWrite::Init()
{
	return true;
}
bool DxWrite::Frame()
{
	return true;
}
bool DxWrite::Render()
{
	m_pRenderTarget->BeginDraw();

	D3DCOLORVALUE TextColor = D2D1::ColorF(1, 1, 1, 0.5);
	m_pBrush->SetColor(TextColor);

	m_pMatText = D2D1::IdentityMatrix();
	m_pRenderTarget->SetTransform(m_pMatText);
	
	//D2D1_COLOR_F TextColor = D2D1::ColorF(1, 1, 1, 0.5);


	m_pRenderTarget->DrawText(textdata.c_str(), textdata.size(), m_pWriteFormat, rt_text, m_pBrush);

	
	m_pRenderTarget->EndDraw();
	return true;
}
bool DxWrite::Release()
{
	return true;
}
DxWrite::DxWrite()
{
}


DxWrite::~DxWrite()
{
}
