// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "PEMSys.h"

#include "MainFrm.h"
//#include ".\mainfrm.h"
#include "PEMSysView.h"
#include "SysConfig.h"
#include "LoginDialog.h"
#include "ResetPaswdDialog.h"
#include "ItemView.h"
#include "ItemDataInputView.h"
#include "ItemExcelView.h"
#include "ItemCommerceSearchView.h"
#include "ItemInExportView.h"
#include "GfxOutBarCtrl.h"
#include ".\mainfrm.h"

//#include "ItemOrderConfigView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

extern CPEMSysApp theApp;
extern CString g_strUserID;
extern CString g_strUserName;
extern CString g_strUserPsw;
extern CString g_strUserDepartment;
extern User_Type g_tUserType;
extern BOOL g_Status;

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)
IMPLEMENT_PINDOCK(CMainFrame)
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	// ȫ�ְ�������
	ON_COMMAND(ID_HELP_FINDER, CMDIFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpFinder)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_SYSCONFIG, OnSysconfig)
	ON_COMMAND(ID_LOGIN, OnLogin)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DATE, OnUpdateDate)
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_COMMAND(ID_PASSWORD, OnPassword)
	ON_COMMAND(ID_LOGOUT, OnLogout)
	ON_COMMAND(ID_VIEW_INSTALLBAR, OnViewInstallbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INSTALLBAR, OnUpdateViewInstallbar)
	//}}AFX_MSG_MAP
	ON_PINDOCK_MESSAGES()
	ON_MESSAGE(WM_OUTBAR_NOTIFY, OnOutbarNotify)
	ON_COMMAND(IDW_CLOSE_ALL, OnCloseAll)
	ON_UPDATE_COMMAND_UI(IDW_CLOSE_ALL, OnUpdateCloseAll)
	ON_COMMAND(IDW_CLOSE_NOW, OnCloseNow)
	ON_UPDATE_COMMAND_UI(IDW_CLOSE_NOW, OnUpdateCloseNow)
	ON_UPDATE_COMMAND_UI(ID_PASSWORD, OnUpdatePassword)
	ON_UPDATE_COMMAND_UI(ID_LOGOUT, OnUpdateLogout)
	ON_COMMAND(ID_SYS_PERSON, OnSysPerson)
	ON_UPDATE_COMMAND_UI(ID_SYS_PERSON, OnUpdateSysPerson)
	ON_COMMAND(ID_BACKUP, OnBackup)
	ON_UPDATE_COMMAND_UI(ID_BACKUP, OnUpdateBackup)
	ON_COMMAND(ID_RESTOREDATA, OnRestoredata)
	ON_UPDATE_COMMAND_UI(ID_RESTOREDATA, OnUpdateRestoredata)
	ON_COMMAND(ID_SKIN_SAP, OnSkinSap)
	ON_COMMAND(ID_SKIN_GTCLASSIC, OnSkinGtclassic)
	ON_COMMAND(ID_SKIN_NO, OnSkinNo)
	ON_UPDATE_COMMAND_UI(ID_LOGIN, OnUpdateLogin)
	ON_COMMAND(ID_ITEM_ITEM, OnItemItem)
	ON_UPDATE_COMMAND_UI(ID_ITEM_ITEM, OnUpdateItemItem)
//	ON_COMMAND(ID_ITEM_SHAFT, OnItemShaft)
//	ON_UPDATE_COMMAND_UI(ID_ITEM_SHAFT, OnUpdateItemShaft)
//	ON_COMMAND(ID_ITEM_BASICDATA, OnItemBasicdata)
//	ON_UPDATE_COMMAND_UI(ID_ITEM_BASICDATA, OnUpdateItemBasicdata)
	ON_COMMAND(ID_ITEM_EXCEL, OnItemExcel)
	ON_UPDATE_COMMAND_UI(ID_ITEM_EXCEL, OnUpdateItemExcel)
