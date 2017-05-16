// EditObject.cpp : 实现文件
//

#include "stdafx.h"
#include "UMLObject1.h"
#include "EditObject.h"
#include "afxdialogex.h"
#include "string"

using namespace std;

// EditObject 对话框

IMPLEMENT_DYNAMIC(EditObject, CDialogEx)

EditObject::EditObject(CWnd* pParent /*=NULL*/)
	: CDialogEx(EditObject::IDD, pParent)
{
	
}

EditObject::~EditObject()
{
}

void EditObject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboWeb);
	DDX_Control(pDX, IDC_COMBO2, m_comboWeb2);
}

BEGIN_MESSAGE_MAP(EditObject, CDialogEx)
	
	ON_CBN_SELCHANGE(IDC_COMBO1, &EditObject::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &EditObject::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &EditObject::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &EditObject::OnBnClickedButton2)
END_MESSAGE_MAP()

// Chomework10Dlg 消息处理程序

BOOL EditObject::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	// 为组合框控件的列表框添加列表项“public”   
    //m_comboWeb.AddString(_T("public"));   
    // 为组合框控件的列表框添加列表项“private”   
    m_comboWeb.AddString(_T("private"));   
    // 在组合框控件的列表框中索引为1的位置插入列表项“protected”   
    m_comboWeb.InsertString(2, _T("protected"));   
 
    m_comboWeb2.SetCurSel(0);   
    m_comboWeb2.AddString(_T("private"));   
    m_comboWeb2.InsertString(2, _T("protected"));   
   
    m_comboWeb.SetCurSel(0);  

	//static text显示
	if (!g->GetName().IsEmpty())
	{
		std::string s(g->GetName().GetBuffer());
		g->GetName().ReleaseBuffer();
		s = "类名："+s;
		CString cstr(s.c_str());
		GetDlgItem(IDC_STATIC1)->SetWindowText(cstr);
	}

	if (!g->feature.empty())
		{
			string s = "属性：\n";
			string line;
			list<Feature>::iterator is;  //定义迭代器  
			list<Feature> f = g->feature;
			for (is = f.begin(); is != f.end(); ++is)
			{
				Feature ft = *is;
				std::string s1(ft.GetIsLook().GetBuffer());//可见性
				ft.GetIsLook().ReleaseBuffer();
				std::string s2(ft.GetFname().GetBuffer());//属性名
				ft.GetFname().ReleaseBuffer();
				//string ii = to_string(i);
				line = "属性名:" + s2 + "  " + "可见性:" + s1 + "\n";
				s = s + line;
			}
			CString cstr(s.c_str());
			GetDlgItem(IDC_STATIC2)->SetWindowText(cstr);
		}

	if (!g->method.empty())
		{
			string s = "属性：\n";
			string line;
			list<Method>::iterator is;  //定义迭代器  
			list<Method> mt = g->method;
			for (is = mt.begin(); is != mt.end(); ++is)
			{
				Method mtd = *is;
				std::string s1(mtd.GetIsLookM().GetBuffer());//可见性
				mtd.GetIsLookM().ReleaseBuffer();
				std::string s2(mtd.GetMname().GetBuffer());//属性名
				mtd.GetMname().ReleaseBuffer();
				//string ii = to_string(i);
				line = "方法名:" + s2 + "  " + "可见性:" + s1 + "\n";
				s = s + line;
			}
			CString cstr(s.c_str());
			GetDlgItem(IDC_STATIC3)->SetWindowText(cstr);
		}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void EditObject::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void EditObject::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR EditObject::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// EditObject 消息处理程序

void EditObject::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}

//设置类名
void EditObject::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//USES_CONVERSION;
	CString str;
	GetDlgItemText(IDC_EDIT1, str); ///这儿就是取该输入框的值，并赋给str;
	if (!str.IsEmpty())
	{
		g->SetName(str);
		std::string s(str.GetBuffer());
		str.ReleaseBuffer();
		s = "类名："+s;
		CString cstr(s.c_str());
		GetDlgItem(IDC_STATIC1)->SetWindowText(cstr);
		MessageBox(_T("添加成功！"));
	}else
	{
		MessageBox(_T("类名不能为空！"));
	}

}


void EditObject::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_EDIT2, str); ///这儿就是取该输入框的值，并赋给str;
	int choose = m_comboWeb.GetCurSel();
	CString str1;
	m_comboWeb.GetLBText(choose,str1);
	if (!str.IsEmpty() && !str1.IsEmpty())
	{
		Feature feature;
		feature.SetFname(str);
		feature.SetIsLook(str1);
		g->feature.push_back(feature);

		string s = "属性：\n";
		if (!g->feature.empty())
		{
			string line;
			list<Feature>::iterator is;  //定义迭代器  
			list<Feature> f = g->feature;
			for (is = f.begin(); is != f.end(); ++is)
			{
				Feature ft = *is;
				std::string s1(ft.GetIsLook().GetBuffer());//可见性
				ft.GetIsLook().ReleaseBuffer();
				std::string s2(ft.GetFname().GetBuffer());//属性名
				ft.GetFname().ReleaseBuffer();
				//string ii = to_string(i);
				line = "属性名:" + s2 + "  " + "可见性:" + s1 + "\n";
				s = s + line;
			}
		}
		CString cstr(s.c_str());
		GetDlgItem(IDC_STATIC2)->SetWindowText(cstr);
		MessageBox(_T("添加成功！"));
	}else
	{
		MessageBox(_T("属性名和可见性不能为空！"));
	}
}


void EditObject::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_EDIT4, str); ///这儿就是取该输入框的值，并赋给str;
	int choose = m_comboWeb2.GetCurSel();
	CString str1;
	m_comboWeb2.GetLBText(choose,str1);
	if (!str.IsEmpty() && !str1.IsEmpty())
	{
		Method method;
		method.SetMname(str);
		method.SetIsLookM(str1);
		g->method.push_back(method);

		string s = "方法：\n";
		if (!g->method.empty())
		{
			string line;
			list<Method>::iterator is;  //定义迭代器  
			list<Method> mt = g->method;
			for (is = mt.begin(); is != mt.end(); ++is)
			{
				Method mtd = *is;
				std::string s1(mtd.GetIsLookM().GetBuffer());//可见性
				mtd.GetIsLookM().ReleaseBuffer();
				std::string s2(mtd.GetMname().GetBuffer());//属性名
				mtd.GetMname().ReleaseBuffer();
				//string ii = to_string(i);
				line = "方法名:" + s2 + "  " + "可见性:" + s1 + "\n";
				s = s + line;
			}
		}
		CString cstr(s.c_str());
		GetDlgItem(IDC_STATIC3)->SetWindowText(cstr);
		MessageBox(_T("添加成功！"));
	}else
	{
		MessageBox(_T("方法名和可见性不能为空！"));
	}
}
