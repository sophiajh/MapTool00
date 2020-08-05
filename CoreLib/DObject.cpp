#include "DObject.h"
#include "TextureManager.h"

HRESULT PlaneObject::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_VertexList.resize(4);

	m_VertexList[0].Position	= D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_VertexList[0].Normal		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].Color		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[0].Texture		= D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[1].Position	= D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_VertexList[1].Normal		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[1].Color		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[1].Texture		= D3DXVECTOR2(1.0f, 0.0f);
							
	m_VertexList[2].Position	= D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	m_VertexList[2].Normal		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[2].Color		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[2].Texture		= D3DXVECTOR2(1.0f, 1.0f);
						
	m_VertexList[3].Position	= D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_VertexList[3].Normal		= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[3].Color		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[3].Texture		= D3DXVECTOR2(0.0f, 1.0f);
	
	return hr;
}

HRESULT PlaneObject::CreateIndexData()
{
	HRESULT hr = S_OK;
	//m_IndexList.resize(12);
	m_IndexList.resize(6);

	m_IndexList[0] = 1;
	m_IndexList[1] = 2;
	m_IndexList[2] = 0;

	m_IndexList[3] = 2;
	m_IndexList[4] = 3;
	m_IndexList[5] = 0;

	return hr;
}

PlaneObject::PlaneObject()
{
}


PlaneObject::~PlaneObject()
{
}

