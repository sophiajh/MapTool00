#include "pch.h"
#include "Sample.h"

bool Sample::Init()
{
	if (!m_BasisLine.Create(m_pDevice, L"../CoreLib/HLSL.vsh", L"../CoreLib/HLSL.psh", nullptr, "VS_Line", "PS_Line"))
		return false;

	m_MinimapCam.Init();
	m_MinimapCam.m_vPosition = D3DXVECTOR3(0.0f, 300.0f, 0.0f);
	m_MinimapCam.m_vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.1f);
	m_MinimapCam.CreateViewMatrix(m_MinimapCam.m_vPosition, m_MinimapCam.m_vTarget);

	//if (!m_Obj.Create(m_pDevice, L"../CoreLib/HLSL.vsh", L"../CoreLib/Field.psh", L"../../data/bitmap/B_Hornet2.png", "VS", "PS_Test"))
	//{
	//	return false;
	//}

	m_FullRT.Create(m_pDevice, 1024, 1024);
	m_MinimapRT.Create(m_pDevice, 1024, 1024);
	if (!m_Screen.Create(m_pDevice, L"../CoreLib/HLSL.vsh", L"../CoreLib/HLSL.psh", nullptr, "VS", "PS_Screen"))
	{
		return false;
	}
	m_Screen.m_VertexList[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_Screen.m_VertexList[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_Screen.m_VertexList[2].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	m_Screen.m_VertexList[3].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

	if (!m_MiniMap.Create(m_pDevice, L"../CoreLib/HLSL.vsh", L"../CoreLib/HLSL.psh", nullptr, "VS", "PS_Screen"))
	{
		return false;
	}

	m_MiniMap.m_VertexList[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_MiniMap.m_VertexList[1].Position = D3DXVECTOR3(-0.3f, 1.0f, 0.0f);
	m_MiniMap.m_VertexList[2].Position = D3DXVECTOR3(-0.3f, 0.3f, 0.0f);
	m_MiniMap.m_VertexList[3].Position = D3DXVECTOR3(-1.0f, 0.3f, 0.0f);

	m_pCurrCamera->CreateProjMatrix(D3DX_PI / 4, (float)g_rtClient.right / (float)g_rtClient.bottom, 1.0f, 1000.0f);
	m_Select.Init();

	m_cbLight.g_cAmbientMaterial = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1);
	m_cbLight.g_cDiffuseMaterial = D3DXVECTOR4(1, 1, 1, 1);
	m_cbLight.g_cAmbientLightColor = D3DXVECTOR4(1, 1, 1, 1);
	m_cbLight.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);

	m_pConstantBufferLight.Attach(DX::CreateConstantBuffer( m_pDevice, &m_cbLight, 1, sizeof(LIGHT_CONSTANT_BUFFER)));

	return true;
}

bool Sample::Frame()
{
	D3DXMATRIX mLightWorld, mTranslate, mRotation;
	D3DXMatrixTranslation(&mTranslate, 100.0f, 100.0f, 0.0f);
	D3DXMatrixRotationY(&mRotation, m_Timer.GetRuntime() * 0.3f);
	D3DXMatrixMultiply(&m_LightMat, &mTranslate, &mRotation);

	m_vLightVector.x = m_LightMat._41;
	m_vLightVector.y = m_LightMat._42;
	m_vLightVector.z = m_LightMat._43;

	D3DXVec3Normalize(&m_vLightVector, &m_vLightVector);
	m_vLightVector *= -1.0f;

	if (m_TestField)
	{
		m_Quad.Update(m_pCurrCamera);
		m_Quad.Frame();

		m_Select.Frame();
	}
	m_Obj.Frame();

	m_pCurrCamera->CreateProjMatrix(D3DX_PI / 4, (float)g_rtClient.right / (float)g_rtClient.bottom, 1.0f, 1000.0f);

	return true;
}

