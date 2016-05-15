#pragma once
#include "afxwin.h"
#include "ItemBasicDataPage.h"
#include "ItemCarPage.h"
#include "ItemElectricPage.h"
#include "ItemUpholsterPage.h"
#include "ItemShaftPage.h"
#include "ItemPartsPage.h"
#include "MyPropertySheet.h"
#include "atlcomtime.h"

// CItemDataInputView 窗体视图

class CItemDataInputView : public CFormView
{
	DECLARE_DYNCREATE(CItemDataInputView)

public:
	CItemDataInputView();           // 动态创建所使用的受保护的构造函数
	virtual ~CItemDataInputView();

public:
	enum { IDD = IDD_DIALOG_ITEM_DATAINPUT };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_cFirst;
	CButton m_cPrevious;
	CButton m_cNext;
	CButton m_cLast;
	CButton m_cSave;
	CButton m_cCancel;
	CButton m_cDelete;
	CString m_sDisplay;
	CComboBox m_cOrderID;
	CString m_sProjectName;
	CString m_sProjectNameEn;
	CString m_sRemark;
	CString m_sInputPerson;
	CString m_sRePerson;
	CString m_sInputDate;
	CString m_sReDate;
	virtual void OnInitialUpdate();

	CItemBasicDataPage m_pageBasicData;
	CItemShaftPage m_pageShaft;
	CItemCarPage m_pageCar;
	CItemUpholsterPage m_pageUpholster;
	CItemElectricPage m_pageElectric;
	CItemPartsPage m_pageParts;
	COleDateTime m_dCurrent;
	CMyPropertySheet m_sheetData;
	_variant_t strSQL;
	_variant_t Holder;
private:
	_RecordsetPtr m_pDataSet;
	_RecordsetPtr m_pTempSet;
public:
	CString m_sID;
	CComboBox m_cID;
	int m_iNumber;
	CString m_sOrderID;
	afx_msg void OnBnClickedOk();
	void InitOrderCtrl(void);
	void UpdateRecord(_RecordsetPtr& pSet);
	void ReadRecord(_RecordsetPtr& pSet);
	void EnableButton(void);
	int m_iPos;
	int m_iCount;
	void RecordSearch(void);
	BOOL m_bCopy;
	BOOL m_bSave;
	CString m_sElevatorID;
	afx_msg void OnBnClickedButtonDatainputSearch();
	void DisplayCtrl(_RecordsetPtr& pSet);
	void ClearEdit(void);
	afx_msg void OnCbnSelendokComboCommerceId();
	afx_msg void OnBnClickedButtonDatainputFirst();
	afx_msg void OnBnClickedButtonDatainputPrevious();
	afx_msg void OnBnClickedButtonDatainputNext();
	afx_msg void OnBnClickedButtonDatainputLast();
	afx_msg void OnCbnSelendokComboDatainputOrderid();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonDatainputDelete();
	afx_msg void OnBnClickedButtonSamecopy();
	int m_iCheck;
	CButton m_cSameCopy;
	BOOL m_bCopyCh;
	int m_iPage;
	afx_msg void OnClose();
	afx_msg void OnBnClickedCheckStandard();
	BOOL m_bCheck;
};

extern CString m_sgElevatorModel;
extern CString m_sgRatedLoad;
extern CString m_sgRatedSpeed;

