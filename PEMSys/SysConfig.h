#pragma once
#include "afxwin.h"


// CSysConfig �Ի���

class CSysConfig : public CDialog
{
	DECLARE_DYNAMIC(CSysConfig)

public:
	CSysConfig(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysConfig();

// �Ի�������
	enum { IDD = IDD_DIALOG_SYSCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
