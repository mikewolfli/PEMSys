// ResetPaswdDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ResetPaswdDialog.h"
#include ".\resetpaswddialog.h"
#include "Crypt.h"


extern CPEMSysApp theApp;
extern CString g_strUserID;
extern CString g_strUserName;
extern CString g_strUserPsw;
extern CString g_strUserDepartment;
extern User_Type g_tUserType;
extern BOOL g_Status;

// CResetPaswdDialog 对话框

IMPLEMENT_DYNAMIC(CResetPaswdDialog, CDialog)
CResetPaswdDialog::CResetPaswdDialog(CWnd* pParent /*=NULL*/)
: CDialog(CResetPaswdDialog::IDD, pParent)
, m_sOldPassword(_T(""))
, m_sNewPassword(_T(""))
, m_sNPConfirm(_T(""))
{
}

CResetPaswdDialog::~CResetPaswdDialog()
{
}

void CResetPaswdDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_sOldPassword);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_cOldPassword);
	DDX_Text(pDX, IDC_EDIT_NEWPASSWORD, m_sNewPassword);
	DDX_Text(pDX, IDC_EDIT_NEWPASSWORDCONFIRM, m_sNPConfirm);
	DDX_Control(pDX, IDC_EDIT_NEWPASSWORDCONFIRM, m_cNPConfirm);
	DDX_Control(pDX, IDC_EDIT_NEWPASSWORD, m_cNewPassword);
}


BEGIN_MESSAGE_MAP(CResetPaswdDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CResetPaswdDialog 消息处理程序

void CResetPaswdDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_sOldPassword!=g_strUserPsw)
	{
		AfxMessageBox("旧密码输入有误！\n请重新输入(区分大小写)...",MB_ICONEXCLAMATION);
		m_cOldPassword.SetFocus();
		m_cOldPassword.SetSel(0,-1);
		return;
	}


	CString str;
	CString strPassword;

	int i=strlen(m_sNewPassword);
	if(i>20)
	{
		AfxMessageBox("密码长度不能超过20个字符...",MB_ICONEXCLAMATION);
		m_cNewPassword.SetFocus();
		m_cNewPassword.SetSel(0,-1);
		return;

	}

	if(m_sNewPassword!=m_sNPConfirm)
	{
		AfxMessageBox("请确认新密码和新密码确认是否一致...",MB_ICONEXCLAMATION);
		m_cNPConfirm.SetFocus();
		m_cNPConfirm.SetSel(0,-1);
		return;
	}

	strPassword = CCrypt::Encrypt(m_sNewPassword, 1980);

	str.Format("update Users set Users.Password='%s' where UserID= '%s'",strPassword, g_strUserID);
	theApp.ADOExecute(m_pADOSet,theApp.m_pConnect,  _variant_t(str));
	g_strUserPsw = m_sNewPassword;

	//	m_pADOSet->Close();
	m_pADOSet.Release();

	CDialog::OnOK();

	//	OnOK();
}

BOOL CResetPaswdDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT_USERID, g_strUserID);
	SetDlgItemText(IDC_EDIT_USERNAME, g_strUserName);
	m_cOldPassword.SetFocus();

	m_pADOSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例

	return FALSE;
	//	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CResetPaswdDialog::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//	CDialog::OnCancel();
}

void CResetPaswdDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//	CDialog::OnOK();
}

void CResetPaswdDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pADOSet->State)
	{
		m_pADOSet->Close();
		
	}
	m_pADOSet.Release();
	CDialog::OnCancel();
//	OnCancel();
}

BOOL CResetPaswdDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(pMsg->message== WM_KEYDOWN)
	{
		if(pMsg->wParam== VK_RETURN)
		{
			if(pMsg->hwnd== m_cOldPassword.GetSafeHwnd())
			{
				m_cOldPassword.SetFocus();
				m_cOldPassword.SetSel(0,-1);
				return FALSE;
			}
			if(pMsg->hwnd == m_cNewPassword.GetSafeHwnd())
			{
				m_cNewPassword.SetFocus();
				m_cNewPassword.SetSel(0,-1);
				return FALSE;
			}
			if(pMsg->hwnd == m_cNPConfirm.GetSafeHwnd())
			{
				m_cNPConfirm.SetFocus();
				m_cNPConfirm.SetSel(0,-1);
				return FALSE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
