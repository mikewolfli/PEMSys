// ResetPaswdDialog.cpp : ʵ���ļ�
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

// CResetPaswdDialog �Ի���

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


// CResetPaswdDialog ��Ϣ�������

void CResetPaswdDialog::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_sOldPassword!=g_strUserPsw)
	{
		AfxMessageBox("��������������\n����������(���ִ�Сд)...",MB_ICONEXCLAMATION);
		m_cOldPassword.SetFocus();
		m_cOldPassword.SetSel(0,-1);
		return;
	}


	CString str;
	CString strPassword;

	int i=strlen(m_sNewPassword);
	if(i>20)
	{
		AfxMessageBox("���볤�Ȳ��ܳ���20���ַ�...",MB_ICONEXCLAMATION);
		m_cNewPassword.SetFocus();
		m_cNewPassword.SetSel(0,-1);
		return;

	}

	if(m_sNewPassword!=m_sNPConfirm)
	{
		AfxMessageBox("��ȷ���������������ȷ���Ƿ�һ��...",MB_ICONEXCLAMATION);
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_EDIT_USERID, g_strUserID);
	SetDlgItemText(IDC_EDIT_USERNAME, g_strUserName);
	m_cOldPassword.SetFocus();

	m_pADOSet.CreateInstance(__uuidof(Recordset)); // ����Recordset����ʵ��

	return FALSE;
	//	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CResetPaswdDialog::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//	CDialog::OnCancel();
}

void CResetPaswdDialog::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//	CDialog::OnOK();
}

void CResetPaswdDialog::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ����ר�ô����/����û���

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
