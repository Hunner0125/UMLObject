#include "stdafx.h"
#include "Line.h"

IMPLEMENT_SERIAL(Line, CObject, 1)

Line::Line(void)
{
}


Line::~Line(void)
{
}

void Line::Draw( CDC *pdc )
{
	pdc->MoveTo(m_Start);
	pdc->LineTo(m_End);
}

void Line::DrawFocus( CDC *pdc )
{	
	CBrush brush(RGB(0,255,0));
	CBrush* oldbrush = pdc->SelectObject(&brush);

	pdc->Ellipse( CRect(m_Start+CPoint(3, 3), m_Start+CPoint(-3, -3)) );
	pdc->Ellipse( CRect(m_End+CPoint(3, 3), m_End+CPoint(-3, -3)) );

	pdc->SelectObject(oldbrush);
}

void Line::Move( int cx, int cy )
{
	m_Start +=  CPoint(cx, cy);
	m_End +=  CPoint(cx, cy);
}

void Line::AdjustSize( CPoint &pt )
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

void Line::GetStartPoint( CPoint &pt )
{
	pt = m_Start;
}

void Line::GetEndPoint( CPoint &pt )
{
	pt = m_End;
}

void Line::SetStartPoint( CPoint &pt )
{
	m_Start = pt;
}

void Line::SetEndPoint( CPoint &pt )
{
	m_End = pt;
}

bool Line::IsSelected( CPoint &pt )
{
	return (IsIn( pt ) || IsOn( pt ));
}

bool Line::IsIn( CPoint &pt )
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

bool Line::IsOn( CPoint &pt )
{
	bool flag = false;
	CRect temp1 = CRect(m_Start+CPoint(-6, -6), m_Start+CPoint(6, 6));
	CRect temp2 = CRect(m_End+CPoint(-6, -6), m_End+CPoint(6, 6));

	if(temp1.PtInRect(pt))
	{ // 起点
		m_AdjustPoint = 1;
		flag = true;
	}
	else if(temp2.PtInRect(pt))
	{ // 终点
		m_AdjustPoint = 2;
		flag = true;
	}

	return flag;
}

bool Line::IsEditable()
{
	return false;
}

int Line::GetAdjustPoint()
{
	return m_AdjustPoint;
}

void Line::Serialize(CArchive& ar)
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