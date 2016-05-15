// CommerceFollowupPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "CommerceFollowupPage.h"
#include ".\commercefollowuppage.h"


// CCommerceFollowupPage 对话框

IMPLEMENT_DYNAMIC(CCommerceFollowupPage, CPropertyPage)
CCommerceFollowupPage::CCommerceFollowupPage()
	: CPropertyPage(CCommerceFollowupPage::IDD)
	, m_dGADReceived(COleDateTime::GetCurrentTime())
	, m_dLatestAmend(COleDateTime::GetCurrentTime())
	, m_dCSRelease(COleDateTime::GetCurrentTime())
	, m_dCSReply(COleDateTime::GetCurrentTime())
	, m_dACompleteDate(COleDateTime::GetCurrentTime())
	, m_sAmendRemark(_T(""))
	, m_sReplyRemark(_T(""))
	, m_bGADReceived(FALSE)
	, m_bLatestAmend(FALSE)
	, m_bCSRelease(FALSE)
	, m_bCSReply(FALSE)
	, m_bACompleteDate(FALSE)
{
}

CCommerceFollowupPage::~CCommerceFollowupPage()
{
}

void CCommerceFollowupPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_GADRECEIVE, m_cGADReceived);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_GADRECEIVE, m_dGADReceived);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TLAMENDMENT, m_cLatestAmend);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_TLAMENDMENT, m_dLatestAmend);
	DDX_Control(pDX, IDC_DATETIMEPICKER_CSRELEASE, m_cCSRelease);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CSRELEASE, m_dCSRelease);
	DDX_Control(pDX, IDC_DATETIMEPICKER_CSREPLY, m_cCSReply);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CSREPLY, m_dCSReply);
	DDX_Control(pDX, IDC_DATETIMEPICKER_ASSESSMENTCDATE, m_cACompleteDate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ASSESSMENTCDATE, m_dACompleteDate);
	DDX_Control(pDX, IDC_EDIT_AMENDMENTREMARK, m_cAmendRemark);
	DDX_Text(pDX, IDC_EDIT_AMENDMENTREMARK, m_sAmendRemark);
	DDX_Control(pDX, IDC_EDIT_REPLYREMARK, m_cReplyRemark);
	DDX_Text(pDX, IDC_EDIT_REPLYREMARK, m_sReplyRemark);
	DDX_Check(pDX, IDC_CHECK_GADRECEIVE, m_bGADReceived);
	DDX_Check(pDX, IDC_CHECK_THELATESTAMENDMENT, m_bLatestAmend);
	DDX_Check(pDX, IDC_CHECK_CONFIRMATIONSHEETRELEASE, m_bCSRelease);
	DDX_Check(pDX, IDC_CHECK_CONFIRMATIONSHEETREPLY, m_bCSReply);
	DDX_Check(pDX, IDC_CHECK_ASSESSMENTCOMPLETE, m_bACompleteDate);
}


BEGIN_MESSAGE_MAP(CCommerceFollowupPage, CPropertyPage)
//	ON_BN_CLICKED(IDC_CHECK_GADRECEIVE, OnBnClickedCheckGadreceive)
	ON_BN_CLICKED(IDC_CHECK_THELATESTAMENDMENT, OnBnClickedCheckThelatestamendment)
	ON_BN_CLICKED(IDC_CHECK_CONFIRMATIONSHEETRELEASE, OnBnClickedCheckConfirmationsheetrelease)
	ON_BN_CLICKED(IDC_CHECK_CONFIRMATIONSHEETREPLY, OnBnClickedCheckConfirmationsheetreply)
	ON_BN_CLICKED(IDC_CHECK_ASSESSMENTCOMPLETE, OnBnClickedCheckAssessmentcomplete)
	ON_BN_CLICKED(IDC_CHECK_GADRECEIVE, OnBnClickedCheckGadreceive)
END_MESSAGE_MAP()


// CCommerceFollowupPage 消息处理程序

void CCommerceFollowupPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

BOOL CCommerceFollowupPage::PreTranslateMessage(MSG* pMsg)
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

