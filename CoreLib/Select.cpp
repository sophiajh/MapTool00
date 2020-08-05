#include "Select.h"

void	Select::SetMatrix(D3DXMATRIX* MatWorld, D3DXMATRIX& MatView, D3DXMATRIX& MatProj)
{
	if (MatWorld != nullptr)
	{
		m_MatWorld = *MatWorld;
	}
	if (MatView != nullptr)
	{
		m_MatView = MatView;
	}
	if (MatProj != nullptr)
	{
		m_MatProj = MatProj;
	}

	return UpdateRay();
}

void	Select::UpdateRay()
{
	POINT ptCursor;

	GetCursorPos(&ptCursor); //POINT 에서 LPPOINT로 변환 -> 참조
	ScreenToClient(g_hWnd, &ptCursor);

	//화면좌표를 투영으로 변환.
	D3DXVECTOR3	vLocate;
	vLocate.x = (ptCursor.x * 2.0f / g_rtClient.right) - 1;
	vLocate.y = -((ptCursor.y * 2.0f / g_rtClient.bottom) - 1);
	vLocate.z = 1.0f;

	//투영좌표를 뷰좌표로 변환.
	vLocate.x = vLocate.x / m_MatProj._11;
	vLocate.y = vLocate.y / m_MatProj._22;

	//뷰좌표 local로 변환.
	D3DXMATRIX MatInvView = m_MatWorld * m_MatView;
	D3DXMatrixInverse(&MatInvView, NULL, &MatInvView);

	m_Ray.Origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ray.Direction = D3DXVECTOR3(vLocate.x, vLocate.y, vLocate.z);

	D3DXVec3TransformCoord(&m_Ray.Origin, &m_Ray.Origin, &MatInvView);
	D3DXVec3TransformNormal(&m_Ray.Direction, &m_Ray.Direction, &MatInvView);
	D3DXVec3Normalize(&m_Ray.Direction, &m_Ray.Direction);
}

bool	Select::IntersectTriangle(D3DXVECTOR3 RayOrigin, D3DXVECTOR3 RayDir, D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, float* u, float* v, float* t)
{
	D3DXVECTOR3 Edge1 = v1 - v0;
	D3DXVECTOR3 Edge2 = v2 - v0;

	D3DXVECTOR3	pvec, tvec, qvec;

	D3DXVec3Cross(&pvec, &RayDir, &Edge2);
	float det = D3DXVec3Dot(&pvec, &Edge1);
	// det > 0 : 일반적인 평면
	// det = 0 : 평면과 ray가 수평인 상황->만날일 없음
	// det < 0 : 뒤집힌 상태
	if (det > 0)
	{
		tvec = RayOrigin - v0;
	}
	else
	{
		tvec = v0 - RayOrigin;
		det = -det;
	}
	if (det < 0.00001f) return false;

	*u = D3DXVec3Dot(&tvec, &pvec);
	if (*u < 0.0f || *u > det) return false;

	D3DXVec3Cross(&qvec, &tvec, &Edge1);
	*v = D3DXVec3Dot(&RayDir, &qvec);
	if (*v < 0.0f || *v > det) return false;

	*t = D3DXVec3Dot(&Edge2, &qvec);
	float fInvDet = 1.0f / det;
	*t *= fInvDet;
	*u *= fInvDet;
	*v *= fInvDet;
	return true;
}
bool	Select::CheckPick(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	float t, u, v;
	if (IntersectTriangle(m_Ray.Origin, m_Ray.Direction, v0, v1, v2, &u, &v, &t))
	{
		m_Intersection = m_Ray.Origin + m_Ray.Direction * t;
		return true;
	}
	return false;
}

bool	Select::CheckPick(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2, float* flenght)
{
	float u, v;
	if (IntersectTriangle(m_Ray.Origin, m_Ray.Direction, v0, v1, v2, &u, &v, flenght))
	{
		m_Intersection = m_Ray.Origin + m_Ray.Direction * *flenght;
		return true;
	}
	return false;
}

bool	Select::SetSelect(FieldHeight& FieldData, Camera& UserCam)
{
	m_DestField = &FieldData;
	m_UserCamera = &UserCam;
	return true;
}

