#include "stdafx.h"
#include "GraphFactory.h"

#include "Rectangle.h"
#include "Ellipse.h"
#include "Line.h"
#include "Arrowhead.h"
#include "Package.h"
#include "ComeTrue.h"
#include "Rely.h"
#include "Relate.h"
#include "JuHe.h"
#include "Combine.h"

GraphFactory::GraphFactory(void)
{
}


GraphFactory::~GraphFactory(void)
{
}

Graph* GraphFactory::CreateRectangle()
{
	return new CRectangle();
}

Graph* GraphFactory::CreateLine()
{
	return new Line();
}

Graph* GraphFactory::CreateArrowLine()
{
	return new Arrowhead();
}

Graph* GraphFactory::CreateEllipse()
{
	return new CEllipse();
}

Graph* GraphFactory::CreatePackage()
{
	return new CPackage();
}

Graph* GraphFactory::CreateComeTrue()
{
	return new ComeTrue();
}

Graph* GraphFactory::CreateRely()
{
	return new Rely();
}

Graph* GraphFactory::CreateRelate()
{
	return new Relate();
}

Graph* GraphFactory::CreateJuHe()
{
	return new JuHe();
}

Graph* GraphFactory::CreateCombine()
{
	return new Combine();
}