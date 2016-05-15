#pragma once
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "afxwin.h"


// CCommerceProductionPage 对话框

class CCommerceProductionPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCommerceProductionPage)

public:
	CCommerceProductionPage();
	virtual ~CCommerceProductionPage();

// 对话框数据
	enum { IDD = IDD_PAGE_COMMERCE_PRODUCTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void UpdateDataPage(BOOL bCheck);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CDateTimeCtrl m_cProductionReceiveDate;
	COleDateTime m_dProductionReceivedDate;
	BOOL m_bProductionReceivedDate;
	CDateTimeCtrl m_cPlantProductionDate;
	COleDateTime m_dPlantProductionDate;
	BOOL m_bPlantProductionDate;
	CDateTimeCtrl m_cPDeliveryDate;
	COleDateTime m_dPDeliveryDate;
	BOOL m_bPDeliveryDate;
	CEdit m_cPDeliveryRemark;
	CString m_sPDeliveryRemark;
	BOOL m_bPBatchCheck;
	CDateTimeCtrl m_cPSecDeliveryDate;
	COleDateTime m_dPSecDeliveryDate;
	CEdit m_cPSecDeliveryRemark;
	CString m_sPSecDeliveryRemark;
	BOOL m_bPThirdDeliveryDate;
	CDateTimeCtrl m_cPThirdDeliveryDate;
	COleDateTime m_dPThirdDeliveryDate;
	CEdit m_cPThirdDeliveryRemark;
	CString m_sPThirdDeliveryRemark;
	afx_msg void OnBnClickedCheckPdeliverydate();
	afx_msg void OnBnClickedCheckBatchcheck();
	afx_msg void OnBnClickedCheckPthirddeliverydate();
	void ClearEdit(void);
	afx_msg void OnBnClickedCheckProductionreceived();
	afx_msg void OnBnClickedCheckPlantproductiondate();
	BOOL m_bConfigureFinsh;
	COleDateTime m_dConfigureFinish;
	BOOL m_bPurchaseReturn;
	COleDateTime m_dPurchaseReturn;
	afx_msg void OnBnClickedCheckConfigurefinish();
	afx_msg void OnBnClickedCheckPurchasereturn();
	CDateTimeCtrl m_cConfigureFinish;
	CDateTimeCtrl m_cPurchaseReturn;
};