bool	Select::SetSelect(FieldHeight& FieldData, Camera& UserCam, QuadTree& QuadData)
{
	m_DestField = &FieldData;
	m_UserCamera = &UserCam;
	m_PartitionedField = &QuadData;
	return true;
}

bool Select::Init()
{
	return true;
}

bool Select::Frame()
{
	if (g_ActionInput.bLeftClick == KEY_HOLD)
	{
		SetMatrix(nullptr, m_UserCamera->m_MatView, m_UserCamera->m_matProj);

		//QuadTree::m_RenderNodeList
		CollTestQuadTree();

		//전체 Face대상 충돌 테스트.
		//CollTestEveryFace();
	}
	return true;
}
bool Select::Render(ID3D11DeviceContext* pContext)
{
	return true;
}
bool Select::Release()
{
	return true;
}
void	Select::CollTestQuadTree()
{
	int iNode = -1;
	int iIndex = -1;
	float fLength = 9999.9f;
	for (int i = 0; i < m_PartitionedField->m_RenderNodeList.size(); i++)
	{

		if (Collision::RayToAABB(&m_Ray, &m_PartitionedField->m_RenderNodeList[i]->m_BBox))
		{
			for (int j = 0; j < m_PartitionedField->m_RenderNodeList[i]->m_IndexData.size();)
			{
				D3DXVECTOR3 v0, v1, v2;
				v0 = m_DestField->m_VertexList[m_PartitionedField->m_RenderNodeList[i]->m_IndexData[j]].Position;
				v1 = m_DestField->m_VertexList[m_PartitionedField->m_RenderNodeList[i]->m_IndexData[j + 1]].Position;
				v2 = m_DestField->m_VertexList[m_PartitionedField->m_RenderNodeList[i]->m_IndexData[j + 2]].Position;

				float fMin = 0.0f;

				if (CheckPick(v0, v1, v2, &fMin))
				{
					//카메라에 더 가까운 대상 찾기.
					if (fMin < fLength)
					{
						m_PreIntersection = m_Intersection;
						fLength = fMin;
						iNode = i;
						iIndex = j;
					}
				}
				j += 3;
			}
		}
	}

	if (iNode >= 0)
	{
		//작업 수행
		switch (m_CurrFunc)
		{
		case (SelectFunc::FUNC_CHANGETEXTURE):
		{
			//m_PartitionedField->m_pField->Splatting(m_PreIntersection, m_iCurrentTexture);
			m_PartitionedField->m_pField->RTSplatting(m_PreIntersection, m_iCurrentTexture);
		}break;
		case (SelectFunc::FUNC_CHANGEHEIGHT):
		{
			float fUserSetHeight = m_fStrength * g_fSecondPerFrame;

			for (int iverNum = 0; iverNum < m_DestField->m_VertexList.size(); iverNum++)
			{
				float fRadian = 10.0f;
				float fLen = D3DXVec3Length(&D3DXVECTOR3(m_DestField->m_VertexList[iverNum].Position - m_PreIntersection));
				if (fLen < fRadian)
				{
					float ftemp;
					if (fLen <= fRadian / 2.0f)
					{ 
						ftemp = fUserSetHeight;
					}
					else
					{
						
						ftemp = fUserSetHeight / fLen;
					}
					m_DestField->m_VertexList[iverNum].Position.y += ftemp;
					m_DestField->CalculateRelatedFace(iverNum);
					//D3DXVECTOR3 FaceU, FaceV, NewFaceNormal[6];
					//int iColNum = m_DestField->m_iNumCols;
					//
					//int itemp = iverNum;
					//FaceU = m_DestField->m_VertexList[itemp - iColNum].Position - m_DestField->m_VertexList[itemp - 1].Position;
					//FaceV = m_DestField->m_VertexList[itemp].Position - m_DestField->m_VertexList[itemp - 1].Position;
					//D3DXVec3Cross(&NewFaceNormal[0], &FaceU, &FaceV); //업데이트 된 vertex를 포함하는 Face의 새 노말값.
					//
					//FaceU = m_DestField->m_VertexList[itemp - iColNum].Position - m_DestField->m_VertexList[itemp].Position;
					//FaceV = m_DestField->m_VertexList[itemp - iColNum + 1].Position - m_DestField->m_VertexList[itemp].Position;
					//D3DXVec3Cross(&NewFaceNormal[1], &FaceU, &FaceV); //업데이트 된 vertex를 포함하는 Face의 새 노말값.
					//
					//FaceU = m_DestField->m_VertexList[itemp - iColNum + 1].Position - m_DestField->m_VertexList[itemp].Position;
					//FaceV = m_DestField->m_VertexList[itemp + 1].Position - m_DestField->m_VertexList[itemp].Position;
					//D3DXVec3Cross(&NewFaceNormal[2], &FaceU, &FaceV); //업데이트 된 vertex를 포함하는 Face의 새 노말값.
					//
					//FaceU = m_DestField->m_VertexList[itemp + 1].Position - m_DestField->m_VertexList[itemp].Position;
					//FaceV = m_DestField->m_VertexList[itemp + iColNum].Position - m_DestField->m_VertexList[itemp].Position;
					//D3DXVec3Cross(&NewFaceNormal[3], &FaceU, &FaceV); //업데이트 된 vertex를 포함하는 Face의 새 노말값.
					//
					//FaceU = m_DestField->m_VertexList[itemp + iColNum].Position - m_DestField->m_VertexList[itemp].Position;
					//FaceV = m_DestField->m_VertexList[itemp + iColNum - 1].Position - m_DestField->m_VertexList[itemp].Position;
					//D3DXVec3Cross(&NewFaceNormal[4], &FaceU, &FaceV); //업데이트 된 vertex를 포함하는 Face의 새 노말값.
					//
					//FaceU = m_DestField->m_VertexList[itemp + iColNum - 1].Position - m_DestField->m_VertexList[itemp].Position;
					//FaceV = m_DestField->m_VertexList[itemp - 1].Position - m_DestField->m_VertexList[itemp].Position;
					//D3DXVec3Cross(&NewFaceNormal[5], &FaceU, &FaceV); //업데이트 된 vertex를 포함하는 Face의 새 노말값.
					//
					//D3DXVECTOR3 vUpdateNormal(0.0f, 0.0f, 0.0f);
					//for (auto vNormal : NewFaceNormal)
					//{
					//	D3DXVec3Normalize(&vNormal, &vNormal);
					//	vUpdateNormal += vNormal;
					//}
					//D3DXVec3Normalize(&vUpdateNormal, &vUpdateNormal);
					//m_DestField->m_VertexList[itemp].Normal = vUpdateNormal;
					if (m_PartitionedField->m_RenderNodeList[iNode]->m_BBox.fExtent[1] < m_DestField->m_VertexList[iverNum].Position.y)
					{
						m_PartitionedField->m_RenderNodeList[iNode]->m_BBox.fExtent[1] += ftemp;
						m_PartitionedField->m_RenderNodeList[iNode]->m_BBox.vMax.y += ftemp;
					}
					//m_PartitionedField->m_RenderNodeList[iNode]->m_BBox.fExtent[1] += fUserSetHeight;
					//m_PartitionedField->m_RenderNodeList[iNode]->m_BBox.vMax.y += fUserSetHeight;
				}				
			}
		}break;
		}
		m_PreIntersection = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

}

void Select::CollTestEveryFace()
{
	//전체 Face를 대상으로 수행됨.
	for (int Tri = 0; Tri < m_DestField->m_IndexList.size(); Tri += 3)
	{
		int i0, i1, i2;
		i0 = m_DestField->m_IndexList[Tri];
		i1 = m_DestField->m_IndexList[Tri + 1];
		i2 = m_DestField->m_IndexList[Tri + 2];

		D3DXVECTOR3 v0, v1, v2;
		v0 = m_DestField->m_VertexList[i0].Position;
		v1 = m_DestField->m_VertexList[i1].Position;
		v2 = m_DestField->m_VertexList[i2].Position;

		if (CheckPick(v0, v1, v2))
		{
			m_DestField->m_VertexList[i0].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
			m_DestField->m_VertexList[i1].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
			m_DestField->m_VertexList[i2].Color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}
}

Select::Select() : m_iCurrentTexture(0), m_CurrFunc(SelectFunc::FUNC_NONE)
{
	D3DXMatrixIdentity(&m_MatClick);
	D3DXMatrixIdentity(&m_MatWorld);
	D3DXMatrixIdentity(&m_MatView);
	D3DXMatrixIdentity(&m_MatProj);
}


Select::~Select()
{
}
