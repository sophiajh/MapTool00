#pragma once
#include "Std.h"
#include <map>
#include "fmod.hpp"
#include <string>

class Sound
{
	//FMOD시스템 시작, 곡 이름, 인덱스.
public:
	FMOD::System*	m_pSystem;
	std::string		m_szName;
	int				m_iIndex;
	//사운드, 사운드 개수, 볼륨, 채널,버퍼
public:
	FMOD::Sound*	m_pSound;
	int				m_iSoundNum;
	float			m_fVolume;
	FMOD::Channel*	m_pChannel;
	std::string		m_csBuffer;
	//재생, 정지, 멈춤, 볼륨, 효과음, 모드
public:
	void	Play();
	void	Stop();
	void	Paused();
	void	Volume(float, bool bUp = true);
	void	PlayEffect();
	//++
	void	SetMode(DWORD dwMode); //모드(재생시 loop) 설정.
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

//class Sound		//리소스.
//{
//	//사운드 엔진 사용. fmod.com
//	//클래스 분리할것. 이제 sound는 한 소리만 관리하게 되므로 사운드 배열 필요 없고 기능들에 사운드을 지정해서 넘겨줄 필요도 없다.
//	//플레이함수에만 시스템 넘김.
//};