#include "Sound.h"


void Sound::Stop()
{
	m_pChannel->stop();
}

void Sound::Paused()
{
	if (m_pChannel == nullptr) return;
	bool paused;
	m_pChannel->getPaused(&paused);
	m_pChannel->setPaused(!paused);
}

void Sound::Volume(float fVolume, bool bUp) //ÃÊ´ç ¿Ã¶ó°¡´Â º¼·ý °³³ä
{
	float fCurrentVolume;
	m_pChannel->getVolume(&fCurrentVolume);
	if (bUp == true)
	{
		fCurrentVolume += fVolume * g_fSecondPerFrame * 10.0f;
		fCurrentVolume = min(1.0f, fCurrentVolume);
	}
	else
	{
		fCurrentVolume -= fVolume * g_fSecondPerFrame * 10.0f;
		fCurrentVolume = max(1.0f, fCurrentVolume);
	}
	m_pChannel->setVolume(fCurrentVolume);
}
void Sound::PlayEffect()
{
	FMOD::Channel* pChannel = nullptr;
	pChannel->setVolume(m_fVolume);
	pChannel->setMode(FMOD_LOOP_OFF);
	m_pSystem->playSound(m_pSound, 0, false, &pChannel);
}

void Sound::Play()
{
	bool playing = false;
	if (m_pChannel)
	{
		m_pChannel->isPlaying(&playing);
	}
	if (playing == false)
	{
		m_pSystem->playSound(m_pSound, 0, false, &m_pChannel);
		m_pChannel->setVolume(m_fVolume);
	}
}
void Sound::SetMode(DWORD dwMode)
{
	m_pChannel->setMode(dwMode);
}

bool Sound::Init()
{
	return true;
}

bool Sound::Frame()
{
	return true;
}

bool Sound::Render()
{
	return true;
}

bool Sound::Release()
{
	if (m_pSound == nullptr) return false;
	m_pSound->release();
	return true;
}

Sound::Sound()
{
	//m_pSystem = nullptr;
	m_pSound = nullptr;
	m_pChannel = nullptr;
	m_fVolume = 0.5f;
}


Sound::~Sound()
{
}
