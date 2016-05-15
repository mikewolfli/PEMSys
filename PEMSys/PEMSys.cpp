// PEMSys.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CPEMSysApp ����

CPEMSysApp::CPEMSysApp()
: m_strDataFile(_T(""))
, m_strPassword(_T(""))
, lRet(FALSE)
, m_dCurrent(COleDateTime::GetCurrentTime())
{
	EnableHtmlHelp();

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CPEMSysApp ����

CAppFace g_af ;
CPEMSysApp theApp;
CString g_strUserID;
CString g_strUserName;
CString g_strUserPsw;
User_Type g_tUserType;
CString g_strUserDepartment;
BOOL g_Status = FALSE;
CString g_strAuthor;
// ���ɵĴ˱�ʶ����ͳ���϶�������Ӧ�ó�����Ψһ��
// �������Ըѡ��һ���ض��ı�ʶ��������Ը�����

// {0E2CE157-5F92-41A2-840D-B78713FB5C17}
static const CLSID clsid =
{ 0xE2CE157, 0x5F92, 0x41A2, { 0x84, 0xD, 0xB7, 0x87, 0x13, 0xFB, 0x5C, 0x17 } };
const GUID CDECL BASED_CODE _tlid =
		{ 0xA53BD978, 0x741C, 0x4FE7, { 0x97, 0x37, 0xBD, 0x71, 0xBC, 0xCD, 0xE0, 0x28 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CPEMSysApp ��ʼ��

BOOL CPEMSysApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();
 
	CWinApp::InitInstance();

	//�˳���ֻ������һ�Σ��û��������жϳ����Ƿ�������
	HANDLE m_hMutex=CreateMutex(NULL,TRUE, m_pszAppName); 
	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{ 
		AfxMessageBox("PEMSys�����Ѿ�����!");
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

	// ��ʼ�� OLE ��
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
			MessageBox(NULL,"�Ի��򴴽�ʧ�ܣ�","Client Error:", MB_OK);

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



	////////////�������ݿ�//////////////

	BOOL blnInit;
	blnInit = InitDataBaseConnect();
	while(!blnInit)
	{
		InitRet = lDlg.DoModal();
		switch(InitRet) {
		case -1: 
			MessageBox(NULL,"�Ի��򴴽�ʧ�ܣ�","Client Error:", MB_OK);

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
	hr = m_pSearchConn.CreateInstance("ADODB.Connection");///����Connection����
	try
	{
		if(SUCCEEDED(hr))
		{
			strConn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source = .\\Configure.cfg";

			hr = m_pSearchConn->Open(strConn,"","",NULL);///�������ݿ�
			//  	hr = m_pConnect->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=E:\\Configuration\\configure.mdb","","",adConnectUnspecified));///�������ݿ�
			///����һ���������ִ��е�Provider�����ACCESS2000�����ģ�����ACCESS97,��Ҫ��Ϊ:Provider=Microsoft.Jet.OLEDB.3.51;  }
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

		AfxMessageBox("δ֪����...");
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
					MessageBox(NULL,"�Ի��򴴽�ʧ�ܣ�","Client Error:", MB_OK);

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
							AfxMessageBox("ע����Ѿ�����!\n����������!",MB_ICONEXCLAMATION);
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
			AfxMessageBox("ע����Ѿ�����!\n����������!",MB_ICONEXCLAMATION);
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
				MessageBox(NULL,"�Ի��򴴽�ʧ�ܣ�","Client Error:", MB_OK);

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
						AfxMessageBox("ע����Ѿ�����!\n����������!",MB_ICONEXCLAMATION);
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


	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	m_pPEMSysTemplate  = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CPEMSysDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
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
	// �� COleTemplateServer ���ӵ��ĵ�ģ��
	// COleTemplateServer ͨ��ʹ��
	// �ĵ�ģ����ָ������Ϣ��Ϊ
	// ���� OLE �����������ĵ�
//	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);
	// �����е� OLE ����������ע��Ϊ�������С��⽫����
	//  OLE ���Դ�����Ӧ�ó����д�������
//	COleTemplateServer::RegisterAll();
		// ע��: MDI Ӧ�ó���ע�����еķ��������󣬶�����
		// �������ϵ� /Embedding �� /Automation
	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;

	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
	//	delete m_pSplashWnd;
		return FALSE;
	}

	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	// ������/��
	m_pMainWnd->DragAcceptFiles();
	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//��Ӵ����ֹ�Զ��򿪿հ��ĵ�
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	// Ӧ�ó������� /Embedding �� /Automation ���������ġ�
	//ʹӦ�ó�����Ϊ�Զ������������С�
//	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
//	{
		// ����ʾ������
//		return TRUE;
//	}
	// ʹ�� /Unregserver �� /Unregister ��������Ӧ�ó���  ע��
	// ���Ϳ⡣����ע�������� ProcessShellCommand() �з�����
//	else if (cmdInfo.m_nShellCommand ==		CCommandLineInfo::AppUnregister)
//	{
//		UnregisterShellFileTypes();
//		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
///		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
//	}
	// Ӧ�ó������Զ�����ʽ������������(�� /Register
	// �� /Regserver)�����ġ�����ע�����������Ϳ⡣
//	else
//	{
//		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
//		COleObjectFactory::UpdateRegistryAll();
//		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
//	}
	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
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

    
	// �������ѳ�ʼ���������ʾ����������и���

	pMainFrame->SetWindowText("���ݺ�ͬ����ϵͳPEMSys 1.0");
	m_nCmdShow = SW_SHOWMAXIMIZED;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();



 //   delete m_pSplashWnd;
	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CPEMSysApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
	

}


// CPEMSysApp ��Ϣ�������


int CPEMSysApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(lRet)
	{
	  if(m_pConnect->State == adStateOpen)
	  {
		m_pConnect->Close(); ///����Ѿ�����������ر���
		m_pConnect.Release();
	  }

	  if(m_pSearchConn->State == adStateOpen)
	  {
		  m_pSearchConn->Close();
		  m_pSearchConn.Release();
	  }
	   
	}
    ::CoUninitialize(); // �ر�COM����
    g_af.Remove();
   return CWinApp::ExitInstance();
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_pLink.SetURL(_T("http://www.donews.net/mikewolfli/"));

	m_bmpDisplay.LoadAlphaBitmap(IDB_BITMAP_HELP, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CPEMSysApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

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
	hr = m_pConnect.CreateInstance("ADODB.Connection");///����Connection����
	try
	{
	    if(SUCCEEDED(hr))
       {
		  m_pConnect->ConnectionTimeout=5;
		hr = m_pConnect->Open(strConn,"","",adModeUnknown);///�������ݿ�
        //����һ���������ִ��е�Provider�����ACCESS2000�����ģ�����ACCESS97,��Ҫ��Ϊ:Provider=Microsoft.Jet.OLEDB.3.51;  }

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
		
		AfxMessageBox("δ֪����...");
		return FALSE;
	}

	// Init ADO RecordSet
}


/*// ���ؼ�¼����¼����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	EndDialog(1);
//	OnOK();
}
