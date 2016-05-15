// CommerceDeliveryPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "CommerceDeliveryPage.h"
#include ".\commercedeliverypage.h"


// CCommerceDeliveryPage 对话框

IMPLEMENT_DYNAMIC(CCommerceDeliveryPage, CPropertyPage)
CCommerceDeliveryPage::CCommerceDeliveryPage()
	: CPropertyPage(CCommerceDeliveryPage::IDD)
	, m_dDeliveryReceivedDate(COleDateTime::GetCurrentTime())
	, m_dADeliveryDate(COleDateTime::GetCurrentTime())
	, m_sADeliveryRemark(_T(""))
	, m_dASecDeliveryDate(COleDateTime::GetCurrentTime())
	, m_sASecDeliveryRemark(_T(""))
	, m_bBatchDelivery(FALSE)
	, m_dAThirdDeliveryDate(COleDateTime::GetCurrentTime())
	, m_sAThirdDeliveryRemark(_T(""))
	, m_bDeliveryDone(FALSE)
	, m_bDeliveryReceived(FALSE)
	, m_bADeliveryDate(FALSE)
	, m_bAThirdDeliveryDate(FALSE)
{
}

CCommerceDeliveryPage::~CCommerceDeliveryPage()
{
}

void CCommerceDeliveryPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DELIVERYRECEIVEDDATE, m_cDeliveryReceivedDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DELIVERYRECEIVEDDATE, m_dDeliveryReceivedDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ADELIVERYDATE, m_cADeliveryDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ADELIVERYDATE, m_dADeliveryDate);
	DDX_Text(pDX, IDC_EDIT_ADELIVERYREMARK, m_sADeliveryRemark);
	DDX_Control(pDX, IDC_EDIT_ADELIVERYREMARK, m_cADeliveryRemark);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ASECDELIVERYDATE, m_dASecDeliveryDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ASECDELIVERYDATE, m_cASecDeliveryDate);
	DDX_Control(pDX, IDC_EDIT_ASECDELIVERYREMARK, m_cASecDeliveryRemark);
	DDX_Text(pDX, IDC_EDIT_ASECDELIVERYREMARK, m_sASecDeliveryRemark);
	DDX_Check(pDX, IDC_CHECK_BATCHDELIVERY, m_bBatchDelivery);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ATHIRDDELIVERYREMARK, m_cAThirdDeliveryDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ATHIRDDELIVERYREMARK, m_dAThirdDeliveryDate);
	DDX_Control(pDX, IDC_EDIT_ATHIRDDELIVERYREMARK, m_cAThirdDeliveryRemark);
	DDX_Text(pDX, IDC_EDIT_ATHIRDDELIVERYREMARK, m_sAThirdDeliveryRemark);
	DDX_Check(pDX, IDC_CHECK_DELIVERYDONE, m_bDeliveryDone);
	DDX_Check(pDX, IDC_CHECK_DELIVERYRECEIVEDATE, m_bDeliveryReceived);
	DDX_Check(pDX, IDC_CHECK_ADELIVERY, m_bADeliveryDate);
	DDX_Check(pDX, IDC_CHECK_ATHIRDDELIVERYREMARK, m_bAThirdDeliveryDate);
}


BEGIN_MESSAGE_MAP(CCommerceDeliveryPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_DELIVERYRECEIVEDATE, OnBnClickedCheckDeliveryreceivedate)
	ON_BN_CLICKED(IDC_CHECK_ADELIVERY, OnBnClickedCheckAdelivery)
	ON_BN_CLICKED(IDC_CHECK_BATCHDELIVERY, OnBnClickedCheckBatchdelivery)
	ON_BN_CLICKED(IDC_CHECK_ATHIRDDELIVERYREMARK, OnBnClickedCheckAthirddeliveryremark)
END_MESSAGE_MAP()


// CCommerceDeliveryPage 消息处理程序

void CCommerceDeliveryPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

BOOL CCommerceDeliveryPage::PreTranslateMessage(MSG* pMsg)
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

void CCommerceDeliveryPage::OnBnClickedCheckDeliveryreceivedate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_DELIVERYRECEIVEDATE))->GetCheck())
	{
       m_bDeliveryReceived = TRUE;
	   m_cDeliveryReceivedDate.EnableWindow(TRUE);

	}
	else
	{
		m_bDeliveryReceived = FALSE;
		m_cDeliveryReceivedDate.EnableWindow(FALSE);
		m_dDeliveryReceivedDate = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}

