#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <DWrite.h>
#include <string>
#include <vector>
#pragma comment( lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")


class DxWrite
{
public:
	ID2D1Factory*			m_pD2DFactory;
	IDWriteFactory*			m_pWriteFactory;
	IDWriteTextFormat*		m_pWriteFormat;

	ID2D1RenderTarget*		m_pRenderTarget;
	ID2D1SolidColorBrush*	m_pBrush;

public:
	D2D1_MATRIX_3X2_F		m_pMatText;
	std::wstring			textdata;
	D2D1_RECT_F				rt_text;
public:
	float m_fDPIX;
	float m_fDPIY;
	float m_fDPIscaleX;
	float m_fDPIscaleY;
public:
	bool Set(IDXGISurface1* pBackBuffer);
	bool CreateDeviceResource(IDXGISurface1* pBackBuffer);
	bool DiscardDeviceResource();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	DxWrite();
	~DxWrite();
};

