#pragma once

#include ".\gridctrl\gridctrl.h"
#include ".\gridctrl\gridctrl.h"
#include ".\NewCellTypes\GridCellCheck.h"

// CDisplayConfigureDlg 对话框

class CDisplayConfigureDlg : public CDialog
{
	DECLARE_DYNAMIC(CDisplayConfigureDlg)

public:
	CDisplayConfigureDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDisplayConfigureDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PRINTCONFIGURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_cConfigure;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	int m_iCheck;
private:
	_RecordsetPtr m_pTempSet;
public:
	_variant_t strSQL;
	_variant_t Holder;
	BOOL m_bEdit;
	void LoadData(void);
//	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	void InsertData(_RecordsetPtr& pSet, int iRow, int iCol);
	afx_msg void OnClose();
};
