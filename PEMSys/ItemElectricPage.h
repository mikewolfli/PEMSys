#pragma once
#include "afxwin.h"

// CItemElectricPage 对话框

class CItemElectricPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemElectricPage)

public:
	CItemElectricPage();
	virtual ~CItemElectricPage();

// 对话框数据
	enum { IDD = IDD_PAGE_ITEM_ELECTRIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sController;
	BOOL m_bDisaPanel;
	BOOL m_bVideoCable;
	CString m_sCallBoardType;
	CString m_sScreenMagic;
	CString m_sPushButton;
	CString m_sInvertorType;
	CString m_sInvertorPower;
	CString m_sCallboardtypeRemark;
	CString m_sScreenMagicRemark;
	afx_msg void OnBnClickedButtonElectricFunction();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ClearEdit(void);
	virtual BOOL OnInitDialog();
	void UpdateDataPage(BOOL bCheck);
	_variant_t strSQL;
	_variant_t Holder;
private:;
	_RecordsetPtr m_pTempSet;
public:
	afx_msg void OnClose();
	CString m_sOrderID;
	afx_msg void OnCbnSelendokComboElectricScreenmagic();
	afx_msg void OnCbnSelendokComboElectricCallboardtype();
	afx_msg void OnCbnSelendokComboElectricInvertorType();
	afx_msg void OnCbnSelendokComboElectricInvertorPower();
	afx_msg void OnCbnEditchangeComboElectricCallboardtype();
	afx_msg void OnCbnEditchangeComboElectricScreenmagic();
	afx_msg void OnCbnEditchangeComboElectricInvertorType();
	afx_msg void OnCbnEditchangeComboElectricInvertorPower();
	CComboBox m_cCallBoardType;
};