HRESULT BoxObject::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_VertexList.resize(24);
	// 근 원 우 좌 상 하
	//근평면
	m_VertexList[0].Position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_VertexList[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[0].Texture = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[1].Position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	m_VertexList[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[1].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[1].Texture = D3DXVECTOR2(1.0f, 0.0f);

	m_VertexList[2].Position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_VertexList[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[2].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[2].Texture = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexList[3].Position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_VertexList[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[3].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[3].Texture = D3DXVECTOR2(0.0f, 1.0f);

	//원
	m_VertexList[4].Position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_VertexList[4].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_VertexList[4].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[4].Texture = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[5].Position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	m_VertexList[5].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_VertexList[5].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[5].Texture = D3DXVECTOR2(1.0f, 0.0f);

	m_VertexList[6].Position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_VertexList[6].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_VertexList[6].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[6].Texture = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexList[7].Position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	m_VertexList[7].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_VertexList[7].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[7].Texture = D3DXVECTOR2(0.0f, 1.0f);

	//우
	m_VertexList[8].Position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	m_VertexList[8].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_VertexList[8].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[8].Texture = D3DXVECTOR2(0.0f, 0.0f);
	
	m_VertexList[9].Position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_VertexList[9].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_VertexList[9].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[9].Texture = D3DXVECTOR2(1.0f, 0.0f);
	
	m_VertexList[10].Position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	m_VertexList[10].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_VertexList[10].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[10].Texture = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexList[11].Position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_VertexList[11].Normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_VertexList[11].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[11].Texture = D3DXVECTOR2(0.0f, 1.0f);

	//좌측
	m_VertexList[12].Position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	m_VertexList[12].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_VertexList[12].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[12].Texture = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[13].Position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_VertexList[13].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_VertexList[13].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[13].Texture = D3DXVECTOR2(1.0f, 0.0f);

	m_VertexList[14].Position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_VertexList[14].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_VertexList[14].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[14].Texture = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexList[15].Position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_VertexList[15].Normal = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_VertexList[15].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[15].Texture = D3DXVECTOR2(0.0f, 1.0f);

	//상
	m_VertexList[16].Position = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	m_VertexList[16].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_VertexList[16].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[16].Texture = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[17].Position = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_VertexList[17].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_VertexList[17].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[17].Texture = D3DXVECTOR2(1.0f, 0.0f);

	m_VertexList[18].Position = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	m_VertexList[18].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_VertexList[18].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[18].Texture = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexList[19].Position = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	m_VertexList[19].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_VertexList[19].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[19].Texture = D3DXVECTOR2(0.0f, 1.0f);

	//하
	m_VertexList[20].Position = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	m_VertexList[20].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_VertexList[20].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[20].Texture = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[21].Position = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	m_VertexList[21].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_VertexList[21].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[21].Texture = D3DXVECTOR2(1.0f, 0.0f);

	m_VertexList[22].Position = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	m_VertexList[22].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_VertexList[22].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[22].Texture = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexList[23].Position = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	m_VertexList[23].Normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_VertexList[23].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[23].Texture = D3DXVECTOR2(0.0f, 1.0f);

	return hr;
}

HRESULT BoxObject::CreateIndexData()
{
	HRESULT hr = S_OK;
	m_IndexList.resize(36);

	m_IndexList[0] = 1;
	m_IndexList[1] = 2;
	m_IndexList[2] = 0;

	m_IndexList[3] = 2;
	m_IndexList[4] = 3;
	m_IndexList[5] = 0;


	m_IndexList[6] = 5;
	m_IndexList[7] = 6;
	m_IndexList[8] = 4;

	m_IndexList[9] = 6;
	m_IndexList[10] = 7;
	m_IndexList[11] = 4;


	m_IndexList[12] = 9;
	m_IndexList[13] = 10;
	m_IndexList[14] = 8;

	m_IndexList[15] = 10;
	m_IndexList[16] = 11;
	m_IndexList[17] = 8;


	m_IndexList[18] = 13;
	m_IndexList[19] = 14;
	m_IndexList[20] = 12;

	m_IndexList[21] = 14;
	m_IndexList[22] = 15;
	m_IndexList[23] = 12;


	m_IndexList[24] = 17;
	m_IndexList[25] = 18;
	m_IndexList[26] = 16;

	m_IndexList[27] = 18;
	m_IndexList[28] = 19;
	m_IndexList[29] = 16;


	m_IndexList[30] = 21;
	m_IndexList[31] = 22;
	m_IndexList[32] = 20;

	m_IndexList[33] = 22;
	m_IndexList[34] = 23;
	m_IndexList[35] = 20;


	return hr;
}

BoxObject::BoxObject()
{

}

BoxObject::~BoxObject()
{

}
HRESULT LineObject::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_VertexList.resize(2);
	m_VertexList[0].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[0].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[0].Color		= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[0].Texture		= D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[1].Position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_VertexList[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[1].Color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[1].Texture = D3DXVECTOR2(1.0f, 0.0f);

	//m_VertexList.resize(6);
	//m_VertexList[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[0].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//m_VertexList[0].Texture = D3DXVECTOR2(0.0f, 0.0f);

	//m_VertexList[1].Position	= D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
	//m_VertexList[1].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[1].Color		= D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	//m_VertexList[1].Texture		= D3DXVECTOR2(1.0f, 0.0f);

	//m_VertexList[2].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[2].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[2].Color		= D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	//m_VertexList[2].Texture		= D3DXVECTOR2(0.0f, 0.0f);
	//
	//m_VertexList[3].Position	= D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
	//m_VertexList[3].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[3].Color		= D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	//m_VertexList[3].Texture		= D3DXVECTOR2(1.0f, 0.0f);
	//
	//m_VertexList[4].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[4].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[4].Color		= D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//m_VertexList[4].Texture		= D3DXVECTOR2(0.0f, 0.0f);
	//
	//m_VertexList[5].Position	= D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
	//m_VertexList[5].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_VertexList[5].Color		= D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//m_VertexList[5].Texture		= D3DXVECTOR2(1.0f, 0.0f);
	return hr;
}

bool LineObject::PostRender(ID3D11DeviceContext* pContext)
{
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_DxHelper.PostRender(pContext, m_DxHelper.m_iNumIndex);
	return true;
}

LineObject::LineObject()
{
}

LineObject::~LineObject()
{
}


HRESULT AxisObject::CreateVertexData()
{
	HRESULT hr = S_OK;
	
	m_VertexList.resize(6);
	
	//int iVertex = 0;
	//for (int iNumLine = 0; iNumLine < 3; iNumLine++)
	//{
	//	LineObject* SingleLine = new LineObject;
	//
	//	m_VertexList[iVertex] = SingleLine->m_VertexList[0];
	//	m_VertexList[iVertex+1] = SingleLine->m_VertexList[1];
	//
	//	iVertex += 2;
	//}

	m_VertexList[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[0].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[0].Texture = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[1].Position	= D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
	m_VertexList[1].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[1].Color		= D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[1].Texture		= D3DXVECTOR2(1.0f, 0.0f);

	m_VertexList[2].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[2].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[2].Color		= D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[2].Texture		= D3DXVECTOR2(0.0f, 0.0f);
	
	m_VertexList[3].Position	= D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
	m_VertexList[3].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[3].Color		= D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[3].Texture		= D3DXVECTOR2(1.0f, 0.0f);
	
	m_VertexList[4].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[4].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[4].Color		= D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[4].Texture		= D3DXVECTOR2(0.0f, 0.0f);
	
	m_VertexList[5].Position	= D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
	m_VertexList[5].Normal		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[5].Color		= D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[5].Texture		= D3DXVECTOR2(1.0f, 0.0f);
	return hr;
}

bool AxisObject::PostRender(ID3D11DeviceContext* pContext)
{
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_DxHelper.PostRender(pContext, m_DxHelper.m_iNumIndex);
	return true;
}

AxisObject::AxisObject()
{
}

AxisObject::~AxisObject()
{
}