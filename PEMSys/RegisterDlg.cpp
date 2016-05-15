// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEMSys.h"
#include "RegisterDlg.h"
#include ".\registerdlg.h"
#include "Crypt.h"

// CRegisterDlg �Ի���

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


// CRegisterDlg ��Ϣ�������

void CRegisterDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	char appPath[256];
	CString  FilePath;
	GetCurrentDirectory(256,appPath); //ȡ��Ӧ�ó���ǰ·��
	FilePath.Format("%s",appPath);
	FilePath+="\\Config.ini";

	m_sUserName.Trim();
	m_sFirst.Trim();
	m_sSecond.Trim();
	m_sThird.Trim();
	m_sFourth.Trim();

	if(m_sUserName.IsEmpty())
	{
		AfxMessageBox("�û�������Ϊ��!",MB_ICONEXCLAMATION);
		m_cUserName.SetFocus();
		m_cUserName.SetSel(0,-1);
		return;
	}

	if(m_sFirst.IsEmpty())
	{
		AfxMessageBox("���кŵ�1���ֲ���Ϊ��!",MB_ICONEXCLAMATION);
		m_cFirst.SetFocus();
		m_cFirst.SetSel(0,-1);
		return;
	}

	if(m_sSecond.IsEmpty())
	{
		AfxMessageBox("���кŵ�2���ֲ���Ϊ��!",MB_ICONEXCLAMATION);
		m_cSecond.SetFocus();
		m_cSecond.SetSel(0,-1);
		return;
	}

	if(m_sThird.IsEmpty())
	{
		AfxMessageBox("���кŵ�3���ֲ���Ϊ��!",MB_ICONEXCLAMATION);
		m_cThird.SetFocus();
		m_cThird.SetSel(0,-1);
		return;
	}

	if(m_sFourth.IsEmpty())
	{
		AfxMessageBox("���кŵ�4���ֲ���Ϊ��!",MB_ICONEXCLAMATION);
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
		AfxMessageBox("ע��Ŵ���!\n����������!",MB_ICONEXCLAMATION);
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
		AfxMessageBox("ע����Ѿ�����!\n����������!",MB_ICONEXCLAMATION);
		return;
	}

	CString strSection = _T("Register");
	CString strSectionKey = _T("User");
	CString strValue  = _T("");
    strValue = m_sUserName;
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);
	//	EndDialog(IDOK); // �رնԻ���

	strSectionKey  = _T("Code");
	strValue  = _T("");
	strValue = sCode;
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);

	//	EndDialog(IDOK); // �رնԻ���
	UpdateData(FALSE);
	OnOK();
}
