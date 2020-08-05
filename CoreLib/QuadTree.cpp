#include "QuadTree.h"

void	QuadTree::SetObject(KJHBOX* pObj)
{
	if (CheckRect(m_pRootNode, pObj))
	{
		FieldNode* Fnode = FindNode(m_pRootNode, pObj);
		if (Fnode)
		{
			Fnode->m_ObjectList.push_back(pObj);
		}
	}
}
FieldNode*	QuadTree::FindNode(FieldNode* pNode, KJHBOX* pObj)
{
	do {
		for (int iNode = 0;
			iNode < pNode->m_ChildList.size(); iNode++)
		{
			if (CheckRect(pNode->m_ChildList[iNode], pObj))
			{
				m_QueueList.push(pNode->m_ChildList[iNode]);
			}
		}
		if (m_QueueList.empty()) break;

		pNode = m_QueueList.front();
		m_QueueList.pop();

	} while (pNode);
	return pNode;

	//for (auto ChildNode : pNode->m_ChildList)
	//{
	//	if (CheckRect(ChildNode, pObj))
	//	{
	//		if (ChildNode->m_ChildList.size())
	//		{
	//			FindNode(ChildNode, pObj);
	//		}
	//	}
	//	return pNode;
	//}
	//return pNode;
}
bool	QuadTree::CheckRect(FieldNode* pNode, KJHBOX* pObj)
{
	if (pNode->m_BBox.vMin.x <= pObj->vCenter.x && pNode->m_BBox.vMax.x >= pObj->vCenter.x)
	{
		if (pNode->m_BBox.vMin.z <= pObj->vCenter.z && pNode->m_BBox.vMax.z >= pObj->vCenter.z)
		{
			if (pNode->m_BBox.vMin.y <= pObj->vCenter.y && pNode->m_BBox.vMax.y >= pObj->vCenter.y)
			{
				return true;
			}
		}
	}
	return false;
}
bool	QuadTree::BuildQuadField(float fWidth, float fHeight, int iMaxDepth, float fMinSize)
{
	m_iMaxDepth = iMaxDepth;
	m_fMinSize = fMinSize;

	m_pRootNode = CreateFieldNode(nullptr, -fWidth / 2, fWidth / 2, -fHeight / 2, fHeight / 2);
	return BuildTree(m_pRootNode);
}
bool	QuadTree::BuildQuadField(FieldHeight* FieldData, int iMaxDepth, float fMinSize)
{
	m_iWidth = FieldData->m_iNumCols;
	m_iHeight = FieldData->m_iNumRows;
	m_iMaxDepth = iMaxDepth;
	m_fMinSize = fMinSize;
	m_pField = FieldData;

	m_pRootNode = CreateFieldIndexNode(nullptr, 0, m_iWidth - 1, m_iWidth * (m_iHeight - 1), m_iWidth * m_iHeight - 1);
	return BuildIndexTree(m_pRootNode);
}
FieldNode*	QuadTree::CreateFieldIndexNode(FieldNode* pParent, int iTopLeft, int iTopRight, int iBottomLeft, int iBottomRight)
{
	FieldNode* pNode = new FieldNode;

	pNode->m_ChildList.reserve(4);
	pNode->m_CornerIndex.push_back(iTopLeft);
	pNode->m_CornerIndex.push_back(iTopRight);
	pNode->m_CornerIndex.push_back(iBottomLeft);
	pNode->m_CornerIndex.push_back(iBottomRight);

	ComputeBoundBox(pNode);

	pNode->m_iDepth = 0;
	if (pParent != nullptr)
	{
		pNode->m_iDepth = pParent->m_iDepth + 1;
	}

	return pNode;
}
void	QuadTree::ComputeBoundBox(FieldNode* pNode)
{
	D3DXVECTOR2 HeightMinMax = GetNodeHeight(pNode->m_CornerIndex[0], pNode->m_CornerIndex[1],
		pNode->m_CornerIndex[2], pNode->m_CornerIndex[3]);

	D3DXVECTOR3 v_Max = m_pField->m_VertexList[pNode->m_CornerIndex[1]].Position;
	D3DXVECTOR3 v_Min = m_pField->m_VertexList[pNode->m_CornerIndex[2]].Position;

	pNode->m_BBox.vMax.x = v_Max.x;
	pNode->m_BBox.vMax.y = HeightMinMax.y;
	pNode->m_BBox.vMax.z = v_Max.z;
	pNode->m_BBox.vMin.x = v_Min.x;
	pNode->m_BBox.vMin.y = HeightMinMax.x;
	pNode->m_BBox.vMin.z = v_Min.z;
	pNode->m_BBox.vCenter = (pNode->m_BBox.vMax + pNode->m_BBox.vMin) / 2;
	pNode->m_BBox.vAxis[0] = D3DXVECTOR3(1, 0, 0);
	pNode->m_BBox.vAxis[1] = D3DXVECTOR3(0, 1, 0);
	pNode->m_BBox.vAxis[2] = D3DXVECTOR3(0, 0, 1);
	pNode->m_BBox.fExtent[0] = (pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
	pNode->m_BBox.fExtent[1] = (pNode->m_BBox.vMax.y - pNode->m_BBox.vMin.y) / 2;
	pNode->m_BBox.fExtent[2] = (pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;

	//pNode->m_Bound.Create(g_pDevice, L"../CoreLib/HLSL.vsh", L"../CoreLib/HLSL.psh", nullptr, "VS_Line", "PS_Line");

}
D3DXVECTOR2	QuadTree::GetNodeHeight(int iTopLeft, int iTopRight, int iBottomLeft, int iBottomRight)
{
	int iStartRow = iTopLeft / m_iWidth;
	int iEndRow = iBottomLeft / m_iWidth;
	int iStartCol = iTopLeft % m_iWidth;
	int iEndCol = iTopRight % m_iWidth;

	float fMinHeight = 9999.0f, fMaxHeight = -9999.9f;

	for (int iRow = iStartRow; iRow < iEndRow; iRow++)
	{
		for (int iCol = iStartCol; iCol < iEndCol; iCol++)
		{
			int iIndex = iRow * m_iWidth + iCol;
			if (m_pField->m_VertexList[iIndex].Position.y < fMinHeight)
			{
				fMinHeight = m_pField->m_VertexList[iIndex].Position.y;
			}
			if (m_pField->m_VertexList[iIndex].Position.y > fMaxHeight)
			{
				fMaxHeight = m_pField->m_VertexList[iIndex].Position.y;
			}
		}
	}
	return D3DXVECTOR2(fMinHeight, fMaxHeight);
}
FieldNode*	QuadTree::CreateFieldNode(FieldNode* pParent, float fMinX, float fMaxX, float fMinZ, float fMaxZ)
{
	FieldNode* pNode = new FieldNode;
	pNode->m_ChildList.reserve(4);

	pNode->m_BBox.vMax.x = fMaxX;	pNode->m_BBox.vMax.y = 0.0f;	pNode->m_BBox.vMax.z = fMaxZ;
	pNode->m_BBox.vMin.x = fMinX;	pNode->m_BBox.vMin.y = 0.0f;	pNode->m_BBox.vMin.z = fMinZ;
	pNode->m_BBox.vCenter = (pNode->m_BBox.vMax + pNode->m_BBox.vMin) / 2;
	pNode->m_BBox.vAxis[0] = D3DXVECTOR3(1, 0, 0);
	pNode->m_BBox.vAxis[1] = D3DXVECTOR3(0, 1, 0);
	pNode->m_BBox.vAxis[2] = D3DXVECTOR3(0, 0, 1);
	pNode->m_BBox.fExtent[0] = (pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
	pNode->m_BBox.fExtent[1] = (pNode->m_BBox.vMax.y - pNode->m_BBox.vMin.y) / 2;
	pNode->m_BBox.fExtent[2] = (pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;

	pNode->m_iDepth = 0;
	if (pParent != nullptr)
	{
		pNode->m_iDepth = pParent->m_iDepth + 1;
	}
	return pNode;
}

bool	QuadTree::BuildTree(FieldNode* pNode)
{
	if (SetChildQuad(pNode))
	{
		for (int iChild = 0; iChild < 4; iChild++)
		{
			BuildTree(pNode->m_ChildList[iChild]);
		}
	}
	return true;
}
bool	QuadTree::BuildIndexTree(FieldNode* pNode)
{
	if (SetIndexChildQuad(pNode))
	{
		for (int iChild = 0; iChild < 4; iChild++)
		{
			BuildIndexTree(pNode->m_ChildList[iChild]);
		}
	}
	return true;
}
bool	QuadTree::SetIndexChildQuad(FieldNode* pNode)
{
	if (m_iMaxDepth <= pNode->m_iDepth)
	{
		pNode->m_bIsLeaf = true;
		CreateIndexBuffer(pNode);
		return false;
	}
	float fWidth = (pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
	float fHeight = (pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;
	if (m_fMinSize >= fWidth || m_fMinSize >= fHeight)
	{
		pNode->m_bIsLeaf = true;
		CreateIndexBuffer(pNode);
		return false;
	}

	int iCenterIdx = (pNode->m_CornerIndex[0] + pNode->m_CornerIndex[3]) / 2;
	int iMidIndx[4];
	//		0
	//	3		1
	//		2
	iMidIndx[0] = (pNode->m_CornerIndex[0] + pNode->m_CornerIndex[1]) / 2;
	iMidIndx[1] = (pNode->m_CornerIndex[1] + pNode->m_CornerIndex[3]) / 2;
	iMidIndx[2] = (pNode->m_CornerIndex[2] + pNode->m_CornerIndex[3]) / 2;
	iMidIndx[3] = (pNode->m_CornerIndex[0] + pNode->m_CornerIndex[2]) / 2;

	//좌상
	FieldNode* ChildNode = CreateFieldIndexNode(pNode, pNode->m_CornerIndex[0], iMidIndx[0], iMidIndx[3], iCenterIdx);
	pNode->m_ChildList.push_back(ChildNode);
	//우상
	ChildNode = CreateFieldIndexNode(pNode, iMidIndx[0], pNode->m_CornerIndex[1], iCenterIdx, iMidIndx[1]);
	pNode->m_ChildList.push_back(ChildNode);
	//좌하
	ChildNode = CreateFieldIndexNode(pNode, iMidIndx[3], iCenterIdx, pNode->m_CornerIndex[2], iMidIndx[2]);
	pNode->m_ChildList.push_back(ChildNode);
	//우하
	ChildNode = CreateFieldIndexNode(pNode, iCenterIdx, iMidIndx[1], iMidIndx[2], pNode->m_CornerIndex[3]);
	pNode->m_ChildList.push_back(ChildNode);
	return true;
}
bool	QuadTree::CreateIndexBuffer(FieldNode* pNode)
{
	int iStartRow = pNode->m_CornerIndex[0] / m_iWidth;
	int iEndRow = pNode->m_CornerIndex[2] / m_iWidth;
	int iStartCol = pNode->m_CornerIndex[0] % m_iWidth;
	int iEndCol = pNode->m_CornerIndex[1] % m_iWidth;

	pNode->m_IndexData.resize((iEndRow - iStartRow) * (iEndCol - iStartCol) * 2 * 3);

	int index = 0;
	for (int iRow = iStartRow; iRow < iEndRow; iRow++)
	{
		for (int iCol = iStartCol; iCol < iEndCol; iCol++)
		{
			pNode->m_IndexData[index + 0] = iRow * m_iWidth + iCol;
			pNode->m_IndexData[index + 1] = iRow * m_iWidth + iCol + 1;
			pNode->m_IndexData[index + 2] = (iRow + 1) * m_iWidth + iCol;

			pNode->m_IndexData[index + 3] = pNode->m_IndexData[index + 2];
			pNode->m_IndexData[index + 4] = pNode->m_IndexData[index + 1];
			pNode->m_IndexData[index + 5] = (iRow + 1) * m_iWidth + (iCol + 1);

			index += 6;
		}
	}

	pNode->m_IndexBuffer.Attach(DX::CreateIndexBuffer(m_pField->m_pDevice,
		&pNode->m_IndexData.at(0), pNode->m_IndexData.size(), sizeof(int)));

	return true;
}
bool	QuadTree::Render(ID3D11DeviceContext* pContext)
{
	pContext->UpdateSubresource(m_pField->m_DxHelper.m_pVertexBuffer.Get(), 0, NULL, &m_pField->m_VertexList.at(0), 0, 0);
	pContext->UpdateSubresource(m_pField->m_DxHelper.m_pConstantBuffer.Get(), 0, NULL, &m_pField->m_ConstBuffer, 0, 0);

	m_pField->PreRender(pContext);
	//pContext->PSSetShaderResources(0, 1, m_pField->m_pPattern.GetAddressOf());

	//	ps에 스플래팅 텍스쳐SRV 세팅
	pContext->PSSetShaderResources(2, 1, &m_pField->m_pSplattingPatternList[0]); //물
	pContext->PSSetShaderResources(3, 1, &m_pField->m_pSplattingPatternList[1]); //모래
	pContext->PSSetShaderResources(4, 1, &m_pField->m_pSplattingPatternList[2]); //나무

	//	필드 상수버퍼 (클릭 위치 / 반지름 길이) 세팅.
	pContext->UpdateSubresource(m_pField->m_pFieldCstBuffer.Get(), 0, NULL, &m_pField->m_FieldCstData, 0, 0);
	pContext->VSSetConstantBuffers(2, 1, m_pField->m_pFieldCstBuffer.GetAddressOf());
	pContext->PSSetConstantBuffers(2, 1, m_pField->m_pFieldCstBuffer.GetAddressOf());

	// 알파 텍스처 렌더 타겟을 PS에 세팅.
	pContext->PSSetShaderResources(1, 1, m_pField->m_FieldRT.m_pSRView.GetAddressOf());
	
	// 프러스텀 컬링으로 정해진 렌더대상 노드들만 렌더.
	for (int iNode = 0; iNode < m_RenderNodeList.size(); iNode++)
	{
		FieldNode* pNode = m_RenderNodeList[iNode];
		//if (pNode->m_iTexture != -1)
		//{
		//	pContext->PSSetShaderResources(0, 1, &m_pField->m_pSplattingPatternList[pNode->m_iTexture]);
		//}
		//else
		//{
		//	pContext->PSSetShaderResources(0, 1, m_pField->m_pPattern.GetAddressOf());
		//
		//}
		UINT stride = sizeof(PNCT_VERTEX);
		UINT offset = 0;
		pContext->IASetIndexBuffer(pNode->m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		pContext->DrawIndexed(pNode->m_IndexData.size(), 0, 0);
	}
	return true;
}
bool	QuadTree::SetChildQuad(FieldNode* pNode)
{
	if (m_iMaxDepth <= pNode->m_iDepth)
	{
		pNode->m_bIsLeaf = true;
		return false;
	}
	float fWidth = (pNode->m_BBox.vMax.x - pNode->m_BBox.vMin.x) / 2;
	float fHeight = (pNode->m_BBox.vMax.z - pNode->m_BBox.vMin.z) / 2;
	if (m_fMinSize >= fWidth || m_fMinSize >= fHeight)
	{
		pNode->m_bIsLeaf = true;
		return false;
	}
	//좌상
	FieldNode* ChildNode = CreateFieldNode(pNode, pNode->m_BBox.vMin.x, pNode->m_BBox.vMin.x + fWidth,
		pNode->m_BBox.vMin.z + fHeight, pNode->m_BBox.vMax.z);
	pNode->m_ChildList.push_back(ChildNode);

	//우상
	ChildNode = CreateFieldNode(pNode, pNode->m_BBox.vMin.x + fWidth, pNode->m_BBox.vMax.x,
		pNode->m_BBox.vMin.z + fHeight, pNode->m_BBox.vMax.z);
	pNode->m_ChildList.push_back(ChildNode);

	//좌하
	ChildNode = CreateFieldNode(pNode, pNode->m_BBox.vMin.x, pNode->m_BBox.vMin.x + fWidth,
		pNode->m_BBox.vMin.z, pNode->m_BBox.vMin.z + fHeight);
	pNode->m_ChildList.push_back(ChildNode);

	//우하
	ChildNode = CreateFieldNode(pNode, pNode->m_BBox.vMin.x + fWidth, pNode->m_BBox.vMax.x,
		pNode->m_BBox.vMin.z, pNode->m_BBox.vMin.z + fHeight);
	pNode->m_ChildList.push_back(ChildNode);

	return true;
}
void	QuadTree::Update(Camera* pCamera)
{
	m_pCamera = pCamera;
}
void	QuadTree::SearchRenderNode(FieldNode* pNode)
{
	CMPPOSITION Pos = m_pCamera->m_Frustum.CheckPosition(pNode->m_BBox);

	//if (Pos == P_FRONT)
	//{
	//	m_RenderNodeList.push_back(pNode);
	//	return;
	//}

	if (pNode->m_bIsLeaf && Pos != P_BACK)
	{
		m_RenderNodeList.push_back(pNode);
	}
	if (pNode->m_bIsLeaf && Pos == P_FRONT)
	{
		for (auto Obj : pNode->m_ObjectList)
		{
			m_RenderObjList.push_back(Obj);
		}
	}
	if (pNode->m_bIsLeaf && Pos == P_SPANNING)
	{
		SearchRenderObj(pNode);
	}

	if (pNode->m_ChildList.size() != 0)
	{
		for (int iChild = 0; iChild < 4; iChild++)
		{
			SearchRenderNode(pNode->m_ChildList[iChild]);
		}
	}
}
void	QuadTree::SearchRenderObj(FieldNode* pNode)
{
	for (auto Obj : pNode->m_ObjectList)
	{
		CMPPOSITION Pos = m_pCamera->m_Frustum.CheckPosition(*Obj);
		if (Pos != P_BACK)
		{
			m_RenderObjList.push_back(Obj);
		}
	}
}
void QuadTree::CreateSharedIndex()
{
	DWORD dwStartRow = 0;
	DWORD dwEndRow = m_pField->m_iNumRows - 1;
	DWORD dwStartCol = 0;
	DWORD dwEndCol = m_pField->m_iNumCols - 1;
	DWORD delRow = dwEndRow - dwStartRow + 1;
	DWORD delCol = dwEndCol - dwStartCol + 1;

	int num = (dwEndRow)*(dwEndCol) * 2 * 3;

	m_SharedIndex.resize(num);
	
	int iIndex = 0;
	for (DWORD iRow = dwStartRow; iRow < dwEndRow; iRow++)
	{
		for (DWORD iCol = dwStartCol; iCol < dwEndCol; iCol++)
		{
			DWORD dwIndex = iRow * delCol + iCol;
			int iNextRow = iRow + 1;
			int iNextCol = iCol + 1;
			m_SharedIndex[iIndex + 0] = iRow * delCol + iCol;
			m_SharedIndex[iIndex + 1] = iRow * delCol + iNextCol;
			m_SharedIndex[iIndex + 2] = iNextRow * delCol + iCol;

			m_SharedIndex[iIndex + 3] = m_SharedIndex[iIndex + 2];
			m_SharedIndex[iIndex + 4] = m_SharedIndex[iIndex + 1];
			m_SharedIndex[iIndex + 5] = iNextRow * delCol + iNextCol;
			iIndex += 6;
		}
	}
	
	m_SharedIndexBuffer.Attach( DX::CreateIndexBuffer(m_pField->m_pDevice, &m_SharedIndex.at(0), m_SharedIndex.size(), sizeof(DWORD)));
}
bool QuadTree::Frame()
{
	m_RenderNodeList.clear();

	SearchRenderNode(m_pRootNode);
	return true;
}
bool QuadTree::Render()
{
	return true;
}
bool QuadTree::Release()
{
	delete m_pRootNode;
	return true;
}

QuadTree::QuadTree()
{
}


QuadTree::~QuadTree()
{
}
