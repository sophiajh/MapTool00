#include "SoundMgr.h"

//bool SoundMgr::Init()
//{
//	FMOD::System_Create(&m_pSystem); //�������̽� ����.
//	m_pSystem->init(32, FMOD_INIT_NORMAL, 0); //fmod���� �ý��� �ʱ�ȭ.
//	//���� �ϳ��� �ε��ؿ� �����ϱ�.
//	FMOD_RESULT ret = m_pSystem->createSound("../../data/sound/xxx.mp3",FMOD_DEFAULT, 0, &m_pSound[m_iNumSoundList++]);//���带 �ε��ؿ� ó������ ���ִ� �Լ�. �� ������ �ε��ؼ�/~����/�迭�� �־��� ��.
//	FMOD::Channel*	pChannel;
//	m_pSystem->playSound(m_pSound[0], 0, false, &pChannel); //�� ���带 / / �ٷ� Ʋ���/ ��ä�ο� ���� �־��
//	return true;						//����Ǵ� ����� ä�ο� ���ؼ� �����ȴ�.
//
//	//�Լ� �и���. SoundMgr::Load(char* pSoundFile) �ε��� �ε����, ������ ������.
//}
//Init, load, ������� ��� �ϳ��� ���ԵǾ� ����. �Ʒ�ó�� ��� �и�.

int SoundMgr::Load(const char* pSoundFile)
{
	//FMOD_RESULT ret = m_pSystem->createSound(pSoundFile, FMOD_DEFAULT, 0, &m_pSound[m_iNumSound++]);
	//			//FMOD_RESULT : Error codes returned from every function.
	//			//createSound : Loads a sound into memory, or opens it for streaming.
	//if (ret != FMOD_OK)
	//{
	//	return -1;
	//}
	//return m_iNumSound - 1;
	//���ͷ����� ���� ������� ���� Load
	
	for (ITOR itor = m_List.begin(); itor != m_List.end();)
	{
		Sound* p_Sound = (*itor).second;
		if (p_Sound->m_szName == pSoundFile)
		{
			return p_Sound->m_iIndex;
		}
	}

	Sound* p_Sound = new Sound;
	FMOD_RESULT ret = m_pSystem->createSound(pSoundFile, FMOD_DEFAULT, 0, &p_Sound->m_pSound);
	if (ret != FMOD_OK)
	{
		return -1;
	}
	p_Sound->m_pSystem = m_pSystem;
	p_Sound->m_szName = pSoundFile;
	p_Sound->m_iIndex = m_iNumSound++;

	m_List.insert(std::make_pair(p_Sound->m_iIndex, p_Sound));
	return p_Sound->m_iIndex;

}

void SoundMgr::Play(int iKey)
{
	//m_pSystem->playSound(m_pSound[iSound], 0, false, &m_pChannel[iSound]);	//Plays a Sound on a Channel.
	//m_pChannel[iSound]->setVolume(m_fVolume);
	//m_pChannel[iSound]->setMode(FMOD_DEFAULT);	//Sets the playback mode that controls how this object behaves.(default : loop)
	//���ͷ����� ���� ����.

	ITOR itor = m_List.find(iKey); //find : Returns an iterator that refers to the location of an element in a map that has a key equivalent to a specified key.
	if (itor != m_List.end())
	{
		Sound* pSound = (*itor).second;
		pSound->Play();
	}
}