//	ON_MESSAGE(WM_HOTKEY, OnHotKey)
//	ON_COMMAND(ID_ITEM_ORDERCONFIG, OnItemOrderconfig)
//	ON_UPDATE_COMMAND_UI(ID_ITEM_ORDERCONFIG, OnUpdateItemOrderconfig)
	ON_COMMAND(ID_ITEM_DATAINPUT, OnItemDatainput)
	ON_UPDATE_COMMAND_UI(ID_ITEM_DATAINPUT, OnUpdateItemDatainput)
	ON_COMMAND(ID_ITEM_COMMERCESEARCH, OnItemCommercesearch)
	ON_UPDATE_COMMAND_UI(ID_ITEM_COMMERCESEARCH, OnUpdateItemCommercesearch)
//	ON_COMMAND(ID_SEARCH_ITEM, OnSearchItem)
//	ON_COMMAND(ID_SEARCH_SAMEORDERID, OnSearchSameorderid)
ON_COMMAND(ID_MENU_INEXPORT, OnMenuInexport)
ON_UPDATE_COMMAND_UI(ID_MENU_INEXPORT, OnUpdateMenuInexport)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��                  
		ID_INDICATOR_CAPS,
		ID_INDICATOR_NUM,
		ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
: IndexOfTimeZone(0)
, m_pDoc(NULL)
, m_pFrame(NULL)
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//	if (!m_wndToolBar.CreateEx(this) ||
	//		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//	{
	//		TRACE0("δ�ܴ���������\n");
	//		return -1;      // δ�ܴ���
	//	}

	//�������ñ�����ɫ��λͼ,���໯�½��Ķ��ĵ�����
	if (!m_wndNewClient.SubclassWindow(m_hWndMDIClient))
	{
		TRACE("Failed to subclass MDI client window\n");
		return -1;      // fail to create
	}

	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("δ�ܴ����Ի���\n");
		return -1;		// δ�ܴ���
	}

	//   if (!m_wndReBar.Create(this))
	if (!m_wndReBar.Create(this) ||
		//		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("δ�ܴ��� Rebar\n");
		return -1;      // δ�ܴ���
	}
	EnablePinDocking(CBRS_ALIGN_ANY);
//	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndDlgBar);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	int nOrigSize = sizeof(indicators) / sizeof(UINT);
	UINT* pIndicators = new UINT[nOrigSize +1];
	memcpy(pIndicators, indicators, sizeof(indicators));
	IndexOfTimeZone = nOrigSize++;
	pIndicators[IndexOfTimeZone] = ID_INDICATOR_DATE;
	m_wndStatusBar.SetIndicators(pIndicators, nOrigSize);
	delete[] pIndicators;

	m_ImgList.Create(IDB_TAB, 16, 1, RGB(255,0,255));
	for(int i = 0;i < 4; i ++)
	m_AutoHideBar[i].SetImageList(&m_ImgList);
	if (!m_MyBar.Create(_T("OutLook������"), this, 127))
	{
		return -1;		// fail to create
	}
	m_MyBar.SetSCBStyle(m_MyBar.GetSCBStyle() |
		SCBS_SIZECHILD);
	m_MyBar.SetBarStyle(m_MyBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_MyBar.EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_MyBar, AFX_IDW_DOCKBAR_LEFT);
