#include "TextureManager.h"

bool	TextureManager::Init()
{
	return true;
} 

Texture*  TextureManager::GetPtr(int iKey)
{
	ITOR itor = m_TextureList.find(iKey);
	if (itor != m_TextureList.end())
	{
		Texture* pData = (*itor).second;
		return pData;
	}
	return nullptr;
}

int		TextureManager::Load(ID3D11Device* pDevice, std::wstring pFilePath)
{
	if (pFilePath.empty()) return false;

	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	_tsplitpath_s(pFilePath.c_str(), Drive, Dir, Name, Ext);

	T_STR filename = Name;
	filename += Ext;

	T_STR path = Drive;
	path += Dir;

	for (ITOR itor = m_TextureList.begin(); itor != m_TextureList.end(); itor++)
	{
		Texture* pData = (*itor).second;
		if (pData->m_szName == filename)
		{
			return pData->m_iIndex;
		}
	}
	Texture* pData = new Texture;
	if (pData->Load(pDevice, pFilePath) == false)
	{
		delete pData;
		return -1;
	}
	pData->m_szName = filename;
	pData->m_szPath = path;
	pData->m_iIndex = m_iTextureNum++;
	m_TextureList.insert(std::make_pair(pData->m_iIndex, pData));
	return pData->m_iIndex;
}

bool TextureManager::Frame()
{
	return true;
}

bool TextureManager::Render()
{
	for (ITOR itor = m_TextureList.begin(); itor != m_TextureList.end(); itor++)
	{
		Texture* pData = (*itor).second;
		pData->Render();
	}
	return true;
}

bool TextureManager::Delete(int iKey)
{
	ITOR itor = m_TextureList.find(iKey);
	if (itor != m_TextureList.end())
	{
		Texture* pData = (*itor).second;
		pData->Release();
		delete pData;
		m_TextureList.erase(itor);
		return true;
	}
	return false;
}

bool TextureManager::Release()
{
	for (ITOR itor = m_TextureList.begin(); itor != m_TextureList.end();)
	{
		Texture* pData = (*itor).second;
		pData->Release();
		delete pData;
		itor = m_TextureList.erase(itor);
	}
	m_TextureList.clear();
	return true;
}


TextureManager::TextureManager()
{
	m_iTextureNum = 0;
}


TextureManager::~TextureManager()
{
	Release();
}
