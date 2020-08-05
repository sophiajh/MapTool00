#include "DxState.h"

namespace DX
{
	ID3D11BlendState*	DxState::m_pAlphaBlend = 0;
	ID3D11BlendState*	DxState::m_pAlphaBlendDisable = 0;
	//
	ID3D11BlendState*	DxState::m_pAlphaBlend2 = 0;
	ID3D11BlendState*	DxState::m_pAlphaBlendMinus = 0;

	ID3D11RasterizerState*	DxState::m_pRSWireFrame = 0;
	ID3D11RasterizerState*	DxState::m_pRSSolidFrame = 0;
	ID3D11RasterizerState*	DxState::m_pRSBackCullSolid = 0;

	ID3D11DepthStencilState*	DxState::m_pDepthEnable = 0;
	ID3D11DepthStencilState*	DxState::m_pDepthDisable = 0;

	ID3D11SamplerState*		DxState::m_pSSWrapLinear = 0;
	ID3D11SamplerState*		DxState::m_pSSWrapAniso = 0;
	ID3D11SamplerState*		DxState::m_pSSClampLinear = 0;

	void DxState::SetState(ID3D11Device* pd3dDevice)
	{
		if (pd3dDevice == nullptr) return;
		HRESULT hr;
		//Depth설정
		D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
		ZeroMemory(&DepthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
		DepthStencilDesc.DepthEnable = TRUE;
		DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
		DepthStencilDesc.StencilEnable = FALSE;
		DepthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		DepthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

		if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&DepthStencilDesc, &m_pDepthEnable)))
		{
			return ;
		}
		DepthStencilDesc.DepthEnable = FALSE;

		if (FAILED(hr = pd3dDevice->CreateDepthStencilState(&DepthStencilDesc, &m_pDepthDisable)))
		{
			return;
		}

		//Sampler설정
		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.Filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		sd.MaxLOD = FLT_MAX;
		sd.MinLOD = FLT_MIN;
		sd.MaxAnisotropy = 16;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(
			&sd,
			&m_pSSWrapLinear)))
		{
			return;
		}
		sd.Filter = D3D11_FILTER_ANISOTROPIC;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(
			&sd,
			&m_pSSWrapAniso)))
		{
			return;
		}
		sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		if (FAILED(hr = pd3dDevice->CreateSamplerState(
			&sd,
			&m_pSSClampLinear)))
		{
			return;
		}

		//Blend설정
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
		bd.AlphaToCoverageEnable = FALSE;//Specifies whether to use alpha-to-coverage as a multisampling technique when setting a pixel to a render target.
		bd.IndependentBlendEnable = TRUE;//Specifies whether to enable independent blending in simultaneous render targets. Set to TRUE to enable independent blending. If set to FALSE, only the RenderTarget[0] members are used; RenderTarget[1..7] are ignored.
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;//how to combine the SrcBlend and DestBlend operations.
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		if (FAILED(hr = pd3dDevice->CreateBlendState(&bd, &m_pAlphaBlend)))
		{
			return;
		}
		bd.RenderTarget[0].BlendEnable = FALSE;
		if (FAILED(hr = pd3dDevice->CreateBlendState(&bd, &m_pAlphaBlendDisable)))
		{
			return;
		}
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		if (FAILED(hr = pd3dDevice->CreateBlendState(&bd, &m_pAlphaBlend2)))
		{
			return;
		}
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		if (FAILED(hr = pd3dDevice->CreateBlendState(&bd, &m_pAlphaBlendMinus)))
		{
			return;
		}
		//Rasterizer설정
		D3D11_RASTERIZER_DESC RSDesc;
		ZeroMemory(&RSDesc, sizeof(D3D11_RASTERIZER_DESC));
		RSDesc.DepthClipEnable = TRUE; //Enable clipping based on distance.
		RSDesc.FillMode = D3D11_FILL_SOLID;//RSDesc.FillMode = D3D11_FILL_WIREFRAME;
		RSDesc.CullMode = D3D11_CULL_NONE;
		//RSDesc.FrontCounterClockwise = false;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&RSDesc, &m_pRSSolidFrame)))
		{
			return;
		}
		RSDesc.FillMode = D3D11_FILL_WIREFRAME;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&RSDesc, &m_pRSWireFrame)))
		{
			return;
		}
		RSDesc.FillMode = D3D11_FILL_SOLID;
		RSDesc.CullMode = D3D11_CULL_BACK;
		if (FAILED(hr = pd3dDevice->CreateRasterizerState(&RSDesc, &m_pRSBackCullSolid)))
		{
			return;
		}
	}
	void DxState::Release()
	{
		if (m_pAlphaBlend)			m_pAlphaBlend->Release();
		if (m_pAlphaBlendDisable)	m_pAlphaBlendDisable->Release();
		if (m_pAlphaBlend2)			m_pAlphaBlend2->Release();
		if (m_pAlphaBlendMinus)		m_pAlphaBlendMinus->Release();



		if (m_pRSWireFrame)			m_pRSWireFrame->Release();
		if (m_pRSSolidFrame)		m_pRSSolidFrame->Release();

		m_pAlphaBlend = 0;
		m_pAlphaBlendDisable = 0;
		m_pAlphaBlend2 = 0;
		m_pAlphaBlendMinus = 0;

		m_pRSWireFrame = 0;
		m_pRSSolidFrame = 0;
	}	
	DxState::DxState()
	{
	}


	DxState::~DxState()
	{
		Release();
	}
}