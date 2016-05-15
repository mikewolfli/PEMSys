// LoginDialog.cpp : 实现文件
//
#include "stdafx.h"
#include "PEMSys.h"
#include "LoginDialog.h"
#include ".\logindialog.h"
#include "Crypt.h"
#define MaxAuthor 13


extern CPEMSysApp theApp;
extern CString g_strUserID;
extern CString g_strUserName;
extern CString g_strUserPsw;
extern CString g_strUserDepartment;
extern User_Type g_tUserType;
extern BOOL g_Status;
extern CString g_strAuthor;
// CLoginDialog 对话框

IMPLEMENT_DYNAMIC(CLoginDialog, CDialog)
CLoginDialog::CLoginDialog(CWnd* pParent /*=NULL*/)
: CDialog(CLoginDialog::IDD, pParent)
, m_sPassword(_T(""))
, m_sLoginID(_T(""))
, m_bUPSave(FALSE)
, lRet(FALSE)
, FilePath(_T(""))
{
}

CLoginDialog::~CLoginDialog()
{
}

void CLoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_EDIT_LOGINID, m_sLoginID);
	DDX_Control(pDX, IDC_EDIT_LOGINID, m_cUserID);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_cPassword);
	DDX_Check(pDX, IDC_CHECK_SAVE, m_bUPSave);
}


BEGIN_MESSAGE_MAP(CLoginDialog, CDialog)
	ON_BN_CLICKED(IDOK, OnBkClickOk)
	ON_BN_CLICKED(IDCANCEL, OnBkClickCancel)
END_MESSAGE_MAP()


// CLoginDialog 消息处理程序

void CLoginDialog::OnBkClickOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//	OnOK();
	UpdateData();
	_variant_t str,Holder;
	short sType;
	int ilens;
	CString strPassword,sPassword;
	CString strSection;
	CString strSectionKey;
	CString sSave;
	int iadd;


	if(""==m_sLoginID)
	{
		AfxMessageBox("请输入用户ID",MB_ICONEXCLAMATION);
		return;

	}

	if(m_bUPSave)
		sSave = "1";
	else 
		sSave = "0";

	strSection = _T("LogInfo");
	strSectionKey  = _T("SaveCheck");
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(sSave), FilePath);

	str="select * from Users where UserID = '"+m_sLoginID+"'";
	theApp.ADOExecute(m_pUsersSet,theApp.m_pConnect, str);


	int i = m_pUsersSet->GetRecordCount();
	if(i==1)
	{
		Holder = m_pUsersSet->GetCollect("Password");
		strPassword = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
		strPassword=CCrypt::Decrypt(strPassword,1980); // 密码解密


		if(strPassword == m_sPassword) // 判断认证是否通过
		{
			g_Status = TRUE;
			g_strUserID = m_sLoginID;
			g_strUserName = (char*)_bstr_t(m_pUsersSet->GetCollect("Name"));
			g_strUserPsw = strPassword;
			sType = m_pUsersSet->GetCollect("UserType").iVal;
			switch(sType)
			{
			case 0:
				g_tUserType = UnLogin ;
				break;
			case 1: 
				g_tUserType = Limit_User;
				break;
			case 2:
				g_tUserType = Common_User;
				break;
			case 3:
				g_tUserType = Manager;
				break;
			case 4:
				g_tUserType = Adm_All;
				break;
			case 5:
				g_tUserType = Superman;
				break;
			default:
				break;
			}
			g_strUserDepartment = (char*)_bstr_t(m_pUsersSet->GetCollect("Department"));

			Holder= m_pUsersSet->GetCollect("Authorization");
			g_strAuthor = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

            ilens = g_strAuthor.GetLength();

			if (ilens< MaxAuthor)
			{
				iadd= MaxAuthor-ilens;
				for (int i=0;i<iadd;i++)
				{
					g_strAuthor= g_strAuthor+"0";
				}
			}

			m_pUsersSet->Close();
			m_pUsersSet.Release();


			if(m_bUPSave)
			{

				strSectionKey  = _T("UserID");
				WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(m_sLoginID), FilePath);

				strSectionKey  = _T("LoginPSW");
				sPassword = CCrypt::Encrypt(m_sPassword, 2005);
				WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(sPassword), FilePath);
			}


			EndDialog(IDOK); // 关闭对话框
		}
		else
		{
			m_cPassword.SetFocus();
			m_cPassword.SetSel(0,-1);
			MessageBox("请确认密码,注意大小写!","认证失败!");
		}
	}
	else
	{
		m_cUserID.SetFocus();
		m_cUserID.SetSel(0,-1);
		MessageBox("请确认用户名，注意大小写!", "认证失败");
	}
}

void CLoginDialog::OnBkClickCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pUsersSet->State)
	{
		m_pUsersSet->Close();
	    m_pUsersSet.Release();
	}
	CDialog::OnCancel();
}

BOOL CLoginDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_DLGICON);
	ASSERT(hIcon != NULL);


	UpdateData(TRUE);

	char *vPassword = new char[256];
	char *vUserID = new char[256];
	char *vSave = new char[256];
	FilePath+=".\\config.ini";
	CString strSection;
	CString strSectionKey;
	CString sSave;

	strSection = _T("LogInfo");
	strSectionKey  = _T("SaveCheck");
	lRet = GetPrivateProfileString (strSection,strSectionKey, NULL, vSave, 256, FilePath); 
	if(lRet)
	{
		sSave = vSave;
		if(sSave=="0")
			m_bUPSave = FALSE;
		else if(sSave=="1")
			m_bUPSave = TRUE;

		if(m_bUPSave)
		{
			strSectionKey  = _T("UserID");
			GetPrivateProfileString (strSection,strSectionKey, NULL, vUserID, 256, FilePath); 
			m_sLoginID  = vUserID;

			strSectionKey  = _T("LoginPSW");
			GetPrivateProfileString (strSection,strSectionKey, NULL, vPassword, 256, FilePath); 
			m_sPassword = CCrypt::Decrypt(vPassword, 2005);      
		}
	}
    
	UpdateData(FALSE);
	SetIcon(hIcon, TRUE);
	m_cUserID.SetFocus();

	m_pUsersSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例

    return FALSE;
//	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CLoginDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if(pMsg->message== WM_KEYDOWN)
	{
		if(pMsg->wParam== VK_RETURN)
		{
			if(pMsg->hwnd== m_cUserID.GetSafeHwnd())
			{
				m_cUserID.SetFocus();
				m_cUserID.SetSel(0,-1);
				return FALSE;
			}
			if(pMsg->hwnd == m_cPassword.GetSafeHwnd())
			{
				m_cPassword.SetFocus();
				m_cPassword.SetSel(0,-1);
				return FALSE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CLoginDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

//	CDialog::OnOK();
}

void CLoginDialog::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

//	CDialog::OnCancel();
}
