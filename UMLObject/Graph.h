#pragma once

#include "afx.h"
#include "ConnectPoint.h"
#include "list"
#include "Feature.h"
#include "Method.h"

using namespace std;

class Graph :public CObject
{
public:
	// 得到和设置该接口的文字
	virtual void GetText(CString &str);
	virtual void SetText(CString &str);

	// 得到和设置该类的名字
	virtual CString GetName();
	virtual void SetName(CString &str);

	// 得到和设置该图元矩形区域的开始点(左上角)和结束点(右下角)
	virtual void GetStartPoint(CPoint &pt);
	virtual void GetEndPoint(CPoint &pt);
	virtual void SetStartPoint(CPoint &pt);
	virtual void SetEndPoint(CPoint &pt);
	// 是否在该图元区域内
	virtual bool IsIn(CPoint &pt);

	// 是否在该图元边界上
	virtual bool IsOn(CPoint &pt);
	virtual bool IsOn(ConnectPoint *pt);

	// 是否被选中
	virtual bool IsSelected(CPoint &pt);

	// 设置该图元的前赴图元和后继图元
	/*virtual void SetPreviousGraph(Graph *previousGraph);
	virtual void SetNextgraph(Graph *nextGraph);
	virtual Graph* GetPreviousGraph();
	virtual Graph* GetNextgraph();*/

	// 设置该图元是否被标记
	//virtual void SetIsMark(bool isMark);

	virtual void Draw(CDC *pdc) = 0;
	virtual void DrawFocus(CDC *pdc) = 0;
	virtual void Move(int cx, int cy) = 0;
	// 调整图元大小
	virtual void AdjustSize(CPoint &pt);
	virtual void Follow(CPoint &pt,int t);

	virtual void Serialize(CArchive& ar) = 0;

	virtual int Type();

	virtual void Relate(Graph *g);

public:
	Graph();
	~Graph(); 

public:
	bool m_IsMark; // 是否标记
	CPoint m_Start; // 开始点
	CPoint m_End; // 结束点
	CString m_text; // 接口描述文字
	CObArray m_Points; // 该图元包含的所有连接点(ConnentPoint)
	CObArray m_Relate;//包含的关系
	CString m_Name;//类名

	int type;

	list<Feature> feature;
	list<Method> method;
};
