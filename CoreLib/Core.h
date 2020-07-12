#pragma once
#include "Device.h"
#include "Input.h"
#include "SoundMgr.h"
#include "DxHelperEx.h"
#include "DxWrite.h"
#include "DxState.h"
#include "DebugCam.h"

class Core : public Device
{
public:
	Timer m_Timer;

	bool m_bDebug;
	bool m_bRenderState;
	bool m_bDepthState;
	DxWrite m_coredxWrite;
	
	//ModelCamera m_Camera[1];
	//Camera		m_Camera[3];
	int			m_iCameraNum = 0;
	Camera*		m_pCurrCamera;
	DebugCam	m_DebugCam;
	LineObject	m_BasisLine;

public:
	virtual bool Init();
	virtual bool PreFrame();
	virtual bool Frame();
	virtual bool PostFrame();
	virtual bool PreRender();
	virtual bool Render();
	virtual bool PostRender();
	virtual bool Release();
	virtual bool DebugRender();

public:
	bool CoreInit();
	bool CoreFrame();
	bool CoreRender();
	bool CoreRelease();
	void MessageProc(MSG msg);
	virtual HRESULT DeleteDXResource() override;
	virtual HRESULT CreateDXResource() override;	
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	
public:
	bool Run();
public:
	Core();
	virtual ~Core();
};

