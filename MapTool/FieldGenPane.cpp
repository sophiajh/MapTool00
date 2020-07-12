// FieldGenPane.cpp: 구현 파일
//

#include "pch.h"
#include "MapTool.h"
#include "FieldGenPane.h"


// FieldGenPane

IMPLEMENT_DYNAMIC(FieldGenPane, CDockablePane)

FieldGenPane::FieldGenPane()
{

}

FieldGenPane::~FieldGenPane()
{
}


BEGIN_MESSAGE_MAP(FieldGenPane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// FieldGenPane 메시지 처리기




void FieldGenPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (m_wndForm)
	{
		m_wndForm->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


int FieldGenPane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


int FieldGenPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndForm = FieldGenerateForm::CreateOne(this);
	return 0;
}
