#pragma once
#include "afxwin.h"
#include "atltypes.h"
#include "atlcomtime.h"
#include "comutil.h"
#include "afxdtctl.h"
#include "ItemCommerceDlg.h"
//#include "ItemListDlg.h"


// CItemView 窗体视图

class CItemView : public CFormView
{
	DECLARE_DYNCREATE(CItemView)

//protected:
public:
	CItemView();           // 动态创建所使用的受保护的构造函数
	virtual ~CItemView();

public:
	enum { IDD = IDD_DIALOG_ITEM_ORDERINTAKE };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CButton m_cAdd;
	CButton m_cModify;
	CButton m_cSave;
	CButton m_cCancel;
	CButton m_cDelete;
	CButton m_cNext;
	CButton m_cLast;
	CButton m_cFirst;
	CButton m_cPrevious;
	BOOL m_bAdd;
	BOOL m_bModify;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CSize m_OldSize;
	CString m_sProjectID;
	CString m_sProjectName;
	CString m_sAddress;
	CComboBox m_cSubCompany;
	CString m_sSubCompany;
	int m_iNumber;
	CString m_sRemark;
	CString m_sInputPerson;
	CString m_sRePerson;
	CButton m_cSearch;
	void RefreshEdit(void);
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnBnClickedButtonPrevious();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonLast();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonCreatorderid();
	CString m_sDisplay;
	void ClearEdit(void);
	CString m_sInputDate;
	CString m_sReDate;
	COleDateTime m_dCurrentDate;
	_variant_t strSQL;
	_variant_t Holder;
private:
	_RecordsetPtr m_pItemSet;
	_RecordsetPtr m_pTempSet;
public:
	VARIANT m_BookMark;
	afx_msg void OnClose();
	BOOL m_bCopy;
	int m_iPos;
//	afx_msg void OnBnClickedButtonItemlist();
	CString m_sID;
	long m_iTotal;

//	COleDateTime m_dDelevery;
	CString m_sAddressEn;
	CString m_sProjectNameEn;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	CString m_sYear;
//	CString m_sMonth;
//	CString m_sDay;
//	CComboBox m_cDay;
//	CComboBox m_cMonth;
//	CComboBox m_cYear;
///	afx_msg void OnCbnEditchangeComboItemMonth();
//	afx_msg void OnCbnSelendokComboItemMonth();
//	afx_msg void OnCbnEditupdateComboItemYear();
//	afx_msg void OnCbnSelchangeComboItemYear();
//	afx_msg void OnBnClickedCheckIntegrality();
//	CButton m_cParts;
//	CButton m_cFull;
//	afx_msg void OnBnClickedCheckFull();
//	afx_msg void OnBnClickedCheckParts();
	BOOL m_bPartsContract;
	int m_rhPartsContract;
	BOOL m_bIntegrality;
	CString m_sProjectNOZS;
	COleDateTime m_dContractReceive;
	COleDateTime m_dTheLatestAmendment;
	afx_msg void OnBnClickedButtonCommerce();
	BOOL m_bContractSigned;
	COleDateTime m_dGADReceived;
	BOOL m_bContractRecieve;
	BOOL m_bLatestAmend;
	CDateTimeCtrl m_cContractReceive;
	CDateTimeCtrl m_cLatestAmend;
	afx_msg void OnBnClickedCheckContractreceive();
	afx_msg void OnBnClickedCheckThelatestamendment();
	void UpdateRecord(_RecordsetPtr& pSet);
	CButton m_cCommerce;
	CButton m_cCreatOrderID;
	CItemCommerceDlg *m_pCommerceDlg;
	_variant_t VarTemp;
	BOOL m_bProjectRequire;
	CDateTimeCtrl m_cProjectRequire;
	COleDateTime m_dProjectRequire;
	afx_msg void OnBnClickedCheckProjectrequire();
	BOOL m_bAffix;
	COleDateTime m_dAffix;
	afx_msg void OnBnClickedCheckProjectaffix();
	CDateTimeCtrl m_cAffix;
};