//	DockControlBar(&m_MyBar);
    this->SetTitle("���ݺ�ͬ����ϵͳPEMSys 1.3.0.0");
	m_MyBar.wndBar.SetOwner(this);

 //   this->SetTitle("���ݺ�ͬ����ϵͳPEMSys 1.0");
	// TODO: �������Ҫ������ʾ���򽫴��Ƴ�
	//	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
	//		CBRS_TOOLTIPS | CBRS_FLYBY);
    SetDlgBarText();

	CString  FilePath;
	FilePath+=".\\Config.ini";

	CString strSection = _T("Path");
	CString strSectionKey  = _T("Skin");
	char inBuf[80];
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	Skin(inBuf);
/*
	RegisterHotKey(m_hWnd, 10001, MOD_CONTROL, 'C');
	RegisterHotKey(m_hWnd, 10002, MOD_CONTROL, 'c');
	RegisterHotKey(m_hWnd, 10003, MOD_CONTROL, 'V');
	RegisterHotKey(m_hWnd, 10004, MOD_CONTROL, 'v');
	RegisterHotKey(m_hWnd, 10005, MOD_CONTROL, 'X');
	RegisterHotKey(m_hWnd, 10006, MOD_CONTROL, 'x');
*/
	BOOL bTip;
	char chTip[80];
	CString sTip;

	strSection = _T("PathofDatabase");
	strSectionKey  = _T("Tips");
	BOOL lRet = GetPrivateProfileString (strSection,strSectionKey, NULL, chTip, 256, FilePath); 
	if(lRet)
	{
		sTip = *chTip;
		if(sTip=="1"||sTip=="2")
			bTip = TRUE;
		else 
			bTip= FALSE;
		if(bTip)
			m_dTips.DoModal();

 
	}
//	m_dTips.DoModal();
	return 0;
}


void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
/*	UnregisterHotKey(m_hWnd, 10001);
	UnregisterHotKey(m_hWnd, 10002);
	UnregisterHotKey(m_hWnd, 10003);
	UnregisterHotKey(m_hWnd, 10004);
	UnregisterHotKey(m_hWnd, 10005);
	UnregisterHotKey(m_hWnd, 10006);
*/
	if(MessageBox("ȷ���˳�ϵͳ��?","�˳�ѯ��",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		CMDIFrameWnd::OnClose();
}
/*
LRESULT CMainFrame::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if(wParam ==10001 || wParam ==10002)
	{
		OnEditCopy();
	}
	if(wParam ==10002 || wParam ==10003)
	{
		OnEditPaste();
	}
	if(wParam ==10005 || wParam ==10006)
	{
		OnEditCut();
	}
	return 0;
}

void CMainFrame::OnEditCut(void)
{		
	CWnd* m_pwnd = this->GetActiveWindow();
	if(m_pwnd->GetSafeHwnd())
		((CEdit*)m_pwnd->GetFocus())->Cut();	

}

void CMainFrame::OnEditCopy(void)
{
	CWnd* m_pwnd = this->GetActiveWindow();
	if(m_pwnd->GetSafeHwnd())
		((CEdit*)m_pwnd->GetFocus())->Copy();	
}

void CMainFrame::OnEditPaste(void)
{
	CWnd* m_pwnd = this->GetActiveWindow();
	if(m_pwnd->GetSafeHwnd())
		((CEdit*)m_pwnd->GetFocus())->Paste();	
}
*/
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame ��Ϣ�������


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMDIFrameWnd::OnGetMinMaxInfo(lpMMI);
	CRect	rectClient;
	GetClientRect(&rectClient);

	CRect	rectWindow;
	GetWindowRect(&rectWindow);

	int nWidthOverhead = rectWindow.Width() - rectClient.Width();
	int nHeightOverhead = rectWindow.Height() - rectClient.Height();

	lpMMI->ptMinTrackSize.x = 800 + nWidthOverhead;
	lpMMI->ptMinTrackSize.y = 600 + nHeightOverhead;
}

void CMainFrame::OnSysconfig()
{
	// TODO: �ڴ���������������
	CSysConfig m_config;
	m_config.DoModal();
}

void CMainFrame::OnLogin()
{
	// TODO: �ڴ���������������
	CLoginDialog m_login;
	int InitRet;
	InitRet = m_login.DoModal();
	switch(InitRet) {
		case -1: 
			MessageBox(NULL,"�Ի��򴴽�ʧ��", MB_OK);
			break;
		case IDCANCEL:
			break;
		case IDOK:
			SetDlgBarText();
			break;
		default:
			break;
	}

}

