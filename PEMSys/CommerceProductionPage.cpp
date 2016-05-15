// CommerceProductionPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "CommerceProductionPage.h"
#include ".\commerceproductionpage.h"


// CCommerceProductionPage 对话框

IMPLEMENT_DYNAMIC(CCommerceProductionPage, CPropertyPage)
CCommerceProductionPage::CCommerceProductionPage()
	: CPropertyPage(CCommerceProductionPage::IDD)
	, m_dProductionReceivedDate(COleDateTime::GetCurrentTime())
	, m_bProductionReceivedDate(FALSE)
	, m_dPlantProductionDate(COleDateTime::GetCurrentTime())
	, m_bPlantProductionDate(FALSE)
	, m_dPDeliveryDate(COleDateTime::GetCurrentTime())
	, m_bPDeliveryDate(FALSE)
	, m_sPDeliveryRemark(_T(""))
	, m_bPBatchCheck(FALSE)
	, m_dPSecDeliveryDate(COleDateTime::GetCurrentTime())
	, m_sPSecDeliveryRemark(_T(""))
	, m_bPThirdDeliveryDate(FALSE)
	, m_dPThirdDeliveryDate(COleDateTime::GetCurrentTime())
	, m_sPThirdDeliveryRemark(_T(""))
	, m_bConfigureFinsh(FALSE)
	, m_dConfigureFinish(COleDateTime::GetCurrentTime())
	, m_bPurchaseReturn(FALSE)
	, m_dPurchaseReturn(COleDateTime::GetCurrentTime())
{
}

CCommerceProductionPage::~CCommerceProductionPage()
{
}

void CCommerceProductionPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PRODUCTIONRECEIVEDDATE, m_cProductionReceiveDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PRODUCTIONRECEIVEDDATE, m_dProductionReceivedDate);
	DDX_Check(pDX, IDC_CHECK_PRODUCTIONRECEIVED, m_bProductionReceivedDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PLANTPRODUCTIONDATE, m_cPlantProductionDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PLANTPRODUCTIONDATE, m_dPlantProductionDate);
	DDX_Check(pDX, IDC_CHECK_PLANTPRODUCTIONDATE, m_bPlantProductionDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PDELIVERYDATE, m_cPDeliveryDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PDELIVERYDATE, m_dPDeliveryDate);
	DDX_Check(pDX, IDC_CHECK_PDELIVERYDATE, m_bPDeliveryDate);
	DDX_Control(pDX, IDC_EDIT_PDELIVERYREMARK, m_cPDeliveryRemark);
	DDX_Text(pDX, IDC_EDIT_PDELIVERYREMARK, m_sPDeliveryRemark);
	DDX_Check(pDX, IDC_CHECK_BATCHCHECK, m_bPBatchCheck);
	DDX_Control(pDX, IDC_DATETIMEPICKER_AMDELIVERYDATE, m_cPSecDeliveryDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_AMDELIVERYDATE, m_dPSecDeliveryDate);
	DDX_Control(pDX, IDC_EDIT_PSECDELIVERYDATE, m_cPSecDeliveryRemark);
	DDX_Text(pDX, IDC_EDIT_PSECDELIVERYDATE, m_sPSecDeliveryRemark);
	DDX_Check(pDX, IDC_CHECK_PTHIRDDELIVERYDATE, m_bPThirdDeliveryDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PTHIRDDELIVERYDATE, m_cPThirdDeliveryDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PTHIRDDELIVERYDATE, m_dPThirdDeliveryDate);
	DDX_Control(pDX, IDC_EDIT_PTHIRDDELIVERYDATE, m_cPThirdDeliveryRemark);
	DDX_Text(pDX, IDC_EDIT_PTHIRDDELIVERYDATE, m_sPThirdDeliveryRemark);
	DDX_Check(pDX, IDC_CHECK_CONFIGUREFINISH, m_bConfigureFinsh);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CONFIGUREFINISH, m_dConfigureFinish);
	DDX_Check(pDX, IDC_CHECK_PURCHASERETURN, m_bPurchaseReturn);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PURCHASERETURN, m_dPurchaseReturn);
	DDX_Control(pDX, IDC_DATETIMEPICKER_CONFIGUREFINISH, m_cConfigureFinish);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PURCHASERETURN, m_cPurchaseReturn);
}


