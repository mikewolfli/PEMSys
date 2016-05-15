#pragma once
#include "afxwin.h"


// CResetPaswdDialog 对话框

class CResetPaswdDialog : public CDialog
{
	DECLARE_DYNAMIC(CResetPaswdDialog)

public:
	CResetPaswdDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResetPaswdDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_RESETPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	// 旧密码
	CString m_sOldPassword;
	CEdit m_cOldPassword;
	CString m_sNewPassword;
	CString m_sNPConfirm;
private:
	_RecordsetPtr m_pADOSet;
protected:
	virtual void OnCancel();
public:
	CEdit m_cNPConfirm;
	CEdit m_cNewPassword;
protected:
	virtual void OnOK();
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
