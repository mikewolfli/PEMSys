#pragma once
#include "afxcmn.h"


// CSearchPopOrderIDDlg �Ի���

class CSearchPopOrderIDDlg : public CDialog
{
	DECLARE_DYNAMIC(CSearchPopOrderIDDlg)

public:
	CSearchPopOrderIDDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSearchPopOrderIDDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1_POPUP_ORDERID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_sOrderID;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CListCtrl m_cList;
	void LoadData(_RecordsetPtr& pSet,int i);
private:
	_RecordsetPtr m_pOrderID;
public:
	_variant_t strSQL;
	_variant_t Holder;
protected:
	virtual void OnCancel();
};
