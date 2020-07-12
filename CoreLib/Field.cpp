#include "Field.h"

HRESULT Field::CreateVertexData()
{
	float fHalfCols = (m_iNumCols - 1) / 2.0f;
	float fHalfRows = (m_iNumRows - 1) / 2.0f;
	float ftxOffSetU = 1.0f / (m_iNumCols - 1);
	float ftxOffSetV = 1.0f / (m_iNumRows - 1);
	
	m_VertexList.resize(m_iNumVertices);

	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int iVertexNum = iRow * m_iNumCols + iCol;
			m_VertexList[iVertexNum].Position.x = (iCol - fHalfCols)*m_fCellDistance;
			m_VertexList[iVertexNum].Position.z = -(iRow - fHalfRows)*m_fCellDistance;
			m_VertexList[iVertexNum].Position.y = GetHeight(iVertexNum);
			//heightmap에서 얻은 값을 사용
			
			m_VertexList[iVertexNum].Texture.x = iCol * ftxOffSetU;
			m_VertexList[iVertexNum].Texture.y = iRow * ftxOffSetV;
			//텍스쳐 한장을 전체에 적용

			m_VertexList[iVertexNum].Normal = GetFaceNormal(iVertexNum); //D3DXVECTOR3
			m_VertexList[iVertexNum].Color = GetColor(iVertexNum);
			//heightmap에서 얻은 값을 사용

		}
	}

	return 1;
}

HRESULT Field::CreateIndexData()
{
	m_IndexList.resize(m_iNumFace * 3);

	int iIndex = 0;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			int iNextRow = iRow + 1;
			int iNextCol = iCol + 1;
			m_IndexList[iIndex + 0] = iRow * m_iNumCols + iCol;
			m_IndexList[iIndex + 1] = iRow * m_iNumCols + iNextCol;
			m_IndexList[iIndex + 2] = iNextRow * m_iNumCols + iCol;

			DWORD i0 = m_IndexList[iIndex + 0];
			DWORD i1 = m_IndexList[iIndex + 1];
			DWORD i2 = m_IndexList[iIndex + 2];

			D3DXVECTOR3 vNormal = ComputeFaceNormal(i0, i1, i2);

			m_VertexList[i0].Normal += vNormal;
			m_VertexList[i1].Normal += vNormal;
			m_VertexList[i2].Normal += vNormal;
			D3DXVec3Normalize(&m_VertexList[i0].Normal,&m_VertexList[i0].Normal);
			D3DXVec3Normalize(&m_VertexList[i1].Normal,&m_VertexList[i1].Normal);
			D3DXVec3Normalize(&m_VertexList[i2].Normal,&m_VertexList[i2].Normal);

			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = iNextRow * m_iNumCols + iNextCol;

			i0 = m_IndexList[iIndex + 3];
			i1 = m_IndexList[iIndex + 4];
			i2 = m_IndexList[iIndex + 5];

			vNormal = ComputeFaceNormal(i0, i1, i2);
			m_VertexList[i0].Normal += vNormal;
			m_VertexList[i1].Normal += vNormal;
			m_VertexList[i2].Normal += vNormal;
			D3DXVec3Normalize(&m_VertexList[i0].Normal, &m_VertexList[i0].Normal);
			D3DXVec3Normalize(&m_VertexList[i1].Normal, &m_VertexList[i1].Normal);
			D3DXVec3Normalize(&m_VertexList[i2].Normal, &m_VertexList[i2].Normal);


			iIndex += 6;
		}
	}

	return 1;
}

