#include "Texture.h"

bool    Texture::Load(std::wstring filename)
{
	return true;
}
bool    Texture::Draw(RECT rtDesk, RECT rtSrc, BLENDFUNCTION bf)
{
	return true;
}
bool    Texture::Draw(xPoint p, RECT rtSrc, BLENDFUNCTION bf)
{
	return true;
}
bool    Texture::Draw(RECT rtDesk, RECT rtSrc, DWORD dwMode)
{
	return true;
}
bool	Texture::Draw(xPoint p, RECT rtSrc, DWORD iMode)
{
	return true;
}
bool    Texture::Draw(float x, float y, RECT rt, DWORD iMode)
{
	return true;
}
bool	Texture::Init()
{
	return true;
}
bool	Texture::Frame()
{
	return true;
}
bool	Texture::Render()
{
	return true;
}
bool	Texture::Release()
{
	return true;
}

bool	Texture::Load(ID3D11Device* pDevice, std::wstring szFileName)
{
	HRESULT hr;
	if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(pDevice, szFileName.c_str(), NULL, NULL, &m_pSRV, NULL)))
	{
		return false;
	}
	return true;
}
bool	Texture::Apply(ID3D11DeviceContext* pContext, UINT iSlot)
{
	pContext->PSSetShaderResources(iSlot, 1, &m_pSRV);
	return true;
}

Texture::Texture()
{
	m_pSRV = 0;
}


Texture::~Texture()
{
	if (m_pSRV) m_pSRV->Release();
}
