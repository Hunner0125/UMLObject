#pragma once

#include "graph.h"
#include <math.h>

class Relate :public Graph
{
	DECLARE_SERIAL(Relate)
public:
	Relate(void);
	~Relate(void);

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

	int GetAdjustPoint();

	int Type();

private:
	void AdjustFocusPoint();
	double GetDistance(int x1, int y1, int x2,int y2);

private:
	int m_FocusPoint;
	int m_AdjustPoint;
};

