#include "Input.h"

InputAction g_ActionInput;
POINT g_MousePos;
//std에서 extern으로 정의함.

DWORD Input::KeyCheck(DWORD dwKey)	//이전 상태를 검사하고 현재상태를 설정해줌.
{
	SHORT sKey = GetAsyncKeyState(dwKey);

	if (sKey & 0x8000)
	{
		if (m_dwKeyState[dwKey] == KEY_FREE || m_dwKeyState[dwKey] == KEY_UP)
		{
			m_dwKeyState[dwKey] = KEY_PUSH;
		}
		else
		{
			m_dwKeyState[dwKey] = KEY_HOLD;
		}
	}
	else
	{
		if (m_dwKeyState[dwKey] == KEY_PUSH || m_dwKeyState[dwKey] == KEY_HOLD)
		{
			m_dwKeyState[dwKey] = KEY_UP;
		}
		else
		{
			m_dwKeyState[dwKey] = KEY_FREE;

		}
	}
	return m_dwKeyState[dwKey];
}

bool Input::Init()	//keystate만 초기화. 왜 마우스는 여기서 초기화 안하지
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	return true;
}

bool Input::Frame() //매 프레임마다 갱신된다. 1)마우스 위치 2)키 이전/현재 상태 3)마우스 이전/현재 상태.
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);
	g_MousePos = m_MousePos;	//1)현재 프레임 마우스 포지션.
	if (g_MousePos.x > g_rtClient.right || g_MousePos.x < 0.0f || g_MousePos.y > g_rtClient.bottom || g_MousePos.y < 0.0f)
	{
		return false;
	}
	g_ActionInput.bWKey = KeyCheck('W');
	g_ActionInput.bAKey = KeyCheck('A');
	g_ActionInput.bSKey = KeyCheck('S');
	g_ActionInput.bDKey = KeyCheck('D');
	g_ActionInput.bLKey = KeyCheck('L');
	g_ActionInput.bOKey = KeyCheck('O');
	g_ActionInput.bSpaceKey = KeyCheck(VK_SPACE);
	g_ActionInput.bTabKey = KeyCheck(VK_TAB);
	g_ActionInput.bDownKey = KeyCheck(VK_DOWN);
	g_ActionInput.bUpKey = KeyCheck(VK_UP);
	g_ActionInput.bRightKey = KeyCheck(VK_RIGHT);
	g_ActionInput.bLeftKey = KeyCheck(VK_LEFT);

	//2)키 상태값. KeyCheck로. 

	//for (int iKey = 0; iKey < 3; iKey++)
	//{
	//	if (m_dwPreMouseState[iKey] == KEY_PUSH)
	//	{
	//		if (m_dwMouseState[iKey] == KEY_PUSH)
	//		{
	//			m_dwMouseState[iKey] = KEY_HOLD;
	//		}
	//	}
	//	m_dwPreMouseState[iKey] = m_dwMouseState[iKey];
	//}//마우스의 이전 상태값을 누적할 수 있는 for문

	g_ActionInput.bLeftClick = KeyCheck(VK_LBUTTON);
	g_ActionInput.bMiddleClick = KeyCheck(VK_MBUTTON);
	g_ActionInput.bRightClick = KeyCheck(VK_RBUTTON);
	//3)전역변수에 마우스의 현재/이전 상태를 저장.
	return true;
}

bool Input::Render()
{
	return true;
}

bool Input::Release()
{
	return true;
}

LRESULT Input::MsgProc(UINT message)
{

	m_dwMouseState[0] = KEY_FREE;
	m_dwMouseState[1] = KEY_FREE;
	m_dwMouseState[2] = KEY_FREE;
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_dwMouseState[0] = KEY_PUSH;		//현재 프레임에 해당하는 마우스 상태. 이전상태값은 알수 없다.
	}break;
	case WM_LBUTTONUP:
	{
		m_dwMouseState[0] = KEY_UP;
	}break;
	case WM_MBUTTONDOWN:
	{
		m_dwMouseState[1] = KEY_PUSH;
	}break;
	case WM_MBUTTONUP:
	{
		m_dwMouseState[1] = KEY_UP;
	}break;
	case WM_RBUTTONDOWN:
	{
		m_dwMouseState[2] = KEY_PUSH;
	}break;
	case WM_RBUTTONUP:
	{
		m_dwMouseState[2] = KEY_UP;
	}break;
	}
	return 1;
}


LRESULT Input::MsgProc(MSG msg)
{
	m_dwMouseState[0] = KEY_FREE;
	m_dwMouseState[1] = KEY_FREE;
	m_dwMouseState[2] = KEY_FREE;
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
	{
		m_dwMouseState[0] = KEY_PUSH;		//현재 프레임에 해당하는 마우스 상태. 이전상태값은 알수 없다.
	}break;
	case WM_LBUTTONUP:
	{
		m_dwMouseState[0] = KEY_UP;
	}break;
	case WM_MBUTTONDOWN:
	{
		m_dwMouseState[1] = KEY_PUSH;
	}break;
	case WM_MBUTTONUP:
	{
		m_dwMouseState[1] = KEY_UP;
	}break;
	case WM_RBUTTONDOWN:
	{
		m_dwMouseState[2] = KEY_PUSH;
	}break;
	case WM_RBUTTONUP:
	{
		m_dwMouseState[2] = KEY_UP;
	}break;
	}
	return 1;
}

Input::Input()
{

}

Input::~Input()
{

}