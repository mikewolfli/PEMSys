#pragma once
#include "afxwin.h"


// CSearchPopItemDlg �Ի���

class CSearchPopItemDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchPopItemDlg)

public:
	CSearchPopItemDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchPopItemDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1_POPUP_ITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_sOrderID;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_sID;
	CString m_sProjectID;
	CString m_sProjectIDZS;
	CString m_sProjectName;
	CString m_sProjectNameEn;
	CString m_sAddress;
	CString m_sAddressEn;
	CString m_sSubCompany;
	int m_iNumber;
	BOOL m_bIntegrality;
	BOOL m_bContractSigned;
	CString m_sContractReceive;
	CString m_sTheLatestAmd;
	CString m_sRemarks;
	_variant_t strSQL;
	_variant_t Holder;
private:
	_RecordsetPtr m_pItemSet;
	_RecordsetPtr m_pTempSet;
public:
	void RefreshEdit(_RecordsetPtr& pSet);
	BOOL m_bPartsContract;
protected:
	virtual void OnCancel();
public:
	CString m_sAmount;
};
