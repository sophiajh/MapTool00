#include "DxHelperEx.h"
#include "D3Dcompiler.h"
namespace DX
{
	HRESULT CompileShaderFromFile(const TCHAR* sFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		HRESULT hr;
		ID3DBlob* pErrorMsg;
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined (_DEBUG)
		dwShaderFlags |= D3DCOMPILE_DEBUG;
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		if (FAILED(hr = D3DX11CompileFromFile(sFileName, NULL, NULL, szEntryPoint, szShaderModel, dwShaderFlags, 0, NULL, ppBlobOut, &pErrorMsg, NULL)))
		{
			TCHAR pMessage[500];
			mbstowcs(pMessage, (CHAR*)pErrorMsg->GetBufferPointer(), 500);
			MessageBox(NULL, pMessage, /*_T*/(LPCWSTR)("ERROR"), MB_OK);
			return false;
		}
		return hr;
	}

	ID3D11VertexShader* LoadVertexShader(ID3D11Device* pd3dDevice, const void* pShaderFileData, ID3DBlob** ppBlob, const char* pFunctionName, bool bBinary)
	{
		HRESULT hr;
		ID3D11VertexShader* pVertexShader;
		ID3DBlob* pBlob = NULL;
		DWORD dwSize = 0;
		LPCVOID lpData = 0;

		ID3DBlob* pErrorMsg;

		if (!bBinary)
		{
			if (pFunctionName == 0)
			{
				if (FAILED(CompileShaderFromFile((TCHAR*)pShaderFileData, "VS", "vs_5_0", &pBlob)))
				{
					return nullptr;
				}
			}
			else
			{
				if (FAILED(CompileShaderFromFile((TCHAR*)pShaderFileData, pFunctionName, "vs_5_0", &pBlob)))
				{
					return nullptr;
				}
			}
			dwSize = pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();

		}
		else
		{
			pBlob = *ppBlob;
			if (pBlob == nullptr) return nullptr;
			dwSize = pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();
		}
		
		if (FAILED(pd3dDevice->CreateVertexShader(lpData, dwSize, NULL, &pVertexShader)))
		{
			pBlob->Release();
			return nullptr;
		}

		if (ppBlob == nullptr)
		{
			pBlob->Release();
		}
		else
		{
			*ppBlob = pBlob;
		}

		return pVertexShader;
	}

	ID3D11PixelShader* LoadPixelShader(ID3D11Device* pd3dDevice, const void* pShaderFileData, ID3DBlob** ppBlob, const char* pFunctionName, bool bBinary)
	{
		HRESULT hr;
		ID3D11PixelShader* pPixelShader;
		ID3DBlob* pBlob = NULL;
		DWORD dwSize = 0;
		LPCVOID lpData = 0;

		if (bBinary == false)
		{
			if (pFunctionName == 0)
			{
				if (FAILED(hr = CompileShaderFromFile((TCHAR*)pShaderFileData, "PS", "ps_5_0", &pBlob)))
				{
					return nullptr;
				}
			}
			else
			{
				if (FAILED(hr = CompileShaderFromFile((TCHAR*)pShaderFileData, pFunctionName, "ps_5_0", &pBlob)))
				{
					return nullptr;
				}
			}
			dwSize = pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();
		}
		else
		{
			pBlob = *ppBlob;
			if (pBlob == nullptr) return nullptr;
			dwSize = pBlob->GetBufferSize();
			lpData = pBlob->GetBufferPointer();
		}
		
		if (FAILED(hr = pd3dDevice->CreatePixelShader(lpData, dwSize, NULL, &pPixelShader)))
		{
			pBlob->Release();
			return nullptr;
		}

		if (ppBlob == nullptr)
		{
			pBlob->Release();
		}
		else
		{
			*ppBlob = pBlob;
		}

		return pPixelShader;
	}

	ID3D11InputLayout* CreateInputLayout(ID3D11Device* pd3dDevice, DWORD dwSize, LPCVOID lpData, D3D11_INPUT_ELEMENT_DESC* layout, UINT iNumElement)
	{
		
		HRESULT hr;
		ID3D11InputLayout* pInputLayout;
		ID3DBlob* pErrorMsg = NULL;
		if (FAILED(hr = pd3dDevice->CreateInputLayout(layout, iNumElement, lpData, dwSize, &pInputLayout)))
		{
			TCHAR pMessage[500];
			mbstowcs(pMessage, (CHAR*)pErrorMsg->GetBufferPointer(), 500);
			MessageBox(NULL, pMessage, /*_T*/(LPCWSTR)("ERROR"), MB_OK);
			return nullptr;
		}
		return pInputLayout;
	}

	ID3D11Buffer*		CreateVertexBuffer(ID3D11Device* pd3dDevice, void* pData, UINT iNumCount, UINT iSize, bool bDynamic)
	{
		HRESULT hr;
		ID3D11Buffer* pBuffer = nullptr;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = iSize * iNumCount;
		if (bDynamic)
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = pData;

		if (pData != nullptr)
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer)))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, NULL, &pBuffer)))//use NULL to allocate space only 
			{
				return nullptr;
			}
		}
		return pBuffer;

	}

	ID3D11Buffer*		CreateIndexBuffer(ID3D11Device* pd3dDevice, void* pData, UINT iNumCount, UINT iSize, bool bDynamic)
	{
		HRESULT hr;
		ID3D11Buffer* pBuffer = nullptr;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = iSize * iNumCount;
		if (bDynamic)
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = pData;

		if (pData != nullptr)
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer)))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, NULL, &pBuffer)))//use NULL to allocate space only 
			{
				return nullptr;
			}
		}
		return pBuffer;
	}

	ID3D11Buffer*		CreateConstantBuffer(ID3D11Device* pd3dDevice, void* pData, UINT iNumCount, UINT iSize, bool bDynamic)
	{
		HRESULT hr;
		ID3D11Buffer* pBuffer = nullptr;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = iSize * iNumCount;
		if (bDynamic)
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = pData;

		if (pData != nullptr)
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer)))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, NULL, &pBuffer)))//use NULL to allocate space only 
			{
				return nullptr;
			}
		}
		return pBuffer;
	}
	
	void DxHelperEx::PreRender(ID3D11DeviceContext* pContext, UINT iSize)
	{
		pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pContext->IASetInputLayout(m_pInputLayout.Get());
		pContext->IASetIndexBuffer(m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		pContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());
		
		pContext->VSSetShader(m_pVertexShader.Get(), NULL, 0);
		pContext->PSSetShader(m_pPixelShader.Get(), NULL, 0);
		
		UINT stride = iSize;
		UINT offset = 0;
		pContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
		pContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
		pContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
		
	}

	bool DxHelperEx::Render(ID3D11DeviceContext* pContext)
	{
		PreRender(pContext, m_iVertexSize);
		PostRender(pContext, m_iNumIndex);
		return true;
	}

	void DxHelperEx::PostRender(ID3D11DeviceContext* pContext, UINT iCount)
	{
		if (iCount == 0) iCount = m_iNumIndex;
		if (iCount != 0)
			pContext->DrawIndexed(iCount, 0, 0);
		else
			pContext->Draw(m_iNumVertex, 0);
	}

	DxHelperEx::DxHelperEx()
	{
		m_iNumVertex = 0;
		m_iNumIndex = 0;
	}
	
	DxHelperEx::~DxHelperEx()
	{
	}
}