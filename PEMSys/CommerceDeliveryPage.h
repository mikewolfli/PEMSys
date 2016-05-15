#pragma once
#include "atlcomtime.h"
#include "afxdtctl.h"
#include "afxwin.h"


// CCommerceDeliveryPage 对话框

class CCommerceDeliveryPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCommerceDeliveryPage)

public:
	CCommerceDeliveryPage();
	virtual ~CCommerceDeliveryPage();

// 对话框数据
	enum { IDD = IDD_PAGE_COMMERCE_DELIVERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void UpdateDataPage(BOOL bCheck);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CDateTimeCtrl m_cDeliveryReceivedDate;
	COleDateTime m_dDeliveryReceivedDate;
	CDateTimeCtrl m_cADeliveryDate;
	COleDateTime m_dADeliveryDate;
	CString m_sADeliveryRemark;
	CEdit m_cADeliveryRemark;
	COleDateTime m_dASecDeliveryDate;
	CDateTimeCtrl m_cASecDeliveryDate;
	CEdit m_cASecDeliveryRemark;
	CString m_sASecDeliveryRemark;
	BOOL m_bBatchDelivery;
	CDateTimeCtrl m_cAThirdDeliveryDate;
	COleDateTime m_dAThirdDeliveryDate;
	CEdit m_cAThirdDeliveryRemark;
	CString m_sAThirdDeliveryRemark;
	BOOL m_bDeliveryDone;
	afx_msg void OnBnClickedCheckDeliveryreceivedate();
	afx_msg void OnBnClickedCheckAdelivery();
	afx_msg void OnBnClickedCheckBatchdelivery();
	afx_msg void OnBnClickedCheckAthirddeliveryremark();
	void ClearEdit(void);
	BOOL m_bDeliveryReceived;
	BOOL m_bADeliveryDate;
	BOOL m_bAThirdDeliveryDate;
};
