#include "stdafx.h"
#include "Graph.h"


Graph::Graph()
{
	m_Start = CPoint(0, 0);
	m_End = CPoint(0, 0);
	m_IsMark = false;
}

Graph::~Graph()
{
}

void Graph::GetText(CString &str)
{
	str = m_text;
}

void Graph::SetText(CString &str)
{
	m_text = str;
}

CString Graph::GetName()
{
	return m_Name;
}

void Graph::SetName(CString &str)
{
	m_Name = str;
}

//void Graph::GetPro(CString &str1,CString &str2)
//{
//	str1 = m_Pro[0];
//	str2 = m_Pro[1];
//}
//
//void Graph::SetPro(CString &str1,CString &str2)
//{
//	m_Pro[0] = str1;
//	m_Pro[1] = str2;
//}
//
//void Graph::GetMethod(CString &str1,CString &str2)
//{
//	str1 = m_Method[0];
//	str2 = m_Method[1];
//}
//
//void Graph::SetMethod(CString &str1,CString &str2)
//{
//	m_Method[0] = str1;
//	m_Method[1] = str2;
//}

// 得到和设置该图元矩形区域的开始点(左上角)和结束点(右下角)
void Graph::GetStartPoint(CPoint &pt)
{
	pt = m_Start;
}

void Graph::GetEndPoint(CPoint &pt)
{
	pt = m_End;
}

void Graph::SetStartPoint(CPoint &pt)
{
	m_Start = pt;
}

void Graph::SetEndPoint(CPoint &pt)
{
	m_End = pt;
}
// 是否在该图元区域内
bool Graph::IsIn(CPoint &pt)
{
	return false;
}
// 是否在该图元边界上
bool Graph::IsOn(CPoint &pt)
{
	return false;
}

bool Graph::IsOn(ConnectPoint *pt)
{
	return false;
}

//void Graph::SetPreviousGraph(Graph *previousGraph)
//{
//}
//void Graph::SetNextgraph(Graph *nextGraph)
//{
//}
//
//Graph* Graph::GetPreviousGraph()
//{ 
//	return NULL;
//}
//
//Graph* Graph::GetNextgraph()
//{ 
//	return NULL;
//}

//void Graph::SetIsMark(bool isMark)
//{
//	m_IsMark = isMark;
//}

bool Graph::IsSelected( CPoint &pt )
{
	return (IsIn( pt ) || IsOn( pt ));
}

void Graph::AdjustSize(CPoint &pt)
{
}

int Graph::Type()
{
	return 0;
}

void Graph::Relate(Graph *g)
{
}


void Graph::Follow(CPoint &pt,int t)
{
}
