#pragma once
#include "Std.h"
class Window
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	RECT		m_rtClient;		//Ŭ���̾�Ʈ �κ� ũ��
	RECT		m_rtWindow;		//������ â ũ��
	DWORD		m_dwStyle;		//��Ÿ�� ���� ����
public:
	ATOM	  MyRegisterClass();
	void	  CenterWindow();
	BOOL	  InitWindow(HINSTANCE hInstance, int iX = 0, int iY = 0, int iWidth = 800, int iHeight = 600);
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	virtual bool ResizeDevice(UINT Width, UINT Height);

	//�� ���
	void SetToolhWnd(HWND hWnd, HINSTANCE instance);

public:
	Window();
	virtual ~Window();
};