bool Sample::Render()
{	
	{
		m_FullRT.Begin(m_pDeviceContext);
		m_BasisLine.SetMatrix(nullptr, (D3DXMATRIX*)&m_pCurrCamera->m_MatView, (D3DXMATRIX*)&m_pCurrCamera->m_matProj);
		m_BasisLine.Render(m_pDeviceContext);
		
		DX::ApplySS(m_pDeviceContext, DX::DxState::m_pSSWrapAniso);
		float t = g_fSecondPerFrame * 3.0f;

		D3DXMATRIX matWorld, matScale;
		D3DXMatrixScaling(&matScale, 100, 100, 100);
		D3DXMatrixRotationY(&matWorld, t);
		D3DXMatrixMultiply(&matWorld, &matScale, &matWorld);
		matWorld._42 = 200.0f;

		m_cbLight.g_vLightDir.x = m_vLightVector.x;
		m_cbLight.g_vLightDir.y = m_vLightVector.y;
		m_cbLight.g_vLightDir.z = m_vLightVector.z;
		m_cbLight.g_vLightDir.w = 1;

		m_cbLight.g_vEyeDir.x = m_pCurrCamera->m_vLook.x;
		m_cbLight.g_vEyeDir.y = m_pCurrCamera->m_vLook.y;
		m_cbLight.g_vEyeDir.z = m_pCurrCamera->m_vLook.z;
		m_cbLight.g_vEyeDir.w = 1;

		D3DXMATRIX matInvWorld;
		D3DXMatrixInverse(&matInvWorld, NULL, &matWorld);
		D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
		D3DXMatrixTranspose(&m_cbLight.g_matInvWorld, &matInvWorld);

		m_pDeviceContext->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);
		m_pDeviceContext->VSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
		m_pDeviceContext->PSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());


		D3DXMatrixIdentity(&m_cbLight.g_matInvWorld);
		m_pDeviceContext->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);
		//m_Obj.SetMatrix(nullptr, (D3DXMATRIX*)&m_pCurrCamera->m_MatView, (D3DXMATRIX*)&m_pCurrCamera->m_matProj);
		//m_Obj.Render(m_pDeviceContext);

		if (m_TestField)
		{
			m_TestField->SetMatrix(nullptr, (D3DXMATRIX*)&m_pCurrCamera->m_MatView, (D3DXMATRIX*)&m_pCurrCamera->m_matProj);
			//color변경 업데이트.
			//m_TestField->m_pAlphaTexture.Get()
			//m_pDeviceContext->PSSetShaderResources(1, 1, &m_TestField->m_pAlphaTexture.GetAddressOf);
			m_pDeviceContext->PSSetShaderResources(1, 1, m_TestField->m_pAlphaSRV.GetAddressOf());
			m_pDeviceContext->PSSetShaderResources(2, 1, &m_TestField->m_pSplattingPatternList[0]); //물
			m_pDeviceContext->PSSetShaderResources(3, 1, &m_TestField->m_pSplattingPatternList[1]); //모래
			m_pDeviceContext->PSSetShaderResources(4, 1, &m_TestField->m_pSplattingPatternList[2]); //나무
			
			m_pDeviceContext->UpdateSubresource(m_TestField->m_DxHelper.m_pVertexBuffer.Get(), 0, NULL, &m_TestField->m_VertexList.at(0), 0, 0);

			//m_TestField->Render(m_pDeviceContext);
			m_Quad.Render(m_pDeviceContext);
			m_Select.Render(m_pDeviceContext);

		}
	}
	m_FullRT.End(m_pDeviceContext);

	m_pDeviceContext->UpdateSubresource(m_Screen.m_DxHelper.m_pVertexBuffer.Get(), 0, NULL, &m_Screen.m_VertexList.at(0), 0, 0);
	m_Screen.PreRender(m_pDeviceContext);
	m_pDeviceContext->PSSetShaderResources(0, 1, m_FullRT.m_pSRView.GetAddressOf());
	m_Screen.PostRender(m_pDeviceContext);
	//m_Screen FPS 6000->4000

	DX::ApplyDSS(m_pDeviceContext, DX::DxState::m_pDepthDisable);
	m_MinimapRT.Begin(m_pDeviceContext);
	{
		if (m_TestField)
		{
			m_TestField->SetMatrix(nullptr, (D3DXMATRIX*)&m_MinimapCam.m_MatView, (D3DXMATRIX*)&m_pCurrCamera->m_matProj);
			m_Quad.Render(m_pDeviceContext);
		}
		DX::ApplyBS(m_pDeviceContext, DX::DxState::m_pAlphaBlend);
		DX::ApplyDSS(m_pDeviceContext, DX::DxState::m_pDepthEnable);
		m_pCurrCamera->SetMatrix(nullptr, (D3DXMATRIX*)&m_MinimapCam.m_MatView, (D3DXMATRIX*)&m_pCurrCamera->m_matProj);
		m_pCurrCamera->Render(m_pDeviceContext);
		DX::ApplyDSS(m_pDeviceContext, DX::DxState::m_pDepthDisable);
		DX::ApplyBS(m_pDeviceContext, DX::DxState::m_pAlphaBlendDisable);
		m_MinimapRT.End(m_pDeviceContext);
	}

	m_pDeviceContext->UpdateSubresource(m_MiniMap.m_DxHelper.m_pVertexBuffer.Get(), 0, NULL, &m_MiniMap.m_VertexList.at(0), 0, 0);

	m_MiniMap.PreRender(m_pDeviceContext);
	m_pDeviceContext->PSSetShaderResources(0, 1, m_MinimapRT.m_pSRView.GetAddressOf());
	m_MiniMap.PostRender(m_pDeviceContext);

	return true;

}

