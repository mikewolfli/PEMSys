#pragma once
#include "afxwin.h"


// ItemUpholsterPage 对话框

class CItemUpholsterPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemUpholsterPage)

public:
	CItemUpholsterPage();
	virtual ~CItemUpholsterPage();

// 对话框数据
	enum { IDD = IDD_PAGE_ITEM_UPHOLSTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sCeiling;
	CString m_sFrontWall;
	CString m_sSideWall;
	CString m_sRearWall;
	BOOL m_bHandRail;
	BOOL m_bGlassPosition;
	CString m_sSideHandRail;
	CString m_sRearHandRail;
	CString m_sGlassType;
	CString m_sGlassPosition;
	CString m_sDoor;
	CString m_sFloor;
	void ClearEdit(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void UpdateDataPage(BOOL bCheck);
	afx_msg void OnBnClickedCheckUpholsterHandrail();
	afx_msg void OnBnClickedCheckUpholsterGlassposition();
	CComboBox m_cSideHandrail;
	CComboBox m_cRearHandrail;
	CComboBox m_cGlassType;
	CComboBox m_cGlassPos;
	CString m_sFloorDoor1;
	CString m_sFloorDoor2;
	int m_iFloorDoor1;
	int m_iFloorDoor2;
};
