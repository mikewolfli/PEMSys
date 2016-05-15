#pragma once
#include ".\gridctrl\gridctrl.h"
#include "afxwin.h"
#include "atlcomtime.h"


// CItemFunctionDlg �Ի���

class CItemFunctionDlg : public CDialog
{
	DECLARE_DYNAMIC(CItemFunctionDlg)

public:
	CItemFunctionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CItemFunctionDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ITEM_FUNCTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_cGrid;
	afx_msg void OnBnClickedCheckFunctionStandard();
	virtual BOOL OnInitDialog();
	BOOL m_bStandard;
	CString m_sElevatorModel,m_sEM;
//	CItemElectricPage *m_pParent;
	CString m_sOrderID;
	_variant_t strSQL;
	_variant_t Holder;
private:
	_RecordsetPtr m_pFunctionSet;
	_RecordsetPtr m_pTempSet;
public:
	CString GetElevatorModel(void);
	afx_msg void OnClose();
	BOOL m_bAdd;
	COleDateTime m_dCurrent;
	BOOL m_bEdit;
	CImageList image_Status;
	CButton m_cSave;
	afx_msg void OnBnClickedOk();
	void RefreshGrid(void);
	CArray<int,BOOL> m_bStatus;//�ж��Ƿ��ǷǱ�/��ѡ����, FALSE - ��׼����
//	void UpdateGrid(_RecordsetPtr& pSet, int iRow);
	int m_iSelect;
	int m_iStandard;
	afx_msg void OnBnClickedCancel();
	CString m_sController;
};