bool Sample::Release()
{
	if (m_TestField)
	{
		if (m_TestField->m_pSrcAlphaTexture)
			m_TestField->m_pSrcAlphaTexture.Get()->Release();
		if (m_TestField->m_pDestAlphaTexture)
			m_TestField->m_pDestAlphaTexture.Get()->Release();
		m_TestField->Release();
	}
	return true;

}

Sample::Sample()
{

}

Sample::~Sample()
{
	
}

FieldHeight& Sample::CreateField(int iRow, int iCol)
{
	static FieldHeight * UserSetField = new FieldHeight;

	FieldDesc fd;
	fd.fCellDistance = 1.0f;
	fd.iNumCols = iCol;
	fd.iNumRows = iRow;
	fd.fHeightScale = 1.0f;
	fd.szTextureFile = L"../../data/bitmap/Tile57.jpg";

	UserSetField->m_iNumCols = fd.iNumCols; //num of vertex
	UserSetField->m_iNumRows = fd.iNumRows;
	UserSetField->m_fHeightScale = fd.fHeightScale;
	UserSetField->m_iNumCellCols = UserSetField->m_iNumCols - 1;
	UserSetField->m_iNumCellRows = UserSetField->m_iNumRows - 1;
	UserSetField->m_iNumVertices = UserSetField->m_iNumCols * UserSetField->m_iNumRows;
	UserSetField->m_iNumFace = UserSetField->m_iNumCellCols * UserSetField->m_iNumCellRows * 2;
	UserSetField->m_fCellDistance = fd.fCellDistance;
	UserSetField->m_pDevice = m_pDevice;
	
	UserSetField->m_ftxOffSetU = 0.5f;
	UserSetField->m_ftxOffSetV = 0.5f;
	
	UserSetField->m_HeightList.resize(fd.iNumCols * fd.iNumRows);
	for (int i = 0; i < UserSetField->m_HeightList.size(); i++)
	{
		UserSetField->m_HeightList[i] = -1.0f;
	}
	UserSetField->Create(m_pDevice, L"../CoreLib/HLSL.vsh", L"../CoreLib/Field.psh", L"../../data/bitmap/Tile57.jpg", "VS", "PS_FieldTest");
	UserSetField->m_pPattern = UserSetField->m_DxHelper.m_pSRV;
	UserSetField->LoadTexture(fd.szCubeFile.c_str());
	UserSetField->m_pCube = UserSetField->m_DxHelper.m_pSRV;

	UserSetField->m_ConstBuffer.etc[1] = fd.iNumCols - 1;


	m_Quad.BuildQuadField(UserSetField);
	m_Quad.CreateSharedIndex();

	int jIndex = TextureManager::GetInstance().Load(m_pDevice, L"../../data/bitmap/031.bmp"); //물
	int tIndex = TextureManager::GetInstance().Load(m_pDevice, L"../../data/bitmap/032.bmp"); //모래
	int pIndex = TextureManager::GetInstance().Load(m_pDevice, L"../../data/bitmap/033.bmp"); //나무
	UserSetField->m_pSplattingPatternList[0] = TextureManager::GetInstance().GetPtr(jIndex)->m_pSRV;
	UserSetField->m_pSplattingPatternList[1] = TextureManager::GetInstance().GetPtr(tIndex)->m_pSRV;
	UserSetField->m_pSplattingPatternList[2] = TextureManager::GetInstance().GetPtr(pIndex)->m_pSRV;
	//UserSetField->m_pPattern = TextureManager::GetInstance().GetPtr(tIndex)->m_pSRV;
	
	m_Select.SetSelect(*UserSetField, *m_pCurrCamera, m_Quad);
	UserSetField->m_pDeviceContext = m_pDeviceContext;
	
	////Create AlphaTexture///////////////////// USING MAP

	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	td.Width = iCol * UserSetField->m_iNumCols;// *UserSetField->m_ftxOffSetU;
	td.Height = iRow * UserSetField->m_iNumRows;// *UserSetField->m_ftxOffSetV;
	td.MipLevels = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	td.Usage = D3D11_USAGE_STAGING;
	td.BindFlags = 0;	
	td.ArraySize = 1;	   
	
	if (FAILED(hr = m_pDevice->CreateTexture2D(&td, 0, UserSetField->m_pSrcAlphaTexture.GetAddressOf())))
	{
		return *UserSetField;
	}
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;// 0;// D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	if (FAILED(hr = m_pDevice->CreateTexture2D(&td, NULL, UserSetField->m_pDestAlphaTexture.GetAddressOf())))
	{
		return *UserSetField;
	}
	if (FAILED(hr = m_pDevice->CreateShaderResourceView(UserSetField->m_pDestAlphaTexture.Get(), NULL, UserSetField->m_pAlphaSRV.GetAddressOf())))
	{
		return *UserSetField;
	}	
	//////////////////////////////////////
	return *UserSetField;

}
