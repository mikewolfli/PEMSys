#pragma once
#include "afxwin.h"


// CItemShaftPage 对话框

class CItemShaftPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemShaftPage)

public:
	CItemShaftPage();
	virtual ~CItemShaftPage();

// 对话框数据
	enum { IDD = IDD_PAGE_ITEM_SHAFT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_iSW;
	int m_iSD;
	long m_lTH;
	long m_lOH;
	int m_iPD;
	CString m_sCounterWeight;
	int m_iCounterWeightHeight;
	BOOL m_bWideJamb;
	int m_iCWGauge;
	int m_iJambXC;
	CString m_sSGPosition;
	CString m_sWJType;
	int m_iCCW;
	int m_iCS1;
	int m_iCS2;
	int m_iCWS;
	void ClearEdit(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void UpdateDataPage(BOOL bCheck);
	afx_msg void OnBnClickedCheckShaftWidejamb();
	CEdit m_cJambXC;
	CComboBox m_cWJType;
	virtual BOOL OnSetActive();
	BOOL m_bCheck;
};
