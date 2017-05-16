#pragma once

#include "Graph.h"
#include "ConnectPoint.h"
#include <iostream>
#include "GraphManager.h"

class CRectangle :public Graph
{
	DECLARE_SERIAL(CRectangle)

public:
	CRectangle(void);
	~CRectangle(void);

public:
	void Draw( CDC *pdc );
	void DrawFocus( CDC *pdc );
	void Move( int cx, int cy );
	void AdjustSize( CPoint &pt );

	void Serialize(CArchive& ar);

	bool IsIn( CPoint &pt );
	bool IsOn( CPoint &pt );
	bool IsOn(ConnectPoint *pt);

	int GetAdjustPoint();

	int Type();

	void Relate(Graph *g);

private:
	void AdjustStartAndEnd();
	void AdjustFocusPoint();

private:
	int m_AdjustPoint;
	//GraphManager m_GraphManager;
};

