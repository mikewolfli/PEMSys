// ItemDataInputView.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemDataInputView.h"
#include ".\itemdatainputview.h"
#include "DataSameCopyDlg.h"

// CItemDataInputView
CString m_sgElevatorModel;
CString m_sgRatedLoad;
CString m_sgRatedSpeed;
extern CString g_strAuthor;
IMPLEMENT_DYNCREATE(CItemDataInputView, CFormView)

CItemDataInputView::CItemDataInputView()
	: CFormView(CItemDataInputView::IDD)
	, m_sDisplay(_T(""))
	, m_sProjectName(_T(""))
	, m_sProjectNameEn(_T(""))
	, m_sRemark(_T(""))
	, m_sInputPerson(_T(""))
	, m_sRePerson(_T(""))
	, m_sInputDate(_T(""))
	, m_sReDate(_T(" of "))
	, m_dCurrent(COleDateTime::GetCurrentTime())
	, m_sID(_T(""))
	, m_iNumber(0)
	, m_iPos(0)
	, m_iCount(0)
	, m_bCopy(FALSE)
	, m_bSave(FALSE)
	, m_sElevatorID(_T(""))
	, m_iCheck(0)
	, m_sOrderID(_T(""))
	, m_bCopyCh(TRUE)
	, m_iPage(0)
	, m_bCheck(TRUE)
{
}

CItemDataInputView::~CItemDataInputView()
{
	if(m_pDataSet->State == adStateOpen)
	{
		m_pDataSet->Close();
	    m_pDataSet.Release();
	}
	if(m_pTempSet->State == adStateOpen)
	{
		m_pTempSet->Close();
	    m_pTempSet.Release();
	}

}

void CItemDataInputView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_DATAINPUT_ORDERID, m_sOrderID);
	DDX_Control(pDX, IDC_BUTTON_DATAINPUT_FIRST, m_cFirst);
	DDX_Control(pDX, IDC_BUTTON_DATAINPUT_PREVIOUS, m_cPrevious);
	DDX_Control(pDX, IDC_BUTTON_DATAINPUT_NEXT, m_cNext);
	DDX_Control(pDX, IDC_BUTTON_DATAINPUT_LAST, m_cLast);
	DDX_Control(pDX, IDOK, m_cSave);
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	DDX_Control(pDX, IDC_BUTTON_DATAINPUT_DELETE, m_cDelete);
	DDX_Text(pDX, IDC_EDIT_DATAINPUT_DISPLAY, m_sDisplay);
	DDX_Control(pDX, IDC_COMBO_DATAINPUT_ORDERID, m_cOrderID);
	DDX_Text(pDX, IDC_EDIT_DATAINPUT_PROJECTNAME, m_sProjectName);
	DDX_Text(pDX, IDC_EDIT_DATAINPUT_PROJECTNAMEEN, m_sProjectNameEn);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_sRemark);
	DDX_Text(pDX, IDC_EDIT_DATAINPUT_INPUTPERSON, m_sInputPerson);
	DDX_Text(pDX, IDC_EDIT_DATAINPUT_REPERSON, m_sRePerson);
	DDX_Text(pDX, IDC_EDIT_DATAINPUT_INPUTDATE, m_sInputDate);
	DDX_Text(pDX, IDC_EDIT_DATAINPUT_REDATE, m_sReDate);
	DDX_CBString(pDX, IDC_COMBO_COMMERCE_ID, m_sID);
	DDX_Control(pDX, IDC_COMBO_COMMERCE_ID, m_cID);
	DDX_Text(pDX, IDC_COMMERCE_EDIT_COMMERCE_NUM, m_iNumber);
	DDX_Text(pDX, IDC_EDIT_DATAINPUT_ELEVATORID, m_sElevatorID);
	DDX_Control(pDX, IDC_BUTTON_SAMECOPY, m_cSameCopy);
	DDX_Check(pDX, IDC_CHECK_COPY, m_bCopyCh);
	DDX_Check(pDX, IDC_CHECK_STANDARD, m_bCheck);
}

BEGIN_MESSAGE_MAP(CItemDataInputView, CFormView)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_DATAINPUT_SEARCH, OnBnClickedButtonDatainputSearch)
	ON_CBN_SELENDOK(IDC_COMBO_COMMERCE_ID, OnCbnSelendokComboCommerceId)
	ON_BN_CLICKED(IDC_BUTTON_DATAINPUT_FIRST, OnBnClickedButtonDatainputFirst)
	ON_BN_CLICKED(IDC_BUTTON_DATAINPUT_PREVIOUS, OnBnClickedButtonDatainputPrevious)
	ON_BN_CLICKED(IDC_BUTTON_DATAINPUT_NEXT, OnBnClickedButtonDatainputNext)
	ON_BN_CLICKED(IDC_BUTTON_DATAINPUT_LAST, OnBnClickedButtonDatainputLast)
	ON_CBN_SELENDOK(IDC_COMBO_DATAINPUT_ORDERID, OnCbnSelendokComboDatainputOrderid)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DATAINPUT_DELETE, OnBnClickedButtonDatainputDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAMECOPY, OnBnClickedButtonSamecopy)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_STANDARD, OnBnClickedCheckStandard)
END_MESSAGE_MAP()


// CItemDataInputView 诊断

#ifdef _DEBUG
void CItemDataInputView::AssertValid() const
{
	CFormView::AssertValid();
}

void CItemDataInputView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CItemDataInputView 消息处理程序

