// PEMSys.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "PEMSys.h"
#include "MainFrm.h"
//#include "SplashWnd.h"
#include "SysConfig.h"
#include "LoginDialog.h"

#include "ChildFrm.h"
#include "HyperLink.h"
#include "PEMSysDoc.h"
#include "PEMSysView.h"
#include "ItemDataInputView.h"
#include "ItemExcelView.h"
#include "ItemCommerceSearchView.h"
#include "ItemInExportView.h"
#include "ItemView.h"
#include ".\pemsys.h"
#include "alphactrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPEMSysApp

BEGIN_MESSAGE_MAP(CPEMSysApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CPEMSysApp 构造

CPEMSysApp::CPEMSysApp()
: m_strDataFile(_T(""))
, m_strPassword(_T(""))
, lRet(FALSE)
, m_dCurrent(COleDateTime::GetCurrentTime())
{
	EnableHtmlHelp();

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CPEMSysApp 对象

CAppFace g_af ;
CPEMSysApp theApp;
CString g_strUserID;
CString g_strUserName;
CString g_strUserPsw;
User_Type g_tUserType;
CString g_strUserDepartment;
BOOL g_Status = FALSE;
CString g_strAuthor;
// 生成的此标识符在统计上对于您的应用程序是唯一的
// 如果您更愿选择一个特定的标识符，则可以更改它

// {0E2CE157-5F92-41A2-840D-B78713FB5C17}
static const CLSID clsid =
{ 0xE2CE157, 0x5F92, 0x41A2, { 0x84, 0xD, 0xB7, 0x87, 0x13, 0xFB, 0x5C, 0x17 } };
const GUID CDECL BASED_CODE _tlid =
		{ 0xA53BD978, 0x741C, 0x4FE7, { 0x97, 0x37, 0xBD, 0x71, 0xBC, 0xCD, 0xE0, 0x28 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CPEMSysApp 初始化

BOOL CPEMSysApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();
 
	CWinApp::InitInstance();

	//此程序只能运行一次，用互斥量来判断程序是否已运行
	HANDLE m_hMutex=CreateMutex(NULL,TRUE, m_pszAppName); 
	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{ 
		AfxMessageBox("PEMSys程序已经运行!");
		return FALSE; 
	}

//	CSplashWnd	*m_pSplashWnd = new CSplashWnd();

//	m_pSplashWnd->Create();
//	m_pSplashWnd->UpdateWindow();
	//m_pSplashWnd->ShowSplashScreen();


	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
//		delete m_pSplashWnd;
		return FALSE;
	}

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
//		delete m_pSplashWnd;
		return FALSE;
	}

	if( FAILED(::CoInitialize(NULL)) ) 
	{
		AfxMessageBox("ADO Init failed");
//		delete m_pSplashWnd;
		return false;
	}

	AfxEnableControlContainer();

	CString  FilePath,sPassword;
	int InitRet;
	CSysConfig lDlg;
	CRegisterDlg RDlg;

	char *vDataFile = new char[256];
	char *vPassword = new char[256];
	char *vUserName = new char[256];
	char *vCode = new char[256];
	FilePath+=".\\config.ini";
	CString strSection;
	CString strSectionKey;
	CString sCode,sUser;
	COleDateTime m_dTemp;
	CString sYear,sMonth,sDay;


	strSection = _T("PathofDatabase");
	strSectionKey  = _T("DataFile");
	lRet = GetPrivateProfileString (strSection,strSectionKey, NULL, vDataFile, 256, FilePath); 

	strSectionKey  = _T("Password");
	GetPrivateProfileString (strSection,strSectionKey, NULL, vPassword, 256, FilePath); 
	sPassword = CCrypt::Decrypt(vPassword, 2005);
	if(!lRet)
	{
		InitRet = lDlg.DoModal();
		switch(InitRet) {
		case -1: 
			MessageBox(NULL,"对话框创建失败！","Client Error:", MB_OK);

			delete [] vDataFile;
			delete [] vPassword;
//			delete m_pSplashWnd;
			return FALSE;
			break;
		case IDCANCEL:
			delete [] vDataFile;
			delete [] vPassword;
	//		delete m_pSplashWnd;
			return FALSE;
			break;
		case IDOK:
			strSection = _T("PathofDatabase");
			strSectionKey  = _T("DataFile");
			lRet = GetPrivateProfileString (strSection,strSectionKey, NULL, vDataFile, 256, FilePath); 
			m_strDataFile = vDataFile;

			strSectionKey  = _T("Password");
			GetPrivateProfileString (strSection,strSectionKey, NULL, vPassword, 256, FilePath); 
			sPassword = CCrypt::Decrypt(vPassword, 2005);
			m_strPassword = sPassword;
//			m_pSplashWnd->UpdateWindow();
			break;

		default:
			break;
		}

	}
	else
	{
		m_strDataFile = vDataFile;
		m_strPassword = sPassword;
	}



	////////////连接数据库//////////////

	BOOL blnInit;
	blnInit = InitDataBaseConnect();
	while(!blnInit)
	{
		InitRet = lDlg.DoModal();
		switch(InitRet) {
		case -1: 
			MessageBox(NULL,"对话框创建失败！","Client Error:", MB_OK);

			delete [] vDataFile;
			delete [] vPassword;
//			delete m_pSplashWnd;
			return FALSE;
			break;
		case IDCANCEL:
			delete [] vDataFile;
			delete [] vPassword;
	//		delete m_pSplashWnd;
			return FALSE;
			break;
		case IDOK:
			strSection = _T("PathofDatabase");
			strSectionKey  = _T("DataFile");
			GetPrivateProfileString (strSection,strSectionKey, NULL, vDataFile, 256, FilePath); 
			m_strDataFile = vDataFile;

			strSectionKey  = _T("Password");
			GetPrivateProfileString (strSection,strSectionKey, NULL, vPassword, 256, FilePath); 
			sPassword = CCrypt::Decrypt(vPassword, 2005);
			m_strPassword = sPassword;

//			m_pSplashWnd->UpdateWindow();
			blnInit = InitDataBaseConnect();
			break;
		default:
			break;
		}
	}

	delete [] vDataFile;
	delete [] vPassword;

	HRESULT hr;
	_bstr_t strConn ;
	hr = m_pSearchConn.CreateInstance("ADODB.Connection");///创建Connection对象
	try
	{
		if(SUCCEEDED(hr))
		{
			strConn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source = .\\Configure.cfg";

			hr = m_pSearchConn->Open(strConn,"","",NULL);///连接数据库
			//  	hr = m_pConnect->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\Configuration\\configure.mdb","","",adConnectUnspecified));///连接数据库
			///上面一句中连接字串中的Provider是针对ACCESS2000环境的，对于ACCESS97,需要改为:Provider=Microsoft.Jet.OLEDB.3.51;  }
		}
		else
			return FALSE;
	}
	catch(_com_error &e)
	{

		CString err;
		err.Format("%s", (char*)(e.Description()) );
		AfxMessageBox(err);
		return FALSE;
	}
	catch(...)
	{

		AfxMessageBox("未知错误...");
		return FALSE;
	}
/*
	int iYear, iMonth,iDay;
	m_dTemp.SetDate(2007,10,1);

	if(  m_dCurrent>=m_dTemp)
	{
		strSection = _T("Register");
		strSectionKey  = _T("User");
		lRet = GetPrivateProfileString (strSection,strSectionKey, NULL, vUserName, 256, FilePath); 
		sUser = vUserName;

		strSectionKey  = _T("Code");
		GetPrivateProfileString (strSection,strSectionKey, NULL, vCode, 256, FilePath); 
		sCode = vCode;

		BOOL bCheck = FALSE;

		if(!lRet)
		{
			while(!bCheck)
			{
				InitRet = RDlg.DoModal();
				switch(InitRet) 
				{
				case -1: 
					MessageBox(NULL,"对话框创建失败！","Client Error:", MB_OK);

					delete [] vUserName;
					delete [] vCode;
	//				delete m_pSplashWnd;
					return FALSE;
					break;
				case IDCANCEL:
					delete [] vUserName;
					delete [] vCode;
	//				delete m_pSplashWnd;
					return FALSE;
					break;
				case IDOK:
					{
						strSection = _T("Register");
						strSectionKey  = _T("User");
						lRet = GetPrivateProfileString (strSection,strSectionKey, NULL, vUserName, 256, FilePath); 
						sUser= vUserName;

						strSectionKey  = _T("Code");
						GetPrivateProfileString (strSection,strSectionKey, NULL, vCode, 256, FilePath); 
						sCode = vCode;
	
						sCode = m_Register.CodeProving(sUser, sCode);
						sYear = sCode.Left(4);
						sMonth= sCode.Mid(4,2);
						sDay = sCode.Right(2);

						iYear = atoi(sYear);
						iMonth = atoi(sMonth);
						iDay = atoi(sDay);
						m_dTemp.SetDate(iYear,iMonth,iDay);
						if(m_dTemp<= m_dCurrent)
						{
							AfxMessageBox("注册号已经过期!\n请重新输入!",MB_ICONEXCLAMATION);
							bCheck = FALSE;
						}
						else
							bCheck = TRUE;

					}
					break;
				default:
					break;
				}
			}
		}

		sCode = m_Register.CodeProving(sUser, sCode);
		sYear = sCode.Left(4);
		sMonth= sCode.Mid(4,2);
		sDay = sCode.Right(2);

		iYear = atoi(sYear);
		iMonth = atoi(sMonth);
		iDay = atoi(sDay);
		m_dTemp.SetDate(iYear,iMonth,iDay);
		if(m_dTemp<= m_dCurrent)
		{
			AfxMessageBox("注册号已经过期!\n请重新输入!",MB_ICONEXCLAMATION);
			bCheck = FALSE;
		}
		else
			bCheck = TRUE;


		while(!bCheck)
		{
			InitRet = RDlg.DoModal();
			switch(InitRet) 
			{
			case -1: 
				MessageBox(NULL,"对话框创建失败！","Client Error:", MB_OK);

				delete [] vUserName;
				delete [] vCode;
	//			delete m_pSplashWnd;
				return FALSE;
				break;
			case IDCANCEL:
				delete [] vUserName;
				delete [] vCode;
	//			delete m_pSplashWnd;
				return FALSE;

				break;
			case IDOK:
				{
					strSection = _T("Register");
					strSectionKey  = _T("User");
					lRet = GetPrivateProfileString (strSection,strSectionKey, NULL, vUserName, 256, FilePath); 
					sUser= vUserName;

					strSectionKey  = _T("Code");
					GetPrivateProfileString (strSection,strSectionKey, NULL, vCode, 256, FilePath); 
					sCode = vCode;

					sCode = m_Register.CodeProving(sUser, sCode);
					sYear = sCode.Left(4);
					sMonth= sCode.Mid(4,2);
					sDay = sCode.Right(2);

					iYear = atoi(sYear);
					iMonth = atoi(sMonth);
					iDay = atoi(sDay);
					m_dTemp.SetDate(iYear,iMonth,iDay);
					if(m_dTemp<= m_dCurrent)
					{
						AfxMessageBox("注册号已经过期!\n请重新输入!",MB_ICONEXCLAMATION);
						bCheck = FALSE;;
					}
					else
					{
						bCheck = TRUE;
					}

				}
				break;
			default:
				break;
			}
		}
	}

*/
	CLoginDialog m_lLogin;
	InitRet=m_lLogin.DoModal();
	if( InitRet  == IDOK)
	{
	}
	else
	{
		return FALSE;
	}


	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	m_pPEMSysTemplate  = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPEMSysDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CPEMSysView));
	AddDocTemplate(m_pPEMSysTemplate);

	m_pItemViewTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPEMSysDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CItemView));
	AddDocTemplate(m_pItemViewTemplate);

	m_pItemDataInputTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPEMSysDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CItemDataInputView));
	AddDocTemplate(m_pItemDataInputTemplate);

	m_pItemExcelTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPEMSysDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CItemExcelView));
	AddDocTemplate(m_pItemExcelTemplate);

	m_pItemCommerceSearchTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPEMSysDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CItemCommerceSearchView));
	AddDocTemplate(m_pItemCommerceSearchTemplate);

	m_pItemInExortViewTempleate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPEMSysDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CItemInExportView));
	AddDocTemplate(m_pItemInExortViewTempleate);
	// 将 COleTemplateServer 连接到文档模板
	// COleTemplateServer 通过使用
	// 文档模板中指定的信息来为
	// 请求 OLE 容器创建新文档
