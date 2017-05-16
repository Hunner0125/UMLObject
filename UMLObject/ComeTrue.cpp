#include "stdafx.h"
#include "ComeTrue.h"

IMPLEMENT_SERIAL(ComeTrue, CObject, 1)

ComeTrue::ComeTrue(void)
{
	m_AdjustPoint = -1;

	ConnectPoint *temp = NULL; 
	for(int i = 0; i < 2; i++)
	{
		temp = new ConnectPoint();
		m_Points.Add(temp);
	}
}


ComeTrue::~ComeTrue(void)
{
}

void ComeTrue::Draw( CDC *pdc )
{
	AdjustFocusPoint();

//	CPen p, *pOldPen;
	
	//if(m_IsMark)
	//{
 //       p.CreatePen(PS_SOLID,1,RGB(255,0,0));     //初始化画笔（红色） 
 //       pOldPen=pdc-> SelectObject(&p);     //把画笔选入DC，并保存原来画笔
	//}

	
	CPen *oPen;
	CPen op[2];
    op[0].CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); //创建实现画笔
    op[1].CreatePen(PS_DASH, 1, RGB(0, 0, 0));//创建虚线画笔
	
	oPen = pdc->SelectObject(&op[1]);
	pdc->MoveTo(m_Start);
	pdc->LineTo(m_End);
	
	oPen = pdc->SelectObject(&op[0]);

	/*if(m_IsMark)
	{
		pdc->SelectObject(pOldPen);
	}*/

	DrawArrow(pdc);
	
 //   double PI = 3.1415926;  
 //   double theta = PI/6;//箭头两侧直线与所画直线之间的夹角  
 //   double len = 20.0;//箭头两侧直线的长度  
 //   double theta1;//所画直线与水平方向之间的夹角  
 //   
	//theta1 = atan2 (double (m_End.y - m_Start.y), double(m_End.x - m_Start.x));  

 //   pdc->MoveTo(m_End);  
 //   pdc->LineTo((int)(m_End.x - len * cos(theta + theta1)), (int)(m_End.y - len * sin(theta + theta1)));  
 //   pdc->MoveTo(m_End);  
 //   pdc->LineTo((int)(m_End.x - len * cos(theta1 - theta)), (int)(m_End.y - len * sin(theta1 - theta)));  
}

void ComeTrue::DrawFocus( CDC *pdc )
{	
	ConnectPoint *temp = NULL;
	for(int i = 0; i < m_Points.GetSize(); i++)
	{
	    temp = (ConnectPoint *)m_Points.GetAt(i);
		temp->Draw(pdc);
	}
}

void ComeTrue::Move( int cx, int cy )
{
	m_Start +=  CPoint(cx, cy);
	m_End +=  CPoint(cx, cy);
}

void ComeTrue::AdjustSize( CPoint &pt )
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


bool ComeTrue::IsEditable()
{
	return false;
}

bool ComeTrue::IsIn( CPoint &pt )
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

bool ComeTrue::IsOn( CPoint &pt )
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

int ComeTrue::GetAdjustPoint()
{
	return m_AdjustPoint;
}

double ComeTrue::GetDistance(int x1, int y1, int x2,int y2)
{
	double distance = 0;

	distance=(double)((x1-x2)*(x1-x2)) + (double)((y1-y2)*(y1-y2));
	distance=sqrt(distance);

	return distance;
}

void ComeTrue::DrawArrow( CDC *pdc )
{
	int flSx = m_Start.x;
	int flSy = m_Start.y;
	int flEx = m_End.x;
	int flEy = m_End.y;
	double flLength = 10;
	double flAngle = 40;

	if(GetDistance(flSx, flSy, flEx, flEy) == 0) return;   
			
	double tmpX = flEx + (flSx - flEx) * flLength/GetDistance(flSx, flSy, flEx, flEy);   
	double tmpY = flEy + (flSy - flEy) * flLength/GetDistance(flSx, flSy, flEx, flEy);   
	double fl1X = (tmpX - flEx) * cos(-flAngle/2) - (tmpY - flEy) * sin(-flAngle/2) + flEx;   
	double fl1Y = (tmpY - flEy) * cos(-flAngle/2) + (tmpX - flEx) * sin(-flAngle/2) + flEy;   
	double fl2X = (tmpX - flEx) * cos(flAngle/2) - (tmpY - flEy) * sin(flAngle/2) + flEx;   
	double fl2Y = (tmpY - flEy) * cos(flAngle/2) + (tmpX - flEx) * sin(flAngle/2) + flEy;   
	CPoint aPoint((int)fl1X, (int)fl1Y);
	CPoint bPoint((int)fl2X, (int)fl2Y);
	CPoint points[]={aPoint, bPoint, m_End};

	CBrush *pBrush = new CBrush;
	CBrush *oldBrush;
	pBrush->CreateSolidBrush(RGB(255,255,255));

	oldBrush = pdc->SelectObject(pBrush);
	pdc->Polygon(points, 3);
	pdc->SelectObject(oldBrush);
}

bool ComeTrue::IsOn(ConnectPoint *pt)
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

void ComeTrue::AdjustFocusPoint()
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

void ComeTrue::Serialize(CArchive& ar)
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

int ComeTrue::Type()
{
	return 12;
}

void ComeTrue::Follow( CPoint &pt,int t )
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