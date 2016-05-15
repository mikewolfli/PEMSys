// ItemBasicDataPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemBasicDataPage.h"
#include ".\itembasicdatapage.h"


// CItemBasicDataPage 对话框
extern CString m_sgElevatorModel;
extern CString m_sgRatedLoad;
extern CString m_sgRatedSpeed;
IMPLEMENT_DYNAMIC(CItemBasicDataPage, CPropertyPage)
CItemBasicDataPage::CItemBasicDataPage()
	: CPropertyPage(CItemBasicDataPage::IDD)
	, m_sElevatorType(_T(""))
	, m_sElevatorModel(_T(""))
	, m_sRatedLoad(_T(""))
	, m_sRatedSpeed(_T(""))
	, m_sControlMode(_T(""))
	, m_sDragMode(_T(""))
	, m_sControlModeRemark(_T(""))
	, m_iFloor(0)
	, m_iStop(0)
	, m_iDoor(0)
	, m_sStopName(_T(""))
	, m_bThrough(FALSE)
{
}

CItemBasicDataPage::~CItemBasicDataPage()
{
}

void CItemBasicDataPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_BASICDATA_ELEVATORTYPE, m_sElevatorType);
	DDX_CBString(pDX, IDC_COMBO_BASICDATA_ELEVATORMODEL, m_sElevatorModel);
	DDX_CBString(pDX, IDC_COMBO_BASICDATA_RATEDLOAD, m_sRatedLoad);
	DDX_CBString(pDX, IDC_COMBO_BASICDATA_RATEDSPEED, m_sRatedSpeed);
	DDX_CBString(pDX, IDC_COMBO_BASICDATA_CONTROLMODE, m_sControlMode);
	DDX_CBString(pDX, IDC_COMBO_BASICDATA_DRAGMODE, m_sDragMode);
	DDX_Text(pDX, IDC_EDIT_BASICDATA_CONTROLMODEREMARK, m_sControlModeRemark);
	DDX_Text(pDX, IDC_EDIT_BASICDATA_FLOOR, m_iFloor);
	DDX_Text(pDX, IDC_EDIT_BASICDATA_STATION, m_iStop);
	DDX_Text(pDX, IDC_EDIT_BASICDATA_DOOR, m_iDoor);
	DDX_Text(pDX, IDC_EDIT_BASICDATA_STOPNAME, m_sStopName);
	DDX_Check(pDX, IDC_CHECK_BASICDATA_THROUGH, m_bThrough);
	DDX_Control(pDX, IDC_COMBO_BASICDATA_ELEVATORMODEL, m_cElevatorModel);
	DDX_Control(pDX, IDC_COMBO_BASICDATA_RATEDLOAD, m_cRatedLoad);
	DDX_Control(pDX, IDC_COMBO_BASICDATA_RATEDSPEED, m_cRatedSpeed);
}


BEGIN_MESSAGE_MAP(CItemBasicDataPage, CPropertyPage)
	ON_CBN_SELENDOK(IDC_COMBO_BASICDATA_ELEVATORMODEL, OnCbnSelendokComboBasicdataElevatormodel)
	ON_CBN_SELENDOK(IDC_COMBO_BASICDATA_RATEDLOAD, OnCbnSelendokComboBasicdataRatedload)
	ON_CBN_SELENDOK(IDC_COMBO_BASICDATA_RATEDSPEED, OnCbnSelendokComboBasicdataRatedspeed)
END_MESSAGE_MAP()


// CItemBasicDataPage 消息处理程序

void CItemBasicDataPage::ClearEdit(void)
{
	UpdateData(TRUE);
    m_sElevatorType.Empty();
	m_sElevatorModel.Empty();
	m_sRatedLoad.Empty();
	m_sRatedSpeed.Empty();
	m_sControlMode.Empty();
	m_sDragMode.Empty();
	m_sControlModeRemark.Empty();
	m_iFloor = 0;
	m_iStop = 0;
	m_iDoor = 0;
    m_sStopName.Empty();
	m_bThrough = FALSE;

	UpdateData(FALSE);
}

BOOL CItemBasicDataPage::PreTranslateMessage(MSG* pMsg)
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

BOOL CItemBasicDataPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
    ClearEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CItemBasicDataPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

void CItemBasicDataPage::OnCbnSelendokComboBasicdataElevatormodel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iIndex = m_cElevatorModel.GetCurSel();
	if(iIndex!=LB_ERR)
	{
		m_cElevatorModel.GetLBText(iIndex,m_sElevatorModel);
		m_sgElevatorModel = m_sElevatorModel;
	}
	else
	{
		m_sElevatorModel.Empty();
		m_sgElevatorModel.Empty();
	}
	UpdateData(FALSE);
}

void CItemBasicDataPage::OnCbnSelendokComboBasicdataRatedload()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iIndex = m_cRatedLoad.GetCurSel();
	if(iIndex!=LB_ERR)
	{
		m_cRatedLoad.GetLBText(iIndex,m_sRatedLoad);
		m_sgRatedLoad = m_sRatedLoad;
	}
	else
	{
		m_sRatedLoad.Empty();
		m_sgRatedLoad.Empty();
	}
	UpdateData(FALSE);
}

void CItemBasicDataPage::OnCbnSelendokComboBasicdataRatedspeed()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iIndex = m_cRatedSpeed.GetCurSel();
	if(iIndex!=LB_ERR)
	{
		m_cRatedSpeed.GetLBText(iIndex,m_sRatedSpeed);
		m_sgRatedSpeed = m_sRatedSpeed;
	}
	else
	{
		m_sRatedSpeed.Empty();
		m_sgRatedSpeed.Empty();
	}
	UpdateData(FALSE);
}
