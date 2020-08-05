#pragma once
#include "Std.h"

class Timer
{
public:
	float		m_fSecondPerFrame;	//프레임당 몇초?
	float		m_fAccumulation;	//실행이후 경과시간
	int			m_iFPS;				//1초에 진행된 프레임 카운터
	DWORD		m_dwBeforeTick;		//이전
	float		m_fFrameTime;		//1초를 세기 위해 사용되는 변수
	DWORD		m_dwFrameCount;		//몇프레임?
	TCHAR		m_csBuffer[MAX_PATH];
	float		m_fRuntime;
public:
	bool		Init();
	bool		Frame();
	//bool       Render();//렌더 아직 없음
	bool		Release();
	float		GetRuntime();
public:
	Timer();
	virtual ~Timer();
};