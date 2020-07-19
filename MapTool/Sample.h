#pragma once
#include "Core.h"
#include "DebugCam.h"
#include "DObject.h"
#include "Field.h"

#include "QuadTree.h"
#include "DXRT.h"
#include "Select.h"
#include "TextureManager.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

struct LIGHT_CONSTANT_BUFFER
{
	D3DXMATRIX			g_matInvWorld;
	// Material
	D3DXVECTOR4			g_cAmbientMaterial;
	D3DXVECTOR4			g_cDiffuseMaterial;
	//D3DXVECTOR4			g_cSpecularMaterial;
	//D3DXVECTOR4			g_cEmissionMaterial;
	// Light
	D3DXVECTOR4			g_cAmbientLightColor;
	D3DXVECTOR4			g_cDiffuseLightColor;
	//D3DXVECTOR4			g_cSpecularLightColor;
	/*시연수정 원본
	D3DXVECTOR4			g_vLightDir; // w = light damping(attenuation) : 감쇠
	D3DXVECTOR4			g_vLightPos; // w = light radius
	*/
	D3DXVECTOR4			g_vLightPos; // w = light radius
	D3DXVECTOR4			g_vLightDir; // w = light damping(attenuation) : 감쇠

	D3DXVECTOR4			g_vEyeDir;// w = light intensity : 강도
	//D3DXVECTOR4			g_vEyePos;// w = light radius	
};


class Sample : public Core
{
public:
	bool Init()		override;
	bool Render()	override;
	bool Frame()	override;
	bool Release()	override;

	//FieldHeight& CreateField(int iRow, int iCol);
	std::unique_ptr<FieldHeight> CreateField(int iRow, int iCol);

	unique_ptr<FieldHeight> m_TestField;
	//FieldHeight* m_TestField;

	QuadTree	m_Quad;
	DXRT		m_FullRT;
	DXRT		m_MinimapRT;
	Camera		m_MinimapCam;
	PlaneObject	m_Screen;
	PlaneObject	m_MiniMap;
	Select		m_Select;

	BoxObject	m_Obj;
	PlaneObject m_Brush;
	D3DXMATRIX	m_LightMat;

	D3DXVECTOR3							m_vLightVector;
	LIGHT_CONSTANT_BUFFER				m_cbLight;
	Microsoft::WRL::ComPtr<ID3D11Buffer>m_pConstantBufferLight;

private:
	AxisObject		m_BasisLine;
	
public:
	Sample();
	~Sample();
};

