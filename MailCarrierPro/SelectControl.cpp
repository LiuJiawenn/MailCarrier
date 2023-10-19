// SelectControl.cpp : 实现文件
//

#include "stdafx.h"
#include "MailCarrierPro.h"
#include "SelectControl.h"
#include "MailCarrierProDoc.h"


// SelectControl

IMPLEMENT_DYNCREATE(SelectControl, CFormView)

SelectControl::SelectControl()
	: CFormView(IDD_SelectControl)
{

}

SelectControl::~SelectControl()
{
}

void SelectControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(SelectControl, CFormView)
	ON_BN_CLICKED(IDC_Track, &SelectControl::OnBnClickedTrack)
	ON_BN_CLICKED(IDC_Clear, &SelectControl::OnBnClickedClear)
END_MESSAGE_MAP()


// SelectControl 诊断

#ifdef _DEBUG
void SelectControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SelectControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SelectControl 消息处理程序


void SelectControl::OnBnClickedTrack()
{
	CMailCarrierProDoc* pDoc = (CMailCarrierProDoc*)GetDocument();
	pDoc->BeginCalcu = TRUE;
	pDoc->UpdateAllViews(this);
}


void SelectControl::OnBnClickedClear()
{
	CMailCarrierProDoc* pDoc = (CMailCarrierProDoc*)GetDocument();
	pDoc->Clear = TRUE;
	pDoc->UpdateAllViews(this);
}
