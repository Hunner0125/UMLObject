
// UMLObject1View.cpp : CUMLObject1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "UMLObject1.h"
#endif

#include "UMLObject1Doc.h"
#include "UMLObject1View.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUMLObject1View

IMPLEMENT_DYNCREATE(CUMLObject1View, CView)

BEGIN_MESSAGE_MAP(CUMLObject1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CUMLObject1View::OnObject)
	ON_COMMAND(ID_32772, &CUMLObject1View::OnInterface)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_32773, &CUMLObject1View::OnPackage)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_32775, &CUMLObject1View::OnInherit)
	ON_COMMAND(ID_32776, &CUMLObject1View::OnComeTrue)
	ON_COMMAND(ID_32779, &CUMLObject1View::OnRely)
	ON_COMMAND(ID_32774, &CUMLObject1View::OnRelate)
	ON_COMMAND(ID_32777, &CUMLObject1View::OnJuHe)
	ON_COMMAND(ID_32778, &CUMLObject1View::OnCombine)
	ON_COMMAND(ID_32780, &CUMLObject1View::OnLeft)
	ON_COMMAND(ID_32781, &CUMLObject1View::OnRight)
	ON_COMMAND(ID_32782, &CUMLObject1View::OnTop)
	ON_COMMAND(ID_32783, &CUMLObject1View::OnBottom)
END_MESSAGE_MAP()

// CUMLObject1View ����/����

CUMLObject1View::CUMLObject1View()
{
	// TODO: �ڴ˴���ӹ������

}

CUMLObject1View::~CUMLObject1View()
{
}

BOOL CUMLObject1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	m_OperateType = SELECT;
	m_LBtnSignal = false;
	m_LDoubleBtnSignal = false;
	m_IsControlFlow = false;
	m_CtrlDown = false;

	m_FocusGraph = NULL;

	pedit = new CEdit(); 

	return CView::PreCreateWindow(cs);
}

// CUMLObject1View ����

void CUMLObject1View::OnDraw(CDC* pDC)
{
	CUMLObject1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//pDoc->m_GraphManager.DrawAll( pDC );
	/*if (pDoc->m_GraphManager.GetFocusGraph() != NULL)
	{
		if (!pDoc->m_GraphManager.GetFocusGraph()->m_Name.IsEmpty())
		{
			CBrush *pBrush = new CBrush;
			CBrush *oldBrush;
			pBrush->CreateSolidBrush(RGB(255,0,0));
			oldBrush = pDC->SelectObject(pBrush);
			pDC->SelectObject(oldBrush);
		}
	}*/
	pDoc->m_GraphManager.DrawAll( pDC );
	//Invalidate();
}


// CUMLObject1View ��ӡ

BOOL CUMLObject1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CUMLObject1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CUMLObject1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CUMLObject1View ���

#ifdef _DEBUG
void CUMLObject1View::AssertValid() const
{
	CView::AssertValid();
}

void CUMLObject1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUMLObject1Doc* CUMLObject1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUMLObject1Doc)));
	return (CUMLObject1Doc*)m_pDocument;
}
#endif //_DEBUG


// CUMLObject1View ��Ϣ�������


