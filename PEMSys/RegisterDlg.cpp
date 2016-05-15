// RegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "RegisterDlg.h"
#include ".\registerdlg.h"
#include "Crypt.h"

// CRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CRegisterDlg, CDialog)
CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
	, m_sFirst(_T(""))
	, m_sSecond(_T(""))
	, m_sThird(_T(""))
	, m_sFourth(_T(""))
	, m_sCode(_T(""))
	, m_sUserName(_T(""))
{
}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIRST, m_sFirst);
	DDV_MaxChars(pDX, m_sFirst, 4);
	DDX_Text(pDX, IDC_EDIT_SECOND, m_sSecond);
	DDV_MaxChars(pDX, m_sSecond, 4);
	DDX_Text(pDX, IDC_EDIT_THIRD, m_sThird);
	DDV_MaxChars(pDX, m_sThird, 4);
	DDX_Text(pDX, IDC_EDIT_FOURTH, m_sFourth);
	DDV_MaxChars(pDX, m_sFourth, 6);
	DDX_Text(pDX, IDC_EDIT4, m_sUserName);
	DDV_MaxChars(pDX, m_sUserName, 16);
	DDX_Control(pDX, IDC_EDIT4, m_cUserName);
	DDX_Control(pDX, IDC_EDIT_FIRST, m_cFirst);
	DDX_Control(pDX, IDC_EDIT_SECOND, m_cSecond);
	DDX_Control(pDX, IDC_EDIT_THIRD, m_cThird);
	DDX_Control(pDX, IDC_EDIT_FOURTH, m_cFourth);
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRegisterDlg 消息处理程序

void CRegisterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char appPath[256];
	CString  FilePath;
	GetCurrentDirectory(256,appPath); //取得应用程序当前路径
	FilePath.Format("%s",appPath);
	FilePath+="\\Config.ini";

	m_sUserName.Trim();
	m_sFirst.Trim();
	m_sSecond.Trim();
	m_sThird.Trim();
	m_sFourth.Trim();

	if(m_sUserName.IsEmpty())
	{
		AfxMessageBox("用户名不能为空!",MB_ICONEXCLAMATION);
		m_cUserName.SetFocus();
		m_cUserName.SetSel(0,-1);
		return;
	}

	if(m_sFirst.IsEmpty())
	{
		AfxMessageBox("序列号第1部分不能为空!",MB_ICONEXCLAMATION);
		m_cFirst.SetFocus();
		m_cFirst.SetSel(0,-1);
		return;
	}

	if(m_sSecond.IsEmpty())
	{
		AfxMessageBox("序列号第2部分不能为空!",MB_ICONEXCLAMATION);
		m_cSecond.SetFocus();
		m_cSecond.SetSel(0,-1);
		return;
	}

	if(m_sThird.IsEmpty())
	{
		AfxMessageBox("序列号第3部分不能为空!",MB_ICONEXCLAMATION);
		m_cThird.SetFocus();
		m_cThird.SetSel(0,-1);
		return;
	}

	if(m_sFourth.IsEmpty())
	{
		AfxMessageBox("序列号第4部分不能为空!",MB_ICONEXCLAMATION);
		m_cFourth.SetFocus();
		m_cFourth.SetSel(0,-1);
		return;
	}
    CRegister m_Register;

	CString sCode=m_sFirst+"-"+m_sSecond+"-"+m_sThird+"-"+m_sFourth;

	m_sCode = m_Register.CodeProving(m_sUserName, sCode);
	

	CString sYear, sMonth, sDay;
	sYear = m_sCode.Left(4);
	sMonth= m_sCode.Mid(4,2);
	sDay = m_sCode.Right(2);

	if(sYear.IsEmpty()||sMonth.IsEmpty()||sDay.IsEmpty())
	{
		AfxMessageBox("注册号错误!\n请重新输入!",MB_ICONEXCLAMATION);
		return;
	}

	int iYear,iMonth, iDay;
	COleDateTime m_dCompare,m_dCurrent;

	iYear = atoi(sYear);
	iMonth = atoi(sMonth);
	iDay = atoi(sDay);
	m_dCompare.SetDate(iYear,iMonth,iDay);
	m_dCurrent = COleDateTime::GetCurrentTime();

	if(m_dCompare<= m_dCurrent)
	{
		AfxMessageBox("注册号已经过期!\n请重新输入!",MB_ICONEXCLAMATION);
		return;
	}

	CString strSection = _T("Register");
	CString strSectionKey = _T("User");
	CString strValue  = _T("");
    strValue = m_sUserName;
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);
	//	EndDialog(IDOK); // 关闭对话框

	strSectionKey  = _T("Code");
	strValue  = _T("");
	strValue = sCode;
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);

	//	EndDialog(IDOK); // 关闭对话框
	UpdateData(FALSE);
	OnOK();
}