void CCommerceDeliveryPage::OnBnClickedCheckAdelivery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_ADELIVERY))->GetCheck())
	{
		m_bADeliveryDate = TRUE;
		m_cADeliveryDate.EnableWindow(TRUE);
		m_cADeliveryRemark.SetReadOnly(FALSE);

	}
	else
	{
		m_bADeliveryDate = FALSE;
		m_cADeliveryDate.EnableWindow(FALSE);
		m_cADeliveryRemark.SetReadOnly(TRUE);

		m_dADeliveryDate = COleDateTime::GetCurrentTime();
		m_sADeliveryRemark.Empty();

		if(((CButton*)GetDlgItem(IDC_CHECK_BATCHDELIVERY))->GetCheck())
		{
			m_bBatchDelivery = FALSE;
			m_cASecDeliveryDate.EnableWindow(FALSE);
			m_cASecDeliveryRemark.SetReadOnly(TRUE);

			m_dASecDeliveryDate = COleDateTime::GetCurrentTime();
			m_sASecDeliveryRemark.Empty();


			if(((CButton*)GetDlgItem(IDC_CHECK_ATHIRDDELIVERYREMARK))->GetCheck())
			{
				m_bAThirdDeliveryDate = FALSE;
				m_cAThirdDeliveryDate.EnableWindow(FALSE);
				m_cAThirdDeliveryRemark.SetReadOnly(TRUE);

				m_dAThirdDeliveryDate = COleDateTime::GetCurrentTime();
				m_sAThirdDeliveryRemark.Empty();
			}

		}


	}
	UpdateData(FALSE);

}

void CCommerceDeliveryPage::OnBnClickedCheckBatchdelivery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_BATCHDELIVERY))->GetCheck())
	{
       m_bBatchDelivery = TRUE;
	   m_cASecDeliveryDate.EnableWindow(TRUE);
	   m_cASecDeliveryRemark.SetReadOnly(FALSE);

	}
	else
	{
		m_bBatchDelivery = FALSE;
		m_cASecDeliveryDate.EnableWindow(FALSE);
		m_cASecDeliveryRemark.SetReadOnly(TRUE);
		
		m_dASecDeliveryDate = COleDateTime::GetCurrentTime();
		m_sASecDeliveryRemark.Empty();


		if(((CButton*)GetDlgItem(IDC_CHECK_ATHIRDDELIVERYREMARK))->GetCheck())
		{
			m_bAThirdDeliveryDate = FALSE;
			m_cAThirdDeliveryDate.EnableWindow(FALSE);
			m_cAThirdDeliveryRemark.SetReadOnly(TRUE);

			m_dAThirdDeliveryDate = COleDateTime::GetCurrentTime();
			m_sAThirdDeliveryRemark.Empty();
		}

	}

	UpdateData(FALSE);
}

void CCommerceDeliveryPage::OnBnClickedCheckAthirddeliveryremark()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_ATHIRDDELIVERYREMARK))->GetCheck() && m_bBatchDelivery)
	{
		m_bAThirdDeliveryDate= TRUE;
		m_cAThirdDeliveryDate.EnableWindow(TRUE);
		m_cAThirdDeliveryRemark.SetReadOnly(FALSE);

	}
	else
	{
		m_bAThirdDeliveryDate = FALSE;
		m_cAThirdDeliveryDate.EnableWindow(FALSE);
		m_cAThirdDeliveryRemark.SetReadOnly(TRUE);

		m_dAThirdDeliveryDate = COleDateTime::GetCurrentTime();
		m_sAThirdDeliveryRemark.Empty();
	}

	UpdateData(FALSE);
}

void CCommerceDeliveryPage::ClearEdit(void)
{
	UpdateData(TRUE);

    m_dDeliveryReceivedDate = COleDateTime::GetCurrentTime();
	m_dADeliveryDate = COleDateTime::GetCurrentTime();
	m_sADeliveryRemark.Empty();
	m_dASecDeliveryDate = COleDateTime::GetCurrentTime();
	m_sASecDeliveryRemark.Empty();
	m_bBatchDelivery = FALSE;
	m_dAThirdDeliveryDate = COleDateTime::GetCurrentTime();
	m_sAThirdDeliveryRemark.Empty();
	m_bDeliveryDone = FALSE;
	m_bDeliveryReceived = FALSE;
	m_bADeliveryDate = FALSE;
	m_bAThirdDeliveryDate = FALSE;
	m_cDeliveryReceivedDate.EnableWindow(FALSE);
	m_cADeliveryDate.EnableWindow(FALSE);
	m_cADeliveryRemark.SetReadOnly(TRUE);
	m_cASecDeliveryDate.EnableWindow(FALSE);
	m_cASecDeliveryRemark.SetReadOnly(TRUE);
	m_cAThirdDeliveryDate.EnableWindow(FALSE);
	m_cAThirdDeliveryRemark.SetReadOnly(TRUE);

	UpdateData(FALSE);
}
