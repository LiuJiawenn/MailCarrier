
// MailCarrierProView.h : CMailCarrierProView ��Ľӿ�
//

#pragma once
#define N 100
#include "State.h"
#include <queue>
class CMailCarrierProView : public CView
{
protected: // �������л�����
	CMailCarrierProView();
	DECLARE_DYNCREATE(CMailCarrierProView)

// ����
public:
	CMailCarrierProDoc* GetDocument() const;

	int m_pNumbers;        // polygon input buffer
	CPoint m_pAccord[N], m_mousePoint;
	CBrush brush = RGB(255, 0, 0);
	CPoint begin;
	CPoint end;
	int b, e;

	State picture[N];
	State Now[N];
	State Odd[N];
	int oddnum;
	int nownum;
	int flag;
	CClientDC *m_pDC;
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	BOOL Track();
	bool FindOdd();
	void Supple();
	bool DeleNeighb(State orig, int limate, int step, int& result);
	int  goaltest(CPoint p);
	void DrawPath(std::queue<CPoint>& path);
	bool Contain(CPoint a[], int num, CPoint p1, CPoint p2);
	State NextPoint(State p);
	BOOL DFSTest(CPoint p1, CPoint p2);
	int dfs(State * p, int s);
	int PointToState(CPoint p);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMailCarrierProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool Check(int x, int y, int sign);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // MailCarrierProView.cpp �еĵ��԰汾
inline CMailCarrierProDoc* CMailCarrierProView::GetDocument() const
   { return reinterpret_cast<CMailCarrierProDoc*>(m_pDocument); }
#endif

