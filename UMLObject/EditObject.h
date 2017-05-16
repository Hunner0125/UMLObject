#pragma once

#include "afxwin.h"
#include "Graph.h"
#include "Feature.h"
#include "Method.h"
//#include "UMLObject1View.h"

// EditObject 对话框

class EditObject : public CDialogEx
{
	DECLARE_DYNAMIC(EditObject)

public:
	EditObject(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~EditObject();

	Graph* g;

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
