#pragma once
#include "FieldGenerateForm.h"

// FieldGenPane

class FieldGenPane : public CDockablePane
{
	DECLARE_DYNAMIC(FieldGenPane)

public:
	FieldGenPane();
	virtual ~FieldGenPane();

	FieldGenerateForm* m_wndForm;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


