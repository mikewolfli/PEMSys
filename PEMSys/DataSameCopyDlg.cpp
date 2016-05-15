// DataSameCopyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "DataSameCopyDlg.h"
#include ".\datasamecopydlg.h"


// CDataSameCopyDlg 对话框
extern CString g_strAuthor;

IMPLEMENT_DYNAMIC(CDataSameCopyDlg, CDialog)
CDataSameCopyDlg::CDataSameCopyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataSameCopyDlg::IDD, pParent)
	, m_sResource(_T(""))
	, m_iCheck(0)
	, m_bSaveCopy(FALSE)
	, m_dCurrent(COleDateTime::GetCurrentTime())
	, m_bSave(FALSE)
	, m_sOrderID(_T(""))
	, m_sProjectName(_T(""))
	, m_sProjectNameEn(_T(""))
	, m_sID(_T(""))
	, m_dConfigureFinish(COleDateTime::GetCurrentTime())
	, m_dPurchaseReturn(COleDateTime::GetCurrentTime())
	, m_iPage(0)
{
}

CDataSameCopyDlg::~CDataSameCopyDlg()
{
}

void CDataSameCopyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SOURCE, m_sResource);
	DDX_Control(pDX, IDC_COMBO1, m_cTarget);
	DDX_Control(pDX, IDC_LIST_TARGET, m_cTargetList);
	DDX_Control(pDX, IDC_LIST_TARGET1, m_cTargetResouce);
	DDX_Text(pDX, IDC_EDIT_SAMECOPY_PROJECTNAME, m_sProjectName);
	DDX_Text(pDX, IDC_EDIT_SAMECOPY_PROJECTNAMEEN, m_sProjectNameEn);
	DDX_CBString(pDX, IDC_COMBO1, m_sID);
}


BEGIN_MESSAGE_MAP(CDataSameCopyDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnBnClickedButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_REMOVEALL, OnBnClickedButtonRemoveall)
	ON_BN_CLICKED(IDC_BUTTON_ADDALL, OnBnClickedButtonAddall)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnBnClickedButtonFind)
	ON_CBN_SELENDOK(IDC_COMBO1, OnCbnSelendokCombo1)
END_MESSAGE_MAP()


// CDataSameCopyDlg 消息处理程序

BOOL CDataSameCopyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// TODO:  在此添加额外的初始化

	UpdateData(TRUE);
	CString strTitle;
	switch(m_iCheck) {
	case 1:	
		strTitle = "商务";
		this->SetWindowText(strTitle);
		break;
	case 2:
		strTitle = "配置";
		this->SetWindowText(strTitle);
		break;
	default:
		break;
	}

	//初始化CListCtrl控件
	// Set Color
	m_cTargetResouce.SetBkColor(RGB(177, 151, 240));
	m_cTargetResouce.SetTextColor(RGB(0,0,0));
	m_cTargetResouce.SetTextBkColor(RGB(177, 151, 240));

	// Set EX-Style
	m_cTargetResouce.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);


	// Create Header
	m_cTargetResouce.InsertColumn(0,_T("订单号"),LVCFMT_LEFT,100);
	m_cTargetResouce.InsertColumn(1,_T("梯号"), LVCFMT_LEFT,50);
	m_cTargetResouce.InsertColumn(2,_T("说明"), LVCFMT_LEFT,100);

	try
	{
		m_pTempSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例

		if(!m_sID.IsEmpty())
		{
			strSQL = "select  *  from OrderOfProject where ID = '"+m_sID+"' and Status = FALSE";
			theApp.ADOExecute(m_pTempSet, theApp.m_pConnect,strSQL);
            LoadTargetResource(m_pTempSet);
			m_pTempSet->Close();
		}

		strSQL = "select DISTINCT top 10 ID from PBInformation Order by ID DESC";
		theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
		int iCount = m_pTempSet->GetRecordCount();
		if(iCount !=0)
		{
			m_pTempSet->MoveFirst();
			for(int i= 0 ;i<iCount;i++)
			{
				Holder = m_pTempSet->GetCollect("ID");
				CString str= (char*)(_bstr_t)Holder;
				m_cTarget.AddString(str);
				m_pTempSet->MoveNext();
			}
		}
		m_pTempSet->Close();

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
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDataSameCopyDlg::LoadTargetResource(_RecordsetPtr& pSet)
{
	//获得合同订单号
	m_cTargetResouce.DeleteAllItems();
	int iCount = pSet->GetRecordCount();
	CString str;
	if(iCount!=0)
		pSet->MoveFirst();
	else
		m_cTargetResouce.DeleteAllItems();
	for(int i = 0; i<iCount ;i++)
	{
		Holder = pSet->GetCollect("OrderID");
		str = (char*)(_bstr_t)Holder;
		m_cTargetResouce.InsertItem(i, str);
		//获得电梯梯号
		Holder = pSet->GetCollect("ElevatorID");
		str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
		m_cTargetResouce.SetItemText(i, 1, str);
		// 获得说明
		Holder = pSet->GetCollect("Remark");
		str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
		m_cTargetResouce.SetItemText(i, 2, str);
		pSet->MoveNext();
	}

}

void CDataSameCopyDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();
	m_pTempSet.Release();
	CDialog::OnClose();
}

void CDataSameCopyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//	OnOK();
	UpdateData(TRUE);

	if(m_sResource.IsEmpty())
	{
		AfxMessageBox(_T("请填入源订单号!"),MB_ICONEXCLAMATION);
		return;
	}

	m_sResource.Remove(' ');

	int iNum=m_sResource.GetLength();
	if(iNum!=8)
	{
		AfxMessageBox(_T("订单号格式不正确,\n请输入8位数字!"),MB_ICONEXCLAMATION);
		return;
	}
	CString str1  = m_sResource.Left(2);
	CString str2 = m_sResource.Mid(2,iNum-6);
	m_sResource = str1+" "+str2+" "+m_sResource.Right(4);

	int iIndex = m_cTargetList.GetCount();
	if(iIndex==0)
	{
		AfxMessageBox(_T("请添加目标订单号!"),MB_ICONEXCLAMATION);
		return;
	}
	try{

		switch(m_iCheck) 
		{
		case 1:
			strSQL = "select * from Delivery where OrderID = '"+m_sResource+"'";	
			break;
		case 2:
			strSQL = " select * from Configuration where OrderID = '"+m_sResource+"'";
			break;
		default:
			return;
			break;
		}

		theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
		int iCount = m_pTempSet->GetRecordCount();
		if(0!=iCount)
		{
           m_pTempSet->MoveFirst();
		   ReadRecord(m_pTempSet);
		}
		else
		{
			AfxMessageBox(_T("源订单号记录不存在请先添加!"),MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return;
		}

		m_pTempSet->Close();

        for(int i = 0;i<iIndex; i++)
		{
			m_cTargetList.GetText(i, m_sOrderID);
            if(m_sOrderID == m_sResource)
				continue;
			switch(m_iCheck) {
		case 1:
				strSQL = "select * from Delivery where OrderID = '"+m_sOrderID+"'";
				break;
		case 2:
                strSQL = "select * from Configuration where OrderID = '"+m_sOrderID+"'";
				break;
		default:
				return;
			}		
			theApp.ADOExecute(m_pTempSet, theApp.m_pConnect,strSQL);
			iCount= m_pTempSet->GetRecordCount();
			if(iCount==0)
			{
				m_bSave = TRUE;
				m_pTempSet->AddNew();
			}

            UpdateRecord(m_pTempSet);
			m_pTempSet->Update();
			m_pTempSet->Close();
/*
			strSQL = "select * from CDUnion where OrderID = '"+m_sOrderID+"'";
			theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
			iCount = m_pTempSet->GetRecordCount();
            if(iCount == 0)
				m_pTempSet->AddNew();
			m_bSaveCopy = TRUE;
			UpdateRecord(m_pTempSet);
			m_pTempSet->Update();
			m_pTempSet->Close();
			*/
			m_bSave = FALSE;
			m_bSaveCopy = FALSE;
		}
		AfxMessageBox("记录已保存!",MB_OK | MB_ICONINFORMATION);


	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("ADO Error: %s",(char*)e.Description());
		AfxMessageBox(err);
		m_pTempSet->Close();
		return ;
	}
	catch(...)
	{
		AfxMessageBox("Unknown Error...");
		m_pTempSet->Close();
		return ;
	}
	UpdateData(FALSE);
}

void CDataSameCopyDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_sResource.Remove(' ');

	int iNum=m_sResource.GetLength();
	CString str1  = m_sResource.Left(2);
	CString str2 = m_sResource.Mid(2,iNum-6);
	m_sResource = str1+" "+str2+" "+m_sResource.Right(4);

	if(m_cTargetResouce.GetItemCount()==0)
	{
		AfxMessageBox(_T("请填入项目订单号!"),MB_ICONEXCLAMATION);
		return;
	}
	else
	{

		int nit;
		POSITION pos=m_cTargetResouce.GetFirstSelectedItemPosition();
		if(pos==NULL)
		{
			AfxMessageBox(_T("没有选择记录!"),MB_ICONEXCLAMATION);
			return;
		}
		else
		{
			while(pos)
			{
				nit=m_cTargetResouce.GetNextSelectedItem(pos);
				CString sid=m_cTargetResouce.GetItemText(nit,0);
				if(sid== m_sResource)
				{
				}
				else
				if(m_cTargetList.FindString(0,sid)==LB_ERR)
					m_cTargetList.AddString(sid);
			}
		}
	}
	UpdateData(FALSE);
}

void CDataSameCopyDlg::OnBnClickedButtonRemoveall()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_cTargetList.ResetContent();

	UpdateData(FALSE);
}

void CDataSameCopyDlg::OnBnClickedButtonAddall()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_sResource.Remove(' ');

	int iNum=m_sResource.GetLength();
	CString str1  = m_sResource.Left(2);
	CString str2 = m_sResource.Mid(2,iNum-6);
	m_sResource = str1+" "+str2+" "+m_sResource.Right(4);

	int iIndex = m_cTargetResouce.GetItemCount();
	CString str;
	for(int i = 0;i<iIndex;i++)
	{
		str = m_cTargetResouce.GetItemText(i,0);
		if(str == m_sResource)
		{}
		else
		if(m_cTargetList.FindString(0,str)==LB_ERR)
			m_cTargetList.AddString(str);
	}

	UpdateData(FALSE);
}

void CDataSameCopyDlg::OnBnClickedButtonRemove()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int count = m_cTargetList.GetSelCount();
	CArray<int,int> arrayListSel;
	arrayListSel.SetSize(count);     // make room in array
	m_cTargetList.GetSelItems(count, arrayListSel.GetData());    // copy data to array
	for( int i=count-1; i>=0; i--)
	{
		m_cTargetList.DeleteString(arrayListSel[i]);
	}
	UpdateData(FALSE);
}

