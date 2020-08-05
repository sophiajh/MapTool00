#pragma once
#include "Std.h"

class Timer
{
public:
	float		m_fSecondPerFrame;	//�����Ӵ� ����?
	float		m_fAccumulation;	//�������� ����ð�
	int			m_iFPS;				//1�ʿ� ����� ������ ī����
	DWORD		m_dwBeforeTick;		//����
	float		m_fFrameTime;		//1�ʸ� ���� ���� ���Ǵ� ����
	DWORD		m_dwFrameCount;		//��������?
	TCHAR		m_csBuffer[MAX_PATH];
	float		m_fRuntime;
public:
	bool		Init();
	bool		Frame();
	//bool       Render();//���� ���� ����
	bool		Release();
	float		GetRuntime();
public:
	Timer();
	virtual ~Timer();
};