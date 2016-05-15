#pragma once
#include "afxwin.h"


// CItemSearchOutOrderDlg �Ի���

class CItemSearchOutOrderDlg : public CDialog
{
	DECLARE_DYNAMIC(CItemSearchOutOrderDlg)

public:
	CItemSearchOutOrderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CItemSearchOutOrderDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1_DISPLAYPOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_cList;
	void MoveUpOrDown(BOOL bCheck);
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonBottom();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	void MoveUporDownEnd(BOOL bDir);
	virtual BOOL OnInitDialog();
};
