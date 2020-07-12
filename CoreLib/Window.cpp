#include "Window.h"
HWND g_hWnd;
HINSTANCE g_hInstance;
RECT g_rtClient;
Window* g_pWindow = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // LONG (�޼��� �߻� ������ �ڵ�, �޼���, �޼����� ���� �ΰ�����1, �ΰ����� 2)
{
	if (g_pWindow != NULL)
	{
		g_pWindow->MsgProc(hWnd, msg, wParam, lParam);						//main MsgProc�� ���޵�
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
	return DefWindowProc(hWnd, msg, wParam, lParam);  //WndProc���� ó������ ���� DefWindowProc ������ �޽����� ���� ó��
}

LRESULT Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return 1;
}

ATOM Window::MyRegisterClass()		//� �����츦 ������ ������ OS�� ���. ������ �����쿡 ���� ������ ��ϵǾ� �־�� �����츦 ��� �� �ִ�.
{												//������ Ŭ������ ���� ����ϰ� createwindow�Լ��� ȣ��.
	WNDCLASSEXW wcex;
	wcex.lpfnWndProc = WndProc;		//�߿�!OS�� ���� �޼���. WndProc�� �����쿡�� ���� �޼����� ����.
	wcex.hInstance = m_hInstance;	//OS�� �� �㰡��ȣ
	wcex.lpszClassName = L"KJH";	//�߿�!�츮�� ����ϴ� Ŭ���� �̸�. ���⼭ ������ �̸��� createwindow�Լ��� ���޵ȴ�.

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;				//������â ���μ���
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//Ŭ���̾�Ʈ ����
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

	RECT rt = { 0,0,iWidth,iHeight };	//���� ���ϴ� ������ â ũ��.
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE); //(�簢��, ��Ÿ��, �޴�)

										//createwindow ������ �ڵ��� �����Ѵ�.
	m_hWnd = CreateWindow(L"KJH",	//lpClassName
		L"DXWindow",				//lpWindowName
		WS_OVERLAPPEDWINDOW,		//dwStyle
		iX, iY,						//��ǥ 
		rt.right - rt.left,			//�ʺ�
		rt.bottom - rt.top,			//����
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
	ShowWindow(m_hWnd, SW_SHOW);	//createwindow�� ���� ������� �޸𸮻󿡸� ������, showwindow�� ����ؾ� �ѷ�����. 
									//hWnd, int(âȰ��ȭ���·� ����)
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
	//�̻� �����찡 ������.
	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);
	g_rtClient = m_rtClient;
	//�̻� MFC�� ��� �����츦 �������.
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
