#pragma once
#include "afxwin.h"


// CRegisterDlg �Ի���

class CRegisterDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegisterDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_sFirst;
	CString m_sSecond;
	CString m_sThird;
	CString m_sFourth;
	afx_msg void OnBnClickedOk();
	CString m_sCode;
	CString m_sUserName;
	CEdit m_cUserName;
	CEdit m_cFirst;
	CEdit m_cSecond;
	CEdit m_cThird;
	CEdit m_cFourth;
};