long CMainFrame::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case NM_OB_ITEMCLICK:
		// cast the lParam to an integer to get the clicked item
		{
			int nFolder = m_MyBar.wndBar.GetSelFolder();
			int index = (int) lParam;
			switch(nFolder)
			{
			case 0:
				switch(index)
				{
				case 0:
					if(g_Status)
					{
                        OnItemItem();
					}
					else
					{
						AfxMessageBox("ע��״̬,���ȵ�¼!", MB_ICONEXCLAMATION);
						return 0;
					}
					break;

				case 1:
					if(g_Status)
					{
						OnItemDatainput();
					}
					else
					{
						AfxMessageBox("ע��״̬,���ȵ�¼!", MB_ICONEXCLAMATION);
						return 0;
					}
					break;
				case 2:
					if(g_Status && g_tUserType>=2)
					{
						OnItemCommercesearch();
					}else
					{
						AfxMessageBox("ע��״̬,���ȵ�¼!\n//�����û��޴�ʹ��Ȩ��", MB_ICONEXCLAMATION);
						return 0;
					}
					break;
				case 3:
					if(g_Status)
					{
						OnMenuInexport();					
//						OnItemExcel();
					}else
					{
						AfxMessageBox("ע��״̬,���ȵ�¼!", MB_ICONEXCLAMATION);
						return 0;
					}
					break;
				default:
					break;

				}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
//			case 5:
//				break;
//			case 6:
//				switch(index)
//				{
//				case 0:
//					if(!g_Status || g_tUserType < 4)
//					{
//						return 0;
//					}else
//					{
//						OnSysPerson();
//					}
//					break;
//				case 1:
//					if(!g_Status)
//						return 0;
//					else 
//						OnSysconfig();
//					break;
//				}
//				break;
			default:
				break;
			}

		}
		break;
	default:
		break;

		/*	case NM_OB_ONLABELENDEDIT:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the edited item
		// return 1 to do the change and 0 to cancel it
		{
		OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
		TRACE2("Editing item %d, new text:%s\n", pOI->index, pOI->cText);
		}
		return 1;

		case NM_OB_ONGROUPENDEDIT:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the edited folder
		// return 1 to do the change and 0 to cancel it
		{
		OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
		TRACE2("Editing folder %d, new text:%s\n", pOI->index, pOI->cText);
		}
		return 1;

		case NM_OB_DRAGITEM:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the dragged items
		// return 1 to do the change and 0 to cancel it
		{
		OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
		TRACE2("Drag item %d at position %d\n", pOI->iDragFrom, pOI->iDragTo);
		}
		return 1;*/
	}
	return 0;
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return CMDIFrameWnd::OnEraseBkgnd(pDC);
	return TRUE;
}


// ��ʼ���Ի��򹤾���;
void CMainFrame::SetDlgBarText(void)
{
	CString strDepartment;	
	if(g_strUserName.IsEmpty())
	{
       m_wndDlgBar.SetDlgItemText(IDC_EDIT_USER, _T("δ��¼"));
	}
	else
		m_wndDlgBar.SetDlgItemText(IDC_EDIT_USER, g_strUserName); 

	if(g_strUserDepartment.IsEmpty())
		    strDepartment = _T("δ��¼");
	else strDepartment = g_strUserDepartment;

	m_wndDlgBar.SetDlgItemText(IDC_EDIT_DEPARTMENT,strDepartment);
	switch(g_tUserType) {
		case 0:
			m_wndDlgBar.SetDlgItemText(IDC_EDIT_POPEDOM, _T("δ��¼"));
			break;
		case 1:
			m_wndDlgBar.SetDlgItemText(IDC_EDIT_POPEDOM, _T("�����û�"));
			break;
		case 2:
			m_wndDlgBar.SetDlgItemText(IDC_EDIT_POPEDOM, _T("��ͨ��"));
			break;
		case 3:
			m_wndDlgBar.SetDlgItemText(IDC_EDIT_POPEDOM, _T("����"));
			break;
		case 4:
			m_wndDlgBar.SetDlgItemText(IDC_EDIT_POPEDOM, _T("ϵͳ����Ա"));
			break;
		case 5:
			m_wndDlgBar.SetDlgItemText(IDC_EDIT_POPEDOM, _T("�����û�"));
			break;
		default:
			break;
	}

	//	m_wndDlgBar.SetDlgItemText(IDC_EDIT_DATE, m_Date.Format(_T("%Y-%m-%d, %A")));

}