void CUMLObject1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CUMLObject1Doc* pDoc = GetDocument();
	//MessageBox(_T("������"));
	m_LBtnSignal = true; // ����������Ϊdown

	switch(m_OperateType)
	{
		case SELECT:
		case MOVE:
		case ADJUST_SIZE:
			{
				bool flag = false;
				flag = pDoc->m_GraphManager.SetFocusGraphID(point);

				if(pDoc->m_GraphManager.IsAdjustSize(point))
				{
					m_OperateType = ADJUST_SIZE;
				}
				else
				//else if(pDoc->m_GraphManager.GetFocusGraph()->IsIn(point))
				{
					m_OperateType = MOVE;
					m_Start1 = point;
				}

				if(flag)
				{
					if(m_LDoubleBtnSignal)
					{
						CString str;
						pedit->GetWindowText(str);
						if(m_FocusGraph != NULL)
						{
							m_FocusGraph->SetText(str);
						}
						pedit->DestroyWindow();
						m_LDoubleBtnSignal = false;
					}

					if (m_CtrlDown)
					{
						Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
						selectG.push_back(temp);
						/*int id = selectG.size();
						CString STemp;
						STemp.Format( _T("%d"),id );
						MessageBox( STemp );*/
					}
				}

				Invalidate();
				break;
			}
		case CREATE:
			{
				if(m_LDoubleBtnSignal)
				{
					CString str;
					pedit->GetWindowText(str);
					if(m_FocusGraph != NULL)
					{
						m_FocusGraph->SetText(str);
					}
					pedit->DestroyWindow();
					m_LDoubleBtnSignal = false;
				}
				Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
				if(temp != NULL)
				{
					if(!m_IsControlFlow)
					{
						//temp->SetStartPoint(point);
						int type = temp->Type();
						if(type == 11||type == 12||type == 13||type == 14||type == 15||type == 16){
							for (int i = 0; i < pDoc->m_GraphManager.GetGraphSum(); i++)
							{
								Graph* g = pDoc->m_GraphManager.GetGraphAt(i);//ͼ��
								bool isin = g->IsIn(point);
								if (isin)
								{
									CPoint mid;
									int l = (g->m_End.x - g->m_Start.x) * 0.5;
									mid.SetPoint(g->m_Start.x+l,g->m_End.y);
									temp->SetStartPoint(mid);
									pDoc->m_GraphManager.SetRelate(g);
									break;
								}else
								{
									temp->SetStartPoint(point);
								}
							}
						}else
						{
							temp->SetStartPoint(point);
						}
					}
					else
					{
						temp->SetEndPoint(point);
					}
				}
				break;
			}
	}
	m_FocusGraph = pDoc->m_GraphManager.GetFocusGraph();
	
	CView::OnLButtonDown(nFlags, point);
}


void CUMLObject1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CUMLObject1Doc* pDoc = GetDocument();

	switch(m_OperateType)
	{
		case SELECT:
		case MOVE:
		case ADJUST_SIZE:
			{
				break;
			}
		case CREATE:
			{
				if(!m_IsControlFlow)
				{
					Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
					//temp->SetEndPoint( point );
					int type = temp->Type();
						if(type == 11||type == 12||type == 13||type == 14||type == 15||type == 16){
							for (int i = 0; i < pDoc->m_GraphManager.GetGraphSum(); i++)
							{
								Graph* g = pDoc->m_GraphManager.GetGraphAt(i);
								if(g->Type() == 1||g->Type() == 2)
								{
								bool isin = g->IsIn(point);
								if (isin)
								{
									CPoint mid;
									int l = (g->m_End.x - g->m_Start.x) * 0.5;
									mid.SetPoint(g->m_Start.x+l,g->m_End.y);
									temp->SetEndPoint(mid);
									pDoc->m_GraphManager.SetRelate(g);
									break;
								}else
								{
									temp->SetEndPoint(point);
								}
								}
							}
						}else
						{
							temp->SetEndPoint(point);
						}
				}
				break;
			}
	}

	Invalidate();
	if(!m_IsControlFlow)
		m_OperateType = SELECT; // �޸Ĳ�������ΪĬ��ֵ
	m_LBtnSignal = false; // ����������Ϊup

	/*int id = pDoc->m_GraphManager.m_FocusID;
	CString STemp;
    STemp.Format( _T("%d"),id );
	MessageBox( STemp );*/

	CView::OnLButtonUp(nFlags, point);
}

