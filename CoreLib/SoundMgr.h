#pragma once
#include "Sound.h"
//#include "fmod.hpp"	//����
//��ũ�帮��Ʈ ��� �ʻ��.
//map�� ������ �����̳ʷ� < Ű, �� > ����.
//#include <map>
//std::vector<Sound*>	m_List; �迭�� ����Ʈȭ		front<->back push����. �߰��̶� ���� �ְ� ���� �ڸ��� ���� �� �ִ�.
//std::list<Sound*>		m_List;���Ḯ��Ʈ			����
//std::set<Sound*>		m_List;�ߺ� �Ұ�.			����

//vector�� map�� �ε��� ����. ����Ʈ�� �迭�� ���� ����.

//std::map<DWORD, Sound*>	m_List;					
//�Ŵ����� ���� map���. �ܺο��� Ű��(DWORD)�� �����ϰ� �޺κ��� �Ŵ����� ���. Ű���� ���ڿ�(����, ��ü,....)�� �������� ���� �ִ�.
//��stl map�� �⺻������ �˻��� ����Ѵ�. �˻��� ����ȭ�� stl
//�⺻�������� BST <binary search tree>. ���� ���� �Է�insert�� ������ ������� �������� �ʴ´�. find�ʿ�
//make_pair(Ű,��) Ű�� ���� ����ȴ�. m_List.insert(make_pair(Ű, ��))ó�� �ѱ�. �ε������� ���� �ѱ� �� ������ ������.
//*map����Ҷ� �ε��� 0���� �ִ°� �Ϲ����̴�(?)0�� ������ ������ �ǹ��ؼ�

const int g_iMaxSound = 10;



//�÷����Լ��� ����Ŵ����� �ְ� Ű���� �Ѱܼ� �÷����ϴ� ���.
//�÷��̿��� find�����Լ��� Ű�� �ְ� ���ϴ� ���带 ã���� �ִ�. �׷��� ���ͷ����� �����̹Ƿ� ���� ����ִ� NODE�� �Ѱ��ش�.
//std::map<int, Sound*>::iterator itor -> ���!(�ڽ�, ������)
//��� stl���� �Ӹ��� ��� ������ �ִ�. �����˻��� �� ������ �� �ִ�.
//itor �ȿ� first�� key, second�� ��

//�������� �ܺο����� �ε����� ������ ���� �÷��̰� �����ϴ�. �ٸ� ������ ���ϸ� �����ͷ� ����Ѵ�.

//map�� reverse_iterator�� �ְ� rbegin rend�� ����ϸ� for�� ������ �ڿ������� �˻��Ҽ��� �ִ�.

//system�� �Ŵ������� �ʿ���.
//���尳�� ������ ����. sdt::map����Ұ�. �ε嵵 ����.
class SoundMgr : public Singleton<SoundMgr>	//���� �Ŵ���. �̱������� ���.
{
	//������
	friend class Singleton<SoundMgr>;
public:
	FMOD::System*		m_pSystem;//FMOD����ϱ� ���ؼ� �ݵ�� �ʿ�.		///sound���� �޾Ƽ� ����Ұ�. ��ü���� system�� �ϳ�
	FMOD::Sound*		m_pSound[10]; //���带 10�� �����!
	int					m_iNumSound; //���� ������ ��ΰ�

	float				m_fVolume;
	FMOD::Channel*		m_pChannel[g_iMaxSound];
	std::string			m_csBuffer;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	int		Load(const char* pSoundFile);
	void	Play(int iSound);
	//void	Stop(int iSound);
	//void	Paused(int iSound);
	//void	Volume(int, float, bool);
	//void	PlayEffect(int iSound);
	bool	Delete(int iKey);
	Sound*	GetPtr(int iKey);

	//PlayEffect�� ȿ����. �ܹ���. ä�� ���� �ʿ� ����. �ӽû��
	//������ �־������. ���尡 ������ ���ö� �����ӿ��� ������Ʈ�� ����� �Ѵ�.

	//frame���� ���� ���� ���������.

	//Ű�� ���� ���ÿ� ������ �ڷ� ���� = ��. ���� �ݵ�� Ű�� �־�� �Ѵ�.
	typedef std::map<int, Sound*>::iterator ITOR;
	std::map<int, Sound*>	m_List;

private: //private ������.
	SoundMgr();		//privateó��
public:
	~SoundMgr();
};

