
// UMLObject1.h : UMLObject1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CUMLObject1App:
// �йش����ʵ�֣������ UMLObject1.cpp
//

class CUMLObject1App : public CWinAppEx
{
public:
	CUMLObject1App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUMLObject1App theApp;
