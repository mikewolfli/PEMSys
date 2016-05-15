// ItemShaftPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemShaftPage.h"
#include ".\itemshaftpage.h"


// CItemShaftPage 对话框
extern CString m_sgElevatorModel;
extern CString m_sgRatedLoad;
extern CString m_sgRatedSpeed;
IMPLEMENT_DYNAMIC(CItemShaftPage, CPropertyPage)
CItemShaftPage::CItemShaftPage()
	: CPropertyPage(CItemShaftPage::IDD)
	, m_iSW(0)
	, m_iSD(0)
	, m_lTH(0)
	, m_lOH(0)
	, m_iPD(0)
	, m_sCounterWeight(_T(""))
	, m_iCounterWeightHeight(0)
	, m_bWideJamb(FALSE)
	, m_iCWGauge(0)
	, m_iJambXC(0)
	, m_sSGPosition(_T(""))
	, m_sWJType(_T(""))
	, m_iCCW(0)
	, m_iCS1(0)
	, m_iCS2(0)
	, m_iCWS(0)
	, m_bCheck(FALSE)
{
}

CItemShaftPage::~CItemShaftPage()
{
}

void CItemShaftPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SHAFT_SHAFTWIDTH, m_iSW);
	DDX_Text(pDX, IDC_EDIT_SHAFT_SHAFTDEPTH, m_iSD);
	DDX_Text(pDX, IDC_EDIT_SHAFT_TH, m_lTH);
	DDX_Text(pDX, IDC_EDIT_SHAFT_OH, m_lOH);
	DDX_Text(pDX, IDC_EDIT_SHAFT_PD, m_iPD);
	DDX_CBString(pDX, IDC_COMBO_SHAFT_COUNTERWEIGHT, m_sCounterWeight);
	DDX_Text(pDX, IDC_EDIT_SHAFT_COUNTERWEIGHTHEIGHT, m_iCounterWeightHeight);
	DDX_Check(pDX, IDC_CHECK_SHAFT_WIDEJAMB, m_bWideJamb);
	DDX_CBIndex(pDX, IDC_COMBO_SHAFT_CWGAUGE, m_iCWGauge);
	DDX_Text(pDX, IDC_EDIT_SHAFT_JAMBXC, m_iJambXC);
	DDX_CBString(pDX, IDC_COMBO_SGPOSITION, m_sSGPosition);
	DDX_CBString(pDX, IDC_COMBO_SHAFT_WJTYPE, m_sWJType);
	DDX_Text(pDX, IDC_EDIT_SHAFT_CCW, m_iCCW);
	DDX_Text(pDX, IDC_EDIT_SHAFT_CS1, m_iCS1);
	DDX_Text(pDX, IDC_EDIT_SHAFT_CS2, m_iCS2);
	DDX_Text(pDX, IDC_EDIT_SHAFT_CWS, m_iCWS);
	DDX_Control(pDX, IDC_EDIT_SHAFT_JAMBXC, m_cJambXC);
	DDX_Control(pDX, IDC_COMBO_SHAFT_WJTYPE, m_cWJType);
}


BEGIN_MESSAGE_MAP(CItemShaftPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_SHAFT_WIDEJAMB, OnBnClickedCheckShaftWidejamb)
END_MESSAGE_MAP()


// CItemShaftPage 消息处理程序

void CItemShaftPage::ClearEdit(void)
{
	UpdateData(TRUE);
	m_iSW = 0;
	m_iSD = 0;
    m_lTH = 0;
	m_lOH = 0;
	m_iPD = 0;
	m_sCounterWeight.Empty();
	m_iCounterWeightHeight = 0;
	m_bWideJamb = FALSE;
	m_iCWGauge = 0;
	m_iJambXC = 0;
	m_sSGPosition.Empty();
    m_sWJType.Empty();
	m_iCCW = 0;
	m_iCS1 = 0;
	m_iCS2 = 0;
	m_iCWS = 0;

	UpdateData(FALSE);
}

BOOL CItemShaftPage::PreTranslateMessage(MSG* pMsg)
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

BOOL CItemShaftPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
    ClearEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CItemShaftPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

void CItemShaftPage::OnBnClickedCheckShaftWidejamb()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_SHAFT_WIDEJAMB))->GetCheck())
	{
		m_bWideJamb = TRUE;
		m_cJambXC.SetReadOnly(FALSE);
		m_cWJType.EnableWindow(TRUE);

	}
	else
	{
		m_bWideJamb = FALSE;
		m_cJambXC.SetReadOnly(TRUE);
		m_cWJType.EnableWindow(FALSE);

	}

	UpdateData(FALSE);
}

