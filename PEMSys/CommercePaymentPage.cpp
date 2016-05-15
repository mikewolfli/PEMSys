// CommercePaymentPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "CommercePaymentPage.h"
#include ".\commercepaymentpage.h"


// CCommercePaymentPage 对话框

IMPLEMENT_DYNAMIC(CCommercePaymentPage, CPropertyPage)
CCommercePaymentPage::CCommercePaymentPage()
	: CPropertyPage(CCommercePaymentPage::IDD)
	, m_dbDiscount(0)
	, m_dbInternalPrice(0)
	, m_dbAGetFreightInsurance(0)
	, m_dPORelease(COleDateTime::GetCurrentTime())
	, m_dPOReturn(COleDateTime::GetCurrentTime())
	, m_bPOReturn(FALSE)
	, m_bPORelease(FALSE)
{

}

CCommercePaymentPage::~CCommercePaymentPage()
{
}

void CCommercePaymentPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DISSCOUNT, m_dbDiscount);
	DDX_Text(pDX, IDC_EDIT_INTERNALPRICE, m_dbInternalPrice);
	DDX_Text(pDX, IDC_EDIT_ACTUALGETFREIGHTINSURANCE, m_dbAGetFreightInsurance);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PORELEASE, m_dPORelease);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PORETURN, m_dPOReturn);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PORELEASE, m_cPORelease);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PORETURN, m_cPOReturn);
	DDX_Check(pDX, IDC_CHECK_PORETURN, m_bPOReturn);
	DDX_Check(pDX, IDC_CHECK_PORELEASE, m_bPORelease);
}


BEGIN_MESSAGE_MAP(CCommercePaymentPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_PORELEASE, OnBnClickedCheckPorelease)
	ON_BN_CLICKED(IDC_CHECK_PORETURN, OnBnClickedCheckPoreturn)
//	ON_BN_CLICKED(IDC_RADIO0, OnBnClickedRadioRmb)
//	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadioDollar)
END_MESSAGE_MAP()


// CCommercePaymentPage 消息处理程序

void CCommercePaymentPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
/*	if(m_iInternalCurrency==0&&bCheck==TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
	}
	else if(m_iInternalCurrency==1 && bCheck==TRUE)
	{
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(FALSE);
	}*/
}

void CCommercePaymentPage::OnBnClickedCheckPorelease()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_PORELEASE))->GetCheck())
	{
		m_bPORelease= TRUE;
		m_cPORelease.EnableWindow(TRUE);

	}
	else
	{
		m_bPORelease = FALSE;
		m_cPORelease.EnableWindow(FALSE);

		m_dPORelease = COleDateTime::GetCurrentTime();

	}

	UpdateData(FALSE);
}

void CCommercePaymentPage::OnBnClickedCheckPoreturn()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_PORETURN))->GetCheck())
	{
		m_bPOReturn = TRUE;
        m_cPOReturn.EnableWindow(TRUE);

	}
	else
	{
        m_bPOReturn = FALSE;
		m_cPOReturn.EnableWindow(FALSE);
		m_dPOReturn = COleDateTime::GetCurrentTime();

	}

	UpdateData(FALSE);
}

BOOL CCommercePaymentPage::PreTranslateMessage(MSG* pMsg)
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

void CCommercePaymentPage::ClearEdit(void)
{
	UpdateData(TRUE);

	 m_dbDiscount = 0.0;
	 m_dbInternalPrice = 0.0;
	 m_dbAGetFreightInsurance = 0.0;
	 m_dPORelease = COleDateTime::GetCurrentTime();
	 m_dPOReturn = COleDateTime::GetCurrentTime();
	 m_bPOReturn = FALSE;
	 m_bPORelease = FALSE;
	 m_cPORelease.EnableWindow(FALSE);
	 m_cPOReturn.EnableWindow(FALSE);
//	 ((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
//	 ((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
//	 m_iInternalCurrency=0;

	 UpdateData(FALSE);
}

/*
void CCommercePaymentPage::OnBnClickedRadioRmb()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
//	m_iInternalCurrency=0;
	UpdateData(FALSE);

}

void CCommercePaymentPage::OnBnClickedRadioDollar()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_iInternalCurrency=1;
	UpdateData(FALSE);
}
*/
//BOOL CCommercePaymentPage::OnInitDialog()
//{
//	CPropertyPage::OnInitDialog();
//
//	// TODO:  在此添加额外的初始化
//   ((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// 异常: OCX 属性页应返回 FALSE
//}