BEGIN_MESSAGE_MAP(CCommerceProductionPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_PDELIVERYDATE, OnBnClickedCheckPdeliverydate)
	ON_BN_CLICKED(IDC_CHECK_BATCHCHECK, OnBnClickedCheckBatchcheck)
	ON_BN_CLICKED(IDC_CHECK_PTHIRDDELIVERYDATE, OnBnClickedCheckPthirddeliverydate)
	ON_BN_CLICKED(IDC_CHECK_PRODUCTIONRECEIVED, OnBnClickedCheckProductionreceived)
	ON_BN_CLICKED(IDC_CHECK_PLANTPRODUCTIONDATE, OnBnClickedCheckPlantproductiondate)
	ON_BN_CLICKED(IDC_CHECK_CONFIGUREFINISH, OnBnClickedCheckConfigurefinish)
	ON_BN_CLICKED(IDC_CHECK_PURCHASERETURN, OnBnClickedCheckPurchasereturn)
END_MESSAGE_MAP()


// CCommerceProductionPage 消息处理程序

void CCommerceProductionPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

BOOL CCommerceProductionPage::PreTranslateMessage(MSG* pMsg)
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

void CCommerceProductionPage::OnBnClickedCheckProductionreceived()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_PRODUCTIONRECEIVED))->GetCheck())
	{
       m_bProductionReceivedDate = TRUE;
	   m_cProductionReceiveDate.EnableWindow(TRUE);

	}
	else
	{
		m_bProductionReceivedDate = FALSE;
		m_cProductionReceiveDate.EnableWindow(FALSE);
		m_dProductionReceivedDate = COleDateTime::GetCurrentTime();

	}

	UpdateData(FALSE);
}

void CCommerceProductionPage::OnBnClickedCheckPdeliverydate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_PDELIVERYDATE))->GetCheck())
	{
		m_bPDeliveryDate = TRUE;
		m_cPDeliveryDate.EnableWindow(TRUE);
		m_cPDeliveryRemark.SetReadOnly(FALSE);

	}
	else
	{
		m_bPDeliveryDate = FALSE;
		m_cPDeliveryDate.EnableWindow(FALSE);
		m_cPDeliveryRemark.SetReadOnly(TRUE);
		m_dPDeliveryDate = COleDateTime::GetCurrentTime();
		m_sPDeliveryRemark.Empty();

		if(((CButton*)GetDlgItem(IDC_CHECK_BATCHCHECK))->GetCheck())
		{
			m_bPBatchCheck = FALSE;
			m_cPSecDeliveryDate.EnableWindow(FALSE);
			m_cPSecDeliveryRemark.SetReadOnly(TRUE);


			m_dPSecDeliveryDate = COleDateTime::GetCurrentTime();
			m_sPSecDeliveryRemark.Empty();

			if(((CButton*)GetDlgItem(IDC_CHECK_PTHIRDDELIVERYDATE))->GetCheck())
			{
				m_bPThirdDeliveryDate= FALSE;
				m_cPThirdDeliveryDate.EnableWindow(FALSE);
				m_cPThirdDeliveryRemark.SetReadOnly(TRUE);

				m_dPThirdDeliveryDate = COleDateTime::GetCurrentTime();
				m_sPThirdDeliveryRemark.Empty();
			}

		}
	}

	UpdateData(FALSE);
}

void CCommerceProductionPage::OnBnClickedCheckBatchcheck()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_BATCHCHECK))->GetCheck() && m_bPDeliveryDate)
	{
		m_bPBatchCheck = TRUE;
		m_cPSecDeliveryDate.EnableWindow(TRUE);
		m_cPSecDeliveryRemark.SetReadOnly(FALSE);

	}
	else
	{
		m_bPBatchCheck = FALSE;
		m_cPSecDeliveryDate.EnableWindow(FALSE);
		m_cPSecDeliveryRemark.SetReadOnly(TRUE);


		m_dPSecDeliveryDate = COleDateTime::GetCurrentTime();
		m_sPSecDeliveryRemark.Empty();

		if(((CButton*)GetDlgItem(IDC_CHECK_PTHIRDDELIVERYDATE))->GetCheck())
		{
			m_bPThirdDeliveryDate= FALSE;
			m_cPThirdDeliveryDate.EnableWindow(FALSE);
			m_cPThirdDeliveryRemark.SetReadOnly(TRUE);

			m_dPThirdDeliveryDate = COleDateTime::GetCurrentTime();
			m_sPThirdDeliveryRemark.Empty();
		}

	}

	UpdateData(FALSE);
}

