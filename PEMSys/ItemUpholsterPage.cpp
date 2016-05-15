// ItemUpholsterPage.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemUpholsterPage.h"
#include ".\itemupholsterpage.h"


// ItemUpholsterPage 对话框

IMPLEMENT_DYNAMIC(CItemUpholsterPage, CPropertyPage)
CItemUpholsterPage::CItemUpholsterPage()
	: CPropertyPage(CItemUpholsterPage::IDD)
	, m_sCeiling(_T(""))
	, m_sFrontWall(_T(""))
	, m_sSideWall(_T(""))
	, m_sRearWall(_T(""))
	, m_bHandRail(FALSE)
	, m_bGlassPosition(FALSE)
	, m_sSideHandRail(_T(""))
	, m_sRearHandRail(_T(""))
	, m_sGlassType(_T(""))
	, m_sGlassPosition(_T(""))
	, m_sDoor(_T(""))
	, m_sFloor(_T("PVC(Grey)"))
	, m_sFloorDoor1(_T(""))
	, m_sFloorDoor2(_T(""))
	, m_iFloorDoor1(0)
	, m_iFloorDoor2(0)
{
}

CItemUpholsterPage::~CItemUpholsterPage()
{
}

void CItemUpholsterPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_CEILING, m_sCeiling);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_FRONTWALL, m_sFrontWall);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_SIDEWALL, m_sSideWall);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_REARWALL, m_sRearWall);
	DDX_Check(pDX, IDC_CHECK_UPHOLSTER_HANDRAIL, m_bHandRail);
	DDX_Check(pDX, IDC_CHECK_UPHOLSTER_GLASSPOSITION, m_bGlassPosition);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_SIDEHANDRAIL, m_sSideHandRail);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_REARHANDRAIL, m_sRearHandRail);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_GLASSTYPE, m_sGlassType);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_GLASSPOSITION, m_sGlassPosition);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_DOOR, m_sDoor);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_FLOOR, m_sFloor);
	DDX_Control(pDX, IDC_COMBO_UPHOLSTER_SIDEHANDRAIL, m_cSideHandrail);
	DDX_Control(pDX, IDC_COMBO_UPHOLSTER_REARHANDRAIL, m_cRearHandrail);
	DDX_Control(pDX, IDC_COMBO_UPHOLSTER_GLASSTYPE, m_cGlassType);
	DDX_Control(pDX, IDC_COMBO_UPHOLSTER_GLASSPOSITION, m_cGlassPos);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_FLOORDOOR1, m_sFloorDoor1);
	DDX_CBString(pDX, IDC_COMBO_UPHOLSTER_FLOORDOOR2, m_sFloorDoor2);
	DDX_Text(pDX, IDC_EDIT_FLOORDOOR1, m_iFloorDoor1);
	DDX_Text(pDX, IDC_EDIT_FLOORDOOR2, m_iFloorDoor2);
}


BEGIN_MESSAGE_MAP(CItemUpholsterPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_UPHOLSTER_HANDRAIL, OnBnClickedCheckUpholsterHandrail)
	ON_BN_CLICKED(IDC_CHECK_UPHOLSTER_GLASSPOSITION, OnBnClickedCheckUpholsterGlassposition)
END_MESSAGE_MAP()


// ItemUpholsterPage 消息处理程序

void CItemUpholsterPage::ClearEdit(void)
{
	UpdateData(TRUE);

	m_sCeiling.Empty();
	m_sFrontWall.Empty();
	m_sSideWall.Empty();
	m_sRearWall.Empty();
	m_bHandRail = FALSE;
	m_bGlassPosition = FALSE;
	m_sSideHandRail.Empty();
	m_sRearHandRail.Empty();
	m_sGlassType.Empty();
	m_sGlassPosition.Empty();
	m_sDoor.Empty();
	m_sFloor="PVC(Grey)";

	UpdateData(FALSE);
}

BOOL CItemUpholsterPage::PreTranslateMessage(MSG* pMsg)
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

BOOL CItemUpholsterPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
    ClearEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CItemUpholsterPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

void CItemUpholsterPage::OnBnClickedCheckUpholsterHandrail()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_UPHOLSTER_HANDRAIL))->GetCheck())
	{
		m_bHandRail = TRUE;
        m_cSideHandrail.EnableWindow(TRUE);
		m_cRearHandrail.EnableWindow(TRUE);

	}
	else
	{
		m_bHandRail = FALSE;
		m_cSideHandrail.EnableWindow(FALSE);
		m_cRearHandrail.EnableWindow(FALSE);

	}

	UpdateData(FALSE);
}

void CItemUpholsterPage::OnBnClickedCheckUpholsterGlassposition()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_UPHOLSTER_GLASSPOSITION))->GetCheck())
	{
		m_bGlassPosition = TRUE;
	    m_cGlassType.EnableWindow(TRUE);
		m_cGlassPos.EnableWindow(TRUE);

	}
	else
	{
		m_bGlassPosition = FALSE;
        m_cGlassPos.EnableWindow(FALSE);
		m_cGlassType.EnableWindow(FALSE);

	}

	UpdateData(FALSE);
}
