// CommercePricePage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "CommercePricePage.h"
#include ".\commercepricepage.h"


// CCommercePricePage 对话框

IMPLEMENT_DYNAMIC(CCommercePricePage, CPropertyPage)
CCommercePricePage::CCommercePricePage()
	: CPropertyPage(CCommercePricePage::IDD)
	, m_dbAmount(0)
	, m_dbFreightInsurance(0)
	, m_dbMaterialAmount(0)
{
}

CCommercePricePage::~CCommercePricePage()
{
}

void CCommercePricePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AMOUNT, m_dbAmount);
	DDX_Text(pDX, IDC_EDIT_FREIGHTINSURANCE, m_dbFreightInsurance);
	DDX_Text(pDX, IDC_EDIT_MATERIALAMOUNT, m_dbMaterialAmount);
}


BEGIN_MESSAGE_MAP(CCommercePricePage, CPropertyPage)
//	ON_EN_CHANGE(IDC_EDIT_AMOUNT, OnEnChangeEditAmount)
	ON_EN_CHANGE(IDC_EDIT_FREIGHTINSURANCE, OnEnChangeEditFreightinsurance)
	ON_EN_CHANGE(IDC_EDIT_MATERIALAMOUNT, OnEnChangeEditMaterialamount)
END_MESSAGE_MAP()


// CCommercePricePage 消息处理程序

void CCommercePricePage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

BOOL CCommercePricePage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if( pMsg->message == WM_KEYDOWN )
	{
		if(pMsg->wParam == VK_RETURN
			|| pMsg->wParam == VK_ESCAPE )
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return TRUE;                    // DO NOT process further
		}
	}

	return CPropertyPage::PreTranslateMessage(pMsg);
}

//void CCommercePricePage::OnEnChangeEditAmount()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
//	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//	m_dbMaterialAmount = m_dbAmount - m_dbFreightInsurance;
//
//	UpdateData(FALSE);
//}

void CCommercePricePage::OnEnChangeEditFreightinsurance()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dbAmount  = m_dbMaterialAmount + m_dbFreightInsurance;

	UpdateData(FALSE);
}

void CCommercePricePage::ClearEdit(void)
{
	UpdateData(TRUE);

	m_dbAmount = 0.0;
	m_dbMaterialAmount = 0.0;
	m_dbFreightInsurance = 0.0;
	UpdateData(FALSE);
}

void CCommercePricePage::OnEnChangeEditMaterialamount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_dbAmount  = m_dbMaterialAmount + m_dbFreightInsurance;

	UpdateData(FALSE);
}