//
//void SoundMgr::Stop(int iSound)
//{
//	m_pChannel[iSound]->stop();
//}
//
//void SoundMgr::Paused(int iSound)
//{
//	bool paused;
//	m_pChannel[iSound]->getPaused(&paused);
//	m_pChannel[iSound]->setPaused(!paused);
//}
//void SoundMgr::Volume(int iSound, float fVolume, bool bUp) //�ʴ� �ö󰡴� ���� ����
//{
//	float fCurrentVolume;
//	m_pChannel[iSound]->getVolume(&fCurrentVolume);
//	if (bUp == true)
//	{
//		fCurrentVolume += fVolume * g_fSecondPerFrame * 10.0f;
//		fCurrentVolume = min(1.0f, fCurrentVolume);
//	}
//	else
//	{
//		fCurrentVolume -= fVolume * g_fSecondPerFrame * 10.0f;
//		fCurrentVolume = max(1.0f, fCurrentVolume);
//	}
//	m_pChannel[iSound]->setVolume(fCurrentVolume);
//}
//void SoundMgr::PlayEffect(int iSound)
//{
//	FMOD::Channel* pChannel;
//	m_pSystem->playSound(m_pSound[iSound], 0, false, &pChannel);
//	pChannel->setVolume(m_fVolume);
//	pChannel->setMode(FMOD_LOOP_OFF);
//}
bool SoundMgr::Init()
{
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, 0);	
	return true;
}
Sound* SoundMgr::GetPtr(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor != m_List.end())
	{
		Sound* pSound = (*itor).second;
		return pSound;
	}
	return nullptr;
}
bool SoundMgr::Frame()
{
	//m_pSystem->update();		//FMOD::update() FMOD�ý����� ������Ʈ�Ѵ�. Should be called once per 'game' tick
	//unsigned int total = 0;
	//unsigned int ms = 0;
	//m_pSound[0]->getLength(&total, FMOD_TIMEUNIT_MS);	//getLength�� sound�� ���̸� ������.
	//m_pChannel[0]->getPosition(&ms, FMOD_TIMEUNIT_MS);	//getPosition�� ���� playback position�� ������.(�����ġ)
	//					//millisecond
	//static float fTimer = 0.0f;
	//fTimer += g_fSecondPerFrame;
	//if (fTimer >= 1)
	//{
	//	fTimer = 0.0f;
	//	char  szBuffer1[256] = { 0, };
	//	char  szBuffer2[256] = { 0, };
	//	sprintf(szBuffer1, "��üũ�� : [%02d:%02d:%02d]", 
	//		total / 1000 / 60, 
	//		total / 1000 % 60, 
	//		total / 10 % 60);
	//	sprintf(szBuffer2, "����ð� : [%02d:%02d:%02d]", 
	//		total / 1000 / 60, 
	//		total / 1000 % 60, 
	//		total / 10 % 60);
	//	m_csBuffer = szBuffer1;
	//	m_csBuffer += szBuffer2;
	//	OutputDebugStringA(m_csBuffer.c_str());	//OutputDebugStringA : Sends a string to the debugger for display.
	//											//c_str : ���ڿ��� ������ c��Ÿ���� null�� ����Ǵ� ���ڿ��� ��ȯ�մϴ�.
	//}
	//���ͷ����� ����.

	m_pSystem->update();
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		Sound* pSound = (*itor).second;
		pSound->Frame();
	}

	return true;
}
bool SoundMgr::Render()
{
	for (ITOR itor = m_List.begin();itor != m_List.end();itor++)
	{
		Sound* pSound = (*itor).second;
		pSound->Render();
	}
	return true;
}
bool SoundMgr::Release()
{
	/*for (int iSound = 0; iSound < g_iMaxSound; iSound++)
	{
		m_pSound[iSound]->release();
	}
	m_pSystem->close();
	m_pSystem->release();
	return true;*/
	//���ͷ����� ����

	for (ITOR itor = m_List.begin();itor != m_List.end();)
	{
		Sound* pSound = (*itor).second;
		pSound->Release();
		delete pSound;
		itor = m_List.erase(itor);
	}

	m_List.clear();

	m_pSystem->close();
	m_pSystem->release();
	return true;
}

bool SoundMgr::Delete(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor != m_List.end())
	{
		Sound* Tmp = (*itor).second;
		Tmp->Release();
		delete Tmp;
		m_List.erase(itor);	//Removes an element or a range of elements in a map from specified positions or removes elements that match a specified key.
		return true;
	}
	return false;
}
SoundMgr::SoundMgr()
{
	m_iNumSound = 0;
	m_fVolume = 0.5f;
}


SoundMgr::~SoundMgr()
{
}
