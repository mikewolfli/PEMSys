#pragma once


// CExcelPathDlg �Ի���

class CExcelPathDlg : public CDialog
{
	DECLARE_DYNAMIC(CExcelPathDlg)

public:
	CExcelPathDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExcelPathDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_EXCEL_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBrowerTemplate();
	afx_msg void OnBnClickedButtonBrowerObject();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_sTemplate;
	CString m_sObject;
};
