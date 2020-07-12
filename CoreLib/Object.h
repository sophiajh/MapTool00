#pragma once
#include "Std.h"
//#include "Bitmap.h"
#include "DxHelperEx.h"
#include "Texture.h"
#include "Model.h"
class Object : public Model
{
protected:
	DX::DxHelperEx			m_dxObj;

	ID3D11DeviceContext*	m_pContext;
	vector<UINT>			m_iTextureList;
	ObjectInfo				m_ObjectInfo;
	Texture*				m_pTexture;
	//ID3D11Device*			m_pDevice;
	//ZID3D11DeviceContext*	m_pDeviceContext;
public:
	
	ID3D11Device*			m_pDevice;
protected:
	//Bitmap*	m_pBitmap;
	//Bitmap*	m_pBitmapMask;
public:
	xPoint		m_Pos;
	float		m_fSpeed;
	RECT		m_rtObj;

	RECT		m_rtDraw;
	RECT		m_rtHit;

	//Bitmap*		GetBitmap() { return m_pBitmap; }
	float		m_fAlpha;
	
	//HDC		m_hColor;
	//HDC		m_hMask;
	float	m_fAngle;

	T_STR	m_Name;
	int		m_iIndex;

	std::vector<RECT> m_rtList;

public:
	
	virtual bool SetDrawRect(xPoint, RECT);
	virtual RECT GetDrawRect();
	virtual bool SetHitRect(xPoint, RECT);
	virtual void Set(xPoint pos, RECT rt, float fSpeed = 100.0f);
	virtual void Set(ObjectInfo info);

	virtual void SetRandom(ObjectInfo info);

	virtual void SetPos(xPoint pt);
	virtual void SetPos(float x, float y);
	virtual xPoint GetPos();
	virtual bool Load(std::wstring filename);

	/*virtual bool AlphaBlendBitmap(int iWidth, int iHeight, HDC hColorDC, HDC hMaskDC, HDC hOffScreenDC);
	virtual bool RotateBitmap(HDC hSrc, HDC hDest, float fAngle, int iSide);
	virtual bool EffectImplement();*/
	//
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool Release();
	
	virtual void Set(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ObjectInfo Info);
	virtual bool Load(ID3D11Device* pDevice, std::wstring filename);
	//
public:
	Object();
	virtual ~Object();
};

