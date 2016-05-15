// SysConfig.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEMSys.h"
#include "SysConfig.h"
#include "Crypt.h"
#include ".\sysconfig.h"


// CSysConfig �Ի���

IMPLEMENT_DYNAMIC(CSysConfig, CDialog)
CSysConfig::CSysConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CSysConfig::IDD, pParent)
	, m_bTip(FALSE)
	, m_bTip2(FALSE)
{
}

CSysConfig::~CSysConfig()
{
}

void CSysConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_BROWER, m_cBrower);
	DDX_Check(pDX, IDC_CHECK_TIPS, m_bTip);
	DDX_Check(pDX, IDC_CHECK_TIPS_RETURN, m_bTip2);
}


BEGIN_MESSAGE_MAP(CSysConfig, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWER, OnBnClickedButtonBrower)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_TIPS, OnBnClickedCheckTips)
	ON_BN_CLICKED(IDC_CHECK_TIPS_RETURN, OnBnClickedCheckTipsReturn)
END_MESSAGE_MAP()


// CSysConfig ��Ϣ�������

void CSysConfig::OnBnClickedButtonBrower()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char appPath[256];
	CString  FilePath;
	GetCurrentDirectory(256,appPath); //ȡ��Ӧ�ó���ǰ·��
	FilePath.Format("%s",appPath);
	CFileDialog fileDialog( TRUE,"*.mdb",NULL,NULL,"Access�ļ�(*.mdb)|*.mdb|�����ļ�(*.*)|*.*||");
	if (fileDialog.DoModal() == IDOK) {
		SetDlgItemText(IDC_EDIT_FILEPATH, fileDialog.GetPathName());	
		UpdateData(FALSE); //�ѱ���ֵ���µ���Ӧ�ؼ���
	}	
	SetCurrentDirectory(FilePath);
}

void CSysConfig::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);


//	FilePath=".\\config\\config.ini";

	CString strSection = _T("PathofDatabase");
	CString strSectionKey  = _T("DataFile");
	CString strValue  = _T("");
	GetDlgItemText(IDC_EDIT_FILEPATH,strValue);
    WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);

	strSectionKey = _T("Password");
	strValue  = _T("");
	GetDlgItemText(IDC_EDIT_DATAPASSWORD, strValue);
	strValue = CCrypt::Encrypt(strValue, 2005);
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);

	if(m_bTip&&!m_bTip2)
		strValue=_T("1");
	else if(!m_bTip&&m_bTip2)
        strValue=_T("2");
	else
		strValue=_T("0");


	strSectionKey = _T("Tips");
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);
//	EndDialog(IDOK); // �رնԻ���
	UpdateData(FALSE);
	OnOK();

}

BOOL CSysConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	char appPath[256];
	GetCurrentDirectory(256,appPath); //ȡ��Ӧ�ó���ǰ·��
	FilePath.Format("%s",appPath);
	FilePath+="\\Config.ini";

	CString strSection = _T("PathofDatabase");
	CString strSectionKey  = _T("DataFile");
	CString strValue       = _T("");
	char inBuf[80];
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	strValue=inBuf;
	SetDlgItemText(IDC_EDIT_FILEPATH,strValue);

	strSectionKey  = _T("Password");
    strValue       = _T("");
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	strValue=CCrypt::Decrypt(inBuf,2005);
	SetDlgItemText(IDC_EDIT_DATAPASSWORD,strValue);

	strSectionKey = _T("Tips");
	strValue = _T("");
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	strValue=inBuf;
	if(strValue=="1")
	{
		((CButton*)GetDlgItem(IDC_CHECK_TIPS))->SetCheck(true);
		m_bTip=TRUE;
	}
	else if(strValue=="2")
	{
        ((CButton*)GetDlgItem(IDC_CHECK_TIPS_RETURN))->SetCheck(TRUE);
		m_bTip2=TRUE;
	}else 
	{
         ((CButton*)GetDlgItem(IDC_CHECK_TIPS))->SetCheck(false);
		 ((CButton*)GetDlgItem(IDC_CHECK_TIPS_RETURN))->SetCheck(FALSE);
		 m_bTip= FALSE;
		 m_bTip2=FALSE;
	}

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_INIT);
	ASSERT(hIcon != NULL);

	SetIcon(hIcon, TRUE);
	m_cBrower.SetFocus();

	return FALSE;
//	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}

void CSysConfig::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnSysCommand(nID, lParam);
}



void CSysConfig::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CSysConfig::OnBnClickedCheckTips()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CString strValue;
	if(((CButton*)GetDlgItem(IDC_CHECK_TIPS))->GetCheck())
	{

		m_bTip2=FALSE;
	}
	UpdateData(FALSE);
}

void CSysConfig::OnBnClickedCheckTipsReturn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CString strValue;
	if(((CButton*)GetDlgItem(IDC_CHECK_TIPS_RETURN))->GetCheck())
	{

		m_bTip=FALSE;
	}
	UpdateData(FALSE);
}
