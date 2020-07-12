#include "Model.h"
#include "TextureManager.h"
bool Model::Init()
{
	return true;
}
bool Model::Frame()
{
	return true;
}
bool Model::PreRender(ID3D11DeviceContext* pContext)
{
	//Set
	m_DxHelper.PreRender(pContext, m_DxHelper.m_iVertexSize/*.m_iNumVertex*/);
	return true;
}
bool Model::Render(ID3D11DeviceContext* pContext)
{
	//constantbuffer°è»ê
	pContext->UpdateSubresource(m_DxHelper.m_pConstantBuffer.Get(), 0, NULL, &m_ConstBuffer, 0, 0);
	
	PreRender(pContext);
	PostRender(pContext);
	return true;
}
bool Model::PostRender(ID3D11DeviceContext* pContext)
{
	//Draw
	m_DxHelper.PostRender(pContext, m_DxHelper.m_iNumIndex);
	return true;
}
bool Model::Release()
{
	return true;
}

bool Model::Create(ID3D11Device* pd3dDevice, const TCHAR* pVSFilename, const TCHAR* pPSFilename, const TCHAR* pLoadTextureFile, const CHAR* pVertexShader, const CHAR* pPixelShader)
{
	m_pDevice = pd3dDevice;

	if (FAILED(LoadShaderFile(pVSFilename, pPSFilename, pVertexShader, pPixelShader)))
	{
		return false;
	}
	if (FAILED(SetInputLayout()))
	{
		return false;
	}
	if (FAILED(CreateVertexData()))
	{
		return false;
	}
	if (FAILED(CreateIndexData()))
	{
		return false;
	}
	if (FAILED(CreateVertexBuffer()))
	{
		return false;
	}
	if (FAILED(CreateIndexBuffer()))
	{
		return false;
	}
	if (FAILED(CreateConstantBuffer()))
	{
		return false;
	}
	if (FAILED(LoadTexture(pLoadTextureFile)))
	{
		return false;
	}
	if (!UpdateBuffer())
	{
		return false;
	}
	if (FAILED(CreateResource()))
	{
		return false;
	}
	SetCollisionData();
	return Init();
}

HRESULT Model::LoadShaderFile(const TCHAR* pVSFilename, const TCHAR* pPSFilename, const CHAR* pVertexShader, const CHAR* pPixelShader)
{
	HRESULT hr = S_OK;
	m_DxHelper.m_pVertexShader.Attach(DX::LoadVertexShader(m_pDevice, pVSFilename, m_DxHelper.m_pVSBlob.GetAddressOf(), pVertexShader));
	m_DxHelper.m_pPixelShader.Attach(DX::LoadPixelShader(m_pDevice, pPSFilename, nullptr, pPixelShader));
	return hr;
}

HRESULT Model::SetInputLayout()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0 ,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL", 0 ,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR", 0 ,DXGI_FORMAT_R32G32B32A32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXTURE", 0 ,DXGI_FORMAT_R32G32_FLOAT,0,40,D3D11_INPUT_PER_VERTEX_DATA,0},
		//{"TANGENT", 0 ,DXGI_FORMAT_R32G32_FLOAT,1,0,D3D11_INPUT_PER_VERTEX_DATA,0}

	};
	int iNumElement = sizeof(layout) / sizeof(layout[0]);
	m_DxHelper.m_pInputLayout.Attach(DX::CreateInputLayout(m_pDevice, m_DxHelper.m_pVSBlob->GetBufferSize(), m_DxHelper.m_pVSBlob->GetBufferPointer(), layout, iNumElement));

	return hr;
}
HRESULT Model::CreateVertexData()
{
	HRESULT hr = S_OK;

	return hr;
}
HRESULT Model::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	m_DxHelper.m_iVertexSize = sizeof(PNCT_VERTEX);
	m_DxHelper.m_iNumVertex = m_VertexList.size();
	m_DxHelper.m_pVertexBuffer.Attach(DX::CreateVertexBuffer(m_pDevice, &m_VertexList.at(0), m_DxHelper.m_iNumVertex, m_DxHelper.m_iVertexSize));
	if (m_DxHelper.m_pVertexBuffer.Get() == nullptr)
	{
		return false;
	}
	return hr;
}

HRESULT Model::CreateIndexData()
{
	HRESULT hr = S_OK;
	return hr;
}
HRESULT Model::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	if (m_IndexList.size() <= 0) return hr;
	m_DxHelper.m_iNumIndex = m_IndexList.size();
	m_DxHelper.m_pIndexBuffer.Attach(DX::CreateIndexBuffer(m_pDevice, &m_IndexList.at(0), m_DxHelper.m_iNumIndex, sizeof(DWORD)));
	if (m_DxHelper.m_pIndexBuffer.Get() == nullptr)
	{
		return false;
	}
	return true;

}
HRESULT Model::CreateConstantBuffer()
{
	HRESULT hr = S_OK;
	D3DXMATRIX MatWorld;
	D3DXMatrixIdentity(&MatWorld);

	EssCB ConstantBuffer;
	ZeroMemory(&ConstantBuffer, sizeof(EssCB));
	ConstantBuffer.MatWorld = MatWorld;
	ConstantBuffer.MatView = m_MatView;
	ConstantBuffer.MatProj = m_MatProj;

	ConstantBuffer.color[0] = 1.0f;
	ConstantBuffer.etc[0] = 0.0f;

	m_DxHelper.m_pConstantBuffer.Attach(DX::CreateConstantBuffer(m_pDevice, &ConstantBuffer, 1, sizeof(EssCB)));
	if (m_DxHelper.m_pConstantBuffer.Get() == nullptr)
	{
		return false;
	}

	return hr;
}
HRESULT Model::LoadTexture(const TCHAR* pTextureFile)
{
	HRESULT hr = S_OK;
	if (pTextureFile == nullptr)
	{
		return true;
	}
	int Index = TextureManager::GetInstance().Load(m_pDevice, pTextureFile);
	m_DxHelper.m_pSRV = TextureManager::GetInstance().GetPtr(Index)->m_pSRV;

	return hr;
}
bool Model::UpdateBuffer()
{
	return true;
}
HRESULT Model::CreateResource()
{
	HRESULT hr = S_OK;
	return hr;
}
void Model::SetCollisionData()
{

}
void Model::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (pWorld != nullptr)
	{
		m_MatWorld = *pWorld;
	}
	if (pView != nullptr)
	{
		m_MatView = *pView;
	}
	if (pProj != nullptr)
	{
		m_MatProj = *pProj;
	}

	D3DXMatrixTranspose(&m_ConstBuffer.MatWorld, &m_MatWorld);
	D3DXMatrixTranspose(&m_ConstBuffer.MatView, &m_MatView);
	D3DXMatrixTranspose(&m_ConstBuffer.MatProj, &m_MatProj);
}
bool Model::Load(ID3D11Device* pDevice, T_STR filename, const TCHAR* pVSFilename, const TCHAR* pPSFilename, const TCHAR* pLoadTextureFile, const CHAR* pVertexShader, const CHAR* pPixelShader)
{
	_tfopen_s(&m_pStream, filename.c_str(), _T("rt"));
	if (m_pStream && !Create(pDevice, pVSFilename, pPSFilename, nullptr, pVertexShader, pPixelShader))
	{
		fclose(m_pStream);
		return false;
	}
	fclose(m_pStream);
	return true;
}
Model::Model()
{
	D3DXMatrixIdentity(&m_MatWorld);
	D3DXMatrixIdentity(&m_MatView);
	D3DXMatrixIdentity(&m_MatProj);
}


Model::~Model()
{
}