//	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);
	// 将所有的 OLE 服务器工厂注册为正在运行。这将启用
	//  OLE 库以从其他应用程序中创建对象
//	COleTemplateServer::RegisterAll();
		// 注意: MDI 应用程序将注册所有的服务器对象，而不管
		// 命令行上的 /Embedding 或 /Automation
	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;

	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
	//	delete m_pSplashWnd;
		return FALSE;
	}

	m_pMainWnd = pMainFrame;
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生
	// 启用拖/放
	m_pMainWnd->DragAcceptFiles();
	// 启用“DDE 执行”
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//添加代码防止自动打开空白文档
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	// 应用程序是用 /Embedding 或 /Automation 开关启动的。
	//使应用程序作为自动化服务器运行。
//	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
//	{
		// 不显示主窗口
//		return TRUE;
//	}
	// 使用 /Unregserver 或 /Unregister 开关启动应用程序。  注销
	// 类型库。其他注销操作在 ProcessShellCommand() 中发生。
//	else if (cmdInfo.m_nShellCommand ==		CCommandLineInfo::AppUnregister)
//	{
//		UnregisterShellFileTypes();
//		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
///		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
//	}
	// 应用程序是以独立方式或用其他开关(如 /Register
	// 或 /Regserver)启动的。更新注册表项，包括类型库。