void CUMLObject1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CUMLObject1Doc* pDoc = GetDocument();

	if(m_IsControlFlow)
	{
		Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
		if(temp != NULL)
		{
			temp->SetStartPoint(point);
			Invalidate();
		}
	}

	// �ƶ�������ǰ��������������
	if(!m_LBtnSignal)
	{ 
		return;
	}

	switch(m_OperateType)
	{
		case MOVE:
			{
				pDoc->m_GraphManager.Move(point.x - m_Start1.x, point.y - m_Start1.y);
				//Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
				//m_Start1 = point;
				if (pDoc->m_GraphManager.GetFocusGraph() != NULL)
				{
					Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
					for (int i = 0; i < temp->m_Relate.GetSize(); i++)
					{
						CPoint s,e;
						Graph* gx = (Graph*)temp->m_Relate.GetAt(i);
						s = gx->m_Start;
						e = gx->m_End;
						if (temp->IsOn(s))
						{
							CPoint mid;
							int l = (temp->m_End.x - temp->m_Start.x) * 0.5;
							mid.SetPoint(temp->m_Start.x+l,temp->m_End.y);
							//gx->SetStartPoint(mid);
							//mid.SetPoint(s.x+(point.x - m_Start1.x),s.y+(point.y - m_Start1.y));
							gx->Follow(mid,1);
						}else if (temp->IsOn(e))
						{
							CPoint mid;
							int l = (temp->m_End.x - temp->m_Start.x) * 0.5;
							mid.SetPoint(temp->m_Start.x+l,temp->m_End.y);
							//gx->SetEndPoint(mid);
							//mid.SetPoint(e.x+(point.x - m_Start1.x),e.y+(point.y - m_Start1.y));
							gx->Follow(mid,2);
						}
					}
				}
				
				

				//pDoc->m_GraphManager.Move(point.x - m_Start1.x, point.y - m_Start1.y);
				m_Start1 = point;
				break;
			}
		case CREATE:
			{
				Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
				if(temp != NULL)
				{
					if(!m_IsControlFlow)
						temp->SetEndPoint( point );
				}
				break;
			}
		case ADJUST_SIZE:
			{
				Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
				if(temp != NULL)
				{
					temp->AdjustSize( point );
				}
				break;
			}
	}

	Invalidate();

	CView::OnMouseMove(nFlags, point);
}

void CUMLObject1View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CUMLObject1Doc* pDoc = GetDocument();

	pDoc->m_GraphManager.SetFocusGraphID(point);

	Graph* temp = pDoc->m_GraphManager.GetFocusGraph();
	m_FocusGraph = temp;
	if(temp != NULL)
	{
		if (temp->Type() == 2)
		{
			m_LDoubleBtnSignal = true;
			CPoint temp1, temp2;
			temp->GetStartPoint(temp1);
			temp->GetEndPoint(temp2);
			CRect rect = CRect(temp1 + CPoint(12, 12), temp2 + CPoint(-12, -12));
			pedit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, 1);
			CString str;
			temp->GetText(str);
			SetDlgItemText(1, str);
		}else if (temp->Type() == 1)
		{
			//m_LDoubleBtnSignal = true;
			EditObject edit;
		    edit.g = temp;   // m_strA��a�༭������ı�����m_strB��b�Ի�������ı�
			edit.DoModal();
		}
	}

	if(m_OperateType == CREATE)
	{
		m_IsControlFlow = false;
		m_OperateType = SELECT;
	}

	CView::OnLButtonDblClk(nFlags, point);
}

void CUMLObject1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CUMLObject1Doc* pDoc = GetDocument();
	
	switch(nChar)
	{
	    case VK_DELETE:
			{
				pDoc->m_GraphManager.DeleteFocusGraph();
				Invalidate();
				break;
			}
		case VK_CONTROL:
			{
				//MessageBox(_T("ctrl"));
				m_CtrlDown = true;
			}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CUMLObject1View::OnObject()
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}
	
	m_IsControlFlow = false;
	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreateRectangle());
}


void CUMLObject1View::OnInterface()
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}

	m_IsControlFlow = false;
	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreateEllipse());
}


