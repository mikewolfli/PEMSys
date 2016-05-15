#pragma once
#include "afxwin.h"


// CItemBasicDataPage 对话框

class CItemBasicDataPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemBasicDataPage)

public:
	CItemBasicDataPage();
	virtual ~CItemBasicDataPage();

// 对话框数据
	enum { IDD = IDD_PAGE_ITEM_BASICDATA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sElevatorType;
	CString m_sElevatorModel;

	CString m_sRatedLoad;
	CString m_sRatedSpeed;
	CString m_sControlMode;
	CString m_sDragMode;
	CString m_sControlModeRemark;
	int m_iFloor;
	int m_iStop;
	int m_iDoor;
	CString m_sStopName;
	BOOL m_bThrough;
	void ClearEdit(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void UpdateDataPage(BOOL bCheck);
	afx_msg void OnCbnSelendokComboBasicdataElevatormodel();
	afx_msg void OnCbnSelendokComboBasicdataRatedload();
	CComboBox m_cElevatorModel;
	CComboBox m_cRatedLoad;
	afx_msg void OnCbnSelendokComboBasicdataRatedspeed();
	CComboBox m_cRatedSpeed;
};