void CDataSameCopyDlg::ReadRecord(_RecordsetPtr& pSet)
{
	switch(m_iCheck) {
	case 1:
		Holder = pSet->GetCollect("Amount");
		m_dbAmount  = Holder;
        
		Holder = pSet->GetCollect("Currency");
		m_iCurrency= Holder;

		Holder = pSet->GetCollect("MaterialAmount");
		m_dbMaterialAmount = Holder;

		Holder = pSet->GetCollect("FreightInsurance");
		m_dbFreightInsurance = Holder;

		Holder = pSet->GetCollect("Discount");
		m_dbDiscount = Holder;

		Holder = pSet->GetCollect("InternalPrice");
		m_dbInternalPrice  = Holder; 

		Holder = pSet->GetCollect("ActualGetFreightInsurance");
		m_dbAGetFreightInsurance = Holder;

		Holder = pSet->GetCollect("POReleaseDate");
		m_dPORelease = Holder;

		Holder = pSet->GetCollect("POReturnDate");
		m_dPOReturn = Holder;

		Holder = pSet->GetCollect("GADReceived");
		m_dGADReceived  = Holder;

		Holder = pSet->GetCollect("TheLatestAmendment");
		m_dLatestAmend = Holder;

		Holder = pSet->GetCollect("AmendmentRemark");
	    m_sAmendRemark = Holder;

		Holder = pSet->GetCollect("ComfirmationSheetRelease");
		m_dCSRelease = Holder;

		Holder = pSet->GetCollect("ComfirmationSheetReply");
		m_dCSReply  = Holder;
	
		Holder = pSet->GetCollect("ReplyRemark");
		m_sReplyRemark = Holder;

		Holder = pSet->GetCollect("AssessmentCompleteDate");
		m_dACompleteDate = Holder;

		Holder = pSet->GetCollect("ProductionReceivedDate");
		m_dProductionReceivedDate = Holder;

		Holder = pSet->GetCollect("PlantProductionDate");
		m_dPlantProductionDate  = Holder;

		Holder = pSet->GetCollect("PDeliveryDate");
		m_dPDeliveryDate = Holder;

		Holder = pSet->GetCollect("PDeliveryRemark");
	    m_sPDeliveryRemark =  Holder;

		Holder = pSet->GetCollect("PBatchCheck");
		m_bPBatchCheck = (bool)Holder;

		Holder = pSet->GetCollect("PSecDeliveryDate");
		m_dPSecDeliveryDate = Holder;

		Holder = pSet->GetCollect("PSecDeliveryRemark");
		m_sPSecDeliveryRemark = Holder;

		Holder = pSet->GetCollect("PThirdDeliveryDate");
		m_dPThirdDeliveryDate  = Holder;

		Holder = pSet->GetCollect("PThirdDeliveryRemark");
		m_sPThirdDeliveryRemark = Holder;

		Holder = pSet->GetCollect("DeliveryReceivedDate");
		m_dDeliveryReceivedDate = Holder;

		Holder = pSet->GetCollect("ADeliveryDate");
		m_dADeliveryDate = Holder;

		Holder = pSet->GetCollect("ADeliveryRemark");
		m_sADeliveryRemark = Holder;		

		Holder = pSet->GetCollect("ABatchCheck");
		m_bBatchDelivery = Holder;

		Holder = pSet->GetCollect("ASecDeliveryDate");
		m_dASecDeliveryDate = Holder;

		Holder = pSet->GetCollect("ASecDeliveryRemark");
		m_sASecDeliveryRemark = Holder;

		Holder = pSet->GetCollect("AThirdDeliveryDate");
		m_dAThirdDeliveryDate = Holder;

		Holder = pSet->GetCollect("AThirdDeliveryRemark");
		m_sAThirdDeliveryRemark = Holder;

		Holder = pSet->GetCollect("DeliveryDone");
		m_bDeliveryDone = Holder;

		Holder = pSet->GetCollect("DDeliveryRemarks");
		m_sRemarks = Holder;

		Holder = pSet->GetCollect("ConfigureFinishCheck");
		m_bConfigureFinishCheck= Holder;

		Holder = pSet->GetCollect("PurchaseReturnCheck");
		m_bPurchaseReturnCheck= Holder;

		Holder = pSet->GetCollect("ConfigureFinish");
		m_dConfigureFinish = Holder;

		Holder = pSet->GetCollect("PurchaseReturn");
		m_dPurchaseReturn = Holder;

		break;
	case 2:
		Holder = pSet->GetCollect("ElevatorType");
		m_sElevatorType = Holder;

		Holder = pSet->GetCollect("ElevatorModel");
		m_sElevatorModel  = Holder;

		Holder = pSet->GetCollect("RatedLoad");
		m_iRatedLoad = Holder;

		Holder = pSet->GetCollect("RatedSpeed");
		m_fRatedSpeed = Holder;

		Holder = pSet->GetCollect("DragMode");
		m_sDragMode = Holder;

		Holder = pSet->GetCollect("ControlMode");
		m_sControlMode = Holder;

		Holder = pSet->GetCollect("ControlModeRemark");
		m_sControlModeRemark = Holder;

		Holder = pSet->GetCollect("Floor");
		m_iFloor = Holder;

		Holder = pSet->GetCollect("Stop");
		m_iStop = Holder;

		Holder = pSet->GetCollect("Door");
		m_iDoor = Holder;

		Holder = pSet->GetCollect("StopName");
		m_sStopName = Holder;

		Holder = pSet->GetCollect("Through");
		m_bThrough = Holder;

		Holder = pSet->GetCollect("CarRail"); 
		m_sCarRail = Holder;

		Holder = pSet->GetCollect("CWRail");
		m_sCWRail = Holder;

		Holder = pSet->GetCollect("ShaftWidth");
		m_iSW = Holder;

		Holder = pSet->GetCollect("ShaftDepth");
		m_iSD = Holder;


		Holder = pSet->GetCollect("TH");
		m_lTH = Holder;

		Holder = pSet->GetCollect("OH");
		m_lOH = Holder;

		Holder = pSet->GetCollect("PD");
		m_iPD = Holder;

		Holder = pSet->GetCollect("CounterWeight");
		m_sCounterWeight = Holder;

		Holder = pSet->GetCollect("CWGauge");
		m_iCWGauge = Holder;

		Holder = pSet->GetCollect("CounterWeightHeight");
		m_iCounterWeightHeight = Holder;

		Holder = pSet->GetCollect("SGPosition");
		m_sSGPosition =  Holder;

		Holder = pSet ->GetCollect("WideJamb");
		m_bWideJamb = Holder;

		Holder = pSet->GetCollect("WJtype");
		m_sWJType =  Holder;

		Holder = pSet->GetCollect("JambXC");
		m_iJambXC = Holder;

		Holder = pSet->GetCollect("CCW");
		m_iCCW = Holder;

		Holder = pSet->GetCollect("CS1");
		m_iCS1 = Holder;

		Holder = pSet->GetCollect("CS2");
		m_iCS2 = Holder;

		Holder = pSet->GetCollect("CWS");
		m_iCWS = Holder;

		Holder = pSet->GetCollect("HostControlPanel");
		m_sHostControlPanel =  Holder;

		Holder = pSet->GetCollect("CD");
		m_iCD = Holder;

		Holder = pSet->GetCollect("CW");
		m_iCW = Holder;

		Holder = pSet->GetCollect("CH");
		m_iCH = Holder;

		Holder = pSet->GetCollect("Operator");
		m_sDoorSystem = Holder;

		Holder = pSet->GetCollect("OpenType");
		m_sOpenType = Holder;

		Holder = pSet->GetCollect("OffsetDir");
		m_sOffsetDir = Holder;

		Holder = pSet->GetCollect("Offset");
		m_iOffset = Holder;

		Holder = pSet->GetCollect("DW");
		m_iDW = Holder;

		Holder = pSet->GetCollect("DH");
		m_iDH = Holder;

		Holder = pSet->GetCollect("Ceiling");
		m_sCeiling = Holder;

		Holder = pSet->GetCollect("FrontWall");
		m_sFrontWall = Holder;

		Holder = pSet->GetCollect("SideWall");
		m_sSideWall = Holder;

		Holder = pSet->GetCollect("RearWall");
		m_sRearWall = Holder;

		Holder = pSet->GetCollect("SideHandRail");
		m_sSideHandRail = Holder;

		Holder = pSet->GetCollect("RearHandRail");
		m_sRearHandRail = Holder;

		Holder = pSet->GetCollect("HandRailCheck");
		m_bHandRail = Holder;

		Holder = pSet->GetCollect("GlassCheck");
		m_bGlassPosition = Holder;

		Holder = pSet->GetCollect("GlassType");
		m_sGlassType = Holder;

		Holder = pSet->GetCollect("GlassPosition");
		m_sGlassPosition = Holder;

		Holder = pSet->GetCollect("CarDoor");
		m_sDoor = Holder;

		Holder = pSet->GetCollect("CarFloor");
		m_sFloor = Holder;

		Holder = pSet->GetCollect("Controller");
		m_sController = Holder;

		Holder = pSet->GetCollect("DisaPanel");
		m_bDisaPanel = (bool)Holder;

		Holder = pSet->GetCollect("PushButton");
		m_sPushButton = Holder;

		Holder = pSet->GetCollect("VideoCable");
		m_bVideoCable = Holder;

		Holder = pSet->GetCollect("CallBoardType");
		m_sCallBoardType = Holder;


		Holder = pSet->GetCollect("CallBoardTypeRemark");
		m_sCallboardtypeRemark = Holder;

		Holder = pSet->GetCollect("ScreenMagic");
		m_sScreenMagic = Holder;

		Holder = pSet->GetCollect("ScreenMagicRemark");
		m_sScreenMagicRemark = Holder;

		Holder = pSet->GetCollect("InvertorType");
		m_sInvertorType = Holder;

		Holder = pSet->GetCollect("InvertorPower");
		m_sInvertorPower = Holder;

		Holder = pSet->GetCollect("Traction");
		m_sTraction = Holder;

		Holder = pSet->GetCollect("SpeedGovernor");
		m_sSpeedGovernor = Holder;


		Holder = pSet->GetCollect("Encode");
		m_sEncode = Holder;

		Holder = pSet->GetCollect("Safety");
		m_sSafety = Holder;

		Holder = pSet->GetCollect("Buffer");
		m_sBuffer = Holder;

		Holder = pSet->GetCollect("NonstandardCheck");
		m_bNonstandardCheck = Holder;

		Holder = pSet->GetCollect("Nonstandard");
		m_sNonstandardRemark = Holder;

		Holder = pSet->GetCollect("ConfigureRemarks");
		m_sRemark = Holder;


		Holder = pSet->GetCollect("FloorDoor1");
		m_sFloorDoor1 = Holder;

		Holder = pSet->GetCollect("FloorDoorNum1");
		m_iFloorDoor1 = Holder;

		Holder = pSet->GetCollect("FloorDoor2");
		m_sFloorDoor2 = Holder;

		Holder = pSet->GetCollect("FloorDoorNum2");
		m_iFloorDoor2 = Holder;
		break;
	default:
		break;
	}
}

