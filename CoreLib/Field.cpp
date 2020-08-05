#include "Field.h"

HRESULT Field::CreateVertexData()
{
	float fHalfCols = (m_iNumCols - 1) / 2.0f;
	float fHalfRows = (m_iNumRows - 1) / 2.0f;
	
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
			
			m_VertexList[iVertexNum].Texture.x = iCol * m_ftxOffSetU;
			m_VertexList[iVertexNum].Texture.y = iRow * m_ftxOffSetV;
			//텍스쳐 한장을 전체에 적용
			//m_ftxOffSetU / m_ftxOffSetV로 변경가능해짐 (20200616)

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
	GenerateVertexNormal();
	return 1;
}

void Field::GenerateVertexNormal()
{
	CreateFaceNormal();
	CreateNormalLookupTable();
	CalculateVertexNormalFastLookup();
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

bool	Field::Init()
{
	//ID3D11Resource* resource;
	//D3DX11CreateTextureFromFile(m_pDevice, alphatexture, imageload, NULL, resource, NULL);
		//디바이스 / 로딩할거 / 텍스쳐 형식 / X / id3d11resource / X

	//ID3D11Texture2D* texture;
	//
	//resource->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&texture));
	//위에 리소스가져와서 id3d11texture2d의 IID를 받아서 texture에 인터페이스 담아서 되돌려준다
	//texture->GetDesc(td);
	//td에 texture의 형식 가져옴.
	m_FieldRT.Create(m_pDevice, m_iNumCols*m_fCellDistance*m_iNumCols, m_iNumRows*m_fCellDistance*m_iNumRows);
	//새 렌더타겟 생성.
	//copyresource(m_rt.m_ptexture.get(), texture);
	//텍스처를 렌더타겟 텍스처에 복사해옴.
	//m_pDeviceContext->CopyResource(m_FieldRT.m_pTexture.Get(), );

	float fClearColor[4] = {1,0,0,0};

	m_pDeviceContext->ClearRenderTargetView(m_FieldRT.m_pRTView.Get(), fClearColor);

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	td.MipLevels = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.CPUAccessFlags = 0;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Width = m_iNumCols * m_fCellDistance * m_iNumCols;
	td.Height = m_iNumRows * m_fCellDistance * m_iNumRows;
	td.MiscFlags = 0;
	td.ArraySize = 1;

	HRESULT hr = S_OK;
	if (FAILED(hr = m_pDevice->CreateTexture2D(&td, 0, m_pSrcAlphaTexture.GetAddressOf())))
	{
		return false;
	}
	if (FAILED(hr = m_pDevice->CreateShaderResourceView(m_pSrcAlphaTexture.Get(), NULL, m_pAlphaSRV.GetAddressOf())))
	{
		return false;
	}
	
	//m_pDeviceContext->CopyResource(m_FieldRT.m_pTexture.Get(), m_pSrcAlphaTexture.Get());
	
	//FIELD_CONSTANT_BUFFER FieldCstData;
	//ZeroMemory(&FieldCstData, sizeof(FIELD_CONSTANT_BUFFER));
	//m_FieldCstData.Coord 
	ZeroMemory(&m_FieldCstData, sizeof(FIELD_CONSTANT_BUFFER));
	m_FieldCstData.Coord = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	m_FieldCstData.etc[0] = 10.0f;

	m_pFieldCstBuffer.Attach(DX::CreateConstantBuffer(m_pDevice, &m_FieldCstData, 1, sizeof(FIELD_CONSTANT_BUFFER)));
	if (m_pFieldCstBuffer.Get() == nullptr)
	{
		return false;
	}
	return true;
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

// Field 알파 텍스처 렌더 타겟에 렌더.
void	Field::RTSplatting(D3DXVECTOR3 vSelectedCoord3, int iTexNum)
{
	m_FieldCstData.Coord[0] = vSelectedCoord3.x;
	m_FieldCstData.Coord[1] = vSelectedCoord3.y;
	m_FieldCstData.Coord[2] = vSelectedCoord3.z;

	m_FieldBrush.m_MatWorld._41 = vSelectedCoord3.x;
	m_FieldBrush.m_MatWorld._42 = vSelectedCoord3.y;
	m_FieldBrush.m_MatWorld._43 = vSelectedCoord3.z;
	
	m_pDeviceContext->UpdateSubresource(m_pFieldCstBuffer.Get(), 0, NULL, &m_FieldCstData, 0, 0);
	m_pDeviceContext->VSSetConstantBuffers(2, 1, m_pFieldCstBuffer.GetAddressOf());
	m_pDeviceContext->PSSetConstantBuffers(2, 1, m_pFieldCstBuffer.GetAddressOf());

	//m_FieldRT.Begin(m_pDeviceContext);
	UINT ViewNum = 1;
	m_pDeviceContext->RSGetViewports(&ViewNum, &m_FieldRT.m_ViewPortOld);
	m_pDeviceContext->OMGetRenderTargets(1, m_FieldRT.m_pRTViewOld.GetAddressOf(), m_FieldRT.m_pDSViewOld.GetAddressOf());
	m_pDeviceContext->OMSetRenderTargets(1, m_FieldRT.m_pRTView.GetAddressOf(), nullptr);
	m_pDeviceContext->RSSetViewports(1, &m_FieldRT.m_ViewPort);
	// 기존 렌더타겟을 이동시키고 현재 렌더타겟을 m_FieldRT으로 변경.
	{
		// 여기에서 render하면 필드렌더타겟에 그려진다. 
		// brush같은 경우 여기서 렌더.
		m_pDeviceContext->PSSetShaderResources(0, 1, m_FieldRT.m_pSRView.GetAddressOf());

		m_FieldBrush.SetMatrix(&m_FieldBrush.m_MatWorld, nullptr, nullptr);
		DX::ApplyBS(m_pDeviceContext, DX::DxState::m_pAlphaBlend2);
		m_FieldBrush.Render(m_pDeviceContext);
		
	}
	//m_FieldRT.End(m_pDeviceContext);
	//m_pDeviceContext->OMSetRenderTargets(1, NULL, NULL);
	ID3D11RenderTargetView* pRTVs = NULL;
	ID3D11DepthStencilView* pDSV = NULL;
	m_pDeviceContext->OMSetRenderTargets(1, &pRTVs, pDSV);

	m_pDeviceContext->RSSetViewports(1, &m_FieldRT.m_ViewPortOld);
	m_pDeviceContext->OMSetRenderTargets(1, m_FieldRT.m_pRTViewOld.GetAddressOf(), m_FieldRT.m_pDSViewOld.Get());
	//pd3dDContext->RSSetState(DX::DxState::m_pRSSolidFrame);
	// 기존 렌더타겟으로 복귀.
	DX::ApplyBS(m_pDeviceContext, DX::DxState::m_pAlphaBlendDisable);
	DX::ApplyDSS(m_pDeviceContext, DX::DxState::m_pDepthDisable);

}

// Field 전체를 덮는 알파 텍스처를 map / unmap으로 변경
// 사용 불가 - 프레임 드랍 심함
void	Field::Splatting(D3DXVECTOR3 vSelectedCoord3, int iTexNum)
{
	float fPickx = m_VertexList[0].Position.x - vSelectedCoord3.x;
	float fPickz = m_VertexList[0].Position.z - vSelectedCoord3.z;
	
	D3D11_TEXTURE2D_DESC desc;
	m_pSrcAlphaTexture.Get()->GetDesc(&desc);
	
	float fTexWidth = desc.Width / m_iNumCols / m_ftxOffSetU;
	float fTexHeight = desc.Height / m_iNumRows / m_ftxOffSetV;

	float fTexU = abs(fPickx / fTexWidth);
	float fTexV = abs(fPickz / fTexHeight);
	
	///***Don't read from a subresource mapped for writing***///
	///because doing so can cause a significant performance penalty///

	//typedef
	//	enum D3D11_MAP
	//{
	//	D3D11_MAP_READ = 1,
	//	D3D11_MAP_WRITE = 2,
	//	D3D11_MAP_READ_WRITE = 3,
	//	D3D11_MAP_WRITE_DISCARD = 4,
	//	D3D11_MAP_WRITE_NO_OVERWRITE = 5 버텍스/인덱스버퍼만.
	//} 	D3D11_MAP;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));
	HRESULT hr = S_OK;
	
	hr = m_pDeviceContext->Map(m_pSrcAlphaTexture.Get(), 0, D3D11_MAP_WRITE, 0, &mappedResource);
	std::unique_ptr<BYTE> pBuf(new BYTE[mappedResource.RowPitch*desc.Height]);
	BYTE* pDestBytes = (BYTE*)mappedResource.pData;

	//

	//
	for (UINT y = 0; y < desc.Height; y++)
	{
		float fy = y;
		float fLenV = abs(fTexV - (fy / desc.Height));
		//텍스처 v축으로 벗어나는 경우 해당 줄은 넘긴다.
		if (fLenV >= 0.1f)
		{
			pDestBytes += mappedResource.RowPitch;	
			continue;
		}
		BYTE* pDest = pDestBytes;
	
		for (UINT x = 0; x < desc.Width; x++)
		{
			float fx = x;

			//텍스처 u축으로 벗어나는 경우 해당 줄은 넘긴다.
			float fLenU = abs(fTexU - (fx / desc.Width));
			float fLenUV = std::sqrtf(std::powf(fLenU, 2) + std::powf(fLenV, 2));
			//if (fLenU >= 0.1f)
			//{
			//	pDest += 4;
			//}
			//else if (std::sqrtf(std::powf(fLenU, 2) + std::powf(fLenV, 2)) < 0.1f)
			//{
			//int iValue = 2;
			//switch (iTexNum)
			//{
			//case(-1):
			//{
			//	//*pDest < (BYTE)255 - iValue ? *pDest++ += iValue : *pDest++;
			//	//*pDest += 2 > (BYTE)255 ? *pDest++ = 255 : *pDest++;
			//	*pDest == (BYTE)255 ? *pDest++ : *pDest++ += 1;
			//	*pDest++;
			//	*pDest++;
			//	*pDest++;
			//}break;
			//case(0):
			//{
			//	*pDest++;
			//	*pDest == (BYTE)255 ? *pDest++ : *pDest++ += 1;
			//	//*pDest < (BYTE)255 - iValue ? *pDest++ += iValue : *pDest++;
			//	*pDest++;
			//	*pDest++;
			//}break;
			//case(1):
			//{
			//	*pDest++;
			//	*pDest++;
			//	//*pDest < (BYTE)255 - iValue ? *pDest++ += iValue : *pDest++;
			//
			//	//*pDest += 2 > (BYTE)255 ? *pDest++ = 255 : *pDest++;
			//	*pDest == (BYTE)255 ? *pDest++ : *pDest++ += 1;
			//	*pDest++;
			//}break;
			//case(2):
			//{
			//	*pDest++;
			//	*pDest++;
			//	*pDest++;
			//	//*pDest < (BYTE)255 - iValue ? *pDest++ += iValue : *pDest++;
			//
			//	//*pDest += 2 > (BYTE)255 ? *pDest++ = 255 : *pDest++;
			//	*pDest == (BYTE)255 ? *pDest++ : *pDest++ += 1;
			//}break;
			//default:
			//	break;
			//}
			//}
			//float fLenUV = std::sqrtf(std::powf(fLenU, 2) + std::powf(fLenV, 2));
			if (fLenU >= 0.1f)
			{
				pDest += 4;
			}
			else if (fLenUV >= 0.1f)
			{
				pDest += 4;
			}
			else
			{
				int iValue = 5;
				if (fLenUV > 0.05f)
					iValue *= fLenUV;
				//if (fLenUV < 0.05f)
				//{
				//	iValue = 5;
				//}
				//else
				//{
				//	iValue = 5 / fLenUV;
				//}
				switch (iTexNum)
				{
				case(-1):
				{
					*pDest < (BYTE)255 - iValue ? *pDest++ += iValue : *pDest++;
					*pDest++;
					*pDest++;
					*pDest++;
				}break;				
				case(0):
				{
					*pDest++;
					*pDest < (BYTE)255 - iValue ? *pDest++ += iValue : *pDest++ ;
					*pDest++;
					*pDest++;
				}break;
				case(1):
				{
					*pDest++;
					*pDest++;
					*pDest < (BYTE)255 - iValue ? *pDest++ += iValue : *pDest++;
					*pDest++;
				}break;
				case(2):
				{
					*pDest++;
					*pDest++;
					*pDest++;
					*pDest < (BYTE)255 - iValue ? *pDest++ += iValue : *pDest++;
				}break;
				default:
					break;
				}
			}
		}
		pDestBytes += mappedResource.RowPitch;
	}
	m_pDeviceContext->Unmap(m_pSrcAlphaTexture.Get(), 0);
	m_pDeviceContext->CopyResource(m_pDestAlphaTexture.Get(), m_pSrcAlphaTexture.Get());
	//m_pDeviceContext->UpdateSubresource(m_pSrcAlphaTexture.Get(), 0, NULL, m_pSrcAlphaTexture.Get(), 0, 0);
}
void Field::CreateNormalLookupTable()
{
	if (m_pNormalLookupTable != NULL)
	{
		free(m_pNormalLookupTable);
		m_pNormalLookupTable = NULL;
	}

	int iTableCnt = m_iNumCols * m_iNumRows * 6;

	m_pNormalLookupTable = (int*)malloc(sizeof(void*) * iTableCnt);
	for (int i = 0; i < iTableCnt; i++)
	{
		m_pNormalLookupTable[i] = -1;
	}
	
	for (int iCurrFace = 0; iCurrFace < m_iNumFace; iCurrFace++)
	{
		for (int iFaceVer = 0; iFaceVer < 3; iFaceVer++)
		{
			for (int iRelateTri = 0; iRelateTri < 6; iRelateTri++)
			{
				int iVertex = m_IndexList[iCurrFace * 3 + iFaceVer];
				if (m_pNormalLookupTable[iVertex * 6 + iRelateTri] == -1)
				{
					m_pNormalLookupTable[iVertex * 6 + iRelateTri] = iCurrFace;
					break;
				}
			}
		}
	}
}

void Field::CreateFaceNormal()
{
	m_pFaceNormal = new D3DXVECTOR3[m_iNumFace];

	for (int iFace = 0; iFace < m_iNumFace; iFace++)
	{
		m_pFaceNormal[iFace] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
}

void Field::CalculateFaceNormal()
{
	int iNum = 0;
	for (int iFace = 0; iFace < m_iNumFace * 3 ; iFace += 3)
	{
		DWORD index0 = m_IndexList[iFace];
		DWORD index1 = m_IndexList[iFace + 1];
		DWORD index2 = m_IndexList[iFace + 2];
		m_pFaceNormal[iNum] = ComputeFaceNormal(index0, index1, index2);
		iNum++;
	}
}

void Field::CalculateVertexNormalFastLookup()
{
	CalculateFaceNormal();

	int iRelateFaceNum = 0;
	for (int i = 0; i < m_iNumVertices; i++)
	{
		D3DXVECTOR3 newNormal(0.0f, 0.0f, 0.0f);
		for (iRelateFaceNum = 0; iRelateFaceNum < 6; iRelateFaceNum++)
		{
			int TriIndex = m_pNormalLookupTable[i * 6 + iRelateFaceNum];
			if (TriIndex != -1)
			{
				newNormal += m_pFaceNormal[TriIndex];
			}
			else
			{
				break;
			}
			
		}
		if (iRelateFaceNum != 0)
		{
			newNormal.x /= (float)iRelateFaceNum;
			newNormal.y /= (float)iRelateFaceNum;
			newNormal.z /= (float)iRelateFaceNum;
			D3DXVec3Normalize(&newNormal, &newNormal);

			m_VertexList[i].Normal = newNormal;
		}
	}
}

void	Field::CalculateRelatedFace(int iVertex)
{
	//CalculateFaceNormal();

	D3DXVECTOR3 newNormal(0.0f, 0.0f, 0.0f);
	int iRelateFaceNum = 0;
	for (iRelateFaceNum = 0; iRelateFaceNum < 6; iRelateFaceNum++)
	{
		int TriIndex = m_pNormalLookupTable[iVertex * 6 + iRelateFaceNum];
		if (TriIndex != -1)
		{
			DWORD index0 = m_IndexList[TriIndex * 3];
			DWORD index1 = m_IndexList[TriIndex * 3 + 1];
			DWORD index2 = m_IndexList[TriIndex * 3 + 2];
			m_pFaceNormal[TriIndex] = ComputeFaceNormal(index0, index1, index2);
			newNormal += m_pFaceNormal[TriIndex];
		}
		else
		{
			break;
		}
		
	}
	if (iRelateFaceNum != 0)
	{
		newNormal.x /= (float)iRelateFaceNum;
		newNormal.y /= (float)iRelateFaceNum;
		newNormal.z /= (float)iRelateFaceNum;
		D3DXVec3Normalize(&newNormal, &newNormal);

		m_VertexList[iVertex].Normal = newNormal;
	}
}

bool Field::Release()
{
	free(m_pNormalLookupTable);
	m_pNormalLookupTable = nullptr;

	free(m_pFaceNormal);
	m_pFaceNormal = nullptr;
	return true;
}

Field::Field() : m_ftxOffSetU(1.0f),m_ftxOffSetV(1.0f), m_pNormalLookupTable(nullptr), m_pFaceNormal(nullptr)
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

bool FieldHeight::Load(ID3D11Device* pd3Device, FieldDesc& md, const CHAR* pVertexShader, const CHAR* pPixelShader, const TCHAR* pVSFile, const TCHAR* pPSFile)
{	
	if (!m_pMapFile)
	{
		m_HeightList.resize(md.iNumCols * md.iNumRows);
		for (int i = 0; i < m_HeightList.size(); i++)
		{
			m_HeightList[i] = -1.0f;
		}
	}
	Field::Load(pd3Device, md, pVertexShader, pPixelShader, pVSFile,  pPSFile);

	return true;

}
bool	FieldHeight::SetFieldHeightData(const TCHAR* pMapFile)
{
	m_pMapFile = pMapFile;
	return true;
}


FieldHeight::FieldHeight() : m_pMapFile()
{
	m_fHeightScale = 1.0f;
}
FieldHeight::~FieldHeight()
{

}