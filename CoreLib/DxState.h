#pragma once
#include <D3DX11.h>
#include <memory>

namespace DX
{
	class DxState
	{
	public:
		static ID3D11BlendState*	m_pAlphaBlend;
		static ID3D11BlendState*	m_pAlphaBlendDisable;

		static ID3D11RasterizerState*	m_pRSWireFrame;
		static ID3D11RasterizerState*	m_pRSSolidFrame;
		static ID3D11RasterizerState*	m_pRSBackCullSolid;

		static ID3D11DepthStencilState*	m_pDepthEnable;
		static ID3D11DepthStencilState*	m_pDepthDisable;

		static ID3D11SamplerState*		m_pSSWrapLinear;
		static ID3D11SamplerState*		m_pSSWrapAniso;
		static ID3D11SamplerState*		m_pSSClampLinear;

		static void SetState(ID3D11Device* pd3dDevice);
		static void Release();

	public:
		DxState();
		~DxState();
	};

	static void ApplyRS(ID3D11DeviceContext* pContext, ID3D11RasterizerState* pRSState)
	{
		pContext->RSSetState(pRSState);
	};

	static void ApplyBS(ID3D11DeviceContext* pContext, ID3D11BlendState* pBlend, const FLOAT fBlendFactor[] = 0, UINT iMask = 0xffffffff)
	{
		pContext->OMSetBlendState(pBlend, fBlendFactor, iMask);
	};

	static void ApplyDSS(ID3D11DeviceContext* pContext, ID3D11DepthStencilState* pDSState, UINT iref = 1)
	{
		pContext->OMSetDepthStencilState(pDSState, iref);
	};

	static void ApplySS(ID3D11DeviceContext* pContext, ID3D11SamplerState* pState, UINT iSlot = 0, UINT iArray = 1)
	{
		pContext->PSSetSamplers(iSlot, iArray, &pState);
	};
}