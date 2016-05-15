// ExcelPathDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ExcelPathDlg.h"
#include ".\excelpathdlg.h"


// CExcelPathDlg 对话框

IMPLEMENT_DYNAMIC(CExcelPathDlg, CDialog)
CExcelPathDlg::CExcelPathDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExcelPathDlg::IDD, pParent)
	, m_sTemplate(_T(""))
	, m_sObject(_T(""))
{
}

CExcelPathDlg::~CExcelPathDlg()
{
}

void CExcelPathDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILEPATH_TEMPLATE, m_sTemplate);
	DDX_Text(pDX, IDC_EDIT_FILEPATH_OBJECT, m_sObject);
}


BEGIN_MESSAGE_MAP(CExcelPathDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BROWER_TEMPLATE, OnBnClickedButtonBrowerTemplate)
	ON_BN_CLICKED(IDC_BUTTON_BROWER_OBJECT, OnBnClickedButtonBrowerObject)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CExcelPathDlg 消息处理程序

void CExcelPathDlg::OnBnClickedButtonBrowerTemplate()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.pszDisplayName=name;
	bi.lpszTitle="选择文件夹";
	bi.ulFlags=BIF_USENEWUI;
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)
		return;
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	m_sTemplate=str;
	if(str.GetAt(str.GetLength()-1)!='\\')
		m_sTemplate+="\\";
	UpdateData(FALSE);
}

void CExcelPathDlg::OnBnClickedButtonBrowerObject()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner=GetSafeHwnd();
	bi.pszDisplayName=name;
	bi.lpszTitle="选择文件夹";
	bi.ulFlags=BIF_USENEWUI;
	LPITEMIDLIST idl=SHBrowseForFolder(&bi);
	if(idl==NULL)
		return;
	SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
	str.ReleaseBuffer();
	m_sObject=str;
	if(str.GetAt(str.GetLength()-1)!='\\')
		m_sObject+="\\";
	UpdateData(FALSE);
}

void CExcelPathDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char appPath[256];
	CString  FilePath;
	GetCurrentDirectory(256,appPath); //取得应用程序当前路径
	FilePath.Format("%s",appPath);
	FilePath+="\\Config.ini";

	CString strSection = _T("Path");
	CString strSectionKey  = _T("Template");
    WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(m_sTemplate), FilePath);

	strSectionKey = _T("Object");
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(m_sObject), FilePath);
    UpdateData(FALSE);

	OnOK();
}

BOOL CExcelPathDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	UpdateData(TRUE);
	CString  FilePath;
	FilePath+=".\\Config.ini";

	CString strSection = _T("Path");
	CString strSectionKey  = _T("Template");
	CString strValue       = _T("");
	char inBuf[80];
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	strValue=inBuf;
	m_sTemplate = strValue;

	strSectionKey  = _T("Object");
	strValue       = _T("");
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
    strValue=inBuf;
	m_sObject = strValue;
	UpdateData(FALSE);


	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_INIT);
	ASSERT(hIcon != NULL);

	SetIcon(hIcon, TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
