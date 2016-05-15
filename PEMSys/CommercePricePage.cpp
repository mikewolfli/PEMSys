// CommercePricePage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEMSys.h"
#include "CommercePricePage.h"
#include ".\commercepricepage.h"


// CCommercePricePage �Ի���

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


// CCommercePricePage ��Ϣ�������

void CCommercePricePage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

BOOL CCommercePricePage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
//	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	UpdateData(TRUE);
//	m_dbMaterialAmount = m_dbAmount - m_dbFreightInsurance;
//
//	UpdateData(FALSE);
//}

void CCommercePricePage::OnEnChangeEditFreightinsurance()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_dbAmount  = m_dbMaterialAmount + m_dbFreightInsurance;

	UpdateData(FALSE);
}