//	else
//	{
//		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
//		COleObjectFactory::UpdateRegistryAll();
//		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
//	}
	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


//	CMenu *pMainMenu = pMainFrame->GetMenu();


//	pMainMenu->GetSubMenu(1)->RemoveMenu(ID__32859, MF_BYCOMMAND);
//	pMainMenu->GetSubMenu(1)->RemoveMenu(ID__32860, MF_BYCOMMAND);
//	pMainMenu->GetSubMenu(1)->RemoveMenu(ID__32861, MF_BYCOMMAND);
//	pMainMenu->GetSubMenu(1)->RemoveMenu(ID__32862, MF_BYCOMMAND);
//	pMainMenu->GetSubMenu(1)->RemoveMenu(ID__32863, MF_BYCOMMAND);

//	if(g_tUserType < 4)
//	{
//      pMainMenu->GetSubMenu(2)->RemoveMenu(ID_SYS_PERSON, MF_BYCOMMAND); 
//       pMainMenu->GetSubMenu(2)->RemoveMenu(ID_BACKUP, MF_BYCOMMAND); 
//	   pMainMenu->GetSubMenu(2)->RemoveMenu(ID_RESTOREDATA, MF_BYCOMMAND); 
//	}

    
	// 主窗口已初始化，因此显示它并对其进行更新

	pMainFrame->SetWindowText("电梯合同管理系统PEMSys 1.0");
	m_nCmdShow = SW_SHOWMAXIMIZED;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();



 //   delete m_pSplashWnd;
	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
