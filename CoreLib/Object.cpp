#include "Object.h"
//#include "Bitmap.h"
#include "Input.h"
//#include "BitmapMgr.h"
#include "TextureManager.h"

bool Object::Init()
{
	//m_hColor = CreateCompatibleDC(NULL);
	//m_hMask = CreateCompatibleDC(NULL);
	m_fAlpha = 0.0f;
	m_fAngle = 0.0f;
	return true;
}

bool Object::SetDrawRect(xPoint point, RECT rec)	//m_rtDraw 좌상단/우하단 좌표
{
	m_rtDraw.left = point.x - (rec.right / 2);
	m_rtDraw.top = point.y - (rec.bottom / 2);
	m_rtDraw.right =  m_rtDraw.left + rec.right;
	m_rtDraw.bottom =  m_rtDraw.top + rec.bottom;
	SetHitRect(point, rec);
	return true;
}
RECT Object::GetDrawRect()
{
	return m_rtDraw;
}
bool Object::SetHitRect(xPoint point, RECT rec)	//m_rtHit 좌상단/우하단 좌표
{
	m_rtHit.left = point.x - (rec.right / 2);
	m_rtHit.top = point.y - (rec.bottom / 2);
	m_rtHit.right = m_rtHit.left + rec.right;
	m_rtHit.bottom = m_rtHit.top + rec.bottom;

	return true;
}

void Object::Set(ObjectInfo info)
{
	m_Pos = info.Initpos;
	m_fSpeed = info.fSpeed;
	m_rtObj = info.rt;
	SetDrawRect(m_Pos, m_rtObj);
}

void Object::SetRandom(ObjectInfo info)
{
	m_Pos = info.Initpos;
	m_fSpeed = info.fSpeed;
	m_rtObj = info.rt;
	m_rtList = info.rtList;
	SetDrawRect(m_Pos, m_rtObj);

}

void Object::SetPos(xPoint pt)
{
	m_Pos = pt;
	SetDrawRect(m_Pos, m_rtObj);
}

void Object::SetPos(float x, float y)
{
	m_Pos.x = x;
	m_Pos.y = y;
	SetDrawRect(m_Pos, m_rtObj);
}

xPoint Object::GetPos()
{
	return m_Pos;
}

void Object::Set(xPoint pos, RECT rt, float fSpeed)
{
	m_Pos = pos;
	m_fSpeed = fSpeed;
	m_rtObj = rt;
	SetDrawRect(m_Pos, m_rtObj);
}

bool Object::Load(std::wstring filename)		//Object map을 관리함.
{
	//int iKey = BitmapMgr::GetInstance().Load(filename);
	//m_pBitmap = BitmapMgr::GetInstance().GetPtr(iKey);
	//if (m_pBitmap == nullptr) return false;

	//T_STR name = m_pBitmap->m_szPath;
	//name += L"Mask_";
	//name += m_pBitmap->m_szName;

	//iKey = BitmapMgr::GetInstance().Load(name);
	//m_pBitmapMask = BitmapMgr::GetInstance().GetPtr(iKey);
	return true;
}