void CMainFrame::OnUpdateDate(CCmdUI* pCmdUI)
{
	//�õ�ϵͳʱ��
	COleDateTime Datetime = COleDateTime::GetCurrentTime();
	CString strDateTime = Datetime.Format(_T("%A %Y-%m-%d %H:%M:%S"));

	//����ʱ��
	//�ַ����ĳ��ȼ�������״̬��������賤��
	CSize size;
	HGDIOBJ hOldFont = NULL;

	//�õ���ǰ״̬������
	HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
	CClientDC dc(NULL);
	if(hFont != NULL)
		hOldFont = dc.SelectObject(hFont);

	//�õ���ǰ�ı�������ʾ���
	size = dc.GetTextExtent(strDateTime);
	if(hOldFont != NULL)
		dc.SelectObject(hOldFont);

	//�޸�״̬��
	//����ʱ��������
	m_wndStatusBar.SetPaneInfo(IndexOfTimeZone, ID_INDICATOR_DATE, 0, size.cx);

	//����ʱ���������
	pCmdUI->SetText(strDateTime);

	//����ʱ������
	pCmdUI->Enable(TRUE);
}
void CMainFrame::OnPassword()
{
	// TODO: �ڴ���������������
	if(!g_Status)
	{
		AfxMessageBox(_T("����δ��¼!"),MB_ICONEXCLAMATION);
		return;
	}
	CResetPaswdDialog m_lDlg;
	m_lDlg.DoModal();
}

