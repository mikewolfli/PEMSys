#pragma once


// CPConfigDlg 对话框

class CPConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CPConfigDlg)

public:
	CPConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPConfigDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_LISTCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
