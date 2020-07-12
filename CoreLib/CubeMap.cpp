#include "CubeMap.h"
#include "TextureManager.h"
HRESULT	CubeMap::LoadTextureArray(const TCHAR* pTextureFile)
{
	HRESULT hr = S_OK;
	//const TCHAR* g_szSkyTextures[] =
	//{
	//	L"../../data/skybox/bk.bmp",
	//	L"../../data/skybox/rt.bmp",
	//	L"../../data/skybox/ft.bmp",
	//	L"../../data/skybox/lt.bmp",
	//	L"../../data/skybox/up.bmp",
	//	L"../../data/skybox/dn.bmp"
	//};
	//for (int iSub = 0; iSub < 6; iSub++)
	//{
	//	int iIndex = TextureManager::GetInstance().Load(m_pDevice, g_szSkyTextures[iSub]);
	//	if (iIndex >= 0)
	//	{
	//		///m_pTexSRV[iSub].Swap(I_TextureMgr.GetPtr(iIndex)->m_pSRV.Get());
	//		//m_pFaceTex[iSub] = TextureManager::GetInstance().GetPtr(iIndex)->m_pSRV;
	//	}
	//}
	return hr;
}

//HRESULT CubeMap::CreateVertexData()
//{
//	HRESULT hr=S_OK;
//	m_VertexList.resize(24);
//
//	//근평면
//	m_VertexList[0].Position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
//	m_VertexList[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//	m_VertexList[0].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[0].Texture = D3DXVECTOR2(0.0f, 0.0f);
//
//	m_VertexList[1].Position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
//	m_VertexList[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//	m_VertexList[1].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
//	m_VertexList[1].Texture = D3DXVECTOR2(1.0f, 0.0f);
//
//	m_VertexList[2].Position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
//	m_VertexList[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//	m_VertexList[2].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[2].Texture = D3DXVECTOR2(1.0f, 1.0f);
//
//	m_VertexList[3].Position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
//	m_VertexList[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//	m_VertexList[3].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	m_VertexList[3].Texture = D3DXVECTOR2(0.0f, 1.0f);
//
//	//원평면
//	m_VertexList[4].Position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//	m_VertexList[4].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	m_VertexList[4].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[4].Texture = D3DXVECTOR2(0.0f, 0.0f);
//
//	m_VertexList[5].Position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
//	m_VertexList[5].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	m_VertexList[5].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
//	m_VertexList[5].Texture = D3DXVECTOR2(1.0f, 0.0f);
//
//	m_VertexList[6].Position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
//	m_VertexList[6].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	m_VertexList[6].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[6].Texture = D3DXVECTOR2(1.0f, 1.0f);
//
//	m_VertexList[7].Position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
//	m_VertexList[7].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	m_VertexList[7].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
//	m_VertexList[7].Texture = D3DXVECTOR2(0.0f, 1.0f);
//
//	//우
//	m_VertexList[8].Position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
//	m_VertexList[8].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//	m_VertexList[8].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
//	m_VertexList[8].Texture = D3DXVECTOR2(0.0f, 0.0f);
//
//	m_VertexList[9].Position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//	m_VertexList[9].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//	m_VertexList[9].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[9].Texture = D3DXVECTOR2(1.0f, 0.0f);
//
//	m_VertexList[10].Position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
//	m_VertexList[10].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//	m_VertexList[10].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	m_VertexList[10].Texture = D3DXVECTOR2(1.0f, 1.0f);
//
//	m_VertexList[11].Position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
//	m_VertexList[11].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//	m_VertexList[11].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[11].Texture = D3DXVECTOR2(0.0f, 1.0f);
//
//	//좌측
//	m_VertexList[12].Position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
//	m_VertexList[12].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	m_VertexList[12].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[12].Texture = D3DXVECTOR2(0.0f, 0.0f);
//
//	m_VertexList[13].Position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
//	m_VertexList[13].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	m_VertexList[13].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
//	m_VertexList[13].Texture = D3DXVECTOR2(1.0f, 0.0f);
//
//	m_VertexList[14].Position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
//	m_VertexList[14].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	m_VertexList[14].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[14].Texture = D3DXVECTOR2(1.0f, 1.0f);
//
//	m_VertexList[15].Position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
//	m_VertexList[15].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	m_VertexList[15].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	m_VertexList[15].Texture = D3DXVECTOR2(0.0f, 1.0f);
//
//	//상
//	m_VertexList[16].Position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
//	m_VertexList[16].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//	m_VertexList[16].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[16].Texture = D3DXVECTOR2(0.0f, 0.0f);
//
//	m_VertexList[17].Position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//	m_VertexList[17].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//	m_VertexList[17].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
//	m_VertexList[17].Texture = D3DXVECTOR2(1.0f, 0.0f);
//
//	m_VertexList[18].Position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
//	m_VertexList[18].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//	m_VertexList[18].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[18].Texture = D3DXVECTOR2(1.0f, 1.0f);
//
//	m_VertexList[19].Position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
//	m_VertexList[19].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//	m_VertexList[19].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	m_VertexList[19].Texture = D3DXVECTOR2(0.0f, 1.0f);
//
//	//하
//	m_VertexList[20].Position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
//	m_VertexList[20].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_VertexList[20].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[20].Texture = D3DXVECTOR2(0.0f, 0.0f);
//
//	m_VertexList[21].Position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
//	m_VertexList[21].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_VertexList[21].Color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
//	m_VertexList[21].Texture = D3DXVECTOR2(1.0f, 0.0f);
//
//	m_VertexList[22].Position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
//	m_VertexList[22].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_VertexList[22].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
//	m_VertexList[22].Texture = D3DXVECTOR2(1.0f, 1.0f);
//
//	m_VertexList[23].Position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
//	m_VertexList[23].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_VertexList[23].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
//	m_VertexList[23].Texture = D3DXVECTOR2(0.0f, 1.0f);
//
//	////근
//	m_VertexList[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	m_VertexList[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	m_VertexList[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	m_VertexList[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
//	//m_VertexList[0].Texture = D3DXVECTOR2(1.0f, 0.0f);
//	//m_VertexList[1].Texture = D3DXVECTOR2(0.0f, 0.0f);
//	//m_VertexList[2].Texture = D3DXVECTOR2(0.0f, 1.0f);
//	//m_VertexList[3].Texture = D3DXVECTOR2(1.0f, 1.0f);
//	////원
//	m_VertexList[4].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//	m_VertexList[5].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//	m_VertexList[6].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//	m_VertexList[7].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
//	//m_VertexList[4].Texture = D3DXVECTOR2(1.0f, 0.0f);
//	//m_VertexList[5].Texture = D3DXVECTOR2(0.0f, 0.0f);
//	//m_VertexList[6].Texture = D3DXVECTOR2(0.0f, 1.0f);
//	//m_VertexList[7].Texture = D3DXVECTOR2(1.0f, 1.0f);
//	////우
//	m_VertexList[8].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	m_VertexList[9].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	m_VertexList[10].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	m_VertexList[11].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
//	//m_VertexList[8].Texture = D3DXVECTOR2(1.0f, 0.0f);
//	//m_VertexList[9].Texture = D3DXVECTOR2(0.0f, 0.0f);
//	//m_VertexList[10].Texture = D3DXVECTOR2(0.0f, 1.0f);
//	//m_VertexList[11].Texture = D3DXVECTOR2(1.0f, 1.0f);
//	////좌
//	m_VertexList[12].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//	m_VertexList[13].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//	m_VertexList[14].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//	m_VertexList[15].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
//	//m_VertexList[12].Texture = D3DXVECTOR2(1.0f, 0.0f);
//	//m_VertexList[13].Texture = D3DXVECTOR2(0.0f, 0.0f);
//	//m_VertexList[14].Texture = D3DXVECTOR2(0.0f, 1.0f);
//	//m_VertexList[15].Texture = D3DXVECTOR2(1.0f, 1.0f);
//	////상
//	m_VertexList[16].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_VertexList[17].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_VertexList[18].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	m_VertexList[19].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
//	////m_VertexList[16].Texture = D3DXVECTOR2(0.0f, 1.0f);
//	////m_VertexList[17].Texture = D3DXVECTOR2(1.0f, 1.0f);
//	////m_VertexList[18].Texture = D3DXVECTOR2(1.0f, 0.0f);
//	////m_VertexList[19].Texture = D3DXVECTOR2(0.0f, 0.0f);
//	//////하
//	m_VertexList[20].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//	m_VertexList[21].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//	m_VertexList[22].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//	m_VertexList[23].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
//	////m_VertexList[20].Texture = D3DXVECTOR2(0.0f, 1.0f);
//	////m_VertexList[21].Texture = D3DXVECTOR2(1.0f, 1.0f);
//	////m_VertexList[22].Texture = D3DXVECTOR2(1.0f, 0.0f);
//	////m_VertexList[23].Texture = D3DXVECTOR2(0.0f, 0.0f);
//	return hr;
//}

