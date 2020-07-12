#include "Timer.h"
float g_fSecondPerFrame = 0.0f;
bool Timer::Init()
{
	m_dwBeforeTick = timeGetTime();
	return true;
}

float Timer::GetRuntime()
{
	m_fRuntime += g_fSecondPerFrame;
	return m_fRuntime;
}

bool Timer::Frame()
{
	DWORD m_dwCurrentTick = timeGetTime();
	DWORD dwElapseTick = m_dwCurrentTick - m_dwBeforeTick;
	m_fSecondPerFrame = dwElapseTick / 1000.0f;
	m_fAccumulation += m_fSecondPerFrame;
	m_fFrameTime += m_fSecondPerFrame;
	g_fSecondPerFrame = m_fSecondPerFrame;
	//g_fSecondPerFrame = m_fAccumulation;

	if (m_fFrameTime >= 1.0f)
	{
		m_iFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
		m_fFrameTime -= 1.0f;

		_stprintf_s(m_csBuffer, _T("Timer : [%10.4f], FPS : [%d]\n"), m_fAccumulation, m_iFPS);
		OutputDebugString(m_csBuffer);
	}
	m_dwFrameCount++;

	m_dwBeforeTick = m_dwCurrentTick;
	return true;
}

//bool Timer::Render()
//{
//	//HDC hdc = GetDC(g_hWnd);
//	SetBkColor(g_hOffScreenDC, RGB(0, 0, 0));
//	SetTextColor(g_hOffScreenDC, RGB(0, 0, 0));
//	SetBkMode(g_hOffScreenDC, TRANSPARENT);
//	TextOut(g_hOffScreenDC, 0, 0, m_csBuffer, _tcslen(m_csBuffer));
//	
//	return true;
//}

bool Timer::Release()
{
	return true;
}

Timer::Timer()
{
	m_fSecondPerFrame = 0.0f;
	m_fAccumulation = 0.0f;
	m_iFPS = 0;
	m_fFrameTime = 0.0f;

	m_dwFrameCount = 0;
}

Timer::~Timer()
{

}