#pragma once
#include "Std.h"

class Texture
{
public:
//	HBITMAP	m_hBitmap;
//	//HDC		m_hMemDC;
	T_STR	m_szPath;
	T_STR	m_szName;
	int		m_iIndex;
//	BITMAP	m_BitmapInfo;
	//
	ID3D11ShaderResourceView* m_pSRV;
	//
public:
	bool    Load(std::wstring filename);

	bool    Draw(RECT rtDesk, RECT rtSrc, BLENDFUNCTION bf);
	bool    Draw(xPoint p, RECT rtSrc, BLENDFUNCTION bf);
	
	bool    Draw(RECT rtDesk, RECT rtSrc, DWORD dwMode);
	bool	Draw(xPoint p, RECT rtSrc, DWORD iMode = SRCCOPY);
	bool    Draw(float x, float y, RECT rt, DWORD iMode = SRCCOPY);
	//
	bool	Load(ID3D11Device* pDevice, std::wstring szFileName);
	bool	Apply(ID3D11DeviceContext* pContext, UINT iSlot = 0);
	//
public:

	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	Texture();
	virtual ~Texture();
};

//기존의 Bitmap과 같은 역할. 이미지.