// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once
#include "afxwin.h"
#include "atlcomtime.h"
#include "NewClientWnd.h"
#include "SysTipDlg.h"

class CMainFrame : public CMDIFrameWnd
{
public:
	CMainFrame();
	DECLARE_DYNAMIC(CMainFrame)

// ����
public:

	CMyBar m_MyBar;
	CImageList m_ImgList;
// ����
public:
	void Skin(/*LPCTSTR*/char* strSkinFile);

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
//	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	CDialogBar      m_wndDlgBar;
	CNewClientWnd	m_wndNewClient;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg long OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateDate(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
	DECLARE_PINDOCK()
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSysconfig();
	afx_msg void OnLogin();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	// ��ʼ���Ի��򹤾���;
	void SetDlgBarText(void);
	// ϵͳ����
//	COleDateTime m_Date;
	int IndexOfTimeZone;
	afx_msg void OnPassword();
	afx_msg void OnLogout();
	afx_msg void OnViewInstallbar();
	afx_msg void OnUpdateViewInstallbar(CCmdUI *pCmdUI);
	afx_msg void OnCloseAll();
	afx_msg void OnUpdateCloseAll(CCmdUI *pCmdUI);
	afx_msg void OnCloseNow();
	afx_msg void OnUpdateCloseNow(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePassword(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLogout(CCmdUI *pCmdUI);
	afx_msg void OnSysPerson();
	afx_msg void OnUpdateSysPerson(CCmdUI *pCmdUI);
	afx_msg void OnBackup();
	afx_msg void OnUpdateBackup(CCmdUI *pCmdUI);
	afx_msg void OnRestoredata();
	afx_msg void OnUpdateRestoredata(CCmdUI *pCmdUI);
	afx_msg void OnSkinSap();
	afx_msg void OnSkinGtclassic();
	afx_msg void OnSkinNo();
	// ����ͼ�йص��ĵ�����ָ��
	CDocument* m_pDoc;
	// ��¼��ͼ��Ӧ���ӿ�ܶ���ָ��
	CFrameWnd* m_pFrame;
	afx_msg void OnUpdateLogin(CCmdUI *pCmdUI);
	afx_msg void OnItemItem();
	afx_msg void OnUpdateItemItem(CCmdUI *pCmdUI);
//	afx_msg void OnItemShaft();
//	afx_msg void OnUpdateItemShaft(CCmdUI *pCmdUI);
//	afx_msg void OnItemBasicdata();
//	afx_msg void OnUpdateItemBasicdata(CCmdUI *pCmdUI);
	afx_msg void OnItemExcel();
	afx_msg void OnUpdateItemExcel(CCmdUI *pCmdUI);
//	void OnEditCut(void);
//	void OnEditCopy(void);
//	void OnEditPaste(void);
//	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
//	afx_msg void OnItemOrderconfig();
//	afx_msg void OnUpdateItemOrderconfig(CCmdUI *pCmdUI);
	afx_msg void OnItemDatainput();
	afx_msg void OnUpdateItemDatainput(CCmdUI *pCmdUI);
	afx_msg void OnItemCommercesearch();
	afx_msg void OnUpdateItemCommercesearch(CCmdUI *pCmdUI);
//	afx_msg void OnSearchItem();
//	afx_msg void OnSearchSameorderid();

	CSysTipDlg m_dTips;
	afx_msg void OnMenuInexport();
	afx_msg void OnUpdateMenuInexport(CCmdUI *pCmdUI);
};