void CMainFrame::OnLogout()
{
	// TODO: �ڴ���������������
	if(AfxMessageBox("ȷ��ע��?",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	{
		g_Status = FALSE;
		g_strUserID.Empty();
		g_strUserName.Empty();
		g_strUserPsw.Empty();
		g_strUserDepartment.Empty();
		g_tUserType = UnLogin;
		SetDlgBarText();
		OnCloseAll();
	}
	else
		return;
}

void CMainFrame::OnViewInstallbar()
{
	// TODO: �ڴ���������������
	BOOL bShow = m_MyBar.IsVisible();
	ShowControlBar(&m_MyBar, !bShow, FALSE);
}

void CMainFrame::OnUpdateViewInstallbar(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(m_MyBar.wndBar.GetParent() == &(m_MyBar));
	pCmdUI->SetCheck(m_MyBar.IsVisible());
}

void CMainFrame::OnCloseAll()
{
	// TODO: �ڴ���������������
	CMDIFrameWnd *pFrame = 
		(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

	CMDIChildWnd *pChild = 
		(CMDIChildWnd *)pFrame->GetActiveFrame();

	CView	*pView = NULL;

	CDocument *pDocument = pChild->GetActiveDocument();

	if(pDocument != NULL)
	{
		POSITION pos = pDocument->GetFirstViewPosition();
		while(pos != NULL)
		{
			pView= pDocument->GetNextView(pos);
			if(pView != NULL)
			{
				pView->GetParentFrame()->DestroyWindow();
			}
		}
	}
}

void CMainFrame::OnUpdateCloseAll(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	OnUpdateCloseNow(pCmdUI);
}

void CMainFrame::OnCloseNow()
{
	// TODO: �ڴ���������������
	//��ȡ�����ָ��
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*) AfxGetApp()->m_pMainWnd;
	//��ȡ�ӿ��ָ��
	CMDIChildWnd *pChild = (CMDIChildWnd*) pFrame->GetActiveFrame();

	//��ȡ���ͼָ��
	CView *pView;
	pView = pChild->GetActiveView();
	//�����ͼָ�벻Ϊ��,��رո���ͼ��Ӧ���Դ���
	if(pView != NULL)
	{
		pView->GetParentFrame()->DestroyWindow();
	}
}

void CMainFrame::OnUpdateCloseNow(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	BOOL bVisible;

	CMDIFrameWnd *pFrame = 
		(CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;

	if(pFrame != NULL)
	{
		CMDIChildWnd *pChild = 
			(CMDIChildWnd *)pFrame->GetActiveFrame();

		CView	*pView = pChild->GetActiveView();

		if(pView ==NULL)
		{
			bVisible = FALSE;
		}
		else
		{
			bVisible = TRUE;
		}
	}
	else
	{
		bVisible = FALSE;
	}
	pCmdUI->Enable(bVisible);
	pCmdUI->SetCheck(bVisible);
}


void CMainFrame::OnUpdatePassword(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(g_Status);
}

void CMainFrame::OnUpdateLogout(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(g_Status);
}


void CMainFrame::OnBackup()
{
	// TODO: �ڴ���������������
}

void CMainFrame::OnUpdateBackup(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	BOOL b_visible = TRUE;
	if((!g_Status) || (g_tUserType < 4))
	{
		b_visible = FALSE;
	}
	pCmdUI->Enable(b_visible);
}

void CMainFrame::OnRestoredata()
{
	// TODO: �ڴ���������������
}

void CMainFrame::OnUpdateRestoredata(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	BOOL b_visible = TRUE;
	if((!g_Status) || (g_tUserType < 4))
	{
		b_visible = FALSE;
	}
	pCmdUI->Enable(b_visible);
}

void CMainFrame::Skin(/*LPCTSTR */ char* strSkinFile)
{
//	char path[256];
//	memset(path,0,256) ;
//	GetModuleFileName(NULL,path,256) ;
//	char * p =".\\skin\\";
//	if(!p) 
//		return;
//	strcpy(p,"\\\0\0");
//	strcat(p,strSkinFile);
//	g_af.Start(path) ;
	g_af.Start(strSkinFile) ;

	char appPath[256];
	CString  FilePath;
	GetCurrentDirectory(256,appPath); //ȡ��Ӧ�ó���ǰ·��
	FilePath.Format("%s",appPath);
	FilePath+="\\Config.ini";


	CString strSection = _T("Path");
	CString strSectionKey  = _T("Skin");
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strSkinFile), FilePath);

	m_MyBar.wndBar.SkinReset() ;

	for(int i=0;i<4;i++)
		m_AutoHideBar[i].SkinReset() ;
}

void CMainFrame::OnSkinSap()
{
	// TODO: �ڴ���������������
	Skin(_T(".\\skin\\sap_af.urf"));
}

void CMainFrame::OnSkinGtclassic()
{
//	// TODO: �ڴ���������������
	Skin(_T(".\\skin\\gtclassic.urf")) ;
}

void CMainFrame::OnSkinNo()
{
	// TODO: �ڴ���������������
	Skin(_T("")) ;
}

void CMainFrame::OnUpdateLogin(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(!g_Status);
}


void CMainFrame::OnSysPerson()
{
	// TODO: �ڴ���������������
	CPEMSysView *pFindView = NULL;
	EkNewOrOpenWnd<CPEMSysView>(theApp.m_pPEMSysTemplate, m_pDoc, m_pFrame, pFindView, "CPEMSysView");
	delete pFindView;
}

void CMainFrame::OnUpdateSysPerson(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	BOOL b_visible = TRUE;
	if((!g_Status) || (g_tUserType < 4))
	{
		b_visible = FALSE;
	}
	pCmdUI->Enable(b_visible);
}

void CMainFrame::OnItemItem()
{
	// TODO: �ڴ���������������
	CItemView *pFindView = NULL;
	EkNewOrOpenWnd<CItemView>(theApp.m_pItemViewTemplate, m_pDoc, m_pFrame, pFindView, "CItemView");
	delete pFindView;
}

void CMainFrame::OnUpdateItemItem(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(g_Status);
}

//void CMainFrame::OnItemShaft()
//{
//	// TODO: �ڴ���������������
//
//}

//void CMainFrame::OnUpdateItemShaft(CCmdUI *pCmdUI)
//{
//	// TODO: �ڴ������������û����洦��������
//	pCmdUI->Enable(g_Status);
//}
/*
void CMainFrame::OnItemBasicdata()
{
	// TODO: �ڴ���������������
	CItemBasicDataView *pFindView = NULL;
	EkNewOrOpenWnd<CItemBasicDataView>(theApp.m_pItemBasicDataTemplate, m_pDoc, m_pFrame, pFindView, "CItemBasicDataView");
	delete pFindView;
}

void CMainFrame::OnUpdateItemBasicdata(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(g_Status);
}
*/
void CMainFrame::OnItemExcel()
{
	// TODO: �ڴ���������������
	CItemExcelView *pFindView = NULL;
	EkNewOrOpenWnd<CItemExcelView>(theApp.m_pItemExcelTemplate, m_pDoc, m_pFrame, pFindView, "CItemExcelView");
	delete pFindView;
}
/*
void CMainFrame::OnItemOrderconfig()
{
	// TODO: �ڴ���������������
	CItemOrderConfigView *pFindView = NULL;
	EkNewOrOpenWnd<CItemOrderConfigView>(theApp.m_pItemOrderConfigTemplate, m_pDoc, m_pFrame, pFindView, "CItemOrderConfigView");
	delete pFindView;

}

void CMainFrame::OnUpdateItemOrderconfig(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(g_Status);
}*/


void CMainFrame::OnUpdateItemExcel(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
//	pCmdUI->Enable(g_Status);
	pCmdUI->Enable(FALSE);
}


void CMainFrame::OnItemDatainput()
{
	// TODO: �ڴ���������������
	CItemDataInputView *pFindView = NULL;
	EkNewOrOpenWnd<CItemDataInputView>(theApp.m_pItemDataInputTemplate, m_pDoc, m_pFrame, pFindView, "CItemDataInputView");
	delete pFindView;
}

void CMainFrame::OnUpdateItemDatainput(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		pCmdUI->Enable(g_Status);
}

void CMainFrame::OnItemCommercesearch()
{
	// TODO: �ڴ���������������
	CItemCommerceSearchView *pFindView = NULL;
	EkNewOrOpenWnd<CItemCommerceSearchView>(theApp.m_pItemCommerceSearchTemplate, m_pDoc, m_pFrame, pFindView, "CItemCommerceSearchView");
	delete pFindView;
}

void CMainFrame::OnUpdateItemCommercesearch(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(g_Status);
}

//void CMainFrame::OnSearchItem()
//{
//	// TODO: �ڴ���������������
//		CSearchPopItemDlg lDlg;
//		lDlg.m_sOrderID = gOrderID;
//		if(!gOrderID.IsEmpty())
//			lDlg.DoModal();
//		else
//			return;
//}

//void CMainFrame::OnSearchSameorderid()
//{
//	// TODO: �ڴ���������������
//	CSearchPopOrderIDDlg lDlg;
//	lDlg.m_sOrderID = gOrderID;
//	if(!gOrderID.IsEmpty())
//		lDlg.DoModal();
//	else
//		return;
//}

void CMainFrame::OnMenuInexport()
{
	// TODO: �ڴ���������������
	CItemInExportView *pFindView = NULL;
	EkNewOrOpenWnd<CItemInExportView>(theApp.m_pItemInExortViewTempleate, m_pDoc, m_pFrame, pFindView, "CItemInExportView");
	delete pFindView;
}

void CMainFrame::OnUpdateMenuInexport(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(g_Status);
}