bool Field::Load(ID3D11Device* pd3Device, FieldDesc& md, const CHAR* pVertexShader, const CHAR* pPixelShader, const TCHAR* pVSFile, const TCHAR* pPSFile)
{
	m_iNumCols = md.iNumCols; //num of vertex
	m_iNumRows = md.iNumRows;
	m_fHeightScale = md.fHeightScale;
	m_iNumCellCols = m_iNumCols -1;
	m_iNumCellRows = m_iNumRows	-1;
	m_iNumVertices = m_iNumCols * m_iNumRows;
	m_iNumFace = m_iNumCellCols * m_iNumCellRows * 2;
	m_fCellDistance = md.fCellDistance;
	m_pDevice = pd3Device;
	if (Create(pd3Device, pVSFile, pPSFile, md.szTextureFile.c_str(), pVertexShader, pPixelShader) == false)
	{
		return false;
	}	
	m_pPattern = m_DxHelper.m_pSRV;
	LoadTexture(md.szCubeFile.c_str());
	m_pCube = m_DxHelper.m_pSRV;
	return true; 
}

D3DXVECTOR3 Field::ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
{
	D3DXVECTOR3 vNormal;
	D3DXVECTOR3 v0, v1, v2;

	v0 = m_VertexList[i0].Position;
	v1 = m_VertexList[i1].Position;
	v2 = m_VertexList[i2].Position;

	D3DXVECTOR3 vEdge0 = v1 - v0;
	D3DXVECTOR3 vEdge1 = v2 - v0;

	D3DXVec3Cross(&vNormal, &vEdge0, &vEdge1);
	D3DXVec3Normalize(&vNormal, &vNormal);

	return vNormal;
}

bool	Field::Render(ID3D11DeviceContext* pContext)
{

	pContext->UpdateSubresource(m_DxHelper.m_pConstantBuffer.Get(), 0, NULL, &m_ConstBuffer, 0, 0);
	PreRender(pContext);
	//
	pContext->PSSetShaderResources(0, 1, m_pPattern.GetAddressOf());
	pContext->PSSetShaderResources(1, 1, m_pCube.GetAddressOf());
	//
	PostRender(pContext);
	return true;
}



Field::Field()
{
}


Field::~Field()
{
}

void FieldHeight::CreateFieldHeight(ID3D11Device* pd3Device, ID3D11DeviceContext* pd3Context, const TCHAR* pMapFile)
{
	D3DX11_IMAGE_LOAD_INFO ImageLoad;
	ZeroMemory(&ImageLoad, sizeof(D3DX11_IMAGE_LOAD_INFO));
	ImageLoad.Usage = D3D11_USAGE_STAGING;
	ImageLoad.CpuAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	ImageLoad.MipLevels = 1;
	ImageLoad.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	ID3D11Resource* tmpTexture;
	HRESULT hr;
	D3DX11CreateTextureFromFile(pd3Device, pMapFile, &ImageLoad, NULL, &tmpTexture, &hr);
	//tmpTexture 컨버팅!

	D3D11_TEXTURE2D_DESC td;

	ID3D11Texture2D* pTexure2D = (ID3D11Texture2D*)tmpTexture;
	pTexure2D->GetDesc(&td);

	m_HeightList.resize((td.Width) * (td.Height));

	D3D11_MAPPED_SUBRESOURCE MapSub;
	if (SUCCEEDED(pd3Context->Map(pTexure2D, D3D11CalcSubresource(0, 0, 1), D3D11_MAP_READ, 0, &MapSub)))//pTexure2D or tmpTexture
	{
		UCHAR* pTexels = (UCHAR*)MapSub.pData;
		for (UINT row = 0; row < td.Height; row++)
		{
			UINT rowStart = row * MapSub.RowPitch;
			for (UINT col = 0; col < td.Width; col++)
			{
				UINT upixel = pTexels[rowStart + col * 4];
				m_HeightList[row*td.Width + col] = upixel;
			}
		}
		pd3Context->Unmap((ID3D11Resource*)tmpTexture, D3D11CalcSubresource(0, 0, 1));
	}
	m_iNumRows = td.Height;
	m_iNumCols = td.Width;

	tmpTexture->Release();
}

float FieldHeight::GetHeight(UINT index)
{
	return m_HeightList[index] / m_fHeightScale;
}

FieldHeight::FieldHeight()
{
	m_fHeightScale = 1.0f;
}
FieldHeight::~FieldHeight()
{

}