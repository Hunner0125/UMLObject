#pragma once

#include "Graph.h"

class GraphFactory
{
public:
	GraphFactory();
	~GraphFactory();

public:
	Graph* CreateRectangle();
	Graph* CreateLine();
	Graph* CreateArrowLine();
	Graph* CreateEllipse();
	Graph* CreatePackage();
	Graph* CreateComeTrue();
	Graph* CreateRely();
	Graph* CreateRelate();
	Graph* CreateJuHe();
	Graph* CreateCombine();
};

