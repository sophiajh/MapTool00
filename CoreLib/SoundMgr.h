#pragma once
#include "Sound.h"
//#include "fmod.hpp"	//사운드
//링크드리스트 대신 맵사용.
//map은 사전식 컨테이너로 < 키, 값 > 구조.
//#include <map>
//std::vector<Sound*>	m_List; 배열을 리스트화		front<->back push가능. 중간이라도 내가 넣고 싶은 자리에 넣을 수 있다.
//std::list<Sound*>		m_List;연결리스트			동일
//std::set<Sound*>		m_List;중복 불가.			동일

//vector와 map만 인덱싱 지원. 리스트를 배열로 접근 가능.

//std::map<DWORD, Sound*>	m_List;					
//매니저는 보통 map사용. 외부에는 키값(DWORD)을 노출하고 뒷부분은 매니저만 사용. 키값은 문자열(정수, 객체,....)로 지정해줄 수도 있다.
//★stl map은 기본적으로 검색을 고려한다. 검색을 최적화한 stl
//기본저장방식이 BST <binary search tree>. 따라서 내가 입력insert한 데이터 순서대로 존재하지 않는다. find필요
//make_pair(키,값) 키랑 값이 연결된다. m_List.insert(make_pair(키, 값))처럼 넘김. 인덱싱으로 직접 넘길 수 있지만 느리다.
//*map사용할때 인덱스 0부터 주는게 일반적이다(?)0은 데이터 없음을 의미해서

const int g_iMaxSound = 10;



//플레이함수는 사운드매니저에 넣고 키값을 넘겨서 플레이하는 방법.
//플레이에서 find내장함수에 키를 주고 원하는 사운드를 찾을수 있다. 그러나 이터레이터 패턴이므로 값이 들어있는 NODE를 넘겨준다.
//std::map<int, Sound*>::iterator itor -> 노드!(박스, 포장지)
//모든 stl에는 머리는 없어도 꼬리는 있다. 오류검사할 때 참고할 수 있다.
//itor 안에 first는 key, second는 값

//이제부터 외부에서는 인덱스만 있으면 사운드 플레이가 가능하다. 다른 조작을 원하면 포인터로 줘야한다.

//map을 reverse_iterator로 주고 rbegin rend를 사용하면 for문 돌릴때 뒤에서부터 검색할수도 있다.

//system만 매니저에서 필요함.
//사운드개수 정도만 남김. sdt::map사용할것. 로드도 남김.
class SoundMgr : public Singleton<SoundMgr>	//사운드 매니저. 싱글톤으로 사용.
{
	//프렌드
	friend class Singleton<SoundMgr>;
public:
	FMOD::System*		m_pSystem;//FMOD사용하기 위해서 반드시 필요.		///sound에서 받아서 사용할것. 전체에서 system은 하나
	FMOD::Sound*		m_pSound[10]; //사운드를 10개 만들것!
	int					m_iNumSound; //사운드 개수가 몇개인가

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

	//PlayEffect는 효과음. 단발적. 채널 저장 필요 없음. 임시사용
	//프레임 넣어줘야함. 사운드가 여러개 나올때 프레임에서 업데이트를 해줘야 한다.

	//frame에서 사운드 길이 구해줘야함.

	//키와 값을 동시에 가지는 자료 구조 = 맵. 따라서 반드시 키가 있어야 한다.
	typedef std::map<int, Sound*>::iterator ITOR;
	std::map<int, Sound*>	m_List;

private: //private 생성자.
	SoundMgr();		//private처리
public:
	~SoundMgr();
};