BOOL CItemShaftPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	if(!m_sgElevatorModel.IsEmpty()&&!m_sgRatedLoad.IsEmpty()&&!m_bCheck)
	{
		int iRatedLoad = atoi(m_sgRatedLoad);
		float fRatedSpeed = atof(m_sgRatedSpeed);
		if(m_sgElevatorModel == "TE-E"||m_sgElevatorModel=="TE-ES")
		{
			if(iRatedLoad == 630)
			{
				m_iSW = 1900;
				m_iSD = 1800;
			}
			if(iRatedLoad == 800)
			{
				m_iSW = 1900;
				m_iSD = 2100;
			}
			if(iRatedLoad == 1000)
			{
				m_iSW = 2200;
				m_iSD = 2100;
			}
			if(iRatedLoad == 1150)
			{
				m_iSW = 2400;
				m_iSD = 2100;
			}
			if(iRatedLoad == 1250)
			{
				m_iSW = 2600;
				m_iSD = 2100;
			}
			if(iRatedLoad == 1350)
			{
				m_iSW = 2550;
				m_iSD = 2250;
			}
			if(iRatedLoad == 1600)
			{
				m_iSW = 2400;
				m_iSD = 3000;
			}

		}

		else if(m_sgElevatorModel == "TE-GL"||m_sgElevatorModel=="TE-GLS")
		{
			if(iRatedLoad == 630)
			{
				m_iSW = 1900;
				m_iSD = 1800;
			}
			if(iRatedLoad == 800)
			{
				m_iSW = 1900;
				m_iSD = 2100;
			}
			if(iRatedLoad == 1000)
			{
				m_iSW = 2200;
				m_iSD = 2100;
			}
			if(iRatedLoad == 1150)
			{
				m_iSW = 2400;
				m_iSD = 2100;
			}
		}
		else if(m_sgElevatorModel == "TE-MRL")
		{
			if(iRatedLoad == 630)
			{
				m_iSW = 1800;
				m_iSD = 1700;
			}   
			if(iRatedLoad == 800)
			{
				m_iSW = 1900;
				m_iSD = 1800;
			}
			if(iRatedLoad == 1000)
			{
				m_iSW = 2150;
				m_iSD = 1900;
			}

		}
		else if(m_sgElevatorModel == "TE-MRLS")
		{
			if(iRatedLoad == 630)
			{
				m_iSW = 1800;
				m_iSD = 1700;
			}   
			if(iRatedLoad == 800)
			{
				m_iSW = 1900;
				m_iSD = 1800;
			}
			if(iRatedLoad == 1000)
			{
				m_iSW = 2150;
				m_iSD = 1900;
			}
		}
		else if(m_sgElevatorModel=="TE-GLM")
		{
			if(iRatedLoad == 800)
			{
				m_iSW = 1900;
				m_iSD = 2100;
			}
			if(iRatedLoad == 1000)
			{
				m_iSW = 2200;
				m_iSD = 2100;
			}
		}
		else if(m_sgElevatorModel=="TE-F")
		{
			if(iRatedLoad == 1000)
			{
				m_iSW = 2400;
				m_iSD = 2150;
			}
			if(iRatedLoad == 2000)
			{
				m_iSW = 3000;
				m_iSD = 2650;
			}
			if(iRatedLoad == 3000)
			{
				m_iSW = 3050;
				m_iSD = 3450;
			}
		}

		if(m_sgElevatorModel == _T("TE-E") || m_sgElevatorModel == _T("TE-ES") || m_sgElevatorModel == _T("TE-GL") || m_sgElevatorModel == _T("TE-GLS") || m_sgElevatorModel == _T("TE-GLM") || m_sgElevatorModel == _T("TE-F"))
		{
			if(iRatedLoad <=1000 && fRatedSpeed <2.5)
			{
				m_iCounterWeightHeight = 2700;
			}
			else if(iRatedLoad > 1000 && iRatedLoad <2000 )
			{
				m_iCounterWeightHeight = 3400;
			}
			else if(iRatedLoad >= 2000)
			{
				m_iCounterWeightHeight = 3700;
			}
		}
		else if(m_sgElevatorModel == _T("TE-MRLS"))
		{
			m_iCounterWeightHeight = 2700;
		}
		else if(m_sgElevatorModel == _T("TE-MRL"))
		{
			if(iRatedLoad == 630)
				m_iCounterWeightHeight = 3130;
			else if(iRatedLoad == 800)
				m_iCounterWeightHeight = 3175;
			else if(iRatedLoad == 1000)
				m_iCounterWeightHeight = 3375;
		}

	}

	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}
