#pragma once
#include "afxwin.h"


// CResetPaswdDialog �Ի���

class CResetPaswdDialog : public CDialog
{
	DECLARE_DYNAMIC(CResetPaswdDialog)

public:
	CResetPaswdDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResetPaswdDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_RESETPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	// ������
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
