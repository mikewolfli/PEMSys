#pragma once
#include ".\gridctrl\gridctrl.h"
#include ".\NewCellTypes\GridCellCheck.h"
#include ".\gridctrl\gridctrl.h"

// COrderIDDlg 对话框
typedef struct _RowStatus {
	int i_Row;  //行数
	BOOL b_Judge; //作废判断
	BOOL b_Status; //是否存入数据库判断
} RowStatus;

class COrderIDDlg : public CDialog
{
	DECLARE_DYNAMIC(COrderIDDlg)

public:
	COrderIDDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COrderIDDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ORDERID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);


	DECLARE_MESSAGE_MAP()
public:
	CButton m_cSave;
	CButton m_cExit;
	CComboBox m_cID;
	CString m_sID;
	CString m_sProjectName;
	CString m_stemp;
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelendokComboOrderId();
private:
	_RecordsetPtr m_pOrderID;
	_RecordsetPtr m_pTempSet;

public:
	_variant_t strSQL;
	_variant_t Holder;
	BOOL m_bEdit;
	void RefreshGrid(void);
	void ClearGrid(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void InsertData(int row, int col);
	CGridCtrl m_cGrid;
	int m_iOrderNum;
	int m_iNum;
	CImageList image_Status;
	int m_iRow;
	COleDateTime m_dCurrent;
	CString m_sYear;
	CString m_sSubCompanyName;
	CString m_sSubCompanyID;
	void LoadData(void);

//	RowStatus  RStatus[500];
    RowStatus  *RStatus;
};
