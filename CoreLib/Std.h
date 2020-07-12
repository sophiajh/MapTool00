#pragma once
#define _CRT_SECURE_NO_WARNINGS

#if defined(DEBUG) || defined(_DEBUG)
#if defined(_WIN64)
#pragma comment( lib, "DXCoreLib64_D.lib" )
#endif
#else
#if defined(_WIN64)
#pragma comment( lib, "DXCoreLib64_R.lib" )
#endif
#endif

#include <windows.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <assert.h>
#include <time.h>
#include <memory>
//
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10math.h>
#include "DxState.h"
//
#include <functional>
#include <algorithm>
using namespace std;

//#pragma comment(lib, "DXCoreLib.lib")
#pragma comment( lib, "msimg32")
//
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
//
//액션맵
typedef std::basic_string<TCHAR>	T_STR;
typedef std::basic_string<char>		C_STR;
typedef std::basic_string<WCHAR>	W_STR;
typedef std::vector<T_STR>			T_STR_VECTOR;
extern HWND g_hWnd;

struct InputAction
{
	DWORD	bWKey;
	DWORD	bAKey;
	DWORD	bSKey;
	DWORD	bDKey;
	DWORD	bLKey;
	DWORD	bOKey;
	DWORD	bSpaceKey;
	DWORD	bLeftClick;
	DWORD	bMiddleClick;
	DWORD	bRightClick;
	DWORD	bTabKey;

	DWORD	bRightKey;
	DWORD	bLeftKey;
	DWORD	bUpKey;
	DWORD	bDownKey;
};

extern InputAction g_ActionInput;	//키입력 처리를 위한 extern변수.
extern POINT g_MousePos;

extern float g_fSecondPerFrame;

enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP }; // 0, 1, 2, 3자동으로 

template <class T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T singleton;
		return singleton;
	};
};

//extern HDC g_hScreenDC;
//extern HDC g_hOffScreenDC;
//extern HDC g_hMemDC;
extern RECT g_rtClient;
extern HINSTANCE g_hInstance;

extern int iNewSize; //player 회전영역 확보후 변의 길이
extern int g_iSceneNum;

extern bool g_bAttacked;

struct xPoint
{
	float	x;
	float	y;
	xPoint() {};
	xPoint(float fx, float fy) { x = fx; y = fy; };
} ;

extern xPoint g_PlayerPos;
extern RECT g_PlayerHitRect;
extern float g_fCamera;

struct ObjectInfo
{
	xPoint	Initpos;
	RECT	rt;
	float	fSpeed;

	int		iNumFrame;
	float	fTime_;
	float	fLifrTime;
	int		iBitmapID;
	int		iMaskID;
	bool	bLoop;
	xPoint	pos;

	std::vector<RECT> rtList;

	ObjectInfo() {
		iBitmapID = -1;
		iMaskID = -1;
		bLoop = false;
	};
	ObjectInfo(xPoint p, RECT r, float f)
	{
		pos = p;
		rt = r;
		fSpeed = f;
		iBitmapID = -1;
		iMaskID = -1;
		bLoop = false;

	}
};

struct xRECT
{
	float	left;
	float	top;
	float	right;
	float	bottom;
	xRECT() {};
	xRECT(float a, float b, float c, float d)
	{
		left = a;
		top = b;
		right = c;
		bottom = d;
	}
};

struct Vertex
{
	xPoint	p;
	xPoint	t;
	Vertex() {}
	Vertex(xPoint a, xPoint b)
	{
		p = a;
		t = b;
	}
	Vertex(float px, float py, float tx, float ty)
	{
		p.x = px;
		p.y = py;
		t.x = tx;
		t.y = ty;
	}
};

//--------------------------------
extern ID3D11Device*	g_pDevice;