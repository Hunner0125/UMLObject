#include "stdafx.h"
#include "ConnectPoint.h"


IMPLEMENT_SERIAL(ConnectPoint, CObject, 1)

ConnectPoint::ConnectPoint()
{
	m_type = true;
}

ConnectPoint::~ConnectPoint()
{

}

void ConnectPoint::Draw(CDC *pdc)
{
	CBrush brush(RGB(0,255,0));
	CBrush* oldbrush = pdc->SelectObject(&brush);

	if(m_type)
	{
		pdc->Rectangle(CRect(m_Point+CPoint(-3, -3), m_Point+CPoint(3, 3)));
	}
	else
	{
		pdc->Ellipse( CRect(m_Point+CPoint(3, 3), m_Point+CPoint(-3, -3)) );
	}

	pdc->SelectObject(oldbrush);
}

void ConnectPoint::SetType(bool type)
{
	m_type = type;
}

void ConnectPoint::SetPoint(CPoint &pt)
{
	m_Point = pt;
}

CPoint ConnectPoint::GetPoint()
{
	return m_Point;
}

bool ConnectPoint::IsOn(CPoint &pt)
{
	bool flag = false;
	CRect temp = CRect(m_Point+CPoint(-6, -6), m_Point+CPoint(6, 6));
	if(temp.PtInRect(pt))
	{
		flag = true;
	}
	return flag;
}

void ConnectPoint::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar<<m_Point;
	}
	else
	{
		ar>>m_Point;
	}
}