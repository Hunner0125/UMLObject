#pragma once

#include "afxwin.h"
#include "Graph.h"
#include "Feature.h"
#include "Method.h"
//#include "UMLObject1View.h"

// EditObject �Ի���

class EditObject : public CDialogEx
{
	DECLARE_DYNAMIC(EditObject)

public:
	EditObject(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~EditObject();

	Graph* g;

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_comboWeb;
	CComboBox m_comboWeb2;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
