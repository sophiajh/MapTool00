#pragma once
#include "Camera.h"
#include "Model.h"
#include <queue>
#include "Field.h"
#include "TextureManager.h"
class FieldNode
{
public:
	vector<FieldNode*>	m_ChildList;
	KJHBOX			m_BBox;
	BOOL			m_bIsLeaf;
	UINT			m_iDepth;
	vector<KJHBOX*> m_ObjectList;
	vector<int>		m_CornerIndex;
	vector<int>		m_IndexData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_IndexBuffer;
	//
	vector<PNCT_VERTEX>	m_VertexData;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;

	int	m_iTexture = 0;
	BoxObject	m_Bound;
public:
	FieldNode() :m_iTexture(-1) {};
	virtual ~FieldNode() {};
};


class QuadTree
{
public:
	FieldNode*			m_pRootNode;
	int					m_iMaxDepth;
	float				m_fMinSize;
	int					m_iWidth;
	int					m_iHeight;
	vector<FieldNode*>	m_RenderNodeList;
	vector<KJHBOX*>		m_RenderObjList;
	Camera*				m_pCamera;
	FieldHeight*		m_pField;
	std::vector<int>	m_SharedIndex;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_SharedIndexBuffer;
	std::queue<FieldNode*>  m_QueueList;
public:
	bool		BuildQuadField(float fWidth, float fHeight, int iMaxDepth = 5, float fMinSize = 10.0f);
	//
	bool		BuildQuadField(FieldHeight* FieldData, int iMaxDepth = 5, float fMinSize = 10.0f);
	FieldNode*	CreateFieldIndexNode(FieldNode* pParent, int iTopLeft, int iTopRight, int iBottomLeft, int iBottomRight);
	void		ComputeBoundBox(FieldNode* pNode);
	D3DXVECTOR2	GetNodeHeight(int iTopLeft, int iTopRight, int iBottomLeft, int iBottomRight);
	bool		BuildIndexTree(FieldNode* pNode);
	bool		SetIndexChildQuad(FieldNode* pNode);
	bool		CreateIndexBuffer(FieldNode* pNode);
	bool		Render(ID3D11DeviceContext* pContext);
	//
	FieldNode*	CreateFieldNode(FieldNode* pParent, float fMinX, float fMaxX, float fMinZ, float fMaxZ);
	bool		BuildTree(FieldNode* pNode);
	bool		SetChildQuad(FieldNode* pNode);

	void		SetObject(KJHBOX* pObj);
	bool		CheckRect(FieldNode* pNode, KJHBOX* pObj);
	FieldNode*	FindNode(FieldNode* pNode, KJHBOX* pObj);

	void		Update(Camera* pCamera);
	void		SearchRenderNode(FieldNode* pNode); //º´¸ñ
	void		SearchRenderObj(FieldNode* pNode);

	void		CreateSharedIndex();

	bool		Frame();
	bool		Render();
	bool		Release();
public:
	QuadTree();
	virtual ~QuadTree();
};