#pragma once
#include "./GridCtrl/gridctrl.h"



// CItemInExportView ������ͼ

class CItemInExportView : public CFormView
{
	DECLARE_DYNCREATE(CItemInExportView)

public:
	CItemInExportView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CItemInExportView();

public:
	enum { IDD = IDD_DIALOG_ITEM_INEXPORT };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_cGrid;
};


