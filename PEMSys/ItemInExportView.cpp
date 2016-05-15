// ItemInExportView.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemInExportView.h"


// CItemInExportView

IMPLEMENT_DYNCREATE(CItemInExportView, CFormView)

CItemInExportView::CItemInExportView()
	: CFormView(CItemInExportView::IDD)
{
}

CItemInExportView::~CItemInExportView()
{
}

void CItemInExportView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_LIST, m_cGrid);
}

BEGIN_MESSAGE_MAP(CItemInExportView, CFormView)
END_MESSAGE_MAP()


// CItemInExportView 诊断

#ifdef _DEBUG
void CItemInExportView::AssertValid() const
{
	CFormView::AssertValid(); 
}

void CItemInExportView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CItemInExportView 消息处理程序
