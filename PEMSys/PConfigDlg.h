#pragma once


// CPConfigDlg �Ի���

class CPConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CPConfigDlg)

public:
	CPConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPConfigDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LISTCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
