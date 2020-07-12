#pragma once
#include "Std.h"
#include <map>
#include "fmod.hpp"
#include <string>

class Sound
{
	//FMOD�ý��� ����, �� �̸�, �ε���.
public:
	FMOD::System*	m_pSystem;
	std::string		m_szName;
	int				m_iIndex;
	//����, ���� ����, ����, ä��,����
public:
	FMOD::Sound*	m_pSound;
	int				m_iSoundNum;
	float			m_fVolume;
	FMOD::Channel*	m_pChannel;
	std::string		m_csBuffer;
	//���, ����, ����, ����, ȿ����, ���
public:
	void	Play();
	void	Stop();
	void	Paused();
	void	Volume(float, bool bUp = true);
	void	PlayEffect();
	//++
	void	SetMode(DWORD dwMode); //���(����� loop) ����.
	//Init, Frame, Render, Release
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	Sound();
	virtual ~Sound();
};

//class Sound		//���ҽ�.
//{
//	//���� ���� ���. fmod.com
//	//Ŭ���� �и��Ұ�. ���� sound�� �� �Ҹ��� �����ϰ� �ǹǷ� ���� �迭 �ʿ� ���� ��ɵ鿡 ������ �����ؼ� �Ѱ��� �ʿ䵵 ����.
//	//�÷����Լ����� �ý��� �ѱ�.
//};