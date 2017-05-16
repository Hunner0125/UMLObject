
// UMLObject1Doc.cpp : CUMLObject1Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CUMLObject1Doc 构造/析构

CUMLObject1Doc::CUMLObject1Doc()
{
	// TODO: 在此添加一次性构造代码

}

CUMLObject1Doc::~CUMLObject1Doc()
{
}

BOOL CUMLObject1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(_T("UML类图编辑器"));

	return TRUE;
}




// CUMLObject1Doc 序列化

void CUMLObject1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		int FocusID = m_GraphManager.m_FocusID;
		ar<<FocusID;
	}
	else
	{
		// TODO: 在此添加加载代码
		int FocusID = -1;
		ar>>FocusID;
		m_GraphManager.m_FocusID = FocusID;
	}
	m_GraphManager.m_Graphs.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CUMLObject1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CUMLObject1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CUMLObject1Doc 诊断

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


// CUMLObject1Doc 命令
