// FieldGenerateForm.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "FieldGenerateForm.h"


// FieldGenerateForm

IMPLEMENT_DYNCREATE(FieldGenerateForm, CFormView)

FieldGenerateForm::FieldGenerateForm()
	: CFormView(IDD_FieldGenerateForm)
	, m_testingint(10)
{
}

FieldGenerateForm::~FieldGenerateForm()
{
}

void FieldGenerateForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HEIGHT_SLIDER, m_HeightSld);
	DDX_Control(pDX, IDC_HEIGHT_EDIT, m_HeightEditBox);
	//  DDX_Text(pDX, IDC_HEIGHT_EDIT, m_testint);
	DDX_Text(pDX, IDC_HEIGHT_EDIT, m_testingint);
	DDV_MinMaxInt(pDX, m_testingint, -50, 50);
	DDX_Control(pDX, IDC_COMBO1, m_FieldSizeCtl);
	//  DDX_Control(pDX, IDC_LIST5, m_TextureList);
	//DDX_Control(pDX, IDC_LIST6, m_TexList);
}

BEGIN_MESSAGE_MAP(FieldGenerateForm, CFormView)
	ON_BN_CLICKED(IDC_FIELDGENBUTTON, &FieldGenerateForm::OnBnClickedFieldgenbutton)
	ON_BN_CLICKED(IDC_TEX2, &FieldGenerateForm::OnBnClickedTex2)
	ON_BN_CLICKED(IDC_TEX1, &FieldGenerateForm::OnBnClickedTex1)
	ON_BN_CLICKED(IDC_TEX3, &FieldGenerateForm::OnBnClickedTex3)
	ON_BN_CLICKED(IDC_TEX4, &FieldGenerateForm::OnBnClickedTex4)
	ON_BN_CLICKED(IDC_HEIGHT, &FieldGenerateForm::OnBnClickedHeight)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_HEIGHT_SLIDER, &FieldGenerateForm::OnNMCustomdrawHeightSlider)
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_HEIGHT_EDIT, &FieldGenerateForm::OnEnChangeHeightEdit)
	ON_CBN_SELCHANGE(IDC_COMBO1, &FieldGenerateForm::OnCbnSelchangeCombo1)
//	ON_WM_INITMENU()
//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &FieldGenerateForm::OnLvnItemchangedList3)
END_MESSAGE_MAP()

FieldGenerateForm* FieldGenerateForm::CreateOne(CWnd* pParent)
{
	FieldGenerateForm* pForm = new FieldGenerateForm;

	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}

// FieldGenerateForm 진단

#ifdef _DEBUG
void FieldGenerateForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void FieldGenerateForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// FieldGenerateForm 메시지 처리기

