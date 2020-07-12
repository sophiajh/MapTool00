#pragma once
#include "Std.h"


class Input : public Singleton<Input>
{
	friend class Singleton<Input>;
public:
	DWORD m_dwKeyState[256];	//254���� ����Ű����. ���ڿ� ���ĺ��� �����ִ�
	DWORD m_dwMouseState[3];	//��,��,�� ���� ��ư ����.
	DWORD m_dwPreMouseState[3];	//��������.
	//���콺 ��ġ��. �� �����Ӹ��� ����� �� �ְ� ���� ��.
	POINT m_MousePos;

public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	DWORD		KeyCheck(DWORD dwKey);
	LRESULT		MsgProc(MSG msg);
	LRESULT		MsgProc(UINT message);
	//DWORD		Key(DWORD dwKey); //<-���ϴ� �Լ�???/
private:
	Input();		//privateó��
public:
	virtual ~Input();
};
