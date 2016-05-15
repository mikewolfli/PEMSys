// ItemElectricPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemElectricPage.h"
#include ".\itemelectricpage.h"
#include "ItemFunctionDlg.h"

// CItemElectricPage �Ի���

extern CString m_sgElevatorModel;

IMPLEMENT_DYNAMIC(CItemElectricPage, CPropertyPage)
CItemElectricPage::CItemElectricPage()
	: CPropertyPage(CItemElectricPage::IDD)
	, m_sController(_T(""))
	, m_bDisaPanel(FALSE)
	, m_bVideoCable(FALSE)
	, m_sCallBoardType(_T(""))
	, m_sScreenMagic(_T(""))
	, m_sPushButton(_T(""))
	, m_sCallboardtypeRemark(_T(""))
	, m_sScreenMagicRemark(_T(""))
	, m_sInvertorType(_T(""))
	, m_sInvertorPower(_T(""))
	, m_sOrderID(_T(""))
{

}

CItemElectricPage::~CItemElectricPage()
{
}

void CItemElectricPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_ELECTRIC_CONTROLLER, m_sController);
	DDX_Check(pDX, IDC_CHECK_ELECTRIC_DISAPANEL, m_bDisaPanel);
	DDX_Check(pDX, IDC_CHECK_ELECTRIC_VIDEOCABLE, m_bVideoCable);
	DDX_CBString(pDX, IDC_COMBO_ELECTRIC_CALLBOARDTYPE, m_sCallBoardType);
	DDX_CBString(pDX, IDC_COMBO_ELECTRIC_SCREENMAGIC, m_sScreenMagic);
	DDX_CBString(pDX, IDC_COMBO_ELECTRIC_PUSHBUTTON, m_sPushButton);
	DDX_Text(pDX, IDC_EDIT_ELECTRIC_CALLBOARDTYPEREMARK, m_sCallboardtypeRemark);
	DDX_Text(pDX, IDC_EDIT_ELECTRIC_SCREENMAGICREMARK, m_sScreenMagicRemark);
	DDX_Control(pDX, IDC_COMBO_ELECTRIC_CALLBOARDTYPE, m_cCallBoardType);
	DDX_CBString(pDX, IDC_COMBO_ELECTRIC_INVERTORTYPE, m_sInvertorType);
	DDX_CBString(pDX, IDC_COMBO_ELECTRIC_INVERTORPOWER, m_sInvertorPower);
}


BEGIN_MESSAGE_MAP(CItemElectricPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_ELECTRIC_FUNCTION, OnBnClickedButtonElectricFunction)
	ON_WM_CLOSE()
	ON_CBN_SELENDOK(IDC_COMBO_ELECTRIC_SCREENMAGIC, OnCbnSelendokComboElectricScreenmagic)
	ON_CBN_SELENDOK(IDC_COMBO_ELECTRIC_CALLBOARDTYPE, OnCbnSelendokComboElectricCallboardtype)
 	ON_CBN_SELENDOK(IDC_COMBO_ELECTRIC_INVERTORTYPE, OnCbnSelendokComboElectricInvertorType)
 	ON_CBN_SELENDOK(IDC_COMBO_ELECTRIC_INVERTORPOWER, OnCbnSelendokComboElectricInvertorPower)
	ON_CBN_EDITCHANGE(IDC_COMBO_ELECTRIC_CALLBOARDTYPE, OnCbnEditchangeComboElectricCallboardtype)
	ON_CBN_EDITCHANGE(IDC_COMBO_ELECTRIC_SCREENMAGIC, OnCbnEditchangeComboElectricScreenmagic)
 	ON_CBN_EDITCHANGE(IDC_COMBO_ELECTRIC_INVERTORTYPE, OnCbnEditchangeComboElectricInvertorType)
 	ON_CBN_EDITCHANGE(IDC_COMBO_ELECTRIC_INVERTORPOWER, OnCbnEditchangeComboElectricInvertorPower)
END_MESSAGE_MAP()


// CItemElectricPage ��Ϣ�������
void CItemElectricPage::OnBnClickedButtonElectricFunction()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;

	UpdateData(TRUE);

	if(m_sOrderID.IsEmpty())
	{
		AfxMessageBox("����ѡ�񶩵���!",MB_ICONEXCLAMATION);
		return;
	}
	if(m_sgElevatorModel.IsEmpty())
	{
		AfxMessageBox("����ѡ������ͺ�!",MB_ICONEXCLAMATION);
		return;
	}

	strSQL = "select * from Configuration where OrderID = '"+m_sOrderID+"'";
	theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
	int iCount = m_pTempSet->GetRecordCount();
	if(iCount == 0)
	{
		AfxMessageBox("�˶����ĵ�����Ϣ��δ���,\n\t �������!", MB_ICONEXCLAMATION);
		m_pTempSet->Close();
		return;
	}
	m_pTempSet->Close();

	CItemFunctionDlg m_dlg;

	//	m_pDlg->m_pParent = this;
	m_dlg.m_sOrderID = m_sOrderID;
	m_dlg.m_sController = m_sController;

	m_dlg.DoModal();
	UpdateData(FALSE);
}

BOOL CItemElectricPage::PreTranslateMessage(MSG* pMsg)
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

