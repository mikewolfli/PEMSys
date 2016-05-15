#pragma once
#include "afxwin.h"
#include "atlcomtime.h"

// CLoginDialog 对话框

class CLoginDialog : public CDialog
{
	DECLARE_DYNAMIC(CLoginDialog)

public:
	CLoginDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 登录密码
	CString m_sPassword;
	afx_msg void OnBkClickOk();
	afx_msg void OnBkClickCancel();
	virtual BOOL OnInitDialog();
private:
	// 数据集对象
	_RecordsetPtr m_pUsersSet;
public:
	CString m_sLoginID;
	CEdit m_cUserID;
	CEdit m_cPassword;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	BOOL m_bUPSave;
	BOOL lRet;
	CString FilePath;
};
