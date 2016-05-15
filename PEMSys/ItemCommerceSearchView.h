#pragma once
#include ".\gridctrl\gridctrl.h"
#include ".\NewCellTypes\GridCellCheck.h" 
#include "atlcomtime.h"
#include "SearchPopItemDlg.h"
#include "SearchPopOrderIDDlg.h"
#include "afxwin.h"


// CItemCommerceSearchView 窗体视图
typedef struct _ItemRow {
	CString sName; 
	CString sItem; 
	int tType;
	CString sTable;
} ItemRow;

class CItemCommerceSearchView : public CFormView
{
	DECLARE_DYNCREATE(CItemCommerceSearchView)

public:
	CItemCommerceSearchView();           // 动态创建所使用的受保护的构造函数
	virtual ~CItemCommerceSearchView();

public:
	enum { IDD = IDD_DIALOG_ITEM_COMMERCESEARCH };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CGridCtrl m_cDisplay;
	afx_msg void OnBnClickedButtonPrintconfigure();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CGridCtrl m_cSearchCase;
	afx_msg void OnBnClickedButtonSearchconfigure();
	int m_iCheck;
	afx_msg void OnBnClickedButtonSaveas();
	afx_msg void OnBnClickedOk();
private:
	_RecordsetPtr m_pTempSet;
	_RecordsetPtr m_pResult;
public:
	afx_msg void OnClose();
	_variant_t strSQL;
	_variant_t Holder;
	BOOL m_bEdit;
	int m_iTotalCount;
	void LoadData(void);
//	ItemRow m_iType[100];//查询条件
//	ItemRow m_iName[100];//显示条件
	ItemRow *m_iType;
	ItemRow *m_iName;
	COleDateTime m_dCurrent;
	void RefreshGrid(_RecordsetPtr& pSet,int row);
	void LoadDisplay(void);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonPrintview();
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnNMRclickGridData(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSearchItem();
	afx_msg void OnSearchSameorderid();
	CString m_sOrderID;
	BOOL m_bSearch;
	void OnExcelOut(CString filepath,CString filename);
	afx_msg void OnBnClickedButtonOutputorder();
    int m_iLink;
	afx_msg void OnBnClickedRadioInner();
	afx_msg void OnBnClickedRadioOuter();
};


