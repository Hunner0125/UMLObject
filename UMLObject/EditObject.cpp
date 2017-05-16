// EditObject.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UMLObject1.h"
#include "EditObject.h"
#include "afxdialogex.h"
#include "string"

using namespace std;

// EditObject �Ի���

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

// Chomework10Dlg ��Ϣ�������

BOOL EditObject::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	// Ϊ��Ͽ�ؼ����б������б��public��   
    //m_comboWeb.AddString(_T("public"));   
    // Ϊ��Ͽ�ؼ����б������б��private��   
    m_comboWeb.AddString(_T("private"));   
    // ����Ͽ�ؼ����б��������Ϊ1��λ�ò����б��protected��   
    m_comboWeb.InsertString(2, _T("protected"));   
 
    m_comboWeb2.SetCurSel(0);   
    m_comboWeb2.AddString(_T("private"));   
    m_comboWeb2.InsertString(2, _T("protected"));   
   
    m_comboWeb.SetCurSel(0);  

	//static text��ʾ
	if (!g->GetName().IsEmpty())
	{
		std::string s(g->GetName().GetBuffer());
		g->GetName().ReleaseBuffer();
		s = "������"+s;
		CString cstr(s.c_str());
		GetDlgItem(IDC_STATIC1)->SetWindowText(cstr);
	}

	if (!g->feature.empty())
		{
			string s = "���ԣ�\n";
			string line;
			list<Feature>::iterator is;  //���������  
			list<Feature> f = g->feature;
			for (is = f.begin(); is != f.end(); ++is)
			{
				Feature ft = *is;
				std::string s1(ft.GetIsLook().GetBuffer());//�ɼ���
				ft.GetIsLook().ReleaseBuffer();
				std::string s2(ft.GetFname().GetBuffer());//������
				ft.GetFname().ReleaseBuffer();
				//string ii = to_string(i);
				line = "������:" + s2 + "  " + "�ɼ���:" + s1 + "\n";
				s = s + line;
			}
			CString cstr(s.c_str());
			GetDlgItem(IDC_STATIC2)->SetWindowText(cstr);
		}

	if (!g->method.empty())
		{
			string s = "���ԣ�\n";
			string line;
			list<Method>::iterator is;  //���������  
			list<Method> mt = g->method;
			for (is = mt.begin(); is != mt.end(); ++is)
			{
				Method mtd = *is;
				std::string s1(mtd.GetIsLookM().GetBuffer());//�ɼ���
				mtd.GetIsLookM().ReleaseBuffer();
				std::string s2(mtd.GetMname().GetBuffer());//������
				mtd.GetMname().ReleaseBuffer();
				//string ii = to_string(i);
				line = "������:" + s2 + "  " + "�ɼ���:" + s1 + "\n";
				s = s + line;
			}
			CString cstr(s.c_str());
			GetDlgItem(IDC_STATIC3)->SetWindowText(cstr);
		}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void EditObject::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void EditObject::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR EditObject::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// EditObject ��Ϣ�������

void EditObject::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//��������
void EditObject::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//USES_CONVERSION;
	CString str;
	GetDlgItemText(IDC_EDIT1, str); ///�������ȡ��������ֵ��������str;
	if (!str.IsEmpty())
	{
		g->SetName(str);
		std::string s(str.GetBuffer());
		str.ReleaseBuffer();
		s = "������"+s;
		CString cstr(s.c_str());
		GetDlgItem(IDC_STATIC1)->SetWindowText(cstr);
		MessageBox(_T("��ӳɹ���"));
	}else
	{
		MessageBox(_T("��������Ϊ�գ�"));
	}

}


void EditObject::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_EDIT2, str); ///�������ȡ��������ֵ��������str;
	int choose = m_comboWeb.GetCurSel();
	CString str1;
	m_comboWeb.GetLBText(choose,str1);
	if (!str.IsEmpty() && !str1.IsEmpty())
	{
		Feature feature;
		feature.SetFname(str);
		feature.SetIsLook(str1);
		g->feature.push_back(feature);

		string s = "���ԣ�\n";
		if (!g->feature.empty())
		{
			string line;
			list<Feature>::iterator is;  //���������  
			list<Feature> f = g->feature;
			for (is = f.begin(); is != f.end(); ++is)
			{
				Feature ft = *is;
				std::string s1(ft.GetIsLook().GetBuffer());//�ɼ���
				ft.GetIsLook().ReleaseBuffer();
				std::string s2(ft.GetFname().GetBuffer());//������
				ft.GetFname().ReleaseBuffer();
				//string ii = to_string(i);
				line = "������:" + s2 + "  " + "�ɼ���:" + s1 + "\n";
				s = s + line;
			}
		}
		CString cstr(s.c_str());
		GetDlgItem(IDC_STATIC2)->SetWindowText(cstr);
		MessageBox(_T("��ӳɹ���"));
	}else
	{
		MessageBox(_T("�������Ϳɼ��Բ���Ϊ�գ�"));
	}
}


void EditObject::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_EDIT4, str); ///�������ȡ��������ֵ��������str;
	int choose = m_comboWeb2.GetCurSel();
	CString str1;
	m_comboWeb2.GetLBText(choose,str1);
	if (!str.IsEmpty() && !str1.IsEmpty())
	{
		Method method;
		method.SetMname(str);
		method.SetIsLookM(str1);
		g->method.push_back(method);

		string s = "������\n";
		if (!g->method.empty())
		{
			string line;
			list<Method>::iterator is;  //���������  
			list<Method> mt = g->method;
			for (is = mt.begin(); is != mt.end(); ++is)
			{
				Method mtd = *is;
				std::string s1(mtd.GetIsLookM().GetBuffer());//�ɼ���
				mtd.GetIsLookM().ReleaseBuffer();
				std::string s2(mtd.GetMname().GetBuffer());//������
				mtd.GetMname().ReleaseBuffer();
				//string ii = to_string(i);
				line = "������:" + s2 + "  " + "�ɼ���:" + s1 + "\n";
				s = s + line;
			}
		}
		CString cstr(s.c_str());
		GetDlgItem(IDC_STATIC3)->SetWindowText(cstr);
		MessageBox(_T("��ӳɹ���"));
	}else
	{
		MessageBox(_T("�������Ϳɼ��Բ���Ϊ�գ�"));
	}
}
