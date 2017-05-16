
// UMLObject1Doc.h : CUMLObject1Doc ��Ľӿ�
//


#pragma once

#include "GraphManager.h"
#include "GraphFactory.h"


class CUMLObject1Doc : public CDocument
{
protected: // �������л�����
	CUMLObject1Doc();
	DECLARE_DYNCREATE(CUMLObject1Doc)

// ����
public:
	GraphManager m_GraphManager;
	GraphFactory m_GraphFactory;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CUMLObject1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