void CUMLObject1View::OnPackage()
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}
	
	m_IsControlFlow = false;
	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreatePackage());
}


void CUMLObject1View::OnInherit()//�̳�
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}

	m_IsControlFlow = false;

	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreateArrowLine());
}


void CUMLObject1View::OnComeTrue()
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}

	m_IsControlFlow = false;

	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreateComeTrue());
}


void CUMLObject1View::OnRely()
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}

	m_IsControlFlow = false;

	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreateRely());
}


void CUMLObject1View::OnRelate()
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}

	m_IsControlFlow = false;

	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreateRelate());
}


void CUMLObject1View::OnJuHe()
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}

	m_IsControlFlow = false;

	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreateJuHe());
}


void CUMLObject1View::OnCombine()//����
{
	// TODO: �ڴ���������������
	CUMLObject1Doc* pDoc = GetDocument();
	
	if(m_OperateType != CREATE)
	{
		m_OperateType = CREATE;
	}
	else
	{
		pDoc->m_GraphManager.DeleteFocusGraph();
	}

	m_IsControlFlow = false;

	pDoc->m_GraphManager.AddGraph(pDoc->m_GraphFactory.CreateCombine());
}


void CUMLObject1View::OnLeft()
{
	// TODO: �ڴ���������������
	list<Graph *>::iterator is;
	Graph* l = NULL;//�����ͼ��
	for (is = selectG.begin(); is != selectG.end(); ++is)
	{
		Graph* temp = *is;
		if (l != NULL)
		{
			int ls = l->m_Start.x;
			int temps = temp->m_Start.x;
			if (temps < ls)
			{
				l = temp;
			}
		}else
		{
			l = temp;
		}
	}

	for (is = selectG.begin(); is != selectG.end(); ++is)
	{
		Graph* temp = *is;
		int juli = temp->m_Start.x - l->m_Start.x;
		
		if (temp != l)
		{
			for (int j = 0; j < temp->m_Relate.GetSize(); j++)
			{
				Graph *ct = NULL;
				ct = (Graph *)temp->m_Relate.GetAt(j);
				if (temp->IsOn(ct->m_Start))
				{
					ct->m_Start.SetPoint(ct->m_Start.x - juli,ct->m_Start.y);
					ct->SetStartPoint(ct->m_Start);
				}else if(temp->IsOn(ct->m_End))
				{
					ct->m_End.SetPoint(ct->m_End.x - juli,ct->m_End.y);
					ct->SetEndPoint(ct->m_End);
				}
			}
		}

		CPoint ms,me;
		ms.SetPoint(temp->m_Start.x - juli,temp->m_Start.y);
		me.SetPoint(temp->m_End.x - juli,temp->m_End.y);
		temp->SetStartPoint(ms);
		temp->SetEndPoint(me);
	}

	selectG.clear();

	Invalidate();
}


void CUMLObject1View::OnRight()
{
	// TODO: �ڴ���������������
	list<Graph *>::iterator is;
	Graph* l = NULL;//���ҵ�ͼ��
	for (is = selectG.begin(); is != selectG.end(); ++is)
	{
		Graph* temp = *is;
		if (l != NULL)
		{
			int ls = l->m_End.x;
			int temps = temp->m_End.x;
			if (temps > ls)
			{
				l = temp;
			}
		}else
		{
			l = temp;
		}
	}

	for (is = selectG.begin(); is != selectG.end(); ++is)
	{
		Graph* temp = *is;
		int juli = l->m_End.x - temp->m_End.x;

		if (temp != l)
		{
			for (int j = 0; j < temp->m_Relate.GetSize(); j++)
			{
				Graph *ct = NULL;
				ct = (Graph *)temp->m_Relate.GetAt(j);
				if (temp->IsOn(ct->m_Start))
				{
					ct->m_Start.SetPoint(ct->m_Start.x + juli,ct->m_Start.y);
					ct->SetStartPoint(ct->m_Start);
				}else if(temp->IsOn(ct->m_End))
				{
					ct->m_End.SetPoint(ct->m_End.x + juli,ct->m_End.y);
					ct->SetEndPoint(ct->m_End);
				}
			}
		}

		CPoint ms,me;
		ms.SetPoint(temp->m_Start.x + juli,temp->m_Start.y);
		me.SetPoint(temp->m_End.x + juli,temp->m_End.y);
		temp->SetStartPoint(ms);
		temp->SetEndPoint(me);
	}

	selectG.clear();

	Invalidate();
}


