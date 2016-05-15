// PEMSysView.h : CPEMSysView 类的接口
//


#pragma once
#include ".\gridctrl\gridctrl.h"
#include "afxwin.h"

class CPEMSysDoc;
class CPEMSysView : public CFormView
{
protected: // 仅从序列化创建
	DECLARE_DYNCREATE(CPEMSysView)

public:
	enum{ IDD = IDD_PEMSYS_FORM };

// 属性
public:
	CPEMSysDoc* GetDocument() const;

// 操作
public:

// 重写
	public:
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
public:
	CPEMSysView();
	virtual ~CPEMSysView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CGridCtrl m_cGrid;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_cSearch;
	CButton m_cAdd;
	CButton m_cModify;
	CButton m_cFirst;
	CButton m_cPrevious;
	CButton m_cNext;
	CButton m_cLast;
	CSize m_OldSize;
	_variant_t strSQL,Holder;
private:
    _RecordsetPtr m_pUsersSet;
public:
	CEdit m_cUserID;
	afx_msg void OnClose();
	void RefreshList();
	CString m_sUserID;
	CString m_sName;
	CString m_sPassword;
	CString m_sCPassword;
	CString m_sTelSubNum;
	CString m_sMobileNum;
	CString m_sDepartment;
	CString m_sRemark;
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonAdd();
	CString m_sDisplay;
	CEdit m_cPassword;
	CEdit m_cPConfirm;
	CButton m_cViewAll;
	VARIANT m_BookMark;
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonLast();
	afx_msg void OnBnClickedButtonFirst();
	afx_msg void OnBnClickedButtonPrevious();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonSave();
	void RefreshEdit(void);
	CButton m_cDelete;
	CButton m_cSave;
	afx_msg void OnBnClickedButtonDelete();
	BOOL m_bAdd;
	BOOL m_bEdit;
	BOOL m_bMove;
	CButton m_cCancel;
	void ClearEdit(void);
	CComboBox m_cDepartment;
	int m_iPos;
	afx_msg void OnBnClickedButtonCancel();
	CEdit m_cName;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void UpdateRecord(_RecordsetPtr& pSet);
	CString m_strAuthor;
	BOOL m_bPrice;
	BOOL m_bPay;
	BOOL m_bTrack;
	BOOL m_bProduction;
	BOOL m_bDelivery;
	BOOL m_bBasic;
	BOOL m_bShaft;
	BOOL m_bCar;
	BOOL m_bDecoration;
	BOOL m_bElectric;
	BOOL m_bPart;
	void AuthorParse(void);
	void AuthorDeParse(void);
};

#ifndef _DEBUG  // PEMSysView.cpp 的调试版本
inline CPEMSysDoc* CPEMSysView::GetDocument() const
   { return reinterpret_cast<CPEMSysDoc*>(m_pDocument); }
#endif

