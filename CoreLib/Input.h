#pragma once
#include "Std.h"


class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	DWORD m_dwKeyState[256];	//254개의 가상키보드. 숫자와 알파벳은 빠져있다
	DWORD m_dwMouseState[3];	//좌,우,휠 세개 버튼 상태.
	DWORD m_dwPreMouseState[3];	//이전상태.
	//마우스 위치값. 매 프레임마다 저장될 수 있게 잡을 것.
	POINT m_MousePos;

public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	DWORD		KeyCheck(DWORD dwKey);
	LRESULT		MsgProc(MSG msg);
	LRESULT		MsgProc(UINT message);
	//DWORD		Key(DWORD dwKey); //<-뭐하는 함수???/
private:
	Input();		//private처리
public:
	virtual ~Input();
};
