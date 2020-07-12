#pragma once
#define _CRT_SECURE_NO_WARNINGS
//#include "Core.h"
#include "DxState.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <wrl.h>
#include <dxgi.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment( lib, "d3dcompiler.lib" )
#if defined(_DEBUG)
	#pragma comment (lib, "d3dx10d.lib")
#else
	#pragma comment (lib, "d3dx10.lib")
#endif

namespace DX
{
	HRESULT				CompileShaderFromFile(const TCHAR* sFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	ID3D11VertexShader* LoadVertexShader(ID3D11Device* pd3dDevice, const void* pShaderFileData, ID3DBlob** ppBlob = nullptr, const char* pFunctionName = 0, bool bBinary = false);
	ID3D11PixelShader*	LoadPixelShader(ID3D11Device* pd3dDevice, const void* pShaderFileData, ID3DBlob** ppBlob = nullptr, const char* pFunctionName = 0, bool bBinary = false);
	ID3D11InputLayout*	CreateInputLayout(ID3D11Device* pd3dDevice, DWORD dwSize, LPCVOID lpData, D3D11_INPUT_ELEMENT_DESC* layout, UINT iNumElement);
	ID3D11Buffer*		CreateVertexBuffer(ID3D11Device* pd3dDevice, void* pData, UINT iNumCount, UINT iSize, bool bDynamic = false);
	ID3D11Buffer*		CreateIndexBuffer(ID3D11Device* pd3dDevice, void* pData, UINT iNumCount, UINT iSize, bool bDynamic = false);
	ID3D11Buffer*		CreateConstantBuffer(ID3D11Device* pd3dDevice, void* pData, UINT iNumCount, UINT iSize, bool bDynamic = false);

	class DxHelperEx
	{
	public:
		UINT			m_iNumVertex;
		UINT			m_iNumIndex;
		UINT			m_iVertexSize;
	public:		
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		m_pVertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		m_pPixelShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_pInputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>			m_pVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>			m_pIndexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>			m_pConstantBuffer;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV;
		Microsoft::WRL::ComPtr<ID3DBlob>				m_pVSBlob;

	public:
		void PreRender(ID3D11DeviceContext* pContext, UINT iSize);
		bool Render(ID3D11DeviceContext* pContext);
		void PostRender(ID3D11DeviceContext* pContext, UINT iCount);
	public:
		DxHelperEx();
		virtual ~DxHelperEx();
	};
}
