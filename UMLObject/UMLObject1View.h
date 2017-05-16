
// UMLObject1View.h : CUMLObject1View ��Ľӿ�
//

#pragma once

#include "GraphManager.h"
#include "GraphFactory.h"
#include <string>
#include "Graph.h"
#include "EditObject.h"
#include "list"

class CUMLObject1View : public CView
{
protected: // �������л�����
	CUMLObject1View();
	DECLARE_DYNCREATE(CUMLObject1View)

// ����
public:
	CUMLObject1Doc* GetDocument() const;

	CPoint m_Start1;//ͼ���ƶ�

	int m_OperateType;
	enum OPERATE_TYPE{SELECT, MOVE, CREATE, ADJUST_SIZE};

	bool m_LBtnSignal;
	bool m_LDoubleBtnSignal;
	bool m_IsControlFlow;
	bool m_CtrlDown;

	Graph* m_FocusGraph;

	CEdit *pedit;

	list<Graph *> selectG;//ͼ������

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CUMLObject1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnObject();
	afx_msg void OnInterface();
	
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPackage();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnInherit();
	afx_msg void OnComeTrue();
	afx_msg void OnRely();
	afx_msg void OnRelate();
	afx_msg void OnJuHe();
	afx_msg void OnCombine();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnTop();
	afx_msg void OnBottom();
};

#ifndef _DEBUG  // UMLObject1View.cpp �еĵ��԰汾
inline CUMLObject1Doc* CUMLObject1View::GetDocument() const
   { return reinterpret_cast<CUMLObject1Doc*>(m_pDocument); }
#endif