void CItemDataInputView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	GetParentFrame()->RecalcLayout();
	//	 ResizeParentToFit();
	ResizeParentToFit(FALSE);
	ResizeParentToFit(TRUE);
	// TODO: 在此添加专用代码和/或调用基类                                                                                                                                                                                                                                                                                                  
	CString strTitle ;
	strTitle = "电梯参数";
	GetParentFrame()->SetWindowText(strTitle);

	UpdateData(TRUE);
	m_cDelete.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DELETE));
	m_cFirst.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_FIRST));
	m_cPrevious.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_PREVIOUS));
	m_cNext.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_NEXT));
	m_cLast.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LAST));
	m_cSave.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_SAVE));
	m_cCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_CANCEL));


	switch(g_tUserType)
	{
	case 1:
		m_cSameCopy.EnableWindow(FALSE);
		m_cDelete.EnableWindow(FALSE);
		m_cSave.EnableWindow(FALSE);
		break;
	case 2:
		m_cDelete.EnableWindow(FALSE);
		break;
	default:
		break;
	}

	m_cNext.EnableWindow(FALSE);
	m_cPrevious.EnableWindow(FALSE);
	m_cFirst.EnableWindow(FALSE);
	m_cLast.EnableWindow(FALSE);
	m_sInputPerson = g_strUserName;
	m_sRePerson = g_strUserName;
	m_sInputDate =  m_dCurrent.Format("%Y-%m-%d");
	m_sReDate =  m_dCurrent.Format("%Y-%m-%d");

	m_sheetData.AddPage(&m_pageBasicData);
	m_sheetData.AddPage(&m_pageShaft);
	m_sheetData.AddPage(&m_pageCar);
	m_sheetData.AddPage(&m_pageUpholster);
	m_sheetData.AddPage(&m_pageElectric);
	m_sheetData.AddPage(&m_pageParts);
	m_sheetData.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);

	RECT rect;
	m_sheetData.GetWindowRect(&rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	m_sheetData.SetWindowPos(NULL, 10, 135, 340, 285, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	m_sheetData.SetActivePage(&m_pageShaft);
	m_sheetData.SetActivePage(&m_pageCar);
	m_sheetData.SetActivePage(&m_pageUpholster);
	m_sheetData.SetActivePage(&m_pageElectric);
	m_sheetData.SetActivePage(&m_pageParts);
	m_sheetData.SetActivePage(&m_pageBasicData);
    m_pageShaft.m_bCheck = m_bCheck;
	m_pageCar.m_bCheck = m_bCheck;

	try
	{
		m_pTempSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例
		m_pDataSet.CreateInstance(__uuidof(Recordset));   

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
				m_cID.AddString(str);
				m_pTempSet->MoveNext();
			}
		}
		m_pTempSet->Close();

		if(!m_sID.IsEmpty())
		{
			InitOrderCtrl();
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

void CItemDataInputView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//乘风东去蓬莱幽,青山依旧绿水流,平心静气信步遛,丛林顽石曲径游,偶遇仙人邀相弈,
	UpdateData(TRUE);
	try{

		if(m_pTempSet->State == adStateOpen)
			m_pTempSet->Close();

		m_sOrderID.Remove(' ');
		if(m_sOrderID.IsEmpty())
		{
			AfxMessageBox("订单号不能为空!",MB_ICONEXCLAMATION);
			return;
		}

		CString str1  = m_sOrderID.Left(2);
		int i=m_sOrderID.GetLength();
		CString str2 = m_sOrderID.Mid(2,i-6);
		m_sOrderID = str1+" "+str2+" "+m_sOrderID.Right(4);

		strSQL = "select * from Configuration where OrderID = '"+m_sOrderID+"'";
		theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
		int iCount = m_pTempSet->GetRecordCount();
		if(iCount == 0)
		{
			m_pTempSet->AddNew();
			m_bSave = TRUE;
		}
		m_bCopy = FALSE;
		UpdateRecord(m_pTempSet);
		m_pTempSet->Update();
		ReadRecord(m_pTempSet);
		m_pTempSet->Close();
		m_bSave = FALSE;
/*
		strSQL = "select * from CDUnion where OrderID = '"+m_sOrderID+"'";
		theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount == 0)
		{
			m_pTempSet->AddNew();
		}
		UpdateRecord(m_pTempSet);
		m_pTempSet->Update();
*/
		m_bCopy = TRUE;

		m_bCopy = FALSE;
		AfxMessageBox("记录已保存!",MB_OK | MB_ICONINFORMATION);
	
	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("ADO Error: %s",(char*)e.Description());
		AfxMessageBox(err);
		m_pTempSet->Close();
		return;
	}
	catch(...)
	{
		AfxMessageBox("Unknown Error...");
		m_pTempSet->Close();
		return;
	}

	UpdateData(FALSE);
}

void CItemDataInputView::InitOrderCtrl(void)
{
	m_cOrderID.ResetContent();
	strSQL = "select  OrderID, ElevatorID from OrderOfProject where ID = '"+m_sID+"' and Status = FALSE";
	theApp.ADOExecute(m_pTempSet, theApp.m_pConnect,strSQL);
	int iCount = m_pTempSet->GetRecordCount();
	if(iCount!=0)
	{
		CString str;
		m_pTempSet->MoveFirst();
		Holder = m_pTempSet->GetCollect("OrderID");
		str = (char*)(_bstr_t)Holder;
		m_sOrderID =str;
		m_pageElectric.m_sOrderID = m_sOrderID;

		m_cOrderID.AddString(str);

		Holder = m_pTempSet->GetCollect("ElevatorID");
		str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
		m_sElevatorID = str;

		for(int i= 1; i<iCount; i++)
		{
			m_pTempSet->MoveNext();
			Holder = m_pTempSet->GetCollect("OrderID");
			str= (char*)(_bstr_t)Holder;
			m_cOrderID.AddString(str);
		}

	}
	else
	{
		m_sOrderID.Empty();
		m_pageBasicData.ClearEdit();
		m_pageCar.ClearEdit();
		m_pageElectric.ClearEdit();
		m_pageParts.ClearEdit();
		m_pageShaft.ClearEdit();
		m_pageUpholster.ClearEdit();
	}


	m_pTempSet->Close();
}

void CItemDataInputView::UpdateRecord(_RecordsetPtr& pSet)
{
	m_pageBasicData.UpdateDataPage(TRUE);
	m_pageCar.UpdateDataPage(TRUE);
	m_pageElectric.UpdateDataPage(TRUE);
	m_pageShaft.UpdateDataPage(TRUE);
	m_pageParts.UpdateDataPage(TRUE);
	m_pageUpholster.UpdateDataPage(TRUE);

	if(g_strAuthor.Mid(5,1)=="1")
	{
	pSet->Fields->GetItem("OrderID")->PutValue(m_sOrderID.AllocSysString());
	pSet->Fields->GetItem("ElevatorType")->PutValue(m_pageBasicData.m_sElevatorType.AllocSysString());
	pSet->Fields->GetItem("ElevatorModel")->PutValue(m_pageBasicData.m_sElevatorModel.AllocSysString());
	pSet->Fields->GetItem("RatedLoad")->PutValue((_variant_t)atoi(m_pageBasicData.m_sRatedLoad));
	pSet->Fields->GetItem("RatedSpeed")->PutValue((_variant_t)atof(m_pageBasicData.m_sRatedSpeed));
	pSet->Fields->GetItem("DragMode")->PutValue(m_pageBasicData.m_sDragMode.AllocSysString());
	pSet->Fields->GetItem("ControlMode")->PutValue(m_pageBasicData.m_sControlMode.AllocSysString());
	pSet->Fields->GetItem("ControlModeRemark")->PutValue(m_pageBasicData.m_sControlModeRemark.AllocSysString());
	pSet->Fields->GetItem("Floor")->PutValue((_variant_t)m_pageBasicData.m_iFloor);
	pSet->Fields->GetItem("Stop")->PutValue((_variant_t)m_pageBasicData.m_iStop);
	pSet->Fields->GetItem("Door")->PutValue((_variant_t)m_pageBasicData.m_iDoor);
	pSet->Fields->GetItem("StopName")->PutValue(m_pageBasicData.m_sStopName.AllocSysString());
	pSet->Fields->GetItem("Through")->PutValue((_variant_t)m_pageBasicData.m_bThrough);
	pSet->Fields->GetItem("CarRail")->PutValue(m_pageParts.m_sCarRail.AllocSysString());
	pSet->Fields->GetItem("CWRail")->PutValue(m_pageParts.m_sCWRail.AllocSysString());
	}
	if(g_strAuthor.Mid(6.1)=="1")
	{
	pSet->Fields->GetItem("ShaftWidth")->PutValue((_variant_t)m_pageShaft.m_iSW);
	pSet->Fields->GetItem("ShaftDepth")->PutValue((_variant_t)m_pageShaft.m_iSD);
	pSet->Fields->GetItem("TH")->PutValue((_variant_t)m_pageShaft.m_lTH);
	pSet->Fields->GetItem("OH")->PutValue((_variant_t)m_pageShaft.m_lOH);
	pSet->Fields->GetItem("PD")->PutValue((_variant_t)m_pageShaft.m_iPD);
	pSet->Fields->GetItem("CounterWeight")->PutValue(m_pageShaft.m_sCounterWeight.AllocSysString());
	pSet->Fields->GetItem("CWGauge")->PutValue((_variant_t)m_pageShaft.m_iCWGauge);
	pSet->Fields->GetItem("CounterWeightHeight")->PutValue((_variant_t)m_pageShaft.m_iCounterWeightHeight);
	pSet->Fields->GetItem("SGPosition")->PutValue(m_pageShaft.m_sSGPosition.AllocSysString());
	pSet->Fields->GetItem("WideJamb")->PutValue((_variant_t)m_pageShaft.m_bWideJamb);
	pSet->Fields->GetItem("WJType")->PutValue(m_pageShaft.m_sWJType.AllocSysString());
	pSet->Fields->GetItem("JambXC")->PutValue((_variant_t)m_pageShaft.m_iJambXC);
	pSet->Fields->GetItem("CCW")->PutValue((_variant_t)m_pageShaft.m_iCCW);
	pSet->Fields->GetItem("CS1")->PutValue((_variant_t)m_pageShaft.m_iCS1);
	pSet->Fields->GetItem("CS2")->PutValue((_variant_t)m_pageShaft.m_iCS2);
	pSet->Fields->GetItem("CWS")->PutValue((_variant_t)m_pageShaft.m_iCWS);
	pSet->Fields->GetItem("HostControlPanel")->PutValue(m_pageCar.m_sHostControlPanel.AllocSysString());
	}
	if(g_strAuthor.Mid(7.1)=="1")
	{
	pSet->Fields->GetItem("CD")->PutValue((_variant_t)m_pageCar.m_iCD);
	pSet->Fields->GetItem("CW")->PutValue((_variant_t)m_pageCar.m_iCW);
	pSet->Fields->GetItem("CH")->PutValue((_variant_t)m_pageCar.m_iCH);
	pSet->Fields->GetItem("OpenType")->PutValue(m_pageCar.m_sOpenType.AllocSysString());
	pSet->Fields->GetItem("OffsetDir")->PutValue(m_pageCar.m_sOffsetDir.AllocSysString());
	pSet->Fields->GetItem("Offset")->PutValue((_variant_t)m_pageCar.m_iOffset);
	pSet->Fields->GetItem("DW")->PutValue((_variant_t)m_pageCar.m_iDW);
	pSet->Fields->GetItem("DH")->PutValue((_variant_t)m_pageCar.m_iDH);
	}
	if(g_strAuthor.Mid(8.1)=="1")
	{
	pSet->Fields->GetItem("Ceiling")->PutValue(m_pageUpholster.m_sCeiling.AllocSysString());
	pSet->Fields->GetItem("FrontWall")->PutValue(m_pageUpholster.m_sFrontWall.AllocSysString());
	pSet->Fields->GetItem("SideWall")->PutValue(m_pageUpholster.m_sSideWall.AllocSysString());
	pSet->Fields->GetItem("RearWall")->PutValue(m_pageUpholster.m_sRearWall.AllocSysString());
	pSet->Fields->GetItem("SideHandRail")->PutValue(m_pageUpholster.m_sSideHandRail.AllocSysString());
	pSet->Fields->GetItem("RearHandRail")->PutValue(m_pageUpholster.m_sRearHandRail.AllocSysString());
	pSet->Fields->GetItem("HandRailCheck")->PutValue((_variant_t)m_pageUpholster.m_bHandRail);
	pSet->Fields->GetItem("GlassCheck")->PutValue((_variant_t)m_pageUpholster.m_bGlassPosition);
	pSet->Fields->GetItem("GlassType")->PutValue(m_pageUpholster.m_sGlassType.AllocSysString());
	pSet->Fields->GetItem("GlassPosition")->PutValue(m_pageUpholster.m_sGlassPosition.AllocSysString());
	pSet->Fields->GetItem("CarDoor")->PutValue(m_pageUpholster.m_sDoor.AllocSysString());
	pSet->Fields->GetItem("CarFloor")->PutValue(m_pageUpholster.m_sFloor.AllocSysString());
	pSet->Fields->GetItem("FloorDoor1")->PutValue(m_pageUpholster.m_sFloorDoor1.AllocSysString());
    pSet->Fields->GetItem("FloorDoorNum1")->PutValue((_variant_t)m_pageUpholster.m_iFloorDoor1);
	pSet->Fields->GetItem("FloorDoor2")->PutValue(m_pageUpholster.m_sFloorDoor2.AllocSysString());
	pSet->Fields->GetItem("FloorDoorNum2")->PutValue((_variant_t)m_pageUpholster.m_iFloorDoor2);
	}
	if(g_strAuthor.Mid(9.1)=="1")
	{
	pSet->Fields->GetItem("Controller")->PutValue(m_pageElectric.m_sController.AllocSysString());
	pSet->Fields->GetItem("DisaPanel")->PutValue((_variant_t)m_pageElectric.m_bDisaPanel);
	pSet->Fields->GetItem("PushButton")->PutValue(m_pageElectric.m_sPushButton.AllocSysString());
	pSet->Fields->GetItem("VideoCable")->PutValue((_variant_t)m_pageElectric.m_bVideoCable);
	pSet->Fields->GetItem("CallBoardType")->PutValue(m_pageElectric.m_sCallBoardType.AllocSysString());
	pSet->Fields->GetItem("CallBoardTypeRemark")->PutValue(m_pageElectric.m_sCallboardtypeRemark.AllocSysString());
	pSet->Fields->GetItem("ScreenMagic")->PutValue(m_pageElectric.m_sScreenMagic.AllocSysString());
	pSet->Fields->GetItem("ScreenMagicRemark")->PutValue(m_pageElectric.m_sScreenMagicRemark.AllocSysString());
	pSet->Fields->GetItem("InvertorType")->PutValue(m_pageElectric.m_sInvertorType.AllocSysString());
	pSet->Fields->GetItem("InvertorPower")->PutValue(m_pageElectric.m_sInvertorPower.AllocSysString());
	}
	if(g_strAuthor.Mid(10.1)=="1")
	{
	pSet->Fields->GetItem("Operator")->PutValue(m_pageParts.m_sDoorSystem.AllocSysString());
	pSet->Fields->GetItem("Traction")->PutValue(m_pageParts.m_sTraction.AllocSysString());
	pSet->Fields->GetItem("SpeedGovernor")->PutValue(m_pageParts.m_sSpeedGovernor.AllocSysString());
	pSet->Fields->GetItem("Encode")->PutValue(m_pageParts.m_sEncode.AllocSysString());
	pSet->Fields->GetItem("Safety")->PutValue(m_pageParts.m_sSafety.AllocSysString());
	pSet->Fields->GetItem("Buffer")->PutValue(m_pageParts.m_sBuffer.AllocSysString());
	pSet->Fields->GetItem("NonstandardCheck")->PutValue((_variant_t)m_pageParts.m_bNonstandardCheck);
	pSet->Fields->GetItem("Nonstandard")->PutValue(m_pageParts.m_sNonstandardRemark.AllocSysString());
    pSet->Fields->GetItem("ConfigureRemarks")->PutValue(m_sRemark.AllocSysString());
	}
	if(!m_bCopy)
	{
		pSet->Fields->GetItem("CReperson")->PutValue(g_strUserName.AllocSysString());
		pSet->Fields->GetItem("CReDate")->PutValue((_variant_t)m_dCurrent);

		if(m_bSave)
		{
			pSet->Fields->GetItem("CInputPerson")->PutValue(g_strUserName.AllocSysString());
			pSet->Fields->GetItem("CInputDate")->PutValue((_variant_t)m_dCurrent);
		}
	}
	m_pageBasicData.UpdateDataPage(FALSE);
	m_pageCar.UpdateDataPage(FALSE);
	m_pageElectric.UpdateDataPage(FALSE);
	m_pageShaft.UpdateDataPage(FALSE);
	m_pageParts.UpdateDataPage(FALSE);
	m_pageUpholster.UpdateDataPage(FALSE);
}

void CItemDataInputView::ReadRecord(_RecordsetPtr& pSet)
{

	m_pageBasicData.UpdateDataPage(TRUE);
	m_pageCar.UpdateDataPage(TRUE);
	m_pageElectric.UpdateDataPage(TRUE);
	m_pageShaft.UpdateDataPage(TRUE);
	m_pageParts.UpdateDataPage(TRUE);
	m_pageUpholster.UpdateDataPage(TRUE);

	Holder = pSet->GetCollect("ElevatorType");
	m_pageBasicData.m_sElevatorType = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ElevatorModel");
	m_pageBasicData.m_sElevatorModel  = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
	m_sgElevatorModel = m_pageBasicData.m_sElevatorModel;

	Holder = pSet->GetCollect("RatedLoad");
	m_pageBasicData.m_sRatedLoad.Format("%d",(int)Holder);

	Holder = pSet->GetCollect("RatedSpeed");
	m_pageBasicData.m_sRatedSpeed.Format("%.2f", (float)Holder);

	Holder = pSet->GetCollect("DragMode");
	m_pageBasicData.m_sDragMode = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ControlMode");
	m_pageBasicData.m_sControlMode = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ControlModeRemark");
	m_pageBasicData.m_sControlModeRemark = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Floor");
	m_pageBasicData.m_iFloor = (int)Holder;

	Holder = pSet->GetCollect("Stop");
	m_pageBasicData.m_iStop = (int)Holder;

	Holder = pSet->GetCollect("Door");
	m_pageBasicData.m_iDoor = (int)Holder;

	Holder = pSet->GetCollect("StopName");
	m_pageBasicData.m_sStopName = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Through");
	m_pageBasicData.m_bThrough = (bool)Holder;

	Holder = pSet->GetCollect("CarRail");
	m_pageParts.m_sCarRail = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

    Holder = pSet->GetCollect("CWRail");
	m_pageParts.m_sCWRail = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

    Holder = pSet->GetCollect("ShaftWidth");
	m_pageShaft.m_iSW = (int)Holder;

	Holder = pSet->GetCollect("ShaftDepth");
    m_pageShaft.m_iSD = (int)Holder;

	Holder = pSet->GetCollect("TH");
	m_pageShaft.m_lTH = (long)Holder;

	Holder = pSet->GetCollect("OH");
	m_pageShaft.m_lOH = (long)Holder;

	Holder = pSet->GetCollect("PD");
	m_pageShaft.m_iPD = (int)Holder;

    Holder = pSet->GetCollect("CounterWeight");
	m_pageShaft.m_sCounterWeight =  Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("CWGauge");
	m_pageShaft.m_iCWGauge = (int)Holder;

	Holder = pSet->GetCollect("CounterWeightHeight");
	m_pageShaft.m_iCounterWeightHeight = (int)Holder;

	Holder = pSet->GetCollect("SGPosition");
	m_pageShaft.m_sSGPosition =  Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet ->GetCollect("WideJamb");
	m_pageShaft.m_bWideJamb = (bool)Holder;

	Holder = pSet->GetCollect("WJtype");
	m_pageShaft.m_sWJType =  Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("JambXC");
    m_pageShaft.m_iJambXC = (int)Holder;

	Holder = pSet->GetCollect("CCW");
	m_pageShaft.m_iCCW = (int)Holder;

	Holder = pSet->GetCollect("CS1");
	m_pageShaft.m_iCS1 = (int)Holder;

	Holder = pSet->GetCollect("CS2");
	m_pageShaft.m_iCS2 = (int)Holder;

	Holder = pSet->GetCollect("CWS");
	m_pageShaft.m_iCWS = (int)Holder;

	Holder = pSet->GetCollect("HostControlPanel");
	m_pageCar.m_sHostControlPanel =  Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("CD");
	m_pageCar.m_iCD = (int)Holder;

	Holder = pSet->GetCollect("CW");
	m_pageCar.m_iCW = (int)Holder;

	Holder = pSet->GetCollect("CH");
	m_pageCar.m_iCH = (int)Holder;

	Holder = pSet->GetCollect("Operator");
	m_pageParts.m_sDoorSystem = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("OpenType");
	m_pageCar.m_sOpenType = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

    Holder = pSet->GetCollect("OffsetDir");
	m_pageCar.m_sOffsetDir = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

    Holder = pSet->GetCollect("Offset");
	m_pageCar.m_iOffset = (int)Holder;

	Holder = pSet->GetCollect("DW");
	m_pageCar.m_iDW= (int)Holder;

	Holder = pSet->GetCollect("DH");
	m_pageCar.m_iDH = (int)Holder;

	Holder = pSet->GetCollect("Ceiling");
	m_pageUpholster.m_sCeiling = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("FrontWall");
	m_pageUpholster.m_sFrontWall = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

    Holder = pSet->GetCollect("SideWall");
	m_pageUpholster.m_sSideWall = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("RearWall");
	m_pageUpholster.m_sRearWall =Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("SideHandRail");
	m_pageUpholster.m_sSideHandRail = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("RearHandRail");
	m_pageUpholster.m_sRearHandRail = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("HandRailCheck");
	m_pageUpholster.m_bHandRail = (bool)Holder;

	Holder = pSet->GetCollect("GlassCheck");
	m_pageUpholster.m_bGlassPosition = (bool)Holder;

	Holder = pSet->GetCollect("GlassType");
	m_pageUpholster.m_sGlassType = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("GlassPosition");
	m_pageUpholster.m_sGlassPosition = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("CarDoor");
	m_pageUpholster.m_sDoor = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("CarFloor");
	m_pageUpholster.m_sFloor = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

    Holder = pSet->GetCollect("FloorDoor1");
	m_pageUpholster.m_sFloorDoor1 = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("FloorDoorNum1");
	m_pageUpholster.m_iFloorDoor1 = (int)Holder;

	Holder = pSet->GetCollect("FloorDoor2");
	m_pageUpholster.m_sFloorDoor2 = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("FloorDoorNum2");
	m_pageUpholster.m_iFloorDoor2 = (int)Holder;


	Holder = pSet->GetCollect("Controller");
	m_pageElectric.m_sController = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("DisaPanel");
	m_pageElectric.m_bDisaPanel = (bool)Holder;

	Holder = pSet->GetCollect("PushButton");
	m_pageElectric.m_sPushButton = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("VideoCable");
	m_pageElectric.m_bVideoCable = (bool)Holder;

	Holder = pSet->GetCollect("CallBoardType");
	m_pageElectric.m_sCallBoardType = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("CallBoardTypeRemark");
	m_pageElectric.m_sCallboardtypeRemark = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ScreenMagic");
	m_pageElectric.m_sScreenMagic = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ScreenMagicRemark");
	m_pageElectric.m_sScreenMagicRemark = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("InvertorType");
	m_pageElectric.m_sInvertorType = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("InvertorPower");
	m_pageElectric.m_sInvertorPower = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Traction");
	m_pageParts.m_sTraction = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("SpeedGovernor");
	m_pageParts.m_sSpeedGovernor = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;


	Holder = pSet->GetCollect("Encode");
	m_pageParts.m_sEncode = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Safety");
	m_pageParts.m_sSafety = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Buffer");
	m_pageParts.m_sBuffer = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
   
	Holder = pSet->GetCollect("NonstandardCheck");
	m_pageParts.m_bNonstandardCheck = (bool)Holder;

	Holder = pSet->GetCollect("Nonstandard");
	m_pageParts.m_sNonstandardRemark = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	m_pageBasicData.UpdateDataPage(FALSE);
	m_pageCar.UpdateDataPage(FALSE);
	m_pageElectric.UpdateDataPage(FALSE);
	m_pageShaft.UpdateDataPage(FALSE);
	m_pageParts.UpdateDataPage(FALSE);
	m_pageUpholster.UpdateDataPage(FALSE);

	Holder = pSet->GetCollect("ConfigureRemarks");
	m_sRemark = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("CInputPerson");
	m_sInputPerson =  Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("CInputDate");
	COleDateTime dTemp;
	dTemp = Holder.date;
	m_sInputDate = dTemp.Format("%Y-%m-%d");

	Holder = pSet->GetCollect("CRePerson");
	m_sRePerson = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("CReDate");
	dTemp = Holder.date;
	m_sReDate = dTemp.Format("%Y-%m-%d");
}

void CItemDataInputView::EnableButton(void)
{
	if(m_iCount <= 1 )
	{
		m_cFirst.EnableWindow(FALSE);
		m_cPrevious.EnableWindow(FALSE);
		m_cNext.EnableWindow(FALSE);
		m_cLast.EnableWindow(FALSE);

	}
	else if(m_iPos==0 && m_iCount >1)
	{
		m_cFirst.EnableWindow(FALSE);
		m_cPrevious.EnableWindow(FALSE);
		m_cNext.EnableWindow(TRUE);
		m_cLast.EnableWindow(TRUE);
	}else 
		if(m_iPos == m_iCount-1 && m_iCount >1)
		{
			m_cFirst.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(TRUE);
			m_cNext.EnableWindow(FALSE);
			m_cLast.EnableWindow(FALSE);
		}
		else  if(m_iPos>0 && m_iPos<m_iCount-1)
		{
			m_cFirst.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(TRUE);
			m_cNext.EnableWindow(TRUE);
			m_cLast.EnableWindow(TRUE);
		}
}

void CItemDataInputView::RecordSearch(void)
{
	try
	{
		m_sOrderID.Trim();

		strSQL = "select * from Configuration where OrderID = '"+m_sOrderID+"'";
		theApp.ADOExecute(m_pTempSet, theApp.m_pConnect,strSQL);
		int iCount = m_pTempSet->GetRecordCount();
		if(iCount!=0)
		{
			m_pTempSet->MoveFirst();
			ReadRecord(m_pTempSet);
		}
		else
		{
			m_pageBasicData.ClearEdit();
			m_pageCar.ClearEdit();
			m_pageElectric.ClearEdit();
			m_pageParts.ClearEdit();
			m_pageShaft.ClearEdit();
			m_pageUpholster.ClearEdit();
			m_sgElevatorModel.Empty();

			m_sInputPerson = g_strUserName;
			m_sRePerson = g_strUserName;
			m_sInputDate =  m_dCurrent.Format("%Y-%m-%d");
			m_sReDate =  m_dCurrent.Format("%Y-%m-%d");
			m_sRemark.Empty();

		}
		m_pTempSet->Close();


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

void CItemDataInputView::OnBnClickedButtonDatainputSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_sID.Trim();
	m_sProjectName.Trim();
	m_sProjectNameEn.Trim();
	m_sProjectName.Replace('\"','_');
	m_sProjectNameEn.Replace('\"','_');
	m_sProjectName.Replace('\'','_');
	m_sProjectNameEn.Replace('\'','_');

	CString strSQLTemp;

	if(!m_sProjectName.IsEmpty())
		strSQLTemp += "and ProjectName like '%"+m_sProjectName+"%'";
	if(!m_sProjectNameEn.IsEmpty())
		strSQLTemp +="and ProjectNameEn like'%"+m_sProjectNameEn+"%'";

	try{

		strSQLTemp = "select ID, ProjectName,ProjectNameEn,Number from PBInformation where ID like'%"+m_sID+"%'"+strSQLTemp;
		strSQL = strSQLTemp.AllocSysString();
		theApp.ADOExecute(m_pDataSet,theApp.m_pConnect, strSQL);
		int iCount = m_pDataSet->GetRecordCount();
		m_iCount = iCount;
		if(iCount!=0)

		{
			m_pDataSet->MoveFirst();
			m_iPos = 0;
			DisplayCtrl(m_pDataSet);

			m_sDisplay.Format("%dof%d",m_iPos+1,m_iCount);

			InitOrderCtrl();
			RecordSearch();
			//          RefreshSheet();

		}
		else
		{
			m_iPos = 0;
			m_sDisplay.Format("0of0");
			AfxMessageBox("没有所要查询的记录!",MB_ICONEXCLAMATION);
			ClearEdit();
			m_pDataSet->Close();

		}

		EnableButton();

	}
	catch(_com_error &e)
	{
		CString err;
		err.Format("ADO Error: %s",(char*)e.Description());
		AfxMessageBox(err);
		m_pDataSet->Close();
		return;
	}
	catch(...)
	{
		AfxMessageBox("Unknown Error...");
		m_pDataSet->Close();
		return;
	}
	UpdateData(FALSE);   
}

void CItemDataInputView::DisplayCtrl(_RecordsetPtr& pSet)
{
	Holder = pSet->GetCollect("ID");
	m_sID= (char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ProjectName");
	m_sProjectName = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ProjectNameEn");
	m_sProjectNameEn  = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Number");
	m_iNumber = (int)Holder;
}

void CItemDataInputView::ClearEdit(void)
{
	m_sID.Empty();
	m_cOrderID.ResetContent();
	m_sOrderID.Empty();

	m_sProjectName.Empty();
	m_sProjectNameEn.Empty();
	m_iNumber=0;
	m_sDisplay.Format("0of0");
	m_sElevatorID.Empty();
	m_sInputPerson = g_strUserName;
	m_sRePerson = g_strUserName;
	m_sInputDate =  m_dCurrent.Format("%Y-%m-%d");
	m_sReDate =  m_dCurrent.Format("%Y-%m-%d");
	m_sRemark.Empty();
	m_sgElevatorModel.Empty();

	m_pageBasicData.ClearEdit();
	m_pageCar.ClearEdit();
	m_pageElectric.ClearEdit();
	m_pageShaft.ClearEdit();
	m_pageParts.ClearEdit();
	m_pageUpholster.ClearEdit();

}

void CItemDataInputView::OnCbnSelendokComboCommerceId()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str;

	try{

		int iIndex = m_cID.GetCurSel();
		if(iIndex!=LB_ERR)
		{
			m_cID.GetLBText(iIndex, str);
			m_sID = str;

			strSQL = "select ProjectName, ProjectNameEn, Number from PBInformation where ID = '"+str+"'";
			theApp.ADOExecute(m_pDataSet,theApp.m_pConnect, strSQL);
			int iCount = m_pDataSet->GetRecordCount();
			m_iCount = iCount;
			if(iCount!=0)
			{
				m_iPos = 0;
				Holder = m_pDataSet->GetCollect("ProjectName");
				str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
				if(!str.IsEmpty())
					m_sProjectName = str; 

				Holder = m_pDataSet->GetCollect("ProjectNameEn");
				str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
				if(!str.IsEmpty())
					m_sProjectNameEn = str;

				Holder = m_pDataSet->GetCollect("Number");
				m_iNumber = (int)Holder;

				InitOrderCtrl();
				RecordSearch();
			}
			else
			{
				m_iPos = -1;
				m_iCount = 0;
				m_pDataSet->Close();

			}
		}
		m_sDisplay.Format("%dof%d",m_iPos+1,m_iCount);
		EnableButton();

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


void CItemDataInputView::OnBnClickedButtonDatainputFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try{

		if(!(m_pDataSet->BOF))
		{   
			m_pDataSet->MoveFirst();
			m_iPos = 0;

			DisplayCtrl(m_pDataSet);

			m_sDisplay.Format("%dof%d",m_iPos+1,m_iCount);

			InitOrderCtrl();
			RecordSearch();
			InitOrderCtrl();
			RecordSearch();
			m_cNext.EnableWindow(TRUE);
			m_cLast.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(FALSE);
			m_cFirst.EnableWindow(FALSE);
		}
		else
		{   
			return;
		}
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
	UpdateData(FALSE);
}

void CItemDataInputView::OnBnClickedButtonDatainputPrevious()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try
	{
		if(0!=m_iPos)
		{
			m_pDataSet->MovePrevious();
			if(m_iPos>0)
				m_iPos-=1;
			else
				m_iPos = m_iPos;

			DisplayCtrl(m_pDataSet);

			m_sDisplay.Format("%dof%d",m_iPos+1,m_iCount);

			InitOrderCtrl();
			RecordSearch();
			InitOrderCtrl();
			RecordSearch();
			m_cNext.EnableWindow(TRUE);
			m_cLast.EnableWindow(TRUE);

		}
		else
		{
			m_cPrevious.EnableWindow(FALSE);
			m_cFirst.EnableWindow(FALSE);
			return;
		}
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
	UpdateData(FALSE);
}

void CItemDataInputView::OnBnClickedButtonDatainputNext()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try
	{
		if(m_iPos!=m_pDataSet->GetRecordCount()-1)
		{
			m_pDataSet->MoveNext();
			m_iPos+=1;

			DisplayCtrl(m_pDataSet);

			m_sDisplay.Format("%dof%d",m_iPos+1,m_iCount);

			InitOrderCtrl();
			RecordSearch();
			InitOrderCtrl();
			RecordSearch();
			m_cFirst.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(TRUE);
		}	
		else
		{
			m_cNext.EnableWindow(FALSE);
			m_cLast.EnableWindow(FALSE);
			return;		
		}
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
	UpdateData(FALSE);
}

void CItemDataInputView::OnBnClickedButtonDatainputLast()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try
	{
		if(!(m_pDataSet->EndOfFile))
		{   
			m_pDataSet->MoveLast();
			m_iPos = m_pDataSet->GetRecordCount()-1;

			DisplayCtrl(m_pDataSet);

			m_sDisplay.Format("%dof%d",m_iPos+1,m_iCount);

			InitOrderCtrl();
			RecordSearch();
			InitOrderCtrl();
			RecordSearch();
			m_cLast.EnableWindow(FALSE);
			m_cNext.EnableWindow(FALSE);
			m_cFirst.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(TRUE);
		}
		else
		{
			return;
		}
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
	UpdateData(FALSE);
}

void CItemDataInputView::OnCbnSelendokComboDatainputOrderid()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	UpdateData(TRUE);

	try{

		int iIndex = m_cOrderID.GetCurSel();
		if(iIndex!=LB_ERR)
		{
			m_cOrderID.GetLBText(iIndex, str);
			SetDlgItemText(IDC_COMBO_DATAINPUT_ORDERID, str);

			m_sOrderID = str;
			m_pageElectric.m_sOrderID = m_sOrderID;

			strSQL = " select ElevatorID from OrderOfProject where OrderID = '"+str+"'";
			theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
			int iCount = m_pTempSet->GetRecordCount();
			if(iCount!=0)
			{
				Holder = m_pTempSet->GetCollect("ElevatorID");
				str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
				m_sElevatorID = str;
			}
			m_pTempSet->Close();	
			if(iCount!=0)
			{
				RecordSearch();
			}
		}      
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
	UpdateData(FALSE);
}

void CItemDataInputView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(m_pDataSet->State == adStateOpen)
		m_pDataSet->Close();
	if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();
	ClearEdit();
	m_iPos = -1;
	m_iCount = 0;

	EnableButton();
	UpdateData(FALSE);
}

void CItemDataInputView::OnBnClickedButtonDatainputDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	strSQL = "select * from Configuration where OrderID = '"+m_sOrderID+"'";
	theApp.ADOExecute(m_pTempSet,theApp.m_pConnect,strSQL);
	int iCount = m_pTempSet->GetRecordCount();
	if(iCount!=0)
	{

		if(AfxMessageBox("是否确认删除此条记录?",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{
			m_pTempSet->MoveFirst();
			m_pTempSet->Delete(adAffectCurrent);
			m_pTempSet->Update();
			m_pTempSet->Close();

			m_sInputPerson = g_strUserName;
			m_sRePerson = g_strUserName;
			m_sInputDate =  m_dCurrent.Format("%Y-%m-%d");
			m_sReDate =  m_dCurrent.Format("%Y-%m-%d");
			m_sRemark.Empty();

			m_pageBasicData.ClearEdit();
			m_pageCar.ClearEdit();
			m_pageElectric.ClearEdit();
			m_pageShaft.ClearEdit();
			m_pageParts.ClearEdit();
			m_pageUpholster.ClearEdit();

			AfxMessageBox("记录已经删除!",MB_ICONINFORMATION);
		}
		else
		{
			m_pTempSet->Close();
			return;
		}

	}
	else
	{
		AfxMessageBox("没有所要删除的记录!",MB_ICONEXCLAMATION);
		m_pTempSet->Close();
		return;     
	}

	UpdateData(FALSE);
}

void CItemDataInputView::OnBnClickedButtonSamecopy()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CDataSameCopyDlg m_dlg;
	m_iCheck = 2;
	m_dlg.m_iCheck = m_iCheck;

	if(m_bCopyCh)
	{
		m_iPage = m_sheetData.GetActiveIndex();
	}
	else 
		m_iPage = -1;
	m_dlg.m_iPage = m_iPage;

	if(!m_sID.IsEmpty())
	{
		m_dlg.m_sID = m_sID;
		m_dlg.m_sProjectName = m_sProjectName;
		m_dlg.m_sProjectNameEn = m_sProjectNameEn;
	}
	if(!m_sOrderID.IsEmpty())
		m_dlg.m_sResource = m_sOrderID;
	m_dlg.DoModal();

	UpdateData(FALSE);
}

void CItemDataInputView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	if(MessageBox("确定退出系统吗?","保存提示",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	      CFormView::OnClose();
}

void CItemDataInputView::OnBnClickedCheckStandard()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString strValue;
	if(!((CButton*)GetDlgItem(IDC_CHECK_STANDARD))->GetCheck())
	{
		m_pageShaft.m_bCheck=FALSE;
		m_pageCar.m_bCheck = FALSE;
	}
	else
	{
		m_pageShaft.m_bCheck=TRUE;
		m_pageCar.m_bCheck= TRUE;
	}
	UpdateData(FALSE);

}
