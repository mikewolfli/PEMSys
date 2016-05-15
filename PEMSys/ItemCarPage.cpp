// ItemCarPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemCarPage.h"
#include ".\itemcarpage.h"


// CItemCarPage 对话框
extern CString m_sgElevatorModel;
extern CString m_sgRatedLoad;
IMPLEMENT_DYNAMIC(CItemCarPage, CPropertyPage)
CItemCarPage::CItemCarPage()
	: CPropertyPage(CItemCarPage::IDD)
	, m_iCD(0)
	, m_iCW(0)
	, m_iCH(2350)
	, m_sOpenType(_T(""))
	, m_sOffsetDir(_T(""))
	, m_iOffset(0)
	, m_iDW(0)
	, m_iDH(2100)
	, m_sHostControlPanel(_T(""))
	, m_bCheck(FALSE)
{
}

CItemCarPage::~CItemCarPage()
{
}

void CItemCarPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CAR_CD, m_iCD);
	DDX_Text(pDX, IDC_EDIT_CAR_CW, m_iCW);
	DDX_Text(pDX, IDC_EDIT_CAR_CH, m_iCH);
	DDX_CBString(pDX, IDC_COMBO_CAR_OPENTYPE, m_sOpenType);
	DDX_CBString(pDX, IDC_COMBO_CAR_OFFSETDIR, m_sOffsetDir);
	DDX_Text(pDX, IDC_EDIT_CAR_OFFSET, m_iOffset);
	DDX_Text(pDX, IDC_EDIT_CAR_DW, m_iDW);
	DDX_Text(pDX, IDC_EDIT_CAR_DH, m_iDH);
	DDX_CBString(pDX, IDC_COMBO_CAR_HOSTCONROLPANEL, m_sHostControlPanel);
}


BEGIN_MESSAGE_MAP(CItemCarPage, CPropertyPage)
END_MESSAGE_MAP()


// CItemCarPage 消息处理程序

BOOL CItemCarPage::PreTranslateMessage(MSG* pMsg)
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

BOOL CItemCarPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
    ClearEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CItemCarPage::ClearEdit(void)
{
	UpdateData(TRUE);

	m_iCD = 0;
	m_iCW =0 ;
	m_iCH = 2350;
	m_sOpenType.Empty();
	m_sOffsetDir.Empty();
	m_iOffset = 0;
	m_iDW = 0;
	m_iDH = 2100;
	m_sHostControlPanel.Empty();

	UpdateData(FALSE);
}

void CItemCarPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

BOOL CItemCarPage::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
    UpdateData(TRUE);
	
    if(!m_sgElevatorModel.IsEmpty()&&!m_sgRatedLoad.IsEmpty()&&!m_bCheck)
	{
		int iRatedLoad = atoi(m_sgRatedLoad);
       if(m_sgElevatorModel == "TE-E"||m_sgElevatorModel=="TE-ES")
	   {
          if(iRatedLoad == 630)
		  {
			  m_iCW = 1400;
			  m_iCD = 1100;
		  }
		  if(iRatedLoad == 800)
		  {
			  m_iCW = 1350;
			  m_iCD = 1400;
		  }
		  if(iRatedLoad == 1000)
		  {
			  m_iCW = 1600;
			  m_iCD = 1400;
		  }
		  if(iRatedLoad == 1150)
		  {
			  m_iCW = 1800;
			  m_iCD = 1400;
		  }
		  if(iRatedLoad == 1250)
		  {
			  m_iCW = 1950;
			  m_iCD = 1400;
		  }
		  if(iRatedLoad == 1350)
		  {
			  m_iCW = 1950;
			  m_iCD = 1500;
		  }
		  if(iRatedLoad == 1600)
		  {
			  m_iCW = 1400;
			  m_iCD = 2400;
		  }

	   }

	   else  if(m_sgElevatorModel == "TE-GL"||m_sgElevatorModel=="TE-GLS")
	   {
		   if(iRatedLoad == 630)
		   {
			   m_iCW = 1400;
			   m_iCD = 1100;
		   }
		   if(iRatedLoad == 800)
		   {
			   m_iCW = 1350;
			   m_iCD = 1400;
		   }
		   if(iRatedLoad == 1000)
		   {
			   m_iCW = 1600;
			   m_iCD = 1400;
		   }
		   if(iRatedLoad == 1150)
		   {
			   m_iCW = 1800;
			   m_iCD = 1400;
		   }
	   }
	   else  if(m_sgElevatorModel == "TE-MRL")
	  {
		  if(iRatedLoad == 630)
		  {
			  m_iCW = 1100;
			  m_iCD = 1330;
		  }   
		  if(iRatedLoad == 800)
		  {
			  m_iCW = 1200;
			  m_iCD = 1430;
		  }
		  if(iRatedLoad == 1000)
		  {
			  m_iCW = 1450;
			  m_iCD = 1530;
		  }

	  }
	  else if(m_sgElevatorModel == "TE-MRLS")
	  {
		  if(iRatedLoad == 630)
		  {
			  m_iCW = 1050;
			  m_iCD = 1330;
		  }   
		  if(iRatedLoad == 800)
		  {
			  m_iCW = 1170;
			  m_iCD = 1430;
		  }
		  if(iRatedLoad == 1000)
		  {
			  m_iCW = 1400;
			  m_iCD = 1530;
		  }
	  }
	  else if(m_sgElevatorModel == "TE-GLM")
	  {
		  if(iRatedLoad == 800)
		  {
			  m_iCW = 1350;
			  m_iCD = 1400;
		  }
		  if(iRatedLoad == 1000)
		  {
			  m_iCW = 1600;
			  m_iCD = 1400;
		  }
	  }
	  else if(m_sgElevatorModel == "TE-F")
	  {
		  if(iRatedLoad == 1000)
		  {
			  m_iCW = 1500;
			  m_iCD = 1600;
		  }
		  if(iRatedLoad == 2000)
		  {
			  m_iCW = 2000;
			  m_iCD = 2100;
		  }
		  if(iRatedLoad == 3000)
		  {
			  m_iCW = 2000;
			  m_iCD = 2900;
		  }
	  }

	  if(iRatedLoad == 630 ||iRatedLoad == 800 )
		  m_iDW = 800;
	  else if(iRatedLoad == 1000)
		  m_iDW = 900;
	  else if(iRatedLoad == 1150 || iRatedLoad == 1250 || iRatedLoad == 1350 || iRatedLoad == 1600)
	      m_iDW = 1100;
	}
        
	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}
