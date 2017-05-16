#include "stdafx.h"
#include "Relate.h"

IMPLEMENT_SERIAL(Relate, CObject, 1)

Relate::Relate(void)
{
	m_AdjustPoint = -1;

	ConnectPoint *temp = NULL; 
	for(int i = 0; i < 2; i++)
	{
		temp = new ConnectPoint();
		m_Points.Add(temp);
	}
}


Relate::~Relate(void)
{
}

void Relate::Draw( CDC *pdc )
{
	AdjustFocusPoint();

	//CPen p, *pOldPen;
	//
	//if(m_IsMark)
	//{
 //       p.CreatePen(PS_SOLID,1,RGB(255,0,0));     //初始化画笔（红色） 
 //       pOldPen=pdc-> SelectObject(&p);     //把画笔选入DC，并保存原来画笔
	//}
	
	pdc->MoveTo(m_Start);
	pdc->LineTo(m_End);

	/*if(m_IsMark)
	{
		pdc->SelectObject(pOldPen);
	}*/
	
    double PI = 3.1415926;  
    double theta = PI/6;//箭头两侧直线与所画直线之间的夹角  
    double len = 20.0;//箭头两侧直线的长度  
    double theta1;//所画直线与水平方向之间的夹角  
    
	theta1 = atan2 (double (m_End.y - m_Start.y), double(m_End.x - m_Start.x));  

    pdc->MoveTo(m_End);  
    pdc->LineTo((int)(m_End.x - len * cos(theta + theta1)), (int)(m_End.y - len * sin(theta + theta1)));  
    pdc->MoveTo(m_End);  
    pdc->LineTo((int)(m_End.x - len * cos(theta1 - theta)), (int)(m_End.y - len * sin(theta1 - theta)));  
}

void Relate::DrawFocus( CDC *pdc )
{	
	ConnectPoint *temp = NULL;
	for(int i = 0; i < m_Points.GetSize(); i++)
	{
	    temp = (ConnectPoint *)m_Points.GetAt(i);
		temp->Draw(pdc);
	}
}

void Relate::Move( int cx, int cy )
{
	m_Start +=  CPoint(cx, cy);
	m_End +=  CPoint(cx, cy);
}

void Relate::AdjustSize( CPoint &pt )
{
	switch(m_AdjustPoint)
	{
		case 1: // 起点
			{
				m_Start = pt;
				break;
			}
		case 2: // 终点
			{
				m_End = pt;
				break;
			}
	}
}


bool Relate::IsEditable()
{
	return false;
}

bool Relate::IsIn( CPoint &pt )
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

bool Relate::IsOn( CPoint &pt )
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

int Relate::GetAdjustPoint()
{
	return m_AdjustPoint;
}

double Relate::GetDistance(int x1, int y1, int x2,int y2)
{
	double distance = 0;

	distance=(double)((x1-x2)*(x1-x2)) + (double)((y1-y2)*(y1-y2));
	distance=sqrt(distance);

	return distance;
}


bool Relate::IsOn(ConnectPoint *pt)
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

void Relate::AdjustFocusPoint()
{
	ConnectPoint *temp = NULL;
	temp = (ConnectPoint *)m_Points.GetAt(0);
	temp->SetPoint(m_Start);
	temp = (ConnectPoint *)m_Points.GetAt(1);
	temp->SetPoint(m_End);
	for(int i = 0; i < 2; i++)
	{
		temp = (ConnectPoint *)m_Points.GetAt(i);
//		temp->SetType(false);
	}
}

void Relate::Serialize(CArchive& ar)
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

int Relate::Type()
{
	return 14;
}

void Relate::Follow( CPoint &pt,int t )
{
	switch(t)
	{
		case 1: // 起点
			{
				m_Start = pt;
				break;
			}
		case 2: // 终点
			{
				m_End = pt;
				break;
			}
	}
}