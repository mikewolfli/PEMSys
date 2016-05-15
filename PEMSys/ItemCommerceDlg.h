#pragma once
#include "afxwin.h"

#include "MyPropertySheet.h"
#include "CommerceDeliveryPage.h"
#include "CommerceFollowupPage.h"
#include "CommercePaymentPage.h"
#include "CommercePricePage.h"
#include "CommerceProductionPage.h"
#include "atlcomtime.h"
// CItemCommerceDlg 对话框

class CItemCommerceDlg : public CDialog
{
	DECLARE_DYNAMIC(CItemCommerceDlg)

public:
	CItemCommerceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CItemCommerceDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_COMMERCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sID;
	CComboBox m_cID;
	CString m_sProjectName;
	CString m_sProjectNameEN;
	int m_iNumber;
	CComboBox m_cOrderID;
	CString m_sOrderID;
	CString m_sELevatorID;
	CMyPropertySheet m_sheetData;
    CCommerceFollowupPage m_pageCFollowup;
	CCommercePaymentPage m_pagePayment;
	CCommercePricePage m_pagePrice;
	CCommerceDeliveryPage m_pageDelivery;
	CCommerceProductionPage m_pageProduction;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_cFirst;
	CButton m_cPrevious;
	CButton m_cNext;
	CButton m_cLast;
	CButton m_cSave;
	CButton m_cCancel;
	CButton m_cDelete;
	CString m_sDisplay;
	int m_iCount;
	int m_iPos;
	void EnableButton(void);
	_variant_t strSQL;
	_variant_t Holder;
private:
	_RecordsetPtr m_pDataSet;
	_RecordsetPtr m_pTempSet;
protected:
//	virtual void OnCancel();
public:
	CButton m_cBack;
	afx_msg void OnBnClickedButtonCommerceBack();
	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	CString m_sInputPerson;
	CString m_sInputDate;
	CString m_sRePerson;
	CString m_sReDate;
	COleDateTime m_dCurrent;
	void InitOrderCtrl(void);
	afx_msg void OnCbnSelendokComboCommerceOrderid();
	afx_msg void OnCbnSelendokComboCommerceId();
	void ClearEdit(void);
	afx_msg void OnBnClickedButtonCommerceSearch();
	BOOL m_bSave;
	afx_msg void OnBnClickedButtonCommerceFirst();
	afx_msg void OnBnClickedButtonCommercePrevious();
	afx_msg void OnBnClickedButtonCommerceNext();
	afx_msg void OnBnClickedButtonCommderceLast();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonCommerceDelete();
	CString m_sRemarks;
	BOOL m_bCopy;
	float m_fRatedSpeed;
	int m_iRatedLoad;
	CString m_ssDeliveryProgramme;
	void UpdateRecord(_RecordsetPtr& pSet);
	void ReadRecord(_RecordsetPtr& pSet);
	void RecordSearch(void);
	afx_msg void OnBnClickedButtonSamecopy();
	void DisplayCtrl(_RecordsetPtr& pSet);
	int m_iCheck;
	COleDateTime m_dCompare;
	CButton m_cSameCopy;
	_variant_t VarTemp;
	BOOL m_bCheck;
	int m_iPage;
	int m_iCurrency;
};