//	afx_msg void OnSysconfig();
	CHyperLink m_pLink;
	CAlphaCtrl m_bmpDisplay;
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINK, m_pLink);
	DDX_Control(pDX, IDC_BMP, m_bmpDisplay);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//	ON_COMMAND(ID_SYSCONFIG, OnSysconfig)
ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CPEMSysApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	

}


// CPEMSysApp 消息处理程序


int CPEMSysApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(lRet)
	{
	  if(m_pConnect->State == adStateOpen)
	  {
		m_pConnect->Close(); ///如果已经打开了连接则关闭它
		m_pConnect.Release();
	  }

	  if(m_pSearchConn->State == adStateOpen)
	  {
		  m_pSearchConn->Close();
		  m_pSearchConn.Release();
	  }
	   
	}
    ::CoUninitialize(); // 关闭COM环境
    g_af.Remove();
   return CWinApp::ExitInstance();
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_pLink.SetURL(_T("http://www.donews.net/mikewolfli/"));

	m_bmpDisplay.LoadAlphaBitmap(IDB_BITMAP_HELP, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CPEMSysApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CWinApp::PreTranslateMessage(pMsg);
}

bool CPEMSysApp::ADOExecute(_RecordsetPtr & ADOSet,_ConnectionPtr& pConn, _variant_t & strSQL)
{
	if ( ADOSet->State == adStateOpen)	ADOSet->Close();
	try
	{
		ADOSet->Open(strSQL, pConn.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdUnknown);
		return true;
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("ADO Error: %s",(char*)e.Description());
		AfxMessageBox(err);
		return false;
	}
}


