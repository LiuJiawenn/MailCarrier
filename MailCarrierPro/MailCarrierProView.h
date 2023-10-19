
// MailCarrierProView.h : CMailCarrierProView 类的接口
//

#pragma once
#define N 100
#include "State.h"
#include <queue>
class CMailCarrierProView : public CView
{
protected: // 仅从序列化创建
	CMailCarrierProView();
	DECLARE_DYNCREATE(CMailCarrierProView)

// 特性
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
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
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

// 实现
public:
	virtual ~CMailCarrierProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool Check(int x, int y, int sign);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // MailCarrierProView.cpp 中的调试版本
inline CMailCarrierProDoc* CMailCarrierProView::GetDocument() const
   { return reinterpret_cast<CMailCarrierProDoc*>(m_pDocument); }
#endif

