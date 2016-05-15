#pragma once
#include "afxwin.h"
#include "atlcomtime.h"

// CLoginDialog �Ի���

class CLoginDialog : public CDialog
{
	DECLARE_DYNAMIC(CLoginDialog)

public:
	CLoginDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��¼����
	CString m_sPassword;
	afx_msg void OnBkClickOk();
	afx_msg void OnBkClickCancel();
	virtual BOOL OnInitDialog();
private:
	// ���ݼ�����
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
