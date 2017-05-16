#include "stdafx.h"
#include "GraphManager.h"


GraphManager::GraphManager()
{
	m_FocusID = -1;
}

GraphManager::~GraphManager()
{
}

void GraphManager::DrawAll( CDC *pdc )
{
	/*for(int i = GetGraphSum(); i > 0; i--)
	{
		GetGraphAt(i-1)->Draw( pdc );
		if(m_FocusID == i-1)
		{
			GetGraphAt(i-1)->DrawFocus( pdc );
		}
	}*/
	//CheckLinkGraph();

	for(int i = 0; i < GetGraphSum(); i++)
	{
		GetGraphAt(i)->Draw(pdc);
		//if(GetGraphAt(i)->IsControlFlow())
			//CheckLinkGraph(GetGraphAt(i));
	}

	Graph *temp = GetFocusGraph();
	if(temp != NULL)
	{
		temp->Draw(pdc);
		temp->DrawFocus(pdc);
	}
}

Graph* GraphManager::GetGraphAt( int ID )
{
	Graph* temp = NULL;
	if((ID >= 0) && (ID < GetGraphSum()))
	{
		temp = (Graph*)m_Graphs.GetAt( ID );
	}
	return temp;
}

int GraphManager::GetGraphSum()
{
	return m_Graphs.GetSize();
}

void GraphManager::DeleteFocusGraph()
{
	if((m_FocusID >= 0) && (m_FocusID < GetGraphSum()))
	{
		Graph* tempF = GetGraphAt(m_FocusID);  //ÒªÉ¾³ýµÄÍ¼ÐÎ

		/*for(int i = 0; i < GetGraphSum(); i++)
		{
			Graph *temp = GetGraphAt(i);

			if(temp->GetPreviousGraph() == tempF || temp->GetNextgraph() == tempF)
			{
				DeleteGraphAt(i);
			}
		}*/

		if (tempF->m_Relate.GetSize() != 0)
		{
			//int num = tempF->m_Relate.GetSize();
			for (int i = 0; i <tempF->m_Relate.GetSize(); i++)
			{
				Graph* gx = (Graph*)tempF->m_Relate.GetAt(i);
				for (int j = 0; j < GetGraphSum(); j++)
				{
					Graph *temp = GetGraphAt(j);
					if (temp == gx)
					{
						DeleteGraphAt(j);
					}
					/*if (temp->m_Relate.IsEmpty() == false)
					{
						for (int k = 0; k < temp->m_Relate.GetSize(); k++)
						{
							if (gx == temp->m_Relate.GetAt(k))
							{
								temp->m_Relate.RemoveAt(k);
							}
						}
					}*/
				}
			}
		}

		tempF->m_Relate.RemoveAll();
		DeleteGraphAt(m_FocusID);

		m_FocusID = -1;
	}
}

void GraphManager::DeleteGraphAt( int ID )
{
	if((ID >= 0) && (ID < GetGraphSum()))
	{
		//Graph* temp = (Graph*)m_Graphs.GetAt(ID);
		//if(temp != NULL)
			//delete temp;
		m_Graphs.RemoveAt( ID );
	}
}

Graph* GraphManager::GetFocusGraph()
{
	Graph* temp = NULL;
	if((m_FocusID >= 0) && (m_FocusID < GetGraphSum()))
	{
		temp = (Graph*)m_Graphs.GetAt( m_FocusID );
	}

	return temp;
}

void GraphManager::AddGraph(Graph* graph)
{
	m_Graphs.InsertAt(0, graph, 1);
	m_FocusID = 0;
}


bool GraphManager::SetFocusGraphID( CPoint &pt )
{
	Graph* temp1 = GetFocusGraph();
	Graph* temp = NULL;
	for(int i = 0; i < GetGraphSum(); i++)
	{
		temp = GetGraphAt(i);
		if(temp->IsSelected(pt))
		{
			if(temp1 != temp)
			{
				DeleteGraphAt( i );
				m_Graphs.InsertAt(0, temp, 1);
				m_FocusID = 0;
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	m_FocusID = -1;
	return true;
}

bool GraphManager::IsAdjustSize( CPoint &pt )
{
	Graph* temp = GetFocusGraph();
	bool flag = false;
	
	if(temp != NULL)
	{
		if(temp->IsOn( pt ))
		{
			flag = true;
		}
	}

	return flag;
}

void GraphManager::AdjustSize( CPoint &pt )
{
	Graph* focusGraph = GetFocusGraph();
	if(focusGraph != NULL)
	{
		focusGraph->AdjustSize( pt );
	}
}

void GraphManager::Move(int cx, int cy)
{
	Graph* tempF = GetFocusGraph();

	if(tempF != NULL)
	{
		tempF->Move(cx, cy);

		/*CObArray relate = tempF->m_Relate;
		for (int i = 0; i < relate.GetSize(); i++)
		{
			CPoint s,e;

		}*/

		/*if(!temp->IsControlFlow())
		{
		}*/
		/*for(int i = 0; i < GetGraphSum(); i++)
		{
			Graph* temp = GetGraphAt(i);
			if(temp->GetPreviousGraph() == tempF)
			{
				CPoint tempPoint;
				temp->GetEndPoint(tempPoint);
				temp->SetEndPoint(tempPoint + CPoint(cx, cy));
			}

			if(temp->GetNextgraph() == tempF)
			{
				CPoint tempPoint;
				temp->GetStartPoint(tempPoint);
				temp->SetStartPoint(tempPoint + CPoint(cx, cy));
			}
		}*/
	}
}


void GraphManager::SetRelate(Graph *g)
{
	for (int i = 0; i < GetGraphSum(); i++)
	{
		Graph* temp = GetGraphAt(i);
		int type = temp->Type();
		if (type == 11||type == 12||type == 13||type == 14||type == 15||type == 16)
		{
			if (g->IsOn(temp->m_Start)||g->IsOn(temp->m_End))
			{
				g->Relate(temp);
			}
		}
	}
}
