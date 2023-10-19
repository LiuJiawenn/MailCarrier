
// MailCarrierProView.cpp : CMailCarrierProView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MailCarrierPro.h"
#endif

#include "MailCarrierProDoc.h"
#include "MailCarrierProView.h"
#include "State.h"
#include <stack>
#include <queue>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMailCarrierProView

IMPLEMENT_DYNCREATE(CMailCarrierProView, CView)

BEGIN_MESSAGE_MAP(CMailCarrierProView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMailCarrierProView ����/����

CMailCarrierProView::CMailCarrierProView()
{
	// TODO: �ڴ˴���ӹ������
	m_pNumbers = 0;
	nownum = 0;
	oddnum = 0;
	flag = 0;
}

CMailCarrierProView::~CMailCarrierProView()
{
}

BOOL CMailCarrierProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMailCarrierProView ����

void CMailCarrierProView::OnDraw(CDC* /*pDC*/)
{
	CMailCarrierProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_pDC = new CClientDC(this);

	if (pDoc->BeginCalcu == TRUE)
	{//�ػ�
		
		State temporary;
		for (int i = 0; i < m_pNumbers; i++)
		{
			temporary = picture[i];
			m_pDC->SelectObject(&brush);
			m_pDC->Ellipse(temporary.point.x - 10, temporary.point.y - 10, temporary.point.x + 10, temporary.point.y + 10);
			for (int j = 0; j < temporary.degree; j++)
			{
				m_pDC->MoveTo(temporary.point);
				m_pDC->LineTo(temporary.next[j]);
			}
		}

		pDoc->BeginCalcu = false;
		Track();
	}
	if (pDoc->Clear == TRUE)
	{
		pDoc->Clear = false;
		for (int i = 0; i < m_pNumbers; i++)
		{
			m_pAccord[i] = 0;
			picture[i].SetZero();
			Now[i].SetZero();
			Odd[i].SetZero();
		}
		m_pNumbers = 0;
		nownum = 0;
		oddnum = 0;
		begin = 0;
		end = 0;
		e = 0;
		b = 0;
		flag = 0;
	}
		
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

BOOL CMailCarrierProView::Track()
{
	nownum = m_pNumbers;
	for (int i = 0; i < m_pNumbers; i++)
	{
		Now[i] = picture[i];
	}
	if (!DFSTest(CPoint(-1, -1), CPoint(-1, -1)))//�����ʼ״̬����ͨ������false��
	{
		MessageBox(_T("��ͼ����ͨ���������ӱߣ�"));
		return false;
	}
	else if (FindOdd())//����ҵ��������ȶ���
	{
		Supple();//�����ʹ���������ȵ��Ϊż���Ȳ���ʹ����ı�����С
	}
	std::queue<CPoint> path;//����·��ջ
	State next = picture[0];//��ʼ���ѹջ
	int number = m_pNumbers;
	while (nownum>1)
	{
		path.push(next.point);
		next = NextPoint(next);//����һ�����
	}
	//path.push(next.point);
	DrawPath(path);
	return true;
}
bool CMailCarrierProView::FindOdd()
{
	for (int i = 0; i < m_pNumbers; i++)
	{
		if (picture[i].degree % 2 != 0)
		{
			Odd[oddnum] = picture[i];
			Odd[oddnum].visited = false;
			oddnum++;
		}
	}
	if (oddnum == 0)return false;
	else return true;
}
int tr = 0;
int yy = 0;
void CMailCarrierProView::Supple()
{
	int limate = 0;
	int result = -1;
	int time = oddnum;
	while (time!=0)
	{
		limate++;  //�����ӽڵ㷵��falseʱ����limit��������
		for (int i = 0; i < oddnum; i++)
		{
			if (Odd[i].visited == false)
			{
				tr = i;
				if (DeleNeighb(Odd[i], limate,0,result) == true)//��ʼ�ݹ��������������
				{
					Odd[i].visited = true;
					Odd[result].visited = true;
					time -= 2;
				}
			}
		}
	}	
}

bool CMailCarrierProView::DeleNeighb(State orig,int limate,int step,int& result)
{
	if (step + 1 > limate)return false;//�����������Ʒ���
	else                               //�������������չ����
	{
		for (int i = 0; i < orig.degree; i++)
		{
			result = goaltest(orig.next[i]);
			if (result != -1)           //�ҵ���Ծͷ���
			{                          //��¼���εݹ�·��
				Now[PointToState(orig.next[i])].next[Now[PointToState(orig.next[i])].degree++] = orig.point;
				Now[PointToState(orig.point)].next[Now[PointToState(orig.point)].degree++] = orig.next[i];
				return true;
			}                          //��δ������������ʱ���ݹ���ӽڵ������չ
			else if (DeleNeighb(Now[PointToState(orig.next[i])], limate, step + 1, result))
			{                          //��¼���εݹ�·��
				Now[PointToState(orig.next[i])].next[Now[PointToState(orig.next[i])].degree++] = orig.point;
				Now[PointToState(orig.point)].next[Now[PointToState(orig.point)].degree++] = orig.next[i];
				return true;
			}
			                           //�����ӽڵ��µ�������Ŀ��ڵ㣬����������һ�ӽڵ�
		}
		return false;                  //���������ӽڵ㶼û���ҵ�����false
	}
}

int  CMailCarrierProView::goaltest(CPoint p)
{
	for (int i = tr+1; i < oddnum; i++)
	{
		if (Odd[i].point == p&&Odd[i].visited == false)
		{
			return i;
		}		
	}
	return -1;
}

void CMailCarrierProView::DrawPath(std::queue<CPoint>& path)
{
	m_pDC = new CClientDC(this);
	int len = path.size();
	CBrush brush1 = RGB(0, 0, 255);
	CPen pen1(PS_SOLID, 2, RGB(0, 0, 255));
	CPen pen2(PS_SOLID, 2, RGB(255, 0, 0));
	CPoint temporary;
	CPoint a[100];
	for (int i = 0; i < len-1; i++)
	{
		temporary = path.front(); a[i]= temporary;
		path.pop();
		
		m_pDC->SelectObject(&brush1);
		m_pDC->Ellipse(temporary.x - 20, temporary.y - 20, temporary.x + 20, temporary.y + 20);
		Sleep(200);
		if(Contain(a,i, temporary, path.front()))
		    m_pDC->SelectObject(&pen2);
		else
			m_pDC->SelectObject(&pen1);
		m_pDC->MoveTo(temporary);
		m_pDC->LineTo(path.front());
		Sleep(800);
	}
	temporary = path.front();
	path.pop();
	m_pDC->SelectObject(&brush);
	m_pDC->Ellipse(temporary.x - 10, temporary.y - 10, temporary.x + 10, temporary.y + 10);
}

bool CMailCarrierProView::Contain(CPoint a[],int num,CPoint p1,CPoint p2)
{
	for (int i = 0; i <= num; i++)
	{
		if (a[i] == p1 && a[i + 1] == p2)
			return true;
		else if (a[i] == p2 && a[i + 1] == p1)
			return true;
	}
	return false;
}

State CMailCarrierProView::NextPoint(State p)
{
	State next;
	int t = 0;
	for (int k = 0; k < nownum; k++)
	{
		if (Now[k].degree == 0)
		{
			for (int j = k; j < nownum; j++)
				Now[j] = Now[j + 1];
			t++;
			k--;
		}
	}
	nownum -= t;
	for (int i = 0; i < Now[PointToState(p.point)].degree;i++)//������p���ڵ����е�
	{
		if (p.related[i] == 1)continue;//�����֪�˱����ţ�������һ���ߵ�����
		else if (DFSTest(p.point, p.next[i]))//���ɾ�������˵��Ӧ�ı�����ͨ��˵�������߲�����
		{
			next = Now[PointToState(p.next[i])];
			
		    //ɾȥ�����ߣ�����Now����

			for (int d = 0; d < next.degree; d++)
			{
				if (next.next[d] == p.point)
				{
					for (int j = d; j <next.degree; j++)
					{
						Now[PointToState(p.next[i])].next[j] = Now[PointToState(p.next[i])].next[j + 1];
					}
					Now[PointToState(p.next[i])].degree--;
					break;
				}
			}
			next = Now[PointToState(p.next[i])];
			for (int j = i; j < p.degree; j++)
			{
				Now[PointToState(p.point)].next[j] = Now[PointToState(p.point)].next[j + 1];
			}
			Now[PointToState(p.point)].degree--;

			return next;
		}
		else//���ʣ�µ����б߶�����
		{
			Now[PointToState(p.point)].related[i] = 1;
		}
	}
	//���ʣ�µ����б߶�����
	int p1 = PointToState(p.point);
	int p2 = PointToState(p.next[p.degree- 1]);
	Now[p1].degree--;

	for (int w = 0; w < Now[p2].degree; w++)
	{
		if (Now[p2].next[w] == p.point)
		{
			for (int u = w; u < Now[p2].degree; u++)
			{
				Now[p2].next[u] = Now[p2].next[u + 1];
			}
			break;
		}
	}
	Now[p2].degree--;
	next = Now[p2];
	return next;
}

BOOL CMailCarrierProView::DFSTest(CPoint p1, CPoint p2)
{
	State Pic[N];//��now���鱸��
	int sum;
	int t = 0;
	for (int i = 0; i < nownum; i++)
	{
		Pic[i] = Now[i];
		Pic[i].visited = false;
	}
	
	int m = Pic[PointToState(p1)].degree;
	int n = Pic[PointToState(p2)].degree;
	if (p1.x==-1 || p2.x==-1)
	{
		sum = dfs(Pic, 0);
	}
	//ɾ��Ҫ���ı�
	else
	{
		for (int i = 0; i < m; i++)
		{
			if (Pic[PointToState(p1)].next[i] == p2)
			{
				Pic[PointToState(p1)].degree--;
				for (int j = i; j < m; j++)
				{
					Pic[PointToState(p1)].next[j] = Pic[PointToState(p1)].next[j + 1];
				}
				break;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (Pic[PointToState(p2)].next[i] == p1)
			{
				Pic[PointToState(p2)].degree--;
				for (int j = i; j < n; j++)
				{
					Pic[PointToState(p2)].next[j] = Pic[PointToState(p2)].next[j + 1];
				}
				break;
			}
		}

		int next = PointToState(p2);//��ɾ���ߵĶ˵���Ϊ����������������
		sum = dfs(Pic, next);
	}
		
	if (sum == nownum)
		return true;
	else return false;

}
int CMailCarrierProView::dfs(State* p, int s)
{
	p[s].visited = TRUE;
	int sum=1;
	for (int i = 0; i < p[s].degree; i++)
	{
		if (p[PointToState(p[s].next[i])].visited == false)
		{
			sum+=dfs(p, PointToState(p[s].next[i]));
		}
	}
	return sum;
}


int CMailCarrierProView::PointToState(CPoint p)//����NOW�����е�λ��
{
	for (int i = 0; i < nownum; i++)
	{
		if (Now[i].point == p)
			return i;
	}
	return -1;
}


// CMailCarrierProView ��ӡ

BOOL CMailCarrierProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMailCarrierProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMailCarrierProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMailCarrierProView ���

#ifdef _DEBUG
void CMailCarrierProView::AssertValid() const
{
	CView::AssertValid();
}

void CMailCarrierProView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMailCarrierProDoc* CMailCarrierProView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailCarrierProDoc)));
	return (CMailCarrierProDoc*)m_pDocument;
}
#endif //_DEBUG