void FieldGenerateForm::OnBnClickedFieldgenbutton()
{
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();
	
	//(2의 n승 +1)만 설정 가능
	int iCell =	m_FieldSizeCtl.GetCurSel() + 1;
	
	pApp->m_Tool.m_TestField = &(pApp->m_Tool.CreateField(std::pow(2, iCell) + 1, std::pow(2, iCell) + 1));

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void FieldGenerateForm::OnBnClickedTex2()
{
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();
	pApp->m_Tool.m_Select.m_CurrFunc = SelectFunc::FUNC_CHANGETEXTURE;

	pApp->m_Tool.m_Select.m_iCurrentTexture = 0;
	//pApp->m_Tool.m_TestField->m_pSplattingPatternList[1];
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void FieldGenerateForm::OnBnClickedTex1()
{
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();
	pApp->m_Tool.m_Select.m_CurrFunc = SelectFunc::FUNC_CHANGETEXTURE;

	pApp->m_Tool.m_Select.m_iCurrentTexture = -1;

	//pApp->m_Tool.m_TestField->m_pSplattingPatternList[0];

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void FieldGenerateForm::OnBnClickedTex3()
{
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();
	pApp->m_Tool.m_Select.m_CurrFunc = SelectFunc::FUNC_CHANGETEXTURE;

	pApp->m_Tool.m_Select.m_iCurrentTexture = 1;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void FieldGenerateForm::OnBnClickedTex4()
{
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();
	pApp->m_Tool.m_Select.m_CurrFunc = SelectFunc::FUNC_CHANGETEXTURE;

	pApp->m_Tool.m_Select.m_iCurrentTexture = 2;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void FieldGenerateForm::OnBnClickedHeight()
{
	CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();
	pApp->m_Tool.m_Select.m_CurrFunc = SelectFunc::FUNC_CHANGEHEIGHT;
	int iPos = m_HeightSld.GetPos();

	//iPos = iPos - 50;

	CString sPos;
	sPos.Format(_T("%d"), iPos);
	m_HeightEditBox.SetWindowTextW(sPos);
	m_testingint = iPos;

	pApp->m_Tool.m_Select.m_fStrength = m_testingint;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//void FieldGenerateForm::OnNMCustomdrawHeightSlider(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//}


void FieldGenerateForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (IDC_HEIGHT_SLIDER == pScrollBar->GetDlgCtrlID())
	{
		int iPos = m_HeightSld.GetPos();
		
		//iPos = iPos - 50;

		CString sPos;
		sPos.Format(_T("%d"), iPos);
		m_HeightEditBox.SetWindowTextW(sPos);
		m_testingint = iPos;

		CMapToolApp* pApp = (CMapToolApp*)AfxGetApp();
		pApp->m_Tool.m_Select.m_fStrength = m_testingint;
	}
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


int FieldGenerateForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//m_HeightSld.SetRange(-50, 50);
	//m_FieldSizeCtl.AddString(L"");
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	
	return 0;
}


//BOOL FieldGenerateForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	//m_HeightSld.SetRange(-50, 50);
//	//m_HeightSld.SetPos(10);
//	//m_HeightSld.SetLineSize(15);
//	//m_HeightSld.SetPageSize(20);
//	//
//	//int iPos = m_HeightSld.GetPos();
//	//
//	//CString sPos;
//	//sPos.Format(_T("%d"), iPos);
//	//m_HeightEditBox.SetWindowTextW(sPos);
//	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}


void FieldGenerateForm::OnEnChangeHeightEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void FieldGenerateForm::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


//void FieldGenerateForm::OnInitMenu(CMenu* pMenu)
//{
//	CFormView::OnInitMenu(pMenu);
//
//	m_HeightSld.SetRange(-50, 50);
//	m_HeightSld.SetPos(10);
//	m_HeightSld.SetLineSize(15);
//	m_HeightSld.SetPageSize(20);
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//}


void FieldGenerateForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_HeightSld.SetRange(-50, 50);
	m_HeightSld.SetPos(10);
	m_HeightSld.SetLineSize(15);
	m_HeightSld.SetPageSize(20);
	
	int iPos = m_HeightSld.GetPos();
	
	CString sPos;
	sPos.Format(_T("%d"), iPos);
	m_HeightEditBox.SetWindowTextW(sPos);

	m_FieldSizeCtl.InsertString(-1, _T("2 * 2"));
	m_FieldSizeCtl.InsertString(-1, _T("4 * 4"));
	m_FieldSizeCtl.InsertString(-1, _T("8 * 8"));
	m_FieldSizeCtl.InsertString(-1, _T("16 * 16"));
	m_FieldSizeCtl.InsertString(-1, _T("32 * 32"));
	m_FieldSizeCtl.InsertString(-1, _T("64 * 64"));
	m_FieldSizeCtl.InsertString(-1, _T("128 * 128"));

	m_FieldSizeCtl.SetCurSel(0);


	
	//CImageList cImgList;
	//cImgList.Create(64, 64, ILC_COLOR16, 2, 2);
	//
	//CBitmap bmp;
	//CImage image;
	//CImage copyImg; // 이미지를 늘려 저장할 변수
	//CImage img;
	//copyImg.Create(64, 64, 16);
	//TCHAR    szPath[_MAX_PATH] = L"../../data/bitmap/000.jpg";
	//
	//image.Load(szPath);
	//BOOL bResult = image.StretchBlt(copyImg.GetDC(), 0, 0, 64, 64, SRCCOPY);
	//bmp.Attach(img);
	//cImgList.Add(&bmp, RGB(0, 0, 0));
	//copyImg.Create(nIconSize, nIconSize, 16);  //카피 이미지 설정 값
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


//void FieldGenerateForm::OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	*pResult = 0;
//}
