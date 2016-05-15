#pragma once
#include "atlcomtime.h"
#include "afxdtctl.h"


// CCommercePaymentPage �Ի���

class CCommercePaymentPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCommercePaymentPage)

public:
	CCommercePaymentPage();
	virtual ~CCommercePaymentPage();

// �Ի�������
	enum { IDD = IDD_PAGE_COMMERCE_PAYMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void UpdateDataPage(BOOL bCheck);
	double m_dbDiscount;
	double m_dbInternalPrice;
	double m_dbAGetFreightInsurance;
	COleDateTime m_dPORelease;
	COleDateTime m_dPOReturn;
	CDateTimeCtrl m_cPORelease;
	CDateTimeCtrl m_cPOReturn;
	afx_msg void OnBnClickedCheckPorelease();
	afx_msg void OnBnClickedCheckPoreturn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ClearEdit(void);
	BOOL m_bPOReturn;
	BOOL m_bPORelease;

	afx_msg void OnBnClickedRadioRmb();
	afx_msg void OnBnClickedRadioDollar();
//	virtual BOOL OnInitDialog();
};
