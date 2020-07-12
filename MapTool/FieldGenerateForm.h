#pragma once
#include "Select.h"


// FieldGenerateForm 폼 보기

class FieldGenerateForm : public CFormView
{
	DECLARE_DYNCREATE(FieldGenerateForm)

protected:
	FieldGenerateForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~FieldGenerateForm();

public:
	static FieldGenerateForm* CreateOne(CWnd* pParent);

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FieldGenerateForm };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedFieldgenbutton();
	afx_msg void OnBnClickedTex2();
	afx_msg void OnBnClickedTex1();
	afx_msg void OnBnClickedTex3();
	afx_msg void OnBnClickedTex4();
	afx_msg void OnBnClickedHeight();
	CSliderCtrl m_HeightSld;
//	afx_msg void OnNMCustomdrawHeightSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CEdit m_HeightEditBox;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg void OnEnChangeHeightEdit();
//	Int m_testint;
	int m_testingint;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_FieldSizeCtl;
//	afx_msg void OnInitMenu(CMenu* pMenu);
	virtual void OnInitialUpdate();
	//afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
//	CListBox m_TextureList;
//	CListCtrl m_TexList;
};


