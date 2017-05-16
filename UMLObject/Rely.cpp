#include "stdafx.h"
#include "Rely.h"

IMPLEMENT_SERIAL(Rely, CObject, 1)

Rely::Rely(void)
{
	m_AdjustPoint = -1;

	ConnectPoint *temp = NULL; 
	for(int i = 0; i < 2; i++)
	{
		temp = new ConnectPoint();
		m_Points.Add(temp);
	}
}


Rely::~Rely(void)
{
}

void Rely::Draw( CDC *pdc )
{
	AdjustFocusPoint();

	//CPen p, *pOldPen;
	//
	//if(m_IsMark)
	//{
 //       p.CreatePen(PS_SOLID,1,RGB(255,0,0));     //��ʼ�����ʣ���ɫ�� 
 //       pOldPen=pdc-> SelectObject(&p);     //�ѻ���ѡ��DC��������ԭ������
	//}

	
	CPen *oPen;
	CPen op[2];
    op[0].CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); //����ʵ�ֻ���
    op[1].CreatePen(PS_DASH, 1, RGB(0, 0, 0));//�������߻���
	
	oPen = pdc->SelectObject(&op[1]);
	pdc->MoveTo(m_Start);
	pdc->LineTo(m_End);
	
	oPen = pdc->SelectObject(&op[0]);

	/*if(m_IsMark)
	{
		pdc->SelectObject(pOldPen);
	}*/
	
    double PI = 3.1415926;  
    double theta = PI/6;//��ͷ����ֱ��������ֱ��֮��ļн�  
    double len = 20.0;//��ͷ����ֱ�ߵĳ���  
    double theta1;//����ֱ����ˮƽ����֮��ļн�  
    
	theta1 = atan2 (double (m_End.y - m_Start.y), double(m_End.x - m_Start.x));  

    pdc->MoveTo(m_End);  
    pdc->LineTo((int)(m_End.x - len * cos(theta + theta1)), (int)(m_End.y - len * sin(theta + theta1)));  
    pdc->MoveTo(m_End);  
    pdc->LineTo((int)(m_End.x - len * cos(theta1 - theta)), (int)(m_End.y - len * sin(theta1 - theta)));  
}

void Rely::DrawFocus( CDC *pdc )
{	
	ConnectPoint *temp = NULL;
	for(int i = 0; i < m_Points.GetSize(); i++)
	{
	    temp = (ConnectPoint *)m_Points.GetAt(i);
		temp->Draw(pdc);
	}
}

void Rely::Move( int cx, int cy )
{
	m_Start +=  CPoint(cx, cy);
	m_End +=  CPoint(cx, cy);
}

void Rely::AdjustSize( CPoint &pt )
{
	switch(m_AdjustPoint)
	{
		case 1: // ���
			{
				m_Start = pt;
				break;
			}
		case 2: // �յ�
			{
				m_End = pt;
				break;
			}
	}
}


bool Rely::IsEditable()
{
	return false;
}

bool Rely::IsIn( CPoint &pt )
{
	bool flag = false;

	CPoint points[4];
	int tempx = 0;
	int tempy = 0;
	if(abs(m_End.x - m_Start.x) > abs(m_End.y - m_Start.y))
	{
		tempy = 6;
	}
	else
	{
		tempx = 6;
	}
	
	CPoint temp = CPoint(tempx, tempy);
	points[0] = m_Start - temp;
	points[1] = m_Start + temp;
	points[2] = m_End + temp;
	points[3] = m_End - temp;

	CRgn cr;
	cr.CreatePolygonRgn(points, 4, ALTERNATE);
	if(cr.PtInRegion( pt ))
	{
		flag = true;
		m_AdjustPoint = -1;
	}

	return flag;
}

bool Rely::IsOn( CPoint &pt )
{
	bool flag = false;
	ConnectPoint *temp = NULL;
	for(int i = 0; i < 2; i++)
	{
	    temp = (ConnectPoint *)m_Points.GetAt(i);
		if(temp->IsOn(pt))
		{
			m_AdjustPoint = 1+i;
		    flag = true;
		}
	}

	return flag;
}

int Rely::GetAdjustPoint()
{
	return m_AdjustPoint;
}

double Rely::GetDistance(int x1, int y1, int x2,int y2)
{
	double distance = 0;

	distance=(double)((x1-x2)*(x1-x2)) + (double)((y1-y2)*(y1-y2));
	distance=sqrt(distance);

	return distance;
}


bool Rely::IsOn(ConnectPoint *pt)
{
	ConnectPoint *temp = NULL;
	for(int i = 0; i < 2; i++)
	{
	    temp = (ConnectPoint *)m_Points.GetAt(i);
		if(temp->IsOn(pt->GetPoint()))
		{
			pt->SetPoint(temp->GetPoint());
		    return true;
		}
	}
	return false;
}

void Rely::AdjustFocusPoint()
{
	ConnectPoint *temp = NULL;
	temp = (ConnectPoint *)m_Points.GetAt(0);
	temp->SetPoint(m_Start);
	temp = (ConnectPoint *)m_Points.GetAt(1);
	temp->SetPoint(m_End);
	for(int i = 0; i < 2; i++)
	{
		temp = (ConnectPoint *)m_Points.GetAt(i);
		temp->SetType(false);
	}
}

void Rely::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar<<m_Start<<m_End<<m_text<<m_AdjustPoint;
	}
	else
	{
		ar>>m_Start>>m_End>>m_text>>m_AdjustPoint;
	}
}

int Rely::Type()
{
	return 13;
}

void Rely::Follow( CPoint &pt,int t )
{
	switch(t)
	{
		case 1: // ���
			{
				m_Start = pt;
				break;
			}
		case 2: // �յ�
			{
				m_End = pt;
				break;
			}
	}
}