void CDataSameCopyDlg::UpdateRecord(_RecordsetPtr& pSet)
{
	pSet->Fields->GetItem("OrderID")->PutValue(m_sOrderID.AllocSysString());

	switch(m_iCheck) {
	case 1:
		pSet->Fields->GetItem("Currency")->PutValue(m_iCurrency);
		if(m_iPage==-1)
		{
			if(g_strAuthor.Mid(0,1)=="1" || g_tUserType>=4)
			{	
				pSet->Fields->GetItem("Amount")->PutValue(m_dbAmount);
				pSet->Fields->GetItem("MaterialAmount")->PutValue(m_dbMaterialAmount);
				pSet->Fields->GetItem("FreightInsurance")->PutValue(m_dbFreightInsurance);
			}

			if(g_strAuthor.Mid(1,1)=="1" || g_tUserType>=4)
			{
				pSet->Fields->GetItem("Discount")->PutValue(m_dbDiscount);
				pSet->Fields->GetItem("InternalPrice")->PutValue(m_dbInternalPrice);
				pSet->Fields->GetItem("ActualGetFreightInsurance")->PutValue(m_dbAGetFreightInsurance);
				pSet->Fields->GetItem("POReleaseDate")->PutValue(m_dPORelease);
				pSet->Fields->GetItem("POReturnDate")->PutValue(m_dPOReturn);   
			}

			if(g_strAuthor.Mid(2,1)=="1" || g_tUserType>=4)
			{
				pSet->Fields->GetItem("GADReceived")->PutValue(m_dGADReceived);
				pSet->Fields->GetItem("TheLatestAmendment")->PutValue(m_dLatestAmend);
				pSet->Fields->GetItem("AmendmentRemark")->PutValue(m_sAmendRemark);
				pSet->Fields->GetItem("ComfirmationSheetRelease")->PutValue(m_dCSRelease);
				pSet->Fields->GetItem("ComfirmationSheetReply")->PutValue(m_dCSReply);
				pSet->Fields->GetItem("ReplyRemark")->PutValue(m_sReplyRemark);
				pSet->Fields->GetItem("AssessmentCompleteDate")->PutValue(m_dACompleteDate);
			}
            if(g_strAuthor.Mid(3,1)=="1" || g_tUserType>=4)
			{
				pSet->Fields->GetItem("ProductionReceivedDate")->PutValue(m_dProductionReceivedDate);
				pSet->Fields->GetItem("PlantProductionDate")->PutValue(m_dPlantProductionDate);
				pSet->Fields->GetItem("PDeliveryDate")->PutValue(m_dPDeliveryDate);
				pSet->Fields->GetItem("PDeliveryRemark")->PutValue(m_sPDeliveryRemark);
				pSet->Fields->GetItem("PBatchCheck")->PutValue(m_bPBatchCheck);
				pSet->Fields->GetItem("PSecDeliveryDate")->PutValue(m_dPSecDeliveryDate);
				pSet->Fields->GetItem("PSecDeliveryRemark")->PutValue(m_sPSecDeliveryRemark);
				pSet->Fields->GetItem("PThirdDeliveryDate")->PutValue(m_dPThirdDeliveryDate);
				pSet->Fields->GetItem("PThirdDeliveryRemark")->PutValue(m_sPThirdDeliveryRemark);

				pSet->Fields->GetItem("ConfigureFinish")->PutValue(m_dConfigureFinish);
				pSet->Fields->GetItem("PurchaseReturn")->PutValue(m_dPurchaseReturn);
				pSet->Fields->GetItem("ConfigureFinishCheck")->PutValue(m_bConfigureFinishCheck);
				pSet->Fields->GetItem("PurchaseReturnCheck")->PutValue(m_bPurchaseReturnCheck);


			}

			if(g_strAuthor.Mid(4,1)=="1"|| g_tUserType>=4)
			{
				pSet->Fields->GetItem("DeliveryReceivedDate")->PutValue(m_dDeliveryReceivedDate);
				pSet->Fields->GetItem("ADeliveryDate")->PutValue(m_dADeliveryDate);
				pSet->Fields->GetItem("ADeliveryRemark")->PutValue(m_sADeliveryRemark);
				pSet->Fields->GetItem("ABatchCheck")->PutValue(m_bBatchDelivery);
				pSet->Fields->GetItem("ASecDeliveryDate")->PutValue(m_dASecDeliveryDate);
				pSet->Fields->GetItem("ASecDeliveryRemark")->PutValue(m_sASecDeliveryRemark);
				pSet->Fields->GetItem("AThirdDeliveryDate")->PutValue(m_dAThirdDeliveryDate);
				pSet->Fields->GetItem("AThirdDeliveryRemark")->PutValue(m_sAThirdDeliveryRemark);
				pSet->Fields->GetItem("DeliveryDone")->PutValue(m_bDeliveryDone);
			}

			pSet->Fields->GetItem("DDeliveryRemarks")->PutValue(m_sRemarks);

			if(!m_bSaveCopy)
			{
				pSet->Fields->GetItem("DReperson")->PutValue(g_strUserName.AllocSysString());
				pSet->Fields->GetItem("DReDate")->PutValue((_variant_t)m_dCurrent);

				if(m_bSave)
				{
					pSet->Fields->GetItem("DInputPerson")->PutValue(g_strUserName.AllocSysString());
					pSet->Fields->GetItem("DInputDate")->PutValue((_variant_t)m_dCurrent);
				}
			}
		}
		else
		{
			if((g_strAuthor.Mid(0,1)=="1" || g_tUserType>=4 ) && m_iPage == 0)
			{	
				pSet->Fields->GetItem("Amount")->PutValue(m_dbAmount);
				pSet->Fields->GetItem("MaterialAmount")->PutValue(m_dbMaterialAmount);
				pSet->Fields->GetItem("FreightInsurance")->PutValue(m_dbFreightInsurance);
			}

			if((g_strAuthor.Mid(1,1)=="1" || g_tUserType>=4 )&& m_iPage==1)
			{
				pSet->Fields->GetItem("Discount")->PutValue(m_dbDiscount);
				pSet->Fields->GetItem("InternalPrice")->PutValue(m_dbInternalPrice);
				pSet->Fields->GetItem("ActualGetFreightInsurance")->PutValue(m_dbAGetFreightInsurance);
				pSet->Fields->GetItem("POReleaseDate")->PutValue(m_dPORelease);
				pSet->Fields->GetItem("POReturnDate")->PutValue(m_dPOReturn);   
			}

			if((g_strAuthor.Mid(2,1)=="1" || g_tUserType>=4)&& m_iPage==2)
			{
	

					pSet->Fields->GetItem("GADReceived")->PutValue(m_dGADReceived);
					pSet->Fields->GetItem("TheLatestAmendment")->PutValue(m_dLatestAmend);
					pSet->Fields->GetItem("AmendmentRemark")->PutValue(m_sAmendRemark);
					pSet->Fields->GetItem("ComfirmationSheetRelease")->PutValue(m_dCSRelease);
					pSet->Fields->GetItem("ComfirmationSheetReply")->PutValue(m_dCSReply);
					pSet->Fields->GetItem("ReplyRemark")->PutValue(m_sReplyRemark);
					pSet->Fields->GetItem("AssessmentCompleteDate")->PutValue(m_dACompleteDate);
			}
		  if((g_strAuthor.Mid(3,1)=="1" || g_tUserType>=4)&&m_iPage == 3)
			{

					pSet->Fields->GetItem("ProductionReceivedDate")->PutValue(m_dProductionReceivedDate);
					pSet->Fields->GetItem("PlantProductionDate")->PutValue(m_dPlantProductionDate);
					pSet->Fields->GetItem("PDeliveryDate")->PutValue(m_dPDeliveryDate);
					pSet->Fields->GetItem("PDeliveryRemark")->PutValue(m_sPDeliveryRemark);
					pSet->Fields->GetItem("PBatchCheck")->PutValue(m_bPBatchCheck);
					pSet->Fields->GetItem("PSecDeliveryDate")->PutValue(m_dPSecDeliveryDate);
					pSet->Fields->GetItem("PSecDeliveryRemark")->PutValue(m_sPSecDeliveryRemark);
					pSet->Fields->GetItem("PThirdDeliveryDate")->PutValue(m_dPThirdDeliveryDate);
					pSet->Fields->GetItem("PThirdDeliveryRemark")->PutValue(m_sPThirdDeliveryRemark);

                    pSet->Fields->GetItem("ConfigureFinishCHeck")->PutValue(m_bConfigureFinishCheck);
					pSet->Fields->GetItem("PurchaseReturnCheck")->PutValue(m_bPurchaseReturnCheck);
					pSet->Fields->GetItem("ConfigureFinish")->PutValue(m_dConfigureFinish);
					pSet->Fields->GetItem("PurchaseReturn")->PutValue(m_dPurchaseReturn);
			
			}

			if((g_strAuthor.Mid(4,1)=="1"  || g_tUserType>=4) && m_iPage == 4)
			{
				pSet->Fields->GetItem("DeliveryReceivedDate")->PutValue(m_dDeliveryReceivedDate);
				pSet->Fields->GetItem("ADeliveryDate")->PutValue(m_dADeliveryDate);
				pSet->Fields->GetItem("ADeliveryRemark")->PutValue(m_sADeliveryRemark);
				pSet->Fields->GetItem("ABatchCheck")->PutValue(m_bBatchDelivery);
				pSet->Fields->GetItem("ASecDeliveryDate")->PutValue(m_dASecDeliveryDate);
				pSet->Fields->GetItem("ASecDeliveryRemark")->PutValue(m_sASecDeliveryRemark);
				pSet->Fields->GetItem("AThirdDeliveryDate")->PutValue(m_dAThirdDeliveryDate);
				pSet->Fields->GetItem("AThirdDeliveryRemark")->PutValue(m_sAThirdDeliveryRemark);
				pSet->Fields->GetItem("DeliveryDone")->PutValue(m_bDeliveryDone);
			}

			pSet->Fields->GetItem("DDeliveryRemarks")->PutValue(m_sRemarks);

			if(!m_bSaveCopy)
			{
				pSet->Fields->GetItem("DReperson")->PutValue(g_strUserName.AllocSysString());
				pSet->Fields->GetItem("DReDate")->PutValue((_variant_t)m_dCurrent);

				if(m_bSave)
				{
					pSet->Fields->GetItem("DInputPerson")->PutValue(g_strUserName.AllocSysString());
					pSet->Fields->GetItem("DInputDate")->PutValue((_variant_t)m_dCurrent);
				}
			}
		}
		break;
	case 2:

		if(m_iPage == -1)
		{
			if(g_strAuthor.Mid(5,1)=="1")
			{
			pSet->Fields->GetItem("ElevatorType")->PutValue(m_sElevatorType);
			pSet->Fields->GetItem("ElevatorModel")->PutValue(m_sElevatorModel);
			pSet->Fields->GetItem("RatedLoad")->PutValue(m_iRatedLoad);
			pSet->Fields->GetItem("RatedSpeed")->PutValue(m_fRatedSpeed);
			pSet->Fields->GetItem("DragMode")->PutValue(m_sDragMode);
			pSet->Fields->GetItem("ControlMode")->PutValue(m_sControlMode);
			pSet->Fields->GetItem("ControlModeRemark")->PutValue(m_sControlModeRemark);
			pSet->Fields->GetItem("Floor")->PutValue(m_iFloor);
			pSet->Fields->GetItem("Stop")->PutValue(m_iStop);
			pSet->Fields->GetItem("Door")->PutValue(m_iDoor);
			pSet->Fields->GetItem("StopName")->PutValue(m_sStopName);
			pSet->Fields->GetItem("Through")->PutValue(m_bThrough);
			}
			if(g_strAuthor.Mid(6,1)=="1")
			{

			pSet->Fields->GetItem("ShaftWidth")->PutValue(m_iSW);
			pSet->Fields->GetItem("ShaftDepth")->PutValue(m_iSD);
			pSet->Fields->GetItem("TH")->PutValue(m_lTH);
			pSet->Fields->GetItem("OH")->PutValue(m_lOH);
			pSet->Fields->GetItem("PD")->PutValue(m_iPD);
			pSet->Fields->GetItem("CounterWeight")->PutValue(m_sCounterWeight);
			pSet->Fields->GetItem("CWGauge")->PutValue(m_iCWGauge);
			pSet->Fields->GetItem("CounterWeightHeight")->PutValue(m_iCounterWeightHeight);
			pSet->Fields->GetItem("SGPosition")->PutValue(m_sSGPosition);
			pSet->Fields->GetItem("WideJamb")->PutValue(m_bWideJamb);
			pSet->Fields->GetItem("WJType")->PutValue(m_sWJType);
			pSet->Fields->GetItem("JambXC")->PutValue(m_iJambXC);
			pSet->Fields->GetItem("CCW")->PutValue(m_iCCW);
			pSet->Fields->GetItem("CS1")->PutValue(m_iCS1);
			pSet->Fields->GetItem("CS2")->PutValue(m_iCS2);
			pSet->Fields->GetItem("CWS")->PutValue(m_iCWS);
			pSet->Fields->GetItem("HostControlPanel")->PutValue(m_sHostControlPanel);
			}
			if(g_strAuthor.Mid(7,1)=="1")
			{
			pSet->Fields->GetItem("CD")->PutValue(m_iCD);
			pSet->Fields->GetItem("CW")->PutValue(m_iCW);
			pSet->Fields->GetItem("CH")->PutValue(m_iCH);
			pSet->Fields->GetItem("Operator")->PutValue(m_sDoorSystem);
			pSet->Fields->GetItem("OpenType")->PutValue(m_sOpenType);
			pSet->Fields->GetItem("OffsetDir")->PutValue(m_sOffsetDir);
			pSet->Fields->GetItem("Offset")->PutValue(m_iOffset);
			pSet->Fields->GetItem("DW")->PutValue(m_iDW);
			pSet->Fields->GetItem("DH")->PutValue(m_iDH);
			}
			if(g_strAuthor.Mid(8,1)=="1")
			{
			pSet->Fields->GetItem("Ceiling")->PutValue(m_sCeiling);
			pSet->Fields->GetItem("FrontWall")->PutValue(m_sFrontWall);
			pSet->Fields->GetItem("SideWall")->PutValue(m_sSideWall);
			pSet->Fields->GetItem("RearWall")->PutValue(m_sRearWall);
			pSet->Fields->GetItem("SideHandRail")->PutValue(m_sSideHandRail);
			pSet->Fields->GetItem("RearHandRail")->PutValue(m_sRearHandRail);
			pSet->Fields->GetItem("HandRailCheck")->PutValue(m_bHandRail);
			pSet->Fields->GetItem("GlassCheck")->PutValue(m_bGlassPosition);
			pSet->Fields->GetItem("GlassType")->PutValue(m_sGlassType);
			pSet->Fields->GetItem("GlassPosition")->PutValue(m_sGlassPosition);
			pSet->Fields->GetItem("CarDoor")->PutValue(m_sDoor);
			pSet->Fields->GetItem("CarFloor")->PutValue(m_sFloor);
			pSet->Fields->GetItem("FloorDoor1")->PutValue(m_sFloorDoor1);
			pSet->Fields->GetItem("FloorDoorNum1")->PutValue(m_iFloorDoor1);
			pSet->Fields->GetItem("FloorDoor2")->PutValue(m_sFloorDoor2);
			pSet->Fields->GetItem("FloorDoorNum2")->PutValue(m_iFloorDoor2);
			}
			if(g_strAuthor.Mid(9,1)=="1")
			{
			pSet->Fields->GetItem("Controller")->PutValue(m_sController);
			pSet->Fields->GetItem("DisaPanel")->PutValue(m_bDisaPanel);
			pSet->Fields->GetItem("PushButton")->PutValue(m_sPushButton);
			pSet->Fields->GetItem("VideoCable")->PutValue(m_bVideoCable);
			pSet->Fields->GetItem("CallBoardType")->PutValue(m_sCallBoardType);
			pSet->Fields->GetItem("CallBoardTypeRemark")->PutValue(m_sCallboardtypeRemark);
			pSet->Fields->GetItem("ScreenMagic")->PutValue(m_sScreenMagic);
			pSet->Fields->GetItem("ScreenMagicRemark")->PutValue(m_sScreenMagicRemark);
			pSet->Fields->GetItem("InvertorType")->PutValue(m_sInvertorType);
			pSet->Fields->GetItem("InvertorPower")->PutValue(m_sInvertorPower);
			}
			if(g_strAuthor.Mid(10,1)=="1")
			{
			pSet->Fields->GetItem("Traction")->PutValue(m_sTraction);
			pSet->Fields->GetItem("SpeedGovernor")->PutValue(m_sSpeedGovernor);
			pSet->Fields->GetItem("Encode")->PutValue(m_sEncode);
			pSet->Fields->GetItem("Safety")->PutValue(m_sSafety);
			pSet->Fields->GetItem("Buffer")->PutValue(m_sBuffer);
			pSet->Fields->GetItem("NonstandardCheck")->PutValue(m_bNonstandardCheck);
			pSet->Fields->GetItem("Nonstandard")->PutValue(m_sNonstandardRemark);
			pSet->Fields->GetItem("ConfigureRemarks")->PutValue(m_sRemark);
			pSet->Fields->GetItem("CarRail")->PutValue(m_sCarRail);
			pSet->Fields->GetItem("CWRail")->PutValue(m_sCWRail);
			}
		}
		else
		{
			if(g_strAuthor.Mid(5,1)=="1"&& m_iPage==0)
			{

				pSet->Fields->GetItem("ElevatorType")->PutValue(m_sElevatorType);
				pSet->Fields->GetItem("ElevatorModel")->PutValue(m_sElevatorModel);
				pSet->Fields->GetItem("RatedLoad")->PutValue(m_iRatedLoad);
				pSet->Fields->GetItem("RatedSpeed")->PutValue(m_fRatedSpeed);
				pSet->Fields->GetItem("DragMode")->PutValue(m_sDragMode);
				pSet->Fields->GetItem("ControlMode")->PutValue(m_sControlMode);
				pSet->Fields->GetItem("ControlModeRemark")->PutValue(m_sControlModeRemark);
				pSet->Fields->GetItem("Floor")->PutValue(m_iFloor);
				pSet->Fields->GetItem("Stop")->PutValue(m_iStop);
				pSet->Fields->GetItem("Door")->PutValue(m_iDoor);
				pSet->Fields->GetItem("StopName")->PutValue(m_sStopName);
				pSet->Fields->GetItem("Through")->PutValue(m_bThrough);
			}
			if(g_strAuthor.Mid(6,1)=="1"&&m_iPage==1)
			{

				pSet->Fields->GetItem("ShaftWidth")->PutValue(m_iSW);
				pSet->Fields->GetItem("ShaftDepth")->PutValue(m_iSD);
				pSet->Fields->GetItem("TH")->PutValue(m_lTH);
				pSet->Fields->GetItem("OH")->PutValue(m_lOH);
				pSet->Fields->GetItem("PD")->PutValue(m_iPD);
				pSet->Fields->GetItem("CounterWeight")->PutValue(m_sCounterWeight);
				pSet->Fields->GetItem("CWGauge")->PutValue(m_iCWGauge);
				pSet->Fields->GetItem("CounterWeightHeight")->PutValue(m_iCounterWeightHeight);
				pSet->Fields->GetItem("SGPosition")->PutValue(m_sSGPosition);
				pSet->Fields->GetItem("WideJamb")->PutValue(m_bWideJamb);
				pSet->Fields->GetItem("WJType")->PutValue(m_sWJType);
				pSet->Fields->GetItem("JambXC")->PutValue(m_iJambXC);
				pSet->Fields->GetItem("CCW")->PutValue(m_iCCW);
				pSet->Fields->GetItem("CS1")->PutValue(m_iCS1);
				pSet->Fields->GetItem("CS2")->PutValue(m_iCS2);
				pSet->Fields->GetItem("CWS")->PutValue(m_iCWS);
			}

			if(g_strAuthor.Mid(7,1)=="1"&&m_iPage==2)
			{
				pSet->Fields->GetItem("HostControlPanel")->PutValue(m_sHostControlPanel);
				pSet->Fields->GetItem("CD")->PutValue(m_iCD);
				pSet->Fields->GetItem("CW")->PutValue(m_iCW);
				pSet->Fields->GetItem("CH")->PutValue(m_iCH);
				pSet->Fields->GetItem("Operator")->PutValue(m_sDoorSystem);
				pSet->Fields->GetItem("OpenType")->PutValue(m_sOpenType);
				pSet->Fields->GetItem("OffsetDir")->PutValue(m_sOffsetDir);
				pSet->Fields->GetItem("Offset")->PutValue(m_iOffset);
				pSet->Fields->GetItem("DW")->PutValue(m_iDW);
				pSet->Fields->GetItem("DH")->PutValue(m_iDH);
			}

			if(g_strAuthor.Mid(8,1)=="1"&&m_iPage==3)
			{
				pSet->Fields->GetItem("Ceiling")->PutValue(m_sCeiling);
				pSet->Fields->GetItem("FrontWall")->PutValue(m_sFrontWall);
				pSet->Fields->GetItem("SideWall")->PutValue(m_sSideWall);
				pSet->Fields->GetItem("RearWall")->PutValue(m_sRearWall);
				pSet->Fields->GetItem("SideHandRail")->PutValue(m_sSideHandRail);
				pSet->Fields->GetItem("RearHandRail")->PutValue(m_sRearHandRail);
				pSet->Fields->GetItem("HandRailCheck")->PutValue(m_bHandRail);
				pSet->Fields->GetItem("GlassCheck")->PutValue(m_bGlassPosition);
				pSet->Fields->GetItem("GlassType")->PutValue(m_sGlassType);
				pSet->Fields->GetItem("GlassPosition")->PutValue(m_sGlassPosition);
				pSet->Fields->GetItem("CarDoor")->PutValue(m_sDoor);
				pSet->Fields->GetItem("CarFloor")->PutValue(m_sFloor);
				pSet->Fields->GetItem("FloorDoor1")->PutValue(m_sFloorDoor1);
				pSet->Fields->GetItem("FloorDoorNum1")->PutValue(m_iFloorDoor1);
				pSet->Fields->GetItem("FloorDoor2")->PutValue(m_sFloorDoor2);
				pSet->Fields->GetItem("FloorDoorNum2")->PutValue(m_iFloorDoor2);
			}

			if(g_strAuthor.Mid(9,1)=="1"&&m_iPage==4)
			{
				pSet->Fields->GetItem("Controller")->PutValue(m_sController);
				pSet->Fields->GetItem("DisaPanel")->PutValue(m_bDisaPanel);
				pSet->Fields->GetItem("PushButton")->PutValue(m_sPushButton);
				pSet->Fields->GetItem("VideoCable")->PutValue(m_bVideoCable);
				pSet->Fields->GetItem("CallBoardType")->PutValue(m_sCallBoardType);
				pSet->Fields->GetItem("CallBoardTypeRemark")->PutValue(m_sCallboardtypeRemark);
				pSet->Fields->GetItem("ScreenMagic")->PutValue(m_sScreenMagic);
				pSet->Fields->GetItem("ScreenMagicRemark")->PutValue(m_sScreenMagicRemark);
				pSet->Fields->GetItem("InvertorType")->PutValue(m_sInvertorType);
				pSet->Fields->GetItem("InvertorPower")->PutValue(m_sInvertorPower);
			}

			if(g_strAuthor.Mid(10,1)=="1"&&m_iPage==5)
			{
				pSet->Fields->GetItem("Traction")->PutValue(m_sTraction);
				pSet->Fields->GetItem("SpeedGovernor")->PutValue(m_sSpeedGovernor);
				pSet->Fields->GetItem("Encode")->PutValue(m_sEncode);
				pSet->Fields->GetItem("Safety")->PutValue(m_sSafety);
				pSet->Fields->GetItem("Buffer")->PutValue(m_sBuffer);
				pSet->Fields->GetItem("NonstandardCheck")->PutValue(m_bNonstandardCheck);
				pSet->Fields->GetItem("Nonstandard")->PutValue(m_sNonstandardRemark);
				pSet->Fields->GetItem("ConfigureRemarks")->PutValue(m_sRemark);
				pSet->Fields->GetItem("CarRail")->PutValue(m_sCarRail);
				pSet->Fields->GetItem("CWRail")->PutValue(m_sCWRail);
			}
		}


		if(!m_bSaveCopy)
		{
			pSet->Fields->GetItem("CReperson")->PutValue(g_strUserName.AllocSysString());
			pSet->Fields->GetItem("CReDate")->PutValue((_variant_t)m_dCurrent);

			if(m_bSave)
			{
				pSet->Fields->GetItem("CInputPerson")->PutValue(g_strUserName.AllocSysString());
				pSet->Fields->GetItem("CInputDate")->PutValue((_variant_t)m_dCurrent);
			}
		}
		break;
	default:
		break;
	}
}


