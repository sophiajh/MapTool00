#include "Frusturm.h"

bool	K_PLANE::CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	D3DXVECTOR3 Edge1 = v1 - v0;
	D3DXVECTOR3 Edge2 = v2 - v0;
	D3DXVECTOR3	vNormal;

	D3DXVec3Cross(&vNormal, &Edge1, &Edge2);
	D3DXVec3Normalize(&vNormal, &vNormal);
	fA = vNormal.x;
	fB = vNormal.y;
	fC = vNormal.z;
	fD = -(fA * v0.x + fB * v0.y + fC * v0.z);
	return true;
}
bool	K_PLANE::CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 vNormal)
{
	D3DXVec3Normalize(&vNormal, &vNormal);
	fA = vNormal.x;
	fB = vNormal.y;
	fC = vNormal.z;
	fD = -(fA * v0.x + fB * v0.y + fC * v0.z);
	return true;
}
void	K_PLANE::Normalization()
{
	return;
}


bool	Frusturm::CreateFrustumObj(ID3D11Device* pDevice)
{
	if (!m_FrustumBox.Create(pDevice, L"../CoreLib/HLSL.vsh", L"../CoreLib/HLSL.psh", nullptr, "VS", "PS_Line"))
	{
		return false;
	}
	return true;
}
bool	Frusturm::CreateFrustum(D3DXMATRIX& pView, D3DXMATRIX& pProj)
{
	D3DXMATRIX matInvVP, matTmp;
	matTmp = pView * pProj;
	D3DXMatrixInverse(&matInvVP, NULL, &matTmp);

	//0	1	4	5
	//3	2	7	6

	m_vFrustum[0] = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_vFrustum[1] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_vFrustum[2] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	m_vFrustum[3] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

	m_vFrustum[4] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	m_vFrustum[5] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_vFrustum[6] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	m_vFrustum[7] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);

	for (int iVer = 0; iVer < 8; iVer++)
	{
		D3DXVec3TransformCoord(&m_vFrustum[iVer], &m_vFrustum[iVer], &matInvVP);
	}


	//근 원 우 좌 상 하
	m_FrustumPlane[0].CreatePlane(m_vFrustum[0], m_vFrustum[2], m_vFrustum[1]);
	m_FrustumPlane[1].CreatePlane(m_vFrustum[4], m_vFrustum[5], m_vFrustum[6]);
	m_FrustumPlane[2].CreatePlane(m_vFrustum[1], m_vFrustum[6], m_vFrustum[5]);
	m_FrustumPlane[3].CreatePlane(m_vFrustum[4], m_vFrustum[3], m_vFrustum[0]);
	m_FrustumPlane[4].CreatePlane(m_vFrustum[4], m_vFrustum[1], m_vFrustum[5]);
	m_FrustumPlane[5].CreatePlane(m_vFrustum[2], m_vFrustum[3], m_vFrustum[7]);

	return true;
}
bool	Frusturm::PreRender(ID3D11DeviceContext* pContext, UINT iSize)
{
	//근
	m_FrustumBox.m_VertexList[0] = PNCT_VERTEX(m_vFrustum[0], D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.2f), D3DXVECTOR2(0.0f, 0.0f));
	m_FrustumBox.m_VertexList[1] = PNCT_VERTEX(m_vFrustum[1], D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.2f), D3DXVECTOR2(1.0f, 0.0f));
	m_FrustumBox.m_VertexList[2] = PNCT_VERTEX(m_vFrustum[2], D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.2f), D3DXVECTOR2(1.0f, 1.0f));
	m_FrustumBox.m_VertexList[3] = PNCT_VERTEX(m_vFrustum[3], D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.2f), D3DXVECTOR2(0.0f, 1.0f));
	//원
	m_FrustumBox.m_VertexList[4] = PNCT_VERTEX(m_vFrustum[5], D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.2f), D3DXVECTOR2(0.0f, 0.0f));
	m_FrustumBox.m_VertexList[5] = PNCT_VERTEX(m_vFrustum[4], D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.2f), D3DXVECTOR2(1.0f, 0.0f));
	m_FrustumBox.m_VertexList[6] = PNCT_VERTEX(m_vFrustum[7], D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.2f), D3DXVECTOR2(1.0f, 1.0f));
	m_FrustumBox.m_VertexList[7] = PNCT_VERTEX(m_vFrustum[6], D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.2f), D3DXVECTOR2(0.0f, 1.0f));
	//우
	m_FrustumBox.m_VertexList[8] = PNCT_VERTEX(m_vFrustum[1], D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.2f), D3DXVECTOR2(0.0f, 0.0f));
	m_FrustumBox.m_VertexList[9] = PNCT_VERTEX(m_vFrustum[5], D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.2f), D3DXVECTOR2(1.0f, 0.0f));
	m_FrustumBox.m_VertexList[10] = PNCT_VERTEX(m_vFrustum[6], D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.2f), D3DXVECTOR2(1.0f, 1.0f));
	m_FrustumBox.m_VertexList[11] = PNCT_VERTEX(m_vFrustum[2], D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.2f), D3DXVECTOR2(0.0f, 1.0f));
	//좌
	m_FrustumBox.m_VertexList[12] = PNCT_VERTEX(m_vFrustum[4], D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.2f), D3DXVECTOR2(0.0f, 0.0f));
	m_FrustumBox.m_VertexList[13] = PNCT_VERTEX(m_vFrustum[0], D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.2f), D3DXVECTOR2(1.0f, 0.0f));
	m_FrustumBox.m_VertexList[14] = PNCT_VERTEX(m_vFrustum[3], D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.2f), D3DXVECTOR2(1.0f, 1.0f));
	m_FrustumBox.m_VertexList[15] = PNCT_VERTEX(m_vFrustum[7], D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.2f), D3DXVECTOR2(0.0f, 1.0f));
	//상
	m_FrustumBox.m_VertexList[16] = PNCT_VERTEX(m_vFrustum[4], D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.2f), D3DXVECTOR2(0.0f, 0.0f));
	m_FrustumBox.m_VertexList[17] = PNCT_VERTEX(m_vFrustum[5], D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.2f), D3DXVECTOR2(1.0f, 0.0f));
	m_FrustumBox.m_VertexList[18] = PNCT_VERTEX(m_vFrustum[1], D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.2f), D3DXVECTOR2(1.0f, 1.0f));
	m_FrustumBox.m_VertexList[19] = PNCT_VERTEX(m_vFrustum[0], D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.2f), D3DXVECTOR2(0.0f, 1.0f));
	//하
	m_FrustumBox.m_VertexList[20] = PNCT_VERTEX(m_vFrustum[3], D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.2f), D3DXVECTOR2(0.0f, 0.0f));
	m_FrustumBox.m_VertexList[21] = PNCT_VERTEX(m_vFrustum[2], D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.2f), D3DXVECTOR2(1.0f, 0.0f));
	m_FrustumBox.m_VertexList[22] = PNCT_VERTEX(m_vFrustum[6], D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.2f), D3DXVECTOR2(1.0f, 1.0f));
	m_FrustumBox.m_VertexList[23] = PNCT_VERTEX(m_vFrustum[7], D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.2f), D3DXVECTOR2(0.0f, 1.0f));

	pContext->UpdateSubresource(m_FrustumBox.m_DxHelper.m_pVertexBuffer.Get(), 0, NULL, &m_FrustumBox.m_VertexList.at(0), 0, 0);

	m_FrustumBox.m_DxHelper.PreRender(pContext, iSize);

	return true;
}
bool	Frusturm::Render(ID3D11DeviceContext* pContext)
{
	pContext->UpdateSubresource(m_FrustumBox.m_DxHelper.m_pConstantBuffer.Get(), 0, NULL, &m_FrustumBox.m_ConstBuffer, 0, 0);
	PreRender(pContext, m_FrustumBox.m_DxHelper.m_iVertexSize);

	PostRender(pContext);
	return true;
}
bool	Frusturm::PostRender(ID3D11DeviceContext* pContext)
{
	m_FrustumBox.m_DxHelper.PostRender(pContext, m_FrustumBox.m_DxHelper.m_iNumIndex);
	return true;
}
void	Frusturm::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	m_FrustumBox.SetMatrix(pWorld, pView, pProj);
}
CMPPOSITION		Frusturm::CheckPosition(KJHBOX& Box)
{
	CMPPOSITION pos = P_FRONT;

	float fDistance = 0;
	float fCentertoPlane = 0;
	D3DXVECTOR3 vLength;
	D3DXVECTOR3 vPlaneNormal;
	//0근1원2우3좌4상5하
	for (int iPlane = 0; iPlane < 6; iPlane++)

	{
		fCentertoPlane =	m_FrustumPlane[iPlane].fA * Box.vCenter.x +
							m_FrustumPlane[iPlane].fB * Box.vCenter.y +
							m_FrustumPlane[iPlane].fC * Box.vCenter.z +
							m_FrustumPlane[iPlane].fD;

		vPlaneNormal = D3DXVECTOR3(m_FrustumPlane[iPlane].fA, m_FrustumPlane[iPlane].fB, m_FrustumPlane[iPlane].fC);

		vLength = Box.vAxis[0] * Box.fExtent[0];
		fDistance = fabs(D3DXVec3Dot(&vPlaneNormal, &vLength));

		vLength = Box.vAxis[1] * Box.fExtent[1];
		fDistance += fabs(D3DXVec3Dot(&vPlaneNormal, &vLength));

		vLength = Box.vAxis[2] * Box.fExtent[2];
		fDistance += fabs(D3DXVec3Dot(&vPlaneNormal, &vLength));

		if (fCentertoPlane <= fDistance)
		{
			pos = P_SPANNING;
		}
		if (fCentertoPlane < -fDistance)
		{
			pos = P_BACK;
			return pos;
		}
	}

	return pos;
}
bool	Frusturm::CheckCollision(KJHBOX& Box)
{
	float fDistance = 0;
	float fCentertoPlane = 0;
	D3DXVECTOR3 vLength;
	D3DXVECTOR3 vPlaneNormal;
	for (int iPlane = 0; iPlane < 6; iPlane++)
	{
		fCentertoPlane = m_FrustumPlane[iPlane].fA * Box.vCenter.x +
			m_FrustumPlane[iPlane].fB * Box.vCenter.y +
			m_FrustumPlane[iPlane].fC * Box.vCenter.z +
			m_FrustumPlane[iPlane].fD;

		vPlaneNormal = D3DXVECTOR3(m_FrustumPlane[iPlane].fA, m_FrustumPlane[iPlane].fB, m_FrustumPlane[iPlane].fC);

		vLength = Box.vAxis[0] * Box.fExtent[0];
		fDistance = fabs(D3DXVec3Dot(&vLength, &vPlaneNormal));

		vLength = Box.vAxis[1] * Box.fExtent[1];
		fDistance += fabs(D3DXVec3Dot(&vLength, &vPlaneNormal));

		vLength = Box.vAxis[2] * Box.fExtent[2];
		fDistance += fabs(D3DXVec3Dot(&vLength, &vPlaneNormal));

		if (fCentertoPlane <= -fDistance)
		{
			return false;
		}
	}
	return true;
}
Frusturm::Frusturm()
{
}


Frusturm::~Frusturm()
{
}
