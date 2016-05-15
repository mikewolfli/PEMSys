#pragma once


// CCommercePricePage �Ի���

class CCommercePricePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CCommercePricePage)

public:
	CCommercePricePage();
	virtual ~CCommercePricePage();

// �Ի�������
	enum { IDD = IDD_PAGE_COMMERCE_PRICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