void CDataSameCopyDlg::OnBnClickedButtonFind()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;

	try{

		strSQL = "select ProjectName, ProjectNameEn from PBInformation where ID = '"+m_sID+"'";
		theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
		int iCount = m_pTempSet->GetRecordCount();
		if(iCount!=0)
		{
			Holder = m_pTempSet->GetCollect("ProjectName");
			str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			if(!str.IsEmpty())
				m_sProjectName = str; 

			Holder =m_pTempSet->GetCollect("ProjectNameEn");
			str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			if(!str.IsEmpty())
				m_sProjectNameEn = str;

			strSQL = "select  *  from OrderOfProject where ID = '"+m_sID+"' and Status = FALSE";
			theApp.ADOExecute(m_pTempSet, theApp.m_pConnect,strSQL);
			LoadTargetResource(m_pTempSet);
			m_pTempSet->Close();


		}
		else
		{
			m_sProjectName.Empty();
			m_sProjectNameEn.Empty();
			m_cTargetResouce.DeleteAllItems();
			m_pTempSet->Close();

		}


		UpdateData(FALSE);
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("ADO Error: %s",(char*)e.Description());
		AfxMessageBox(err);
		return;
	}
	catch(...)
	{
		AfxMessageBox("Unknown Error...");
		return;
	}

}


