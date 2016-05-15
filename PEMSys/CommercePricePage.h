#pragma once


// CCommercePricePage 对话框

class CCommercePricePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCommercePricePage)

public:
	CCommercePricePage();
	virtual ~CCommercePricePage();

// 对话框数据
	enum { IDD = IDD_PAGE_COMMERCE_PRICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void UpdateDataPage(BOOL bCheck);
	double m_dbAmount;
	double m_dbFreightInsurance;
	double m_dbMaterialAmount;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnEnChangeEditAmount();
	afx_msg void OnEnChangeEditFreightinsurance();
	void ClearEdit(void);
	afx_msg void OnEnChangeEditMaterialamount();
};
