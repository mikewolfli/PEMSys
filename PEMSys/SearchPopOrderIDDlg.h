#pragma once
#include "afxcmn.h"


// CSearchPopOrderIDDlg 对话框

class CSearchPopOrderIDDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchPopOrderIDDlg)

public:
	CSearchPopOrderIDDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSearchPopOrderIDDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1_POPUP_ORDERID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sOrderID;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl m_cList;
	void LoadData(_RecordsetPtr& pSet,int i);
private:
	_RecordsetPtr m_pOrderID;
public:
	_variant_t strSQL;
	_variant_t Holder;
protected:
	virtual void OnCancel();
};