//void CCommerceFollowupPage::OnBnClickedCheckGadreceive()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	UpdateData(TRUE);
//
//	if(((CButton*)GetDlgItem(IDC_CHECK_GADRECEIVE))->GetCheck())
//	{
//		m_bGADReceived = TRUE;
//		m_cGADReceived.EnableWindow(TRUE);
//
//	}
//	else
//	{
//		m_bGADReceived = FALSE;
//		m_cGADReceived.EnableWindow(FALSE);
//
//		m_dGADReceived = COleDateTime::GetCurrentTime();
//
//	}
//
//	UpdateData(FALSE);
//}

void CCommerceFollowupPage::OnBnClickedCheckThelatestamendment()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_THELATESTAMENDMENT))->GetCheck())
	{
		m_bLatestAmend  = TRUE;
		m_cLatestAmend.EnableWindow(TRUE);
		m_cAmendRemark.SetReadOnly(FALSE);

	}
	else
	{
		m_bLatestAmend  = FALSE;
		m_cLatestAmend.EnableWindow(FALSE);
		m_cAmendRemark.SetReadOnly(TRUE);
		m_sAmendRemark.Empty();
		m_dLatestAmend = COleDateTime::GetCurrentTime();

	}

	UpdateData(FALSE);
}

void CCommerceFollowupPage::OnBnClickedCheckConfirmationsheetrelease()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_CONFIRMATIONSHEETRELEASE))->GetCheck())
	{
		m_bCSRelease = TRUE;
		m_cCSRelease.EnableWindow(TRUE);

	}
	else
	{
		m_bCSRelease = FALSE;
		m_cCSRelease.EnableWindow(FALSE);
		m_dCSRelease = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}

void CCommerceFollowupPage::OnBnClickedCheckConfirmationsheetreply()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_CONFIRMATIONSHEETREPLY))->GetCheck())
	{
		m_bCSReply = TRUE;
		m_cCSReply.EnableWindow(TRUE);
		m_cReplyRemark.SetReadOnly(FALSE);

	}
	else
	{
		m_bCSReply = FALSE;
		m_cCSReply.EnableWindow(FALSE);
		m_cReplyRemark.SetReadOnly(TRUE);
		m_sReplyRemark.Empty();
		m_dCSReply = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}

void CCommerceFollowupPage::OnBnClickedCheckAssessmentcomplete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_ASSESSMENTCOMPLETE))->GetCheck())
	{
		m_bACompleteDate = TRUE;
		m_cACompleteDate.EnableWindow(TRUE);

	}
	else
	{
		m_bACompleteDate = FALSE;
		m_cACompleteDate.EnableWindow(FALSE);
		m_dACompleteDate = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);

}

void CCommerceFollowupPage::ClearEdit(void)
{
	UpdateData(TRUE);

	m_dGADReceived = COleDateTime::GetCurrentTime();
	m_dLatestAmend = COleDateTime::GetCurrentTime();
	m_dCSRelease = COleDateTime::GetCurrentTime();
	m_dCSReply = COleDateTime::GetCurrentTime();
	m_dACompleteDate = COleDateTime::GetCurrentTime();
	m_sAmendRemark.Empty();
	m_sReplyRemark.Empty();
	m_bGADReceived = FALSE;
    m_bLatestAmend = FALSE;
	m_bCSRelease = FALSE;
	m_bCSReply = FALSE;
	m_bACompleteDate = FALSE;
	m_cGADReceived.EnableWindow(FALSE);
	m_cLatestAmend.EnableWindow(FALSE);
	m_cCSRelease.EnableWindow(FALSE);
	m_cCSReply.EnableWindow(FALSE);
	m_cACompleteDate.EnableWindow(FALSE);
	m_cReplyRemark.SetReadOnly(TRUE);
	m_cAmendRemark.SetReadOnly(TRUE);

	UpdateData(FALSE);
}

void CCommerceFollowupPage::OnBnClickedCheckGadreceive()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_GADRECEIVE))->GetCheck())
	{
		m_bGADReceived = TRUE;
		m_cGADReceived.EnableWindow(TRUE);

	}
	else
	{
		m_bGADReceived = FALSE;
		m_cGADReceived.EnableWindow(FALSE);
		m_dGADReceived = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}
