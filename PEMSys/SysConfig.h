#pragma once
#include "afxwin.h"


// CSysConfig 对话框

class CSysConfig : public CDialog
{
	DECLARE_DYNAMIC(CSysConfig)

public:
	CSysConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysConfig();

// 对话框数据
	enum { IDD = IDD_DIALOG_SYSCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBrower();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CButton m_cBrower;
	afx_msg void OnBnClickedCancel();
	BOOL m_bTip;
	CString FilePath;
	BOOL m_bTip2;
	afx_msg void OnBnClickedCheckTips();
	afx_msg void OnBnClickedCheckTipsReturn();
};
