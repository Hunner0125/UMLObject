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
	// �õ������øýӿڵ�����
	virtual void GetText(CString &str);
	virtual void SetText(CString &str);

	// �õ������ø��������
	virtual CString GetName();
	virtual void SetName(CString &str);

	// �õ������ø�ͼԪ��������Ŀ�ʼ��(���Ͻ�)�ͽ�����(���½�)
	virtual void GetStartPoint(CPoint &pt);
	virtual void GetEndPoint(CPoint &pt);
	virtual void SetStartPoint(CPoint &pt);
	virtual void SetEndPoint(CPoint &pt);
	// �Ƿ��ڸ�ͼԪ������
	virtual bool IsIn(CPoint &pt);

	// �Ƿ��ڸ�ͼԪ�߽���
	virtual bool IsOn(CPoint &pt);
	virtual bool IsOn(ConnectPoint *pt);

	// �Ƿ�ѡ��
	virtual bool IsSelected(CPoint &pt);

	// ���ø�ͼԪ��ǰ��ͼԪ�ͺ��ͼԪ
	/*virtual void SetPreviousGraph(Graph *previousGraph);
	virtual void SetNextgraph(Graph *nextGraph);
	virtual Graph* GetPreviousGraph();
	virtual Graph* GetNextgraph();*/

	// ���ø�ͼԪ�Ƿ񱻱��
	//virtual void SetIsMark(bool isMark);

	virtual void Draw(CDC *pdc) = 0;
	virtual void DrawFocus(CDC *pdc) = 0;
	virtual void Move(int cx, int cy) = 0;
	// ����ͼԪ��С
	virtual void AdjustSize(CPoint &pt);
	virtual void Follow(CPoint &pt,int t);

	virtual void Serialize(CArchive& ar) = 0;

	virtual int Type();

	virtual void Relate(Graph *g);

public:
	Graph();
	~Graph(); 

public:
	bool m_IsMark; // �Ƿ���
	CPoint m_Start; // ��ʼ��
	CPoint m_End; // ������
	CString m_text; // �ӿ���������
	CObArray m_Points; // ��ͼԪ�������������ӵ�(ConnentPoint)
	CObArray m_Relate;//�����Ĺ�ϵ
	CString m_Name;//����

	int type;

	list<Feature> feature;
	list<Method> method;
};