bool	CubeMap::Render(ID3D11DeviceContext* pd3dDeviceContext)
{
	//DX::ApplySS(pd3dDeviceContext, DX::DxState::m_pSSWrapAniso);
	//DX::DxState::m_pSSWrapAniso
	D3D11_MAPPED_SUBRESOURCE msr;
	HRESULT hr;
	if (SUCCEEDED(hr = pd3dDeviceContext->Map(m_DxHelper.m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &msr)))
	{
		EssCB* Data = (EssCB*)msr.pData;

		Data->MatWorld = m_ConstBuffer.MatWorld;	//D3DXMatrixIdentity(&Data->MatWorld);
		Data->MatView = m_ConstBuffer.MatView;
		Data->MatProj = m_ConstBuffer.MatProj;
		Data->color[0] = 1.0f;
		Data->etc[0] = 0.0f;
		pd3dDeviceContext->Unmap(m_DxHelper.m_pConstantBuffer.Get(), 0);
	}
	pd3dDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pd3dDeviceContext->IASetInputLayout(m_DxHelper.m_pInputLayout.Get());
	pd3dDeviceContext->IASetIndexBuffer(m_DxHelper.m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	//pd3dDeviceContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());
	pd3dDeviceContext->VSSetShader(m_DxHelper.m_pVertexShader.Get(), NULL, 0);
	pd3dDeviceContext->PSSetShader(m_DxHelper.m_pPixelShader.Get(), NULL, 0);
	UINT stride = 48;
	UINT offset = 0;
	pd3dDeviceContext->IASetVertexBuffers(0, 1, m_DxHelper.m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	pd3dDeviceContext->VSSetConstantBuffers(0, 1, m_DxHelper.m_pConstantBuffer.GetAddressOf());
	pd3dDeviceContext->VSSetConstantBuffers(1, 1, m_DxHelper.m_pConstantBuffer.GetAddressOf());
	pd3dDeviceContext->PSSetConstantBuffers(0, 1, m_DxHelper.m_pConstantBuffer.GetAddressOf());

	pd3dDeviceContext->UpdateSubresource(m_DxHelper.m_pConstantBuffer.Get(), 0, NULL, &m_ConstBuffer, 0, 0);
	//PreRender(pd3dDeviceContext);
	pd3dDeviceContext->PSSetShaderResources(1,1, m_DxHelper.m_pSRV.GetAddressOf());
	PostRender(pd3dDeviceContext);
	//DX::ApplySS(pd3dDeviceContext, DX::DxState::m_pSSWrapLinear);
	return true;
}

CubeMap::CubeMap()
{
}


CubeMap::~CubeMap()
{
}
