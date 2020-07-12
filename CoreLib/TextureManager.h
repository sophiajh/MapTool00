#pragma once
#include "Texture.h"

class TextureManager : public Singleton<TextureManager>
{
	friend class Singleton<TextureManager>;
	typedef std::map<int, Texture*>::iterator ITOR;
	std::map<int, Texture*>	m_TextureList;
	int		m_iTextureNum;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int			Load(ID3D11Device* pDevice, std::wstring pFilePath);
	Texture*	GetPtr(int iKey);
	bool		Delete(int iKey);

private:
	TextureManager();
public:
	~TextureManager();

};

//기존 bitmapMgr역할