#pragma once
#include "afxwin.h"


// CItemPartsPage 对话框

class CItemPartsPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemPartsPage)

public:
	CItemPartsPage();
	virtual ~CItemPartsPage();

// 对话框数据
	enum { IDD = IDD_PAGE_ITEM_PARTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sTraction;
	CString m_sCarRail;
	CString m_sEncode;
	CString m_sCWRail;
	CString m_sDoorSystem;
	CString m_sSafety;
	CString m_sSpeedGovernor;
	CString m_sBuffer;
	BOOL m_bNonstandardCheck;
	CString m_sNonstandardRemark;
	CEdit m_cNonstandardRemark;
	void ClearEdit(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void UpdateDataPage(BOOL bCheck);
	afx_msg void OnBnClickedCheckNonstandard();
	virtual BOOL OnSetActive();
	afx_msg void OnCbnSelchangeComboSafety();
};
