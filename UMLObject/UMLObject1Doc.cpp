
// UMLObject1Doc.cpp : CUMLObject1Doc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "UMLObject1.h"
#endif

#include "UMLObject1Doc.h"
#include "UMLObject1View.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CUMLObject1Doc

IMPLEMENT_DYNCREATE(CUMLObject1Doc, CDocument)

BEGIN_MESSAGE_MAP(CUMLObject1Doc, CDocument)
END_MESSAGE_MAP()


// CUMLObject1Doc ����/����

CUMLObject1Doc::CUMLObject1Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CUMLObject1Doc::~CUMLObject1Doc()
{
}

BOOL CUMLObject1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle(_T("UML��ͼ�༭��"));

	return TRUE;
}




// CUMLObject1Doc ���л�

void CUMLObject1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		int FocusID = m_GraphManager.m_FocusID;
		ar<<FocusID;
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		int FocusID = -1;
		ar>>FocusID;
		m_GraphManager.m_FocusID = FocusID;
	}
	m_GraphManager.m_Graphs.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CUMLObject1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CUMLObject1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CUMLObject1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CUMLObject1Doc ���

#ifdef _DEBUG
void CUMLObject1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUMLObject1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUMLObject1Doc ����
