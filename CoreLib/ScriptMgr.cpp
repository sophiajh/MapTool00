#include "ScriptMgr.h"
#include "BitmapMgr.h"

bool ScriptMgr::GameDataLoad(T_STR name, GroupData & data)
{
	FILE* fp = 0;
	_wfopen_s(&fp, name.c_str(), _T("rt"));
	if (fp == NULL) return false;

	TCHAR buffer[256] = { 0, };
	TCHAR temp[256] = { 0, };
	TCHAR bitmap[256] = { 0, };
	int iNumSprite = -1;

	_fgetts(buffer, _countof(buffer), fp);
	_stscanf_s(buffer, _T("%s%d%s"), 
		temp, _countof(temp), 
		&iNumSprite, 
		bitmap, _countof(bitmap)); //마스크 필요없음 //여기서 맨 첫줄 받아감 #Object 2 character2.bmp

	T_STR path = L"../../data/solo2Dproject/";
	T_STR BitmapPath = path + bitmap;
	//data.m_iBitmapID = BitmapMgr::GetInstance().Load(BitmapPath.c_str());
	data.m_ImageList.resize(iNumSprite);

	int iNumFrame = -1;
	for (int iSprite = 0; iSprite < iNumSprite; iSprite++)
	{
		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%d%f%f%f%f%s"), 
			temp, _countof(temp), 
			&data.m_ImageList[iSprite].iNumFrame,
			&data.m_ImageList[iSprite].Initpos.x, 
			&data.m_ImageList[iSprite].Initpos.y,
			&data.m_ImageList[iSprite].fTime_,
			&data.m_ImageList[iSprite].fLifrTime,
			bitmap, _countof(bitmap)); //여기서 각 그룹당 첫 안내?글 받아감

		if (_tcscmp(bitmap, L"null"))
		{
			BitmapPath.clear();
			BitmapPath = path + bitmap;
			//data.m_ImageList[iSprite].iBitmapID = BitmapMgr::GetInstance().Load(BitmapPath.c_str());
		}
		data.m_ImageList[iSprite].rtList.resize(data.m_ImageList[iSprite].iNumFrame);

		int iCount = -1;
		for (int iCnt = 0; iCnt < data.m_ImageList[iSprite].iNumFrame; iCnt++)
		{
			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%d%d%d%d%d"),
				&iCount,
				&data.m_ImageList[iSprite].rtList[iCnt].left,		//여기서 입력된 rt값을 받음.
				&data.m_ImageList[iSprite].rtList[iCnt].top,
				&data.m_ImageList[iSprite].rtList[iCnt].right,
				&data.m_ImageList[iSprite].rtList[iCnt].bottom);
		}
	}
	fclose(fp);
	return true;
}

int ScriptMgr::Load(const TCHAR* pFileName)
{
	GroupData data;
	if (GameDataLoad(pFileName, data))
	{
		data.m_iIndex = m_iIndex;
		data.m_szName = pFileName;
		m_List.insert(make_pair(m_iIndex++, data));
	}
	return m_iIndex - 1;
}

GroupData* ScriptMgr::GetPtr(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor == m_List.end())
	{
		return NULL;
	}
	GroupData* data = &(*itor).second;
	return data;
}

bool ScriptMgr::Init()
{
	return true;
}
bool ScriptMgr::Frame()
{
	return true;
}
bool ScriptMgr::Render() //렌더도 어쩌구저쩌구 해야됌
{
	return true;
}
bool ScriptMgr::Release()
{
	return true;
}
ScriptMgr::ScriptMgr()
{
	m_iIndex = 0;
}
ScriptMgr::~ScriptMgr()
{
}
