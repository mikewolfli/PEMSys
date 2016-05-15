// ItemPartsPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemPartsPage.h"
#include ".\itempartspage.h"


// CItemPartsPage 对话框
extern CString m_sgElevatorModel;
extern CString m_sgRatedLoad;
extern CString m_sgRatedSpeed;
IMPLEMENT_DYNAMIC(CItemPartsPage, CPropertyPage)
CItemPartsPage::CItemPartsPage()
	: CPropertyPage(CItemPartsPage::IDD)
	, m_sTraction(_T(""))
	, m_sCarRail(_T(""))
	, m_sEncode(_T(""))
	, m_sCWRail(_T(""))
	, m_sDoorSystem(_T(""))
	, m_sSafety(_T(""))
	, m_sSpeedGovernor(_T(""))
	, m_sBuffer(_T(""))
	, m_bNonstandardCheck(FALSE)
	, m_sNonstandardRemark(_T(""))
{
}

CItemPartsPage::~CItemPartsPage()
{
}

void CItemPartsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_TRACTION, m_sTraction);
	DDX_CBString(pDX, IDC_COMBO_CARRAIL, m_sCarRail);
	DDX_CBString(pDX, IDC_COMBO_ENCODE, m_sEncode);
	DDX_CBString(pDX, IDC_COMBO_CWRAIL, m_sCWRail);
	DDX_CBString(pDX, IDC_COMBO_CAR_DOORSYSTEM, m_sDoorSystem);
	DDX_CBString(pDX, IDC_COMBO_SAFETY, m_sSafety);
	DDX_CBString(pDX, IDC_COMBO_SPEEDGOVERNOR, m_sSpeedGovernor);
	DDX_CBString(pDX, IDC_COMBO_BUFFER, m_sBuffer);
	DDX_Check(pDX, IDC_CHECK_NONSTANDARD, m_bNonstandardCheck);
	DDX_Text(pDX, IDC_EDIT_NONSTANDARDREMARK, m_sNonstandardRemark);
	DDX_Control(pDX, IDC_EDIT_NONSTANDARDREMARK, m_cNonstandardRemark);
}


BEGIN_MESSAGE_MAP(CItemPartsPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_NONSTANDARD, OnBnClickedCheckNonstandard)
	ON_CBN_SELCHANGE(IDC_COMBO_SAFETY, OnCbnSelchangeComboSafety)
END_MESSAGE_MAP()


// CItemPartsPage 消息处理程序

void CItemPartsPage::ClearEdit(void)
{
	UpdateData(TRUE);
	m_sTraction.Empty();
	m_sCarRail.Empty();
	m_sEncode.Empty();
	m_sCWRail.Empty();
	m_sDoorSystem.Empty();
	m_sSafety.Empty();
	m_sSpeedGovernor.Empty();
	m_sBuffer.Empty();
	m_bNonstandardCheck = FALSE;
	m_sNonstandardRemark.Empty();

	UpdateData(FALSE);
}

BOOL CItemPartsPage::PreTranslateMessage(MSG* pMsg)
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

BOOL CItemPartsPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
    ClearEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CItemPartsPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

