#pragma once

#include "graph.h"

class CPackage :public Graph
{
	DECLARE_SERIAL(CPackage)

public:
	CPackage(void);
	~CPackage(void);

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

private:
	void AdjustStartAndEnd();
	void AdjustFocusPoint();

private:
	int m_AdjustPoint;
};

