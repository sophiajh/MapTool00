#pragma once
#include "Object.h"
struct GroupData
{
	T_STR	m_szPath;
	T_STR	m_szName;
	int		m_iIndex;
	int		m_iBitmapID;
	std::vector<ObjectInfo> m_ImageList;
};

class ScriptMgr : public Singleton<ScriptMgr>
{
	friend class Singleton<ScriptMgr>;
	typedef std::map<int, GroupData>::iterator ITOR;
	std::map<int, GroupData>	m_List;
	int		m_iIndex;
public:
	int		Load(const TCHAR* pFileName);
	bool	GameDataLoad(T_STR name, GroupData& data);
	GroupData* GetPtr(int iKey);
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
private:
	ScriptMgr();
public:
	virtual ~ScriptMgr();
};