void CItemPartsPage::OnBnClickedCheckNonstandard()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(((CButton*)GetDlgItem(IDC_CHECK_NONSTANDARD))->GetCheck())
	{
		m_bNonstandardCheck = TRUE;
		m_cNonstandardRemark.EnableWindow(TRUE);
	}
	else
	{
		m_bNonstandardCheck = FALSE;
		m_cNonstandardRemark.EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

BOOL CItemPartsPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	int iRatedLoad = atoi(m_sgRatedLoad);
	float fRatedSpeed = atof(m_sgRatedSpeed);

	if(!m_sgElevatorModel.IsEmpty()&&!m_sgRatedLoad.IsEmpty())
	{
		if(m_sgElevatorModel == "TE-E")
		{
			if(iRatedLoad == 630 && fRatedSpeed == 0.63)
			{
                m_sTraction = "TW73S";
			}
			else if(iRatedLoad == 630 && fRatedSpeed == 1.0)
			{
               m_sTraction = "TW75S";
			}
			else if(iRatedLoad == 1000 ||iRatedLoad == 800 &&fRatedSpeed == 1.0)
			{
               m_sTraction = "TW63";
			}
	
			else if((iRatedLoad == 800 && fRatedSpeed == 1.75)||(iRatedLoad == 1150 && fRatedSpeed == 1.0))
			{
                m_sTraction = "TW93";
			}
			else if((iRatedLoad == 1000 || iRatedLoad == 1150 && fRatedSpeed == 1.75)||(iRatedLoad == 1250 ||iRatedLoad == 1350)||(iRatedLoad == 1600&& fRatedSpeed == 1.0))
			{
                m_sTraction = "TW98";
			}
			else if(iRatedLoad ==1600 && fRatedSpeed == 1.75)
			{
                m_sTraction = "TW104B9";
			}

			if((iRatedLoad==1000||iRatedLoad == 800) &&( fRatedSpeed == 1.0))
				m_sEncode =  "RI76TD";
			else

				m_sEncode = "SBH-1024-2T";
		}
		else if(m_sgElevatorModel == "TE-ES")
		{
            if(iRatedLoad == 630)
			{
				m_sTraction = "TWN160D";
			}
			else if(iRatedLoad == 800 && fRatedSpeed == 1.0)
			{
				m_sTraction = "TWT200";
			}
			else if((iRatedLoad == 800 && fRatedSpeed == 1.75)||iRatedLoad == 1000 || iRatedLoad == 1150)
			{
				m_sTraction = "TWT240";
			}
			else if(iRatedLoad == 1250 ||iRatedLoad == 1350 || iRatedLoad == 1600)
			{
				m_sTraction = "TWT245D";
			}

			m_sEncode = "1024 Pulse NEMICON(Japan)";

		}
		else if(m_sgElevatorModel == "TE-GL" || m_sgElevatorModel == "TE-MRL")
		{
            m_sTraction = "PMS425";
			if(m_sgElevatorModel == "TE-GL")
			    m_sEncode = "ECN1313 (ENDAT01)";
			else if(m_sgElevatorModel == "TE-MRL")
			{
               m_sEncode = "SRS60";
			}
		}
		else if(m_sgElevatorModel == "TE-GLS")
		{
            m_sTraction = "PMS300";
			m_sEncode = "ECN1313 (ENDAT01)";
		}
		else if(m_sgElevatorModel == "TE-MRLS")
		{
	       m_sTraction = "PMS215";
		   m_sEncode = "TS5246N160";
		}
		else if(m_sgElevatorModel == "TE-GLM")
		{
	       m_sTraction = "TGT300";
		   m_sEncode = "ECN1313 (ENDAT01)";
		}
		else if(m_sgElevatorModel == "TE-F")
		{
            if(iRatedLoad == 1000 || iRatedLoad == 2000)
			{
				m_sTraction = "TWT245";
			}
			else if(iRatedLoad == 3000)
			{
				m_sTraction = "TWT245D";
			}
		   m_sEncode = "MEMICON(1024Pulse)";
		}

		if(m_sgElevatorModel== _T("TE-E")||m_sgElevatorModel==_T("TE-ES")||m_sgElevatorModel==_T("TE-GL"))
		{
			if(iRatedLoad == 630)
			{
				m_sCarRail = _T("T75/3B");
			}
			else if(iRatedLoad <=1000&& iRatedLoad >= 800)
			{
				m_sCarRail = _T("T89/B");
			}
			else if(iRatedLoad>1000)
			{
				m_sCarRail = _T("T114/B");
			}
		}
		else if(m_sgElevatorModel == _T("TE-GLS")||m_sgElevatorModel==_T("TE-GLM"))
		{
			if(iRatedLoad >=800 && iRatedLoad <= 1000 && fRatedSpeed < 2.5)
			{
				m_sCarRail = _T("T89/B");
			}else if(fRatedSpeed >= 2.5)
			{
				m_sCarRail = _T("T90/B");
			}
			else if(iRatedLoad >=1150)
			{
				m_sCarRail = _T("T114/B");
			}
		}
		else if(m_sgElevatorModel == _T("TE-MRL"))
		{
			m_sCarRail = _T("T89/B");
		}
		else if(m_sgElevatorModel==_T("TE-MRLS"))
		{
			if(iRatedLoad == 630)
			{
				m_sCarRail = _T("T75/3B");
			}
			else
				if(iRatedLoad >=800 && iRatedLoad <=1000 || iRatedLoad ==1150 && fRatedSpeed <= 1.0)
				{
					m_sCarRail = _T("T89/B");
				}
				if(iRatedLoad > 1150 || iRatedLoad == 1150 && fRatedSpeed >1.0)
				{
					m_sCarRail = _T("T114/B");
				}
		}
		else if(m_sgElevatorModel==_T("TE-F"))
		{
			if(iRatedLoad <= 2000)
			{
				m_sCarRail = _T("T89/B");
			}
			else if(iRatedLoad ==3000)
			{
				m_sCarRail = _T("T114/B");
			}
		}

		if(m_sgElevatorModel==_T("TE-F")||(iRatedLoad<=1000 && fRatedSpeed<=1.0))
		{
			m_sCWRail = _T("TK5A");
		}
		else if(iRatedLoad>1000 || fRatedSpeed>=1.5)
		{
			m_sCWRail = _T("T75/3B");
		}
	}

	if(m_sgElevatorModel == "TE-F")
		m_sBuffer = "ZDQ-A";
	else if(iRatedLoad <= 1150 && fRatedSpeed <=1.00)
		m_sBuffer = "T4";
	else if(iRatedLoad >1150 && fRatedSpeed <=1.00)
		m_sBuffer = "T5";
	else if((m_sgElevatorModel == "TE-ES" || m_sgElevatorModel == "TE-E")&&(iRatedLoad <= 1350 && fRatedSpeed == 1.75))
	{
		m_sBuffer = "HY2/206";
	}
	else if(fRatedSpeed <=2.0 && fRatedSpeed >=1.75)
	{
       m_sBuffer = "YH4/270";
	}
	else if(fRatedSpeed >=2.5)
	{
		m_sBuffer = "YH2/420";
	}

	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

void CItemPartsPage::OnCbnSelchangeComboSafety()
{
	// TODO: 在此添加控件通知处理程序代码
}
