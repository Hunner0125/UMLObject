#pragma once

#include "graph.h"
#include <math.h>

class Arrowhead :public Graph
{

	DECLARE_SERIAL(Arrowhead)
public:
	Arrowhead();
	~Arrowhead();

public:
	void Draw(CDC *pdc);
	void DrawFocus(CDC *pdc);
	void Move(int cx, int cy);
	void AdjustSize(CPoint &pt);
	void Follow(CPoint &pt,int t);

	void Serialize(CArchive& ar);

	bool IsIn(CPoint &pt);
	bool IsOn(CPoint &pt);
	bool IsOn(ConnectPoint *pt);

	bool IsEditable();

	/*void SetPreviousGraph(Graph *previousGraph);
	void SetNextgraph(Graph *nextGraph);
	Graph* GetPreviousGraph();
	Graph* GetNextgraph();*/

	int GetAdjustPoint();

	int Type();

private:
	void AdjustFocusPoint();
	double GetDistance(int x1, int y1, int x2,int y2);
	void DrawArrow( CDC *pdc );

private:
	int m_FocusPoint;
	int m_AdjustPoint;

	/*Graph* m_Previous;
	Graph* m_Next;*/
};

