#pragma once

#include "Graph.h"

class GraphManager
{
public:
	GraphManager();
	~GraphManager();

public:
	void DrawAll(CDC *pdc);
	void DeleteAll();
	void DeleteFocusGraph();
	void DeleteGraphAt(int ID);

	bool SetFocusGraphID(CPoint &pt);
	bool IsAdjustSize(CPoint &pt);
	void AdjustSize(CPoint &pt);
	void Move(int cx, int cy);

	Graph* GetGraphAt(int ID);
	Graph* GetFocusGraph();
	
	void AddGraph(Graph* graph);

	int GetGraphSum();

	void SetRelate(Graph *g);

public:
	CObArray m_Graphs;
	int m_FocusID;
};

