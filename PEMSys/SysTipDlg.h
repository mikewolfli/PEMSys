#pragma once
#include "atlcomtime.h"
#include "afxwin.h"


// CSysTipDlg �Ի���
#include ".\gridctrl\gridctrl.h"

class CSysTipDlg : public CDialog
{
	DECLARE_DYNAMIC(CSysTipDlg)

public:
	CSysTipDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysTipDlg();

// �Ի������� 
	enum { IDD = IDD_DIALOG1_TIPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	_variant_t strSQL;
	_variant_t Holder;
private:
	_RecordsetPtr m_pSet;
public:
	COleDateTime m_dCurrent;
	CGridCtrl m_cList;
	BOOL m_bTip;
	afx_msg void OnBnClickedCheckNexttips();
	CString FilePath;
	afx_msg void OnBnClickedCheckNexttips2();
	BOOL m_bTip2;
	int m_iNum;
};
