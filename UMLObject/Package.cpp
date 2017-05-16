#include "stdafx.h"
#include "Package.h"

IMPLEMENT_SERIAL(CPackage, CObject, 1)

CPackage::CPackage(void)
{
	m_AdjustPoint = -1;

	ConnectPoint *temp = NULL; 
	for(int i = 0; i < 8; i++)
	{
		temp = new ConnectPoint();
		m_Points.Add(temp);
	}
}


CPackage::~CPackage(void)
{
}

void CPackage::Draw( CDC *pdc )
{
	AdjustFocusPoint();

	//CPen p, *pOldPen;     
	//if(m_IsMark)
	//{
 //       p.CreatePen(PS_SOLID,1,RGB(255,0,0));     //初始化画笔（红色） 
 //       pOldPen=pdc-> SelectObject(&p);     //把画笔选入DC，并保存原来画笔
	//}

	//pdc->Rectangle( CRect(m_Start, m_End) );
	CPoint m1,n1;

	int kuan = (m_End.y - m_Start.y) * 0.15;
	int chang = (m_End.x - m_Start.x) * 0.15;
	
	m1.SetPoint(m_Start.x+chang,m_Start.y+kuan);
	pdc->Rectangle( CRect(m_Start, m1) );

	n1.SetPoint(m_Start.x,m1.y);
	pdc->Rectangle( CRect(n1, m_End) );
	
	/*if(m_IsMark)
	{
		pdc->SelectObject(pOldPen);
	}*/

	//pdc->DrawText(m_text, CRect(m_Start+CPoint(8, 8), m_End+CPoint(-8, -8)), DT_CENTER);
}

void CPackage::DrawFocus( CDC *pdc )
{
	ConnectPoint *temp = NULL;
	for(int i = 0; i < m_Points.GetSize(); i++)
	{
	    temp = (ConnectPoint *)m_Points.GetAt(i);
		temp->Draw(pdc);
	}
}

void CPackage::Move( int cx, int cy )
{
	m_Start +=  CPoint(cx, cy);
	m_End +=  CPoint(cx, cy);
}

void CPackage::AdjustSize( CPoint &pt )
{
	switch(m_AdjustPoint)
	{
		case 1:
		case 2:
			{
				m_Start = pt;
				break;
			}
		case 3:
		case 4:
			{
				m_End = pt;
				break;
			}
		case 5:
			{
				m_Start.y = pt.y;
				break;
			}
		case 6:
			{
				m_End.x = pt.x;
				break;
			}
		case 7:
			{
				m_End.y = pt.y;
				break;
			}
		case 8:
			{
				m_Start.x = pt.x;
				break;
			}
	}
}

bool CPackage::IsIn( CPoint &pt )
{
	AdjustStartAndEnd();

	bool flag = false;
	CRect temp = CRect( m_Start, m_End );
	if(temp.PtInRect( pt ))
	{
		flag = true;
		m_AdjustPoint = -1;
	}
	return flag;
}

bool CPackage::IsOn(ConnectPoint *pt)
{
	ConnectPoint *temp = NULL;
	for(int i = 0; i < 8; i++)
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

bool CPackage::IsOn( CPoint &pt )
{
	AdjustStartAndEnd();

	bool flag = false;
	CPoint temp1 = CPoint( m_Start.x, m_End.y );
	CPoint temp2 = CPoint(m_End.x, m_Start.y);

	ConnectPoint *temp = NULL;
	for(int i = 0; i < 8; i++)
	{
	    temp = (ConnectPoint *)m_Points.GetAt(i);
		if(temp->IsOn(pt))
		{
			if(i == 1 || i == 2)
			{
				m_Start = temp1;
				m_End = temp2;
			}
			m_AdjustPoint = 1+i;
		    flag = true;
		}
	}

	return flag;
}

void CPackage::AdjustStartAndEnd()
{
	CPoint temp1, temp2;
	if((m_End.x < m_Start.x) && (m_End.y < m_Start.y))
	{
		temp1 = m_Start;
		m_Start = m_End;
		m_End = temp1;
	}
	else if(!((m_End.x > m_Start.x) && (m_End.y > m_Start.y)))
	{
		temp1 = CPoint( m_End.x, m_Start.y );
		temp2 = CPoint( m_Start.x, m_End.y );
		m_Start = temp1;
		m_End = temp2;
	}

	AdjustFocusPoint();
}

int CPackage::GetAdjustPoint()
{
	return m_AdjustPoint;
}

void CPackage::AdjustFocusPoint()
{
	ConnectPoint *temp = NULL;
	temp = (ConnectPoint *)m_Points.GetAt(0);
	temp->SetPoint(m_Start);
	temp = (ConnectPoint *)m_Points.GetAt(1);
	temp->SetPoint(CPoint(m_Start.x, m_End.y));
	temp = (ConnectPoint *)m_Points.GetAt(2);
	temp->SetPoint(CPoint(m_End.x, m_Start.y));
	temp = (ConnectPoint *)m_Points.GetAt(3);
	temp->SetPoint(m_End);
	for(int i = 0; i < 4; i++)
	{
		temp = (ConnectPoint *)m_Points.GetAt(i);
		temp->SetType(false);
	}

	temp = (ConnectPoint *)m_Points.GetAt(4);
	temp->SetPoint(CPoint( (m_Start.x+m_End.x)/2, m_Start.y ));
	temp = (ConnectPoint *)m_Points.GetAt(5);
	temp->SetPoint(CPoint( m_End.x, (m_Start.y+m_End.y)/2 ));
	temp = (ConnectPoint *)m_Points.GetAt(6);
	temp->SetPoint(CPoint( (m_Start.x+m_End.x)/2, m_End.y ));
	temp = (ConnectPoint *)m_Points.GetAt(7);
	temp->SetPoint(CPoint( m_Start.x, (m_Start.y+m_End.y)/2 ));
}

void CPackage::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar<<m_Start<<m_End<<m_text<<m_AdjustPoint;
	}
	else
	{
		ar>>m_Start>>m_End>>m_text>>m_AdjustPoint;
	}

	m_Points.Serialize(ar);
}


int CPackage::Type()
{
	return 3;
}