void CUMLObject1View::OnTop()
{
	// TODO: �ڴ���������������
	list<Graph *>::iterator is;
	Graph* l = NULL;//��˵�ͼ��
	for (is = selectG.begin(); is != selectG.end(); ++is)
	{
		Graph* temp = *is;
		if (l != NULL)
		{
			int ls = l->m_Start.y;
			int temps = temp->m_Start.y;
			if (temps < ls)
			{
				l = temp;
			}
		}else
		{
			l = temp;
		}
	}

	for (is = selectG.begin(); is != selectG.end(); ++is)
	{
		Graph* temp = *is;
		int juli = temp->m_Start.y - l->m_Start.y;
		
		if (temp != l)
		{
			for (int j = 0; j < temp->m_Relate.GetSize(); j++)
			{
				Graph *ct = NULL;
				ct = (Graph *)temp->m_Relate.GetAt(j);
				if (temp->IsOn(ct->m_Start))
				{
					ct->m_Start.SetPoint(ct->m_Start.x,ct->m_Start.y - juli);
					ct->SetStartPoint(ct->m_Start);
				}else if(temp->IsOn(ct->m_End))
				{
					ct->m_End.SetPoint(ct->m_End.x,ct->m_End.y - juli);
					ct->SetEndPoint(ct->m_End);
				}
			}
		}

		CPoint ms,me;
		ms.SetPoint(temp->m_Start.x,temp->m_Start.y - juli);
		me.SetPoint(temp->m_End.x,temp->m_End.y - juli);
		temp->SetStartPoint(ms);
		temp->SetEndPoint(me);
	}

	selectG.clear();

	Invalidate();
}


void CUMLObject1View::OnBottom()
{
	// TODO: �ڴ���������������
	list<Graph *>::iterator is;
	Graph* l = NULL;//��׶˵�ͼ��
	for (is = selectG.begin(); is != selectG.end(); ++is)
	{
		Graph* temp = *is;
		if (l != NULL)
		{
			int ls = l->m_End.y;
			int temps = temp->m_End.y;
			if (temps > ls)
			{
				l = temp;
			}
		}else
		{
			l = temp;
		}
	}

	for (is = selectG.begin(); is != selectG.end(); ++is)
	{
		Graph* temp = *is;
		int juli = l->m_End.y - temp->m_End.y;

		if (temp != l)
		{
			for (int j = 0; j < temp->m_Relate.GetSize(); j++)
			{
				Graph *ct = NULL;
				ct = (Graph *)temp->m_Relate.GetAt(j);
				if (temp->IsOn(ct->m_Start))
				{
					ct->m_Start.SetPoint(ct->m_Start.x,ct->m_Start.y + juli);
					ct->SetStartPoint(ct->m_Start);
				}else if(temp->IsOn(ct->m_End))
				{
					ct->m_End.SetPoint(ct->m_End.x,ct->m_End.y + juli);
					ct->SetEndPoint(ct->m_End);
				}
			}
		}

		CPoint ms,me;
		ms.SetPoint(temp->m_Start.x,temp->m_Start.y + juli);
		me.SetPoint(temp->m_End.x,temp->m_End.y + juli);
		temp->SetStartPoint(ms);
		temp->SetEndPoint(me);
	}

	selectG.clear();

	Invalidate();
}
