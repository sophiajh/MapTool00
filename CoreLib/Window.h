#pragma once
#include "Std.h"
class Window
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	RECT		m_rtClient;		//클라이언트 부분 크기
	RECT		m_rtWindow;		//윈도우 창 크기
	DWORD		m_dwStyle;		//스타일 지정 쉽게
public:
	ATOM	  MyRegisterClass();
	void	  CenterWindow();
	BOOL	  InitWindow(HINSTANCE hInstance, int iX = 0, int iY = 0, int iWidth = 800, int iHeight = 600);
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	virtual bool ResizeDevice(UINT Width, UINT Height);

	//툴 사용
	void SetToolhWnd(HWND hWnd, HINSTANCE instance);

public:
	Window();
	virtual ~Window();
};

