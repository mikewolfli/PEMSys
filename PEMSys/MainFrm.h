// MainFrm.h : CMainFrame 类的接口
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

// 属性
public:

	CMyBar m_MyBar;
	CImageList m_ImgList;
// 操作
public:
	void Skin(/*LPCTSTR*/char* strSkinFile);

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar  m_wndStatusBar;
//	CToolBar    m_wndToolBar;
	CReBar      m_wndReBar;
	CDialogBar      m_wndDlgBar;
	CNewClientWnd	m_wndNewClient;

// 生成的消息映射函数
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
	// 初始化对话框工具条;
	void SetDlgBarText(void);
	// 系统日期
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
	// 与视图有关的文档对象指针
	CDocument* m_pDoc;
	// 记录视图对应的子框架对象指针
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