void CCommerceProductionPage::OnBnClickedCheckPthirddeliverydate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_PTHIRDDELIVERYDATE))->GetCheck() && m_bPBatchCheck)
	{
		m_bPThirdDeliveryDate= TRUE;
		m_cPThirdDeliveryDate.EnableWindow(TRUE);
		m_cPThirdDeliveryRemark.SetReadOnly(FALSE);

	}
	else
	{
		m_bPThirdDeliveryDate= FALSE;
		m_cPThirdDeliveryDate.EnableWindow(FALSE);
		m_cPThirdDeliveryRemark.SetReadOnly(TRUE);

		m_dPThirdDeliveryDate = COleDateTime::GetCurrentTime();
		m_sPThirdDeliveryRemark.Empty();
	}

	UpdateData(FALSE);

}

void CCommerceProductionPage::ClearEdit(void)
{
	UpdateData(TRUE);

	m_dProductionReceivedDate = COleDateTime::GetCurrentTime();
	m_bProductionReceivedDate = FALSE;
    m_dPlantProductionDate = COleDateTime::GetCurrentTime();
	m_bPlantProductionDate = FALSE;
	m_dPDeliveryDate = COleDateTime::GetCurrentTime();
	m_bPDeliveryDate = FALSE;
	m_sPDeliveryRemark.Empty();
	m_bPBatchCheck = FALSE;
	m_dPSecDeliveryDate = COleDateTime::GetCurrentTime();
	m_sPSecDeliveryRemark.Empty();
	m_bPThirdDeliveryDate = FALSE;
	m_dPThirdDeliveryDate = COleDateTime::GetCurrentTime();
	m_sPThirdDeliveryRemark.Empty();
	m_cProductionReceiveDate.EnableWindow(FALSE);
	m_cPlantProductionDate.EnableWindow(FALSE);
	m_cPDeliveryDate.EnableWindow(FALSE);
	m_cPDeliveryRemark.SetReadOnly(TRUE);
	m_cPSecDeliveryDate.EnableWindow(FALSE);
	m_cPSecDeliveryRemark.SetReadOnly(TRUE);
	m_cPThirdDeliveryDate.EnableWindow(FALSE);
	m_cPThirdDeliveryRemark.SetReadOnly(TRUE);

	m_bConfigureFinsh = FALSE;
	m_dConfigureFinish = COleDateTime::GetCurrentTime();
	m_cConfigureFinish.EnableWindow(FALSE);

	m_bPurchaseReturn = FALSE;
	m_dPurchaseReturn = COleDateTime::GetCurrentTime();
	m_cPurchaseReturn.EnableWindow(FALSE);
	UpdateData(FALSE);
}



void CCommerceProductionPage::OnBnClickedCheckPlantproductiondate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_PLANTPRODUCTIONDATE))->GetCheck())
	{
		m_bPlantProductionDate= TRUE;
		m_cPlantProductionDate.EnableWindow(TRUE);
	}
	else
	{
		m_bPlantProductionDate= FALSE;
		m_cPlantProductionDate.EnableWindow(FALSE);
		m_dPlantProductionDate = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);

}

void CCommerceProductionPage::OnBnClickedCheckConfigurefinish()
{
	// TODO: 在此添加控件通知处理程序代码
	if(((CButton*)GetDlgItem(IDC_CHECK_CONFIGUREFINISH))->GetCheck())
	{
		m_bConfigureFinsh= TRUE;
		m_cConfigureFinish.EnableWindow(TRUE);
	}
	else
	{
		m_bConfigureFinsh= FALSE;
		m_cConfigureFinish.EnableWindow(FALSE);
		m_dConfigureFinish = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}

void CCommerceProductionPage::OnBnClickedCheckPurchasereturn()
{
	// TODO: 在此添加控件通知处理程序代码
	if(((CButton*)GetDlgItem(IDC_CHECK_PURCHASERETURN))->GetCheck())
	{
		m_bPurchaseReturn= TRUE;
		m_cPurchaseReturn.EnableWindow(TRUE);
	}
	else
	{
		m_bPurchaseReturn = FALSE;
		m_cPurchaseReturn.EnableWindow(FALSE);
		m_dPurchaseReturn = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}
