#pragma once
#include "afxdtctl.h"
#include "atlcomtime.h"
#include "afxwin.h"


// CCommerceFollowupPage 对话框

class CCommerceFollowupPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCommerceFollowupPage)

public:
	CCommerceFollowupPage();
	virtual ~CCommerceFollowupPage();

// 对话框数据
	enum { IDD = IDD_PAGE_COMMERCE_CONTRACT_FOLLOWUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void UpdateDataPage(BOOL bCheck);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CDateTimeCtrl m_cGADReceived;
	COleDateTime m_dGADReceived;
	CDateTimeCtrl m_cLatestAmend;
	COleDateTime m_dLatestAmend;
	CDateTimeCtrl m_cCSRelease;
	COleDateTime m_dCSRelease;
	CDateTimeCtrl m_cCSReply;
	COleDateTime m_dCSReply;
	CDateTimeCtrl m_cACompleteDate;
	COleDateTime m_dACompleteDate;
	CEdit m_cAmendRemark;
	CString m_sAmendRemark;
	CEdit m_cReplyRemark;
	CString m_sReplyRemark;
	BOOL m_bGADReceived;
	BOOL m_bLatestAmend;
	BOOL m_bCSRelease;
	BOOL m_bCSReply;
	BOOL m_bACompleteDate;
//	afx_msg void OnBnClickedCheckGadreceive();
	afx_msg void OnBnClickedCheckThelatestamendment();
	afx_msg void OnBnClickedCheckConfirmationsheetrelease();
	afx_msg void OnBnClickedCheckConfirmationsheetreply();
	afx_msg void OnBnClickedCheckAssessmentcomplete();
	void ClearEdit(void);
	afx_msg void OnBnClickedCheckGadreceive();
};
