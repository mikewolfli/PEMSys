#pragma once
#include "./GridCtrl/gridctrl.h"



// CItemInExportView 窗体视图

class CItemInExportView : public CFormView
{
	DECLARE_DYNCREATE(CItemInExportView)

public:
	CItemInExportView();           // 动态创建所使用的受保护的构造函数
	virtual ~CItemInExportView();

public:
	enum { IDD = IDD_DIALOG_ITEM_INEXPORT };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_cGrid;
};