//bool Object::Render()
//{
//	/*if (m_pBitmapMask != nullptr)
//	{
//		m_pBitmapMask->Draw(m_Pos.x, m_Pos.y, m_rtObj, SRCAND);
//		m_pBitmap->Draw(m_Pos.x, m_Pos.y, m_rtObj, SRCINVERT);
//		m_pBitmapMask->Draw(m_Pos.x, m_Pos.y, m_rtObj, SRCINVERT);
//	}
//	else
//	{
//		m_pBitmap->Draw(m_Pos.x, m_Pos.y, m_rtObj, SRCCOPY);
//	}*/
//	
//	BITMAPINFO bmi;
//	ZeroMemory(&bmi, sizeof(BITMAPINFO));
//	bmi.bmiHeader.biHeight = m_rtObj.bottom;//h;		//The height of the bitmap, in pixels. If biHeight is positive, the bitmap is a bottom-up DIB and its origin is the lower-left corner. 
//												//If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
//	bmi.bmiHeader.biWidth = m_rtObj.right;//w;			//The width of the bitmap, in pixels.
//	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);	//The number of bytes required by the structure.
//	bmi.bmiHeader.biBitCount = 32;						//The number of bits-per-pixel.
//	bmi.bmiHeader.biCompression = BI_RGB;				//The type of compression for a compressed bottom-up bitmap (top-down DIBs cannot be compressed).
//	bmi.bmiHeader.biSizeImage = m_rtObj.right * m_rtObj.bottom * 4;	//The size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps.
//	bmi.bmiHeader.biPlanes = 1;
//
//	void *pvBit = 0;
//	HBITMAP hBitmap = CreateDIBSection(g_hScreenDC, &bmi, DIB_RGB_COLORS, &pvBit, NULL, 0); //pvBit에 DIB bit시작주소 받음.
//	HDC dc = CreateCompatibleDC(NULL);
//	SelectObject(dc, hBitmap);	//SelectObject는 특정 DC에 object를 select시킨다. 새로운 object가 같은 타입의 이전 오브젝트를 대체한다. SelectObject( HDC hdc , HGDIOBJ h(지금은 여기에 비트맵이 들어감) )
//	BitBlt(dc, 0, 0, m_rtObj.right, m_rtObj.bottom, this->GetBitmap()->m_hMemDC, m_rtObj.left, m_rtObj.top, SRCCOPY); //BitBlt은 특정 소스 DC에서 destDC로 색을 옮긴다???
//	DeleteDC(dc);
//
//	void *pvOffBit = 0;
//	HBITMAP hOffBitmap = CreateDIBSection(g_hScreenDC, &bmi, DIB_RGB_COLORS, &pvOffBit, NULL, 0); //pvBit에 DIB bit시작주소 받음.
//	HDC offdc = CreateCompatibleDC(NULL);
//	SelectObject(offdc, hOffBitmap);	//SelectObject는 특정 DC에 object를 select시킨다. 새로운 object가 같은 타입의 이전 오브젝트를 대체한다. SelectObject( HDC hdc , HGDIOBJ h(지금은 여기에 비트맵이 들어감) )
//	BitBlt(offdc, 0, 0, m_rtObj.right, m_rtObj.bottom, g_hOffScreenDC, m_Pos.x, m_Pos.y/*m_rtObj.left, m_rtObj.top*/, SRCCOPY); //BitBlt은 특정 소스 DC에서 destDC로 색을 옮긴다???
//	DeleteDC(offdc);
//
//	for (int y = 0; y < m_rtObj.bottom; y++)
//	{
//		byte* pRGB = (byte*)&((DWORD*)pvBit)[y*m_rtObj.right];
//		//byte* pMaskRGB = (byte*)&((DWORD*)pvMaskBit)[y*iWidth];
//		byte* pOffRGB = (byte*)&((DWORD*)pvOffBit)[y*m_rtObj.right];
//
//		for (int x = 0; x < m_rtObj.right; x++)
//		{
//			byte  A = pRGB[3];
//			byte  R = pRGB[2];
//			byte  G = pRGB[1];
//			byte  B = pRGB[0];
//			byte  offA = pOffRGB[3];
//			byte  offR = pOffRGB[2];
//			byte  offG = pOffRGB[1];
//			byte  offB = pOffRGB[0];
//
//			if (A)
//				//if (pMaskRGB[0]==0 && pMaskRGB[1] == 0 && pMaskRGB[2] == 0)
//			{
//				pRGB[3] = 0xff;
//
//				pRGB[2] = R; //* (1.0f - m_fAlpha) + pMaskRGB[2] * m_fAlpha;
//				pRGB[1] = G;//* (1.0f - m_fAlpha) + pMaskRGB[2] * m_fAlpha;
//				pRGB[0] = B; //* (1.0f - m_fAlpha) + pMaskRGB[2] * m_fAlpha;
//			}
//			else
//			{
//				pRGB[3] = 0xff;
//				pRGB[2] = offR;
//				pRGB[1] = offG;
//				pRGB[0] = offB;
//
//			}
//			pRGB += 4;
//			pOffRGB += 4;
//			//pMaskRGB += 4;
//		}
//	}
//
//	HDC tmpdc = CreateCompatibleDC(NULL);
//	SelectObject(tmpdc, hBitmap);
//	
//	SetStretchBltMode(g_hOffScreenDC, HALFTONE);
//	StretchBlt(g_hOffScreenDC, m_Pos.x, m_Pos.y, m_rtObj.right, m_rtObj.bottom, tmpdc, 0, 0, m_rtObj.right, m_rtObj.bottom, SRCCOPY);
//	DeleteObject(tmpdc);
//
//	DeleteObject(hBitmap);
//	DeleteObject(hOffBitmap);
//	return true;
//}


bool Object::Frame()
{
	SetDrawRect(m_Pos, m_rtObj);
	return true;
}
bool Object::Release()
{
	//DeleteObject(m_hMask);
	//DeleteObject(m_hColor);
	return true;
}
//

bool Object::Render(ID3D11DeviceContext* pContext)
{
	m_pTexture->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCCOPY);
	return true;
}

void Object::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, ObjectInfo Info)
{
	m_pDevice = pDevice;
	m_pContext = pContext;

	m_Pos = Info.Initpos;
	m_fSpeed = Info.fSpeed;
	m_rtObj = Info.rt;
	SetDrawRect(m_Pos, m_rtObj);
}

bool Object::Load(ID3D11Device* pDevice, std::wstring filename)
{
	
	int iKey = TextureManager::GetInstance().Load(pDevice, filename);
	m_pTexture = TextureManager::GetInstance().GetPtr(iKey);
	if (m_pTexture == nullptr) return false;
/*
	T_STR name = m_pTexture->m_szPath;
	name += L"Mask_";
	name += m_pTexture->m_szName;

	iKey = TextureManager::GetInstance().Load(pDevice, name);
	m_pTextureMask = I_TextureMgr.GetPtr(iKey);*/
	return true;
}
//
Object::Object()
{
	m_fAlpha = 255.0f;
	m_iIndex = 0;
}


Object::~Object()
{
}