BOOL CPEMSysApp::InitDataBaseConnect(void)
{
	HRESULT hr;
	_bstr_t strConn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source = "+m_strDataFile+"; Persist Security Info=False; Jet OLEDB:Database Password = "+m_strPassword.Trim();
	hr = m_pConnect.CreateInstance("ADODB.Connection");///创建Connection对象
	try
	{
	    if(SUCCEEDED(hr))
       {
		  m_pConnect->ConnectionTimeout=5;
		hr = m_pConnect->Open(strConn,"","",adModeUnknown);///连接数据库
        //上面一句中连接字串中的Provider是针对ACCESS2000环境的，对于ACCESS97,需要改为:Provider=Microsoft.Jet.OLEDB.3.51;  }

	      return TRUE;
	    }
		else
			return FALSE;
	}
	catch(_com_error &e)
	{
		
		CString err;
		err.Format("%s", (char*)(e.Description()) );
		AfxMessageBox(err);
		return FALSE;
	}
	catch(...)
	{
		
		AfxMessageBox("未知错误...");
		return FALSE;
	}

	// Init ADO RecordSet
}


/*// 返回记录集记录数量
long CPEMSysApp::TheGetRecordCount(_RecordsetPtr &m_pSet)
{
	long iTmp;
    
	if(!m_pSet->BOF)
		m_pSet->MoveFirst();
	while(!m_pSet->ADOEOF)
	{
		m_pSet->MoveNext ();
	}
	iTmp = m_pSet->GetRecordCount();
	return iTmp;

//	return 0;
}*/

HRESULT CPEMSysApp::get_Empty(_RecordsetPtr& ADOSet, VARIANT_BOOL* bEmpty)
{
	HRESULT hr = ADOSet->get_EndOfFile(bEmpty);
	if(SUCCEEDED(hr) && bEmpty)
		hr = ADOSet->get_BOF(bEmpty);

	return hr;;
}

int CPEMSysApp::GetRecordCountEx(_RecordsetPtr& pSet)
{
	int nCnt =0;
	if(!pSet->BOF)
		pSet->MoveFirst();
	while(!pSet->EndOfFile)
	    pSet->MoveNext();
	nCnt= pSet->GetRecordCount();
	return nCnt;
//	return 0;
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	EndDialog(1);
//	OnOK();
}