void CItemElectricPage::ClearEdit(void)
{
	UpdateData(TRUE);
	m_sController.Empty();
	m_bDisaPanel = FALSE;
	m_bVideoCable = FALSE;
	m_sCallBoardType.Empty();
	m_sScreenMagic.Empty();
	m_sPushButton.Empty();
	m_sCallboardtypeRemark.Empty();
	m_sScreenMagicRemark.Empty();
	m_sInvertorType.Empty();
	m_sInvertorPower.Empty();

	UpdateData(FALSE);
}

BOOL CItemElectricPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
    ClearEdit();

	try
	{
		m_pTempSet.CreateInstance(__uuidof(Recordset)); // ����Recordset����ʵ��
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("ADO Error: %s",(char*)e.Description());
		AfxMessageBox(err);
		return FALSE;
	}
	catch(...)
	{
		AfxMessageBox("Unknown Error...");
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CItemElectricPage::UpdateDataPage(BOOL bCheck)
{
	UpdateData(bCheck);
}

void CItemElectricPage::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();
	CPropertyPage::OnClose();
}

void CItemElectricPage::OnCbnSelendokComboElectricScreenmagic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_ELECTRIC_SCREENMAGIC))->GetCurSel();
	if(iIndex!=LB_ERR)
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_ELECTRIC_SCREENMAGIC))->GetLBText(iIndex,m_sScreenMagic);
		if(m_sScreenMagic == _T("LSE"))
			m_sScreenMagicRemark = _T("54��DC24V");
		else if(m_sScreenMagic == _T("Microscan D100SL"))
			m_sScreenMagicRemark = _T("100��DC24V");
		else if(m_sScreenMagic == _T("MEMCO 618 NPN N/C"))
			m_sScreenMagicRemark = _T("81��DC24V");
		else if(m_sScreenMagic == _T("SFT-EB"))
			m_sScreenMagicRemark = _T("74��AV220V");
		else m_sScreenMagicRemark.Empty();
	}
	else return;

	UpdateData(FALSE);
}

void CItemElectricPage::OnCbnSelendokComboElectricCallboardtype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iIndex = m_cCallBoardType.GetCurSel();
	if(iIndex!=LB_ERR)
	{
		m_cCallBoardType.GetLBText(iIndex,m_sCallBoardType);
		if(m_sCallBoardType == _T("TGX301"))
			m_sCallboardtypeRemark = _T("�ٻ���ť����ʾһ��(��̨)");
		else if(m_sCallBoardType == _T("TGX302"))
			m_sCallboardtypeRemark = _T("�ٻ���ť����ʾһ��(��̨����)");
		else if(m_sCallBoardType == _T("TGX303"))
			m_sCallboardtypeRemark = _T("�ٻ���ť����ʾһ��(��̨IC����");
		else if(m_sCallBoardType == _T("TG300S+TGZ301"))
			m_sCallboardtypeRemark = _T("�ٻ���ť����ʾ�ֿ�(����)");
		else m_sCallboardtypeRemark.Empty();
	}
	else return;
	UpdateData(FALSE);
}

void CItemElectricPage::OnCbnSelendokComboElectricInvertorType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

void CItemElectricPage::OnCbnSelendokComboElectricInvertorPower()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}

void CItemElectricPage::OnCbnEditchangeComboElectricCallboardtype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	GetDlgItemText(IDC_COMBO_ELECTRIC_CALLBOARDTYPE,m_sCallBoardType);
	if(m_sCallBoardType == _T("TGX301"))
		m_sCallboardtypeRemark = _T("�ٻ���ť����ʾһ��(��̨)");
	else if(m_sCallBoardType == _T("TGX302"))
		m_sCallboardtypeRemark = _T("�ٻ���ť����ʾһ��(��̨����)");
	else if(m_sCallBoardType == _T("TGX303"))
		m_sCallboardtypeRemark = _T("�ٻ���ť����ʾһ��(��̨IC����");
	else if(m_sCallBoardType == _T("TG300S+TGZ301"))
		m_sCallboardtypeRemark = _T("�ٻ���ť����ʾ�ֿ�(����)");
	else  m_sCallboardtypeRemark.Empty();

	UpdateData(FALSE);
}

void CItemElectricPage::OnCbnEditchangeComboElectricScreenmagic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	GetDlgItemText(IDC_COMBO_ELECTRIC_SCREENMAGIC, m_sScreenMagic);
	if(m_sScreenMagic == _T("LSE"))
		m_sScreenMagicRemark = _T("54��DC24V");
	else if(m_sScreenMagic == _T("Microscan D100SL"))
		m_sScreenMagicRemark = _T("100��DC24V");
	else if(m_sScreenMagic == _T("MEMCO 618 NPN N/C"))
		m_sScreenMagicRemark = _T("81��DC24V");
	else m_sScreenMagicRemark.Empty();

	UpdateData(FALSE);
}
void CItemElectricPage::OnCbnEditchangeComboElectricInvertorType()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	GetDlgItemText(IDC_COMBO_ELECTRIC_INVERTORTYPE,m_sInvertorType);

	UpdateData(FALSE);
}
void CItemElectricPage::OnCbnEditchangeComboElectricInvertorPower()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	GetDlgItemText(IDC_COMBO_ELECTRIC_INVERTORPOWER,m_sInvertorPower);

	UpdateData(FALSE);
}