void CDataSameCopyDlg::OnCbnSelendokCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;

	try{

		int iIndex = m_cTarget.GetCurSel();
		if(iIndex!=LB_ERR)
		{
			m_cTarget.GetLBText(iIndex, str);
			m_sID = str;

			strSQL = "select ProjectName, ProjectNameEn from PBInformation where ID = '"+str+"'";
			theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
			int iCount = m_pTempSet->GetRecordCount();
			if(iCount!=0)
			{
				Holder = m_pTempSet->GetCollect("ProjectName");
				str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
				if(!str.IsEmpty())
					m_sProjectName = str; 

				Holder =m_pTempSet->GetCollect("ProjectNameEn");
				str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
				if(!str.IsEmpty())
					m_sProjectNameEn = str;

				strSQL = "select  *  from OrderOfProject where ID = '"+m_sID+"' and Status = FALSE";
				theApp.ADOExecute(m_pTempSet, theApp.m_pConnect,strSQL);
				LoadTargetResource(m_pTempSet);
				m_pTempSet->Close();


			}
			else
			{
				m_pTempSet->Close();

			}
		}

		UpdateData(FALSE);
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("ADO Error: %s",(char*)e.Description());
		AfxMessageBox(err);
		return;
	}
	catch(...)
	{
		AfxMessageBox("Unknown Error...");
		return;
	}

}
