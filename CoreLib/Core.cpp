#include "Core.h"

LRESULT Core::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrCamera == nullptr) return 1;
	return m_pCurrCamera->MsgProc(hWnd, msg, wParam, lParam);
}
bool Core::Init()
{
	return true;
}
bool Core::PreFrame()
{
	return true;
}
bool Core::Frame()
{
	return true;
}
bool Core::PostFrame()
{
	return true;
}
bool Core::PreRender()
{
	Device::PreRender();
	if (m_bRenderState)
	{
		DX::ApplyRS(m_pDeviceContext, DX::DxState::m_pRSSolidFrame);
	}
	else
	{
		DX::ApplyRS(m_pDeviceContext, DX::DxState::m_pRSWireFrame);
	}
	if (m_bDepthState)
	{
		DX::ApplyDSS(m_pDeviceContext, DX::DxState::m_pDepthEnable);
	}
	else
	{
		DX::ApplyDSS(m_pDeviceContext, DX::DxState::m_pDepthDisable);
	}
	DX::ApplySS(m_pDeviceContext, DX::DxState::m_pSSWrapLinear);
	return true;
}
bool Core::Render()
{
	Device::Render();
	return true;
}
bool Core::PostRender()
{
	m_coredxWrite.textdata = m_Timer.m_csBuffer;

	m_coredxWrite.rt_text.left = 0;
	m_coredxWrite.rt_text.top = 0;
	m_coredxWrite.Render();
	
	if (m_bDebug == true)
	{
		DebugRender();
	}
	
	Device::PostRender();
	return true;
}
bool Core::DebugRender()
{
	//m_Timer.Render();
	Input::GetInstance().Render();
	SoundMgr::GetInstance().Render();
	return true;
}
bool Core::Release()
{
	return true;
}
#pragma region Core

bool Core::CoreInit()
{
	Device::InitDevice();
	DX::DxState::SetState(m_pDevice);
	m_coredxWrite.Init();

	IDXGISurface1* pBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (LPVOID*)&pBuffer);
	m_coredxWrite.Set(pBuffer);

	if (pBuffer) pBuffer->Release();	

	m_Timer.Init();
	Input::GetInstance().Init();
	SoundMgr::GetInstance().Init();

	m_DebugCam.Init();
	m_DebugCam.m_Frustum.CreateFrustumObj(m_pDevice);
	m_DebugCam.m_vPosition = D3DXVECTOR3(0.0f, 10.0f, -10.0f);
	m_DebugCam.m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	m_DebugCam.CreateViewMatrix(m_DebugCam.m_vPosition, m_DebugCam.m_vTarget);
	m_DebugCam.CreateProjMatrix(D3DX_PI / 4, g_rtClient.right / g_rtClient.bottom, 1.0f, 1000.0f);

	m_pCurrCamera = &m_DebugCam;
	return Init();
}
bool Core::CoreFrame()
{
	if (g_ActionInput.bSpaceKey == KEY_PUSH)
	{
		m_bDebug = !m_bDebug;
	}
	if (g_ActionInput.bSpaceKey == KEY_PUSH)
	{
		m_bRenderState = !m_bRenderState;
	}
	if (g_ActionInput.bTabKey == KEY_PUSH)
	{
		m_bDepthState = !m_bDepthState;
	}
	PreFrame();
	//camera move input
	{
		m_pCurrCamera->m_fSpeed = 1.0f;
		if (g_ActionInput.bSpaceKey)
		{
			m_pCurrCamera->m_fSpeed = 0.05f;
		}
		if (g_ActionInput.bWKey)
		{
			m_pCurrCamera->Forward();
		}
		if (g_ActionInput.bSKey)
		{
			m_pCurrCamera->Backward();
		}
		if (g_ActionInput.bAKey)
		{
			m_pCurrCamera->Left();
		}
		if (g_ActionInput.bDKey)
		{
			m_pCurrCamera->Right();
		}
		if (g_ActionInput.bQKey)
		{
			m_pCurrCamera->Down();
		}
		if (g_ActionInput.bEKey)
		{
			m_pCurrCamera->Up();
		}
	}
	m_pCurrCamera->Frame();
		m_Timer.Frame();
		Input::GetInstance().Frame();
		SoundMgr::GetInstance().Frame();
		//m_BasisLine.Frame();
		Frame();
	return PostFrame();
}
bool Core::CoreRender()
{

	PreRender();	//  지우고
	Render();	    //  뿌리고
	PostRender();	//	덮어쓴다!
	
	return true;
}
bool Core::CoreRelease()
{
	m_Timer.Release();
	Input::GetInstance().Release();
	//m_Input.Release();
	SoundMgr::GetInstance().Release();
	//
	Device::Release();
	//
	return Release();
}
bool Core::Run()
{
	CoreInit();
	MSG msg = { 0, };
	while (msg.message != WM_QUIT)
	{									//PeekMessage는 메세지가 available이면 true를, no message available이면 false를 리턴한다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //(메세지를 가져올 변수, 해당 윈도우의 핸들, 메세지 범위, 메세지 범위, 행동 지정)
														//PM_REMOVE는 메세지큐를 읽고 큐에 있던 메세지 삭제.
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			MessageProc(msg);
		}
		else
		{
			CoreFrame();
			CoreRender();
		}
	}
	CoreRelease();
	return true;

}
#pragma endregion

void Core::MessageProc(MSG msg)
{
	Input::GetInstance().MsgProc(msg);
	//m_Input.MsgProc(msg);		//core에서 발생한 메세지를 input에 넘겨준다. 다른 작업이 생기면 같은 형태로 그 객체에 넘겨주면 된다. 
}

HRESULT Core::DeleteDXResource()
{
	m_coredxWrite.DiscardDeviceResource();

	return true;
}
HRESULT Core::CreateDXResource()
{
	IDXGISurface1* pBackBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (LPVOID*)&pBackBuffer);

	m_coredxWrite.CreateDeviceResource(pBackBuffer);
	if (pBackBuffer) pBackBuffer->Release();


	return true;
}

Core::Core()
{
	m_bDebug = false;
	m_bRenderState = false;
}


Core::~Core()
{
}


