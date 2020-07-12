#include "Window.h"
HWND g_hWnd;
HINSTANCE g_hInstance;
RECT g_rtClient;
Window* g_pWindow = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // LONG (메세지 발생 윈도우 핸들, 메세지, 메세지에 따른 부가정보1, 부가정보 2)
{
	if (g_pWindow != NULL)
	{
		g_pWindow->MsgProc(hWnd, msg, wParam, lParam);						//main MsgProc로 전달됨
	}
	switch (msg)
	{
		case WM_SIZE:
		{
			UINT Width = LOWORD(lParam);
			UINT Height = HIWORD(lParam);
			g_pWindow->ResizeDevice(Width, Height);
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);  //WndProc에서 처리되지 않은 DefWindowProc 나머지 메시지에 관한 처리
}

LRESULT Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 1;
}

ATOM Window::MyRegisterClass()		//어떤 윈도우를 생성할 것인지 OS에 등록. 생성될 윈도우에 대한 내용이 등록되어 있어야 윈도우를 띄울 수 있다.
{												//윈도우 클래스를 먼저 등록하고 createwindow함수를 호출.
	WNDCLASSEXW wcex;
	wcex.lpfnWndProc = WndProc;		//중요!OS가 보낸 메세지. WndProc에 윈도우에서 보낸 메세지가 들음.
	wcex.hInstance = m_hInstance;	//OS가 준 허가번호
	wcex.lpszClassName = L"KJH";	//중요!우리가 등록하는 클래스 이름. 여기서 지정한 이름이 createwindow함수에 전달된다.

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;				//윈도우창 가로세로
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//클라이언트 영역
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.lpszMenuName = NULL;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	if (!RegisterClassExW(&wcex))
		return false;
	return true;
	
}
BOOL Window::InitWindow(HINSTANCE hInstance, int iX, int iY, int iWidth, int iHeight)
{
	m_hInstance = hInstance;

	if (!MyRegisterClass())
		return false;

	RECT rt = { 0,0,iWidth,iHeight };	//내가 원하는 윈도우 창 크기.
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE); //(사각형, 스타일, 메뉴)

										//createwindow 윈도우 핸들을 리턴한다.
	m_hWnd = CreateWindow(L"KJH",	//lpClassName
		L"DXWindow",				//lpWindowName
		WS_OVERLAPPEDWINDOW,		//dwStyle
		iX, iY,						//좌표 
		rt.right - rt.left,			//너비
		rt.bottom - rt.top,			//높이
		NULL,						//hWndParent
		NULL,						//hMenu
		m_hInstance,				//hInstance
		NULL);						//lpParam

	g_hWnd = m_hWnd;
	GetClientRect(m_hWnd, &m_rtClient);
	g_rtClient = m_rtClient;
	GetWindowRect(m_hWnd, &m_rtWindow);

	CenterWindow();

	if (m_hWnd == NULL) return 0;
	ShowWindow(m_hWnd, SW_SHOW);	//createwindow로 만든 윈도우는 메모리상에만 있으며, showwindow를 사용해야 뿌려진다. 
									//hWnd, int(창활성화상태로 열기)
	return true;

}

void Window::CenterWindow()
{
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int x = (iScreenWidth - (m_rtWindow.right - m_rtWindow.left)) / 2;
	int y = (iScreenHeight - (m_rtWindow.bottom - m_rtWindow.top)) / 2;
	MoveWindow(m_hWnd,x, y, m_rtWindow.right - m_rtWindow.left, m_rtWindow.bottom - m_rtWindow.top, true);
}

void Window::SetToolhWnd(HWND hWnd, HINSTANCE instance)
{
	m_hWnd = hWnd;
	m_hInstance = instance;
	g_hWnd = hWnd;
	g_hInstance = instance;
	//이상 윈도우가 생성됨.
	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);
	g_rtClient = m_rtClient;
	//이상 MFC가 대신 윈도우를 만들어줌.
}
bool Window::ResizeDevice(UINT Width, UINT Height)
{
	return true;
}
Window::Window()
{
	m_dwStyle = WS_OVERLAPPEDWINDOW;
	g_pWindow = this;
}
Window::~Window()
{
}
