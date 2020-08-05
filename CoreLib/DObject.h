#pragma once
#include "Object.h"

class PlaneObject :public Model
{
public:
	int			m_iNumVertex;
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();

public:
	PlaneObject();
	~PlaneObject();
};

class BoxObject : public Model
{
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
public:
	BoxObject();
	~BoxObject();
};

class LineObject : public Model
{
public:
	int			m_iNumVertex;
public:
	HRESULT CreateVertexData();
	bool PostRender(ID3D11DeviceContext* pContext);

public:
	LineObject();
	~LineObject();

};

class AxisObject : public LineObject
{

public:
	HRESULT CreateVertexData();
	bool PostRender(ID3D11DeviceContext* pContext);

public:
	AxisObject();
	~AxisObject();

};