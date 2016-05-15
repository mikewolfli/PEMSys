#pragma once


// CExcelPathDlg 对话框

class CExcelPathDlg : public CDialog
{
	DECLARE_DYNAMIC(CExcelPathDlg)

public:
	CExcelPathDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExcelPathDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EXCEL_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonBrowerTemplate();
	afx_msg void OnBnClickedButtonBrowerObject();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_sTemplate;
	CString m_sObject;
};