// CMailCarrierProView ��Ϣ�������


void CMailCarrierProView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!Check(point.x, point.y, 0) && m_pNumbers < N)
	{
		m_pAccord[m_pNumbers] = point;
		picture[m_pNumbers] = State(point);
		m_pNumbers++;
		//����ԲƬ
		//CBrush* pbr = m_pDC->SelectObject(&brush);
		m_pDC->SelectObject(&brush);
		m_pDC->Ellipse(point.x - 20, point.y - 20, point.x + 20, point.y + 20);
		m_mousePoint = point;
	}
	else
	{
		flag = 1;
		m_mousePoint = point;
	}

	CView::OnLButtonDown(nFlags, point);
}

bool CMailCarrierProView::Check(int x, int y, int sign)
{
	int sum = 0;
	for (int i = 0; i < m_pNumbers; i++)
	{
		sum = (x - m_pAccord[i].x)*(x - m_pAccord[i].x) + (y - m_pAccord[i].y)*(y - m_pAccord[i].y);
		if (sum < 400)
		{
			if (sign == 0)//�������ʱ��¼begin
			{
				begin.x = m_pAccord[i].x;
				begin.y = m_pAccord[i].y;
				b = i;
			}
			else if (sign == 1)//̧�������¼end
			{
				end.x = m_pAccord[i].x;
				end.y = m_pAccord[i].y;
				if (end == begin)
					return false;
				e = i;
			}
			return true;
		}
		sum = 0;
	}
	if (sum == 0)return false;
	else return false;
}


void CMailCarrierProView::OnLButtonUp(UINT nFlags, CPoint point)
{
	flag = 0;
	if (begin.x==0||begin.y==0)
	{
		return;
	}
	else if (Check(point.x, point.y, 1))
	{
		picture[b].next[picture[b].degree++] = end;
		picture[e].next[picture[e].degree++] = begin;
	}
	else
	{
		m_pDC->SetROP2(2);
		m_pDC->MoveTo(begin);
		m_pDC->LineTo(m_mousePoint);
	}


	CView::OnLButtonUp(nFlags, point);
}


void CMailCarrierProView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (flag == 1 && m_pNumbers)
	{

		m_pDC->SetROP2(2);
		m_pDC->MoveTo(begin);
		m_pDC->LineTo(m_mousePoint);

		m_mousePoint = point;
		m_pDC->MoveTo(begin);
		m_pDC->LineTo(m_mousePoint);
	}
	CView::OnMouseMove(nFlags, point);
}


int CMailCarrierProView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//m_pDC = new CClientDC(this);

	return 0;
}
