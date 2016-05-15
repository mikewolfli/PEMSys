// ItemExcelView.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemExcelView.h"
#include ".\itemexcelview.h"
#include "ExcelPathDlg.h"
#include <Windows.h>
// CItemExcelView

IMPLEMENT_DYNCREATE(CItemExcelView, CFormView)

CItemExcelView::CItemExcelView()
	: CFormView(CItemExcelView::IDD)
	, m_sTemplatePath(_T(""))
	, m_sObjectPath(_T(""))
	, m_sProjectName(_T(""))
	, m_sElevatorModel(_T(""))
	, m_sRatedLoad(_T(""))
	, m_sRatedSpeed(_T(""))
	, m_bCheck(FALSE)
	, m_bCopy(FALSE)
	, m_iNum(0)
	, m_iWideJamb(0)
{
}

CItemExcelView::~CItemExcelView()
{
}

void CItemExcelView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_EXCEL_SEARCH, m_cSearch);
	DDX_Control(pDX, IDC_BUTTON_EXCEL_CANCEL, m_cCancel);
	DDX_Control(pDX, IDC_COMBO_EXCEL_MARKID, m_cMarkID);
	DDX_Control(pDX, IDC_LIST_EXCEL_ORDERLIST, m_cOrderList);
	DDX_Text(pDX, IDC_EDIT_EXCEL_PROJECTNAME, m_sProjectName);
	DDX_Text(pDX, IDC_EDIT_EXCEL_ELEVATORMODEL, m_sElevatorModel);
	DDX_Text(pDX, IDC_EDIT_EXCEL_RATEDLOAD, m_sRatedLoad);
	DDX_Text(pDX, IDC_EDIT_EXCEL_RATEDSPEED, m_sRatedSpeed);
	DDX_Check(pDX, IDC_CHECK_EXCEL_OPEN, m_bCheck);
}

BEGIN_MESSAGE_MAP(CItemExcelView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL_OUTPUT, OnBnClickedButtonExcelOutput)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL_OPEN, OnBnClickedButtonExcelOpen)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL_OPEN2, OnBnClickedButtonExcelOpen2)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL_FILEPATH, OnBnClickedButtonExcelFilepath)
	ON_CBN_SELENDOK(IDC_COMBO_EXCEL_MARKID, OnCbnSelendokComboExcelMarkid)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_EXCEL_CANCEL, OnBnClickedButtonExcelCancel)
	ON_BN_CLICKED(IDC_BUTTON_EXCEL_SEARCH, OnBnClickedButtonExcelSearch)
	ON_BN_CLICKED(IDC_CHECK_EXCEL_OPEN, OnBnClickedCheckExcelOpen)
END_MESSAGE_MAP()


// CItemExcelView 诊断

#ifdef _DEBUG
void CItemExcelView::AssertValid() const
{
	CFormView::AssertValid();
}

void CItemExcelView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

// CItemExcelView 消息处理程序

void CItemExcelView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
/*
	GetParentFrame()->RecalcLayout();
	//	 ResizeParentToFit();
	ResizeParentToFit(FALSE);
	ResizeParentToFit(TRUE);
	// TODO: 在此添加专用代码和/或调用基类                                                                                                                                                                                                                                                                                                  
	CString strTitle ;
	strTitle = "Excel输出";
	GetParentFrame()->SetWindowText(strTitle);
	// TODO: 在此添加专用代码和/或调用基类

	m_cCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_CANCEL));
	m_cSearch.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_FIND));

	UpdateData(TRUE);
	CString  FilePath;
	FilePath+=".\\Config.ini";

	CString strSection = _T("Path");
	CString strSectionKey  = _T("Template");
	char inBuf[80];
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	m_sTemplatePath = inBuf;

	strSectionKey  = _T("Object");
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	m_sObjectPath = inBuf;

	strSectionKey  = _T("OpenCheck");
	GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	CString strCheck = inBuf;
	int iCheck = atoi(strCheck);
	switch(iCheck) {
	case 0:
		m_bCheck = FALSE;
		break;
	case 1:
		m_bCheck = TRUE;
		break;
	default:
		break;
	}
	UpdateData(FALSE);

	try{
		m_pTempSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例

		if(m_pTempSet->State== adStateOpen)
			m_pTempSet->Close();
		m_cMarkID.ResetContent();
		strSQL = "select DISTINCT top 10 MarkID from MarkOfOrder Order by MarkID DESC";
		theApp.ADOExecute(m_pTempSet,strSQL);
		int iCount = m_pTempSet->GetRecordCount();
		if(iCount !=0)
		{
			m_pTempSet->MoveFirst();
			for(int i= 0 ;i<iCount;i++)
			{
				Holder = m_pTempSet->GetCollect("MarkID");
				CString str= (char*)(_bstr_t)Holder;
				m_cMarkID.AddString(str);
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
		return;
	}
	catch(...)
	{
		AfxMessageBox("Unknown Error...");
		return;
	}*/

}

void CItemExcelView::OnBnClickedButtonExcelFilepath()
{
	// TODO: 在此添加控件通知处理程序代码
	CExcelPathDlg m_Dlg;
	m_Dlg.DoModal();
}

BOOL CItemExcelView::InitOrderList(const CString str)
{
/*	CString strTemp;
	if(m_pTempSet->State== adStateOpen)
		m_pTempSet->Close();
	strSQL = "select ProjectName, Number from PBInformation where ID in (select DISTINCT ID from OrderOfProject where OrderID ='"+str+"')";
	theApp.ADOExecute(m_pTempSet,strSQL);
	int iCount = m_pTempSet->GetRecordCount();
	if(iCount!=0)
	{

		Holder = m_pTempSet->GetCollect("ProjectName");
		m_sProjectName = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
		SetDlgItemText(IDC_EDIT_EXCEL_PROJECTNAME, m_sProjectName);

		Holder = m_pTempSet->GetCollect("Number");
		m_iNum = (int)Holder;

		m_pTempSet->Close();
	}
	else
	{
		m_pTempSet->Close();
		return FALSE;
	}
	strTemp = str;
	m_cOrderList.ResetContent();
	strSQL = "select * from MarkOfOrder where MarkID = '"+strTemp+"'";
	theApp.ADOExecute(m_pTempSet, strSQL);
	iCount = m_pTempSet->GetRecordCount();
	if(iCount!=0)
	{
		m_pTempSet->MoveFirst();
		for(int i=0;i<iCount;i++)
		{
			Holder = m_pTempSet->GetCollect("OrderID");
			strTemp= (char*)(_bstr_t)Holder;
			m_cOrderList.AddString(strTemp);
			m_pTempSet->MoveNext();

		}
		m_pTempSet->Close();
	}else
	{
		m_pTempSet->Close();
		return FALSE;
	}	  
	return TRUE;*/
	//	return 0;
	return FALSE;
}

CString CItemExcelView::GetMarkID(CString str)
{
/*	CString strTemp;
	if(m_pTempSet->State== adStateOpen)
		m_pTempSet->Close();
	str.Trim();
	if(str.IsEmpty())
	{
		AfxMessageBox("订单号不能为空!",MB_ICONEXCLAMATION);
		return _T("");
	}
	CMarkIDString strMarkID(str);
	str = strMarkID.GetDataString();
	strSQL = "select * from MarkOfOrder where OrderID ='"+str+"'";
	theApp.ADOExecute(m_pTempSet, strSQL);
	int iCount = m_pTempSet->GetRecordCount();
	if(iCount!=0)
	{ 
		Holder = m_pTempSet->GetCollect("MarkID");
		strTemp = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;		
	}
	else
	{
		strTemp= _T("");
		AfxMessageBox("订单号尚未配置\n请先返回订单配置!",MB_ICONEXCLAMATION);
	}

	m_pTempSet->Close();
	return strTemp;*/
	return str;
}

void CItemExcelView::ClearEdit(void)
{

/*	m_sMarkID.Empty();
	SetDlgItemText(IDC_COMBO_EXCEL_MARKID,_T(""));
	m_sProjectName.Empty();
	m_cOrderList.ResetContent();
	m_sElevatorModel.Empty();
	m_sRatedLoad.Empty();
	m_sRatedSpeed.Empty();*/
}

void CItemExcelView::OnCbnSelendokComboExcelMarkid()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	CString str;

	try{
		int iIndex = m_cMarkID.GetCurSel();
		if(iIndex!=LB_ERR)
		{

			m_cMarkID.GetLBText(iIndex, str);
			m_sMarkID = GetMarkID(str);
			InitOrderList(m_sMarkID);

			strSQL = "select * from ProjectBasicData where MarkID ='"+m_sMarkID+"'";
			theApp.ADOExecute(m_pTempSet, strSQL);
			int iCount = m_pTempSet->GetRecordCount();
			if(iCount!= 0)
			{
				m_pTempSet->MoveFirst();
				RefreshEdit(m_pTempSet);
				m_bCopy = TRUE;
			}
			else
			{
				m_bCopy= FALSE;
				ClearEdit();
			}
			m_pTempSet->Close();
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
	UpdateData(FALSE);*/
}

void CItemExcelView::RefreshEdit(_RecordsetPtr& pSet)
{
/*	Holder = pSet->GetCollect("ElevatorModel");
	m_sElevatorModel = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("RatedLoad");
	m_sRatedLoad.Format("%d",(int)Holder);


	Holder = pSet->GetCollect("RatedSpeed");
	m_sRatedSpeed.Format("%.2f",(float)Holder);

	SetDlgItemText(IDC_COMBO_EXCEL_MARKID,m_sMarkID);*/
}

void CItemExcelView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	/*if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();
	m_pTempSet.Release();

	CFormView::OnClose();*/
}

void CItemExcelView::OnBnClickedButtonExcelCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);

	if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();
	ClearEdit();
	UpdateData(FALSE);*/
}

void CItemExcelView::OnBnClickedButtonExcelSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	GetDlgItemText(IDC_COMBO_EXCEL_MARKID,m_sMarkID);
	if(m_sMarkID.IsEmpty())
	{
		AfxMessageBox("订单号不能为空1",MB_ICONEXCLAMATION);
		return;
	}
	else  if((m_sMarkID.GetLength()<8 )|| (m_sMarkID.GetLength()>10))
	{
		AfxMessageBox("请输入完整格式的订单号,\n有效8~10位字符数字(空格不计)\n例如:05 21 0001或05210001",MB_ICONEXCLAMATION);
		return;
	}

	m_sMarkID = GetMarkID(m_sMarkID);

	if(!InitOrderList(m_sMarkID))
		return;

	strSQL  = "select * from ProjectBasicData where MarkID = '"+m_sMarkID+"'";
	theApp.ADOExecute(m_pTempSet, strSQL);
	if(m_pTempSet->GetRecordCount()!=0)
	{
		m_pTempSet->MoveFirst();
		RefreshEdit(m_pTempSet);
		m_bCopy= TRUE;
	}
	else
	{
		m_bCopy = FALSE;
		ClearEdit();
	}
	m_pTempSet->Close();
	UpdateData(FALSE);*/
}

void CItemExcelView::OnBnClickedButtonExcelOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	if(!InsertMapData())
		return;
	if(!ExcelOutput())
		return;
	UpdateData(FALSE);*/

}

void CItemExcelView::OnBnClickedButtonExcelOpen()
{
	// TODO: 在此添加控件通知处理程序代码
/*	CString strMarkID,strPath;
	if(!m_sMarkID.IsEmpty())
	   strMarkID = m_sMarkID;
	else
	   GetDlgItemText(IDC_COMBO_EXCEL_MARKID,strMarkID);
	if(strMarkID.IsEmpty())
	{
		AfxMessageBox(_T("请先选择订单号!"),MB_ICONEXCLAMATION);
		return;
	}
	strMarkID.Remove(' ');
	strPath = m_sObjectPath+strMarkID+_T(".xls");
    ShellExecute(NULL, "open", strPath, NULL, NULL, SW_SHOWNORMAL);*/
}

void CItemExcelView::OnBnClickedButtonExcelOpen2()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CString strPath;
	CString strTemplate = m_sElevatorModel;
	if(m_sMarkID.IsEmpty())
	{
		AfxMessageBox(_T("请先选择订单号!"),MB_ICONEXCLAMATION);
		return;
	}

	strTemplate.Replace("-","_");
	strPath = m_sTemplatePath+strTemplate+".xlt";
     
    ShellExecute(NULL, "open", strPath, NULL, NULL, SW_SHOWNORMAL);*/
}

BOOL CItemExcelView::InsertMapData(void)
{
	/*CString strFirst, strSecond;
	int iCount;

	try {
		if(!m_bCopy)
		{
		   GetDlgItemText(IDC_COMBO_EXCEL_MARKID,m_sMarkID);
		   if(m_sMarkID.IsEmpty())
		   {
			   AfxMessageBox("订单号不能为空!",MB_ICONEXCLAMATION);
			   return FALSE;
		   }
		   m_sMarkID = GetMarkID(m_sMarkID);

		   if(!InitOrderList(m_sMarkID))
			   return FALSE;
		}

		if(!m_eData.empty())
			m_eData.clear();
        
		strSQL = "select ExpectedDelivery from  PBInformation where ID in (select DISTINCT ID from OrderOfProject where OrderID ='"+m_sMarkID+"')";
		theApp.ADOExecute(m_pTempSet, strSQL );
		iCount = m_pTempSet->GetRecordCount();
		if(iCount != 0)
		{
			m_pTempSet->MoveFirst();
			Holder = m_pTempSet->GetCollect("ExpectedDelivery");
			strFirst = _T("ExpectedDelivery");
			COleDateTime dDate = Holder.date;
			if(dDate<= COleDateTime::GetCurrentTime())
			{
				AfxMessageBox("请先确认此订单的预计交货期!",MB_ICONEXCLAMATION);
				m_pTempSet->Close();
				return FALSE;
			}
			strSecond = dDate.Format("%Y-%m-%d");
			m_eData.insert(Str_Pair(strFirst,strSecond));
		}
		else
		{
			AfxMessageBox("此合同编号尚未添加", MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return FALSE;
		}
		m_pTempSet->Close();

		strSQL = "select * from ProjectBasicData where MarkID = '"+m_sMarkID+"'";
		theApp.ADOExecute(m_pTempSet,strSQL);
        
		iCount = m_pTempSet->GetRecordCount();
		if(iCount!= 0)
		{
			if(!m_bCopy)
			{
				RefreshEdit(m_pTempSet);
				UpdateData(FALSE);
			}

			Holder =  m_pTempSet->GetCollect("ElevatorType");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			strFirst = _T("ElevatorType");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("ElevatorModel");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			strFirst = _T("ElevatorModel");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("RatedLoad");
			strFirst = _T("RatedLoad");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("RatedSpeed");
			strFirst = _T("RatedSpeed");
			strSecond.Format("%.2f",(float)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("DragMode");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			strFirst = _T("DragMode");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("ControlMode");
			strFirst = _T("ControlMode");
			strSecond = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("ControlModeRemark");
			strFirst = _T("ControlModeRemark");
			strSecond = Holder.vt ==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("DriveMode");
			strFirst = _T("DriveMode");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("Floor");
			strFirst = _T("Floor");
			strSecond.Format("%d", (int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("Station");
			strFirst = _T("Station");
			strSecond.Format("%d", (int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("Door");
			strFirst = _T("Door");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("StopName");
			strFirst = _T("StopName");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("TractionPos");
			strFirst = _T("TractionPos");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("MRPOS");
			strFirst = _T("MRPOS");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("Through");
			strFirst = _T("Through");
			if(Holder.boolVal)
			     strSecond = _T("TRUE");
			else
			     strSecond = _T("FALSE");
			m_eData.insert(Str_Pair(strFirst,strSecond));
		}
		else
		{
			AfxMessageBox("此订单资料尚未在主要技术参数表中添加!",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return FALSE;
		}
		m_pTempSet->Close();

		strSQL = "select * from PFLoor where MarkID = '"+m_sMarkID+"'";
		theApp.ADOExecute(m_pTempSet,strSQL);
		iCount = m_pTempSet->GetRecordCount();
//		if(!m_ddDoorMaterial)
//			delete [] m_ddDoorMaterial;
//		if(!m_ddJambMaterial)
//			delete [] m_ddJambMaterial;
   

		CString str,str1,str2;
		int idNum;
		if(iCount !=0)
		{
			m_iWideJamb = 0;
			m_pTempSet->MoveFirst();

			m_ddJambMaterial[0].iNum = 0;
			m_ddDoorMaterial[0].iNum = 0;
			m_ddJambMaterial[1].iNum = 0;
			m_ddDoorMaterial[1].iNum = 0;
			for(int i = 0;i<iCount;++i)
			{
				idNum = 0;
				Holder = m_pTempSet->GetCollect("JambType");
				str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

				Holder = m_pTempSet->GetCollect("JambMaterial");
				str1 = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

				Holder = m_pTempSet->GetCollect("DoorMaterial");
				str2 = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

				Holder = m_pTempSet->GetCollect("Num");
				idNum= (int)Holder;

				if(str == _T("大门套"))
				{
					m_iWideJamb += idNum;

					if(i==0)
					{
					   m_ddDoorMaterial[0].strDoorMaterial = str2;
                       m_ddDoorMaterial[0].iNum += idNum;
					}

					if(i!=0)
					{
						if(str2 !=m_ddDoorMaterial[0].strDoorMaterial)
						{
							m_ddDoorMaterial[1].strDoorMaterial = str2;
							m_ddDoorMaterial[1].iNum +=idNum;
						}
						else
						{
							m_ddDoorMaterial[0].iNum += idNum;
						}

					}
				}
				if( str == _T("小门套"))
				{
					if(i==0)
					{
					     m_ddDoorMaterial[0].strDoorMaterial = str2;
					     m_ddDoorMaterial[0].iNum += idNum;
                     
					     m_ddJambMaterial[0].strJambMaterial = str1;
					     m_ddJambMaterial[0].iNum += idNum;		
					}
					if(i!=0)
					{
						if(str2 !=m_ddDoorMaterial[0].strDoorMaterial)
						{
							m_ddDoorMaterial[1].strDoorMaterial = str2;
							m_ddDoorMaterial[1].iNum +=idNum;
						}
						else
						{
							m_ddDoorMaterial[0].iNum += idNum;
						}

						if(str1 !=m_ddJambMaterial[0].strJambMaterial)
						{
							m_ddJambMaterial[1].strJambMaterial = str1;
							m_ddJambMaterial[1].iNum +=idNum;
						}
						else
						{
							m_ddJambMaterial[0].iNum +=idNum;
						}

					}
				}
				m_pTempSet->MoveNext();
			}

		}
		else
		{
			AfxMessageBox("此订单资料尚未添加楼层数据!",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return FALSE;
		}

		m_pTempSet->Close();
//以下调试使用
#ifdef _DEBUG
		CString d1,d2,di1,di2,j1,j2,ji1,ji2;
		d1 = m_ddDoorMaterial[0].strDoorMaterial;
		d2 = m_ddDoorMaterial[1].strDoorMaterial;
		di1.Format("%d",m_ddDoorMaterial[0].iNum);
		di2.Format("%d",m_ddDoorMaterial[1].iNum); 
		j1 = m_ddJambMaterial[0].strJambMaterial;
		j2 = m_ddJambMaterial[1].strJambMaterial;
		ji1.Format("%d",m_ddJambMaterial[0].iNum); 
		ji2.Format("%d",m_ddJambMaterial[1].iNum); 
#endif

		strSQL = "select * from PShaft where MarkID = '"+m_sMarkID+"'";
		theApp.ADOExecute(m_pTempSet, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount!=0)
		{
			Holder =  m_pTempSet->GetCollect("CarRail");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			strFirst = _T("CarRail");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CWRail");
			strFirst = _T("CWRail");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("ShaftWidth");
			strFirst = _T("ShaftWidth");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("ShaftDepth");
			strFirst = _T("ShaftDepth");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("TH");
			strFirst = _T("TH");
			strSecond.Format("%d",(long)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("OH");
			strFirst = _T("OH");
			strSecond.Format("%d",(long)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("PD");
			strFirst = _T("PD");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CounterWeight");
			strFirst = _T("CounterWeight");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CWGauge");
			strFirst = _T("CWGauge");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CounterWeightHeight");
			strFirst = _T("CounterWeightHeight");
			strSecond.Format("%d", (int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("SGPosition");
			strFirst = _T("SGPosition");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("WideJamb");
			strFirst = _T("WideJamb");
			if(Holder.boolVal)
				strSecond = _T("TRUE");
			else
				strSecond = _T("FALSE");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("WJType");
			strFirst = _T("WJType");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("JambXC");
			strFirst = _T("JambXC");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CCW");
			strFirst = _T("CCW");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CS1");
			strFirst = _T("CS1");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CS2");
			strFirst = _T("CS2");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CWS");
			strFirst = _T("CWS");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));
		}
		else 
		{
			AfxMessageBox("此订单资料尚未添加井道数据!",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return FALSE;
		}

		m_pTempSet->Close();

		strSQL = "select * from PCar where MarkID = '"+m_sMarkID+"'";
		theApp.ADOExecute(m_pTempSet, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount != 0)
		{
			Holder = m_pTempSet->GetCollect("HostControlPanel");
			strFirst = _T("HostControlPanel");
			strSecond = Holder.vt ==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("AssControlPanel");
			strFirst = _T("AssControlPanel");
			if(Holder.boolVal)
				strSecond = _T("TRUE");
			else
				strSecond = _T("FALSE");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CD");
			strFirst = _T("CD");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder= m_pTempSet->GetCollect("CW");
			strFirst = _T("CW");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CH");
			strFirst= _T("CH");
			strSecond.Format("%d", (int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("Operator");
			strFirst = _T("Operator");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));


			Holder = m_pTempSet->GetCollect("OpenType");
			strFirst = _T("OpenType");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("OffsetDir");
			strFirst = _T("OffsetDir");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			if(strSecond == _T("偏左"))
				strSecond = _T("轿门中心线相对轿厢中心线偏左");
			else if(strSecond == _T("偏右"))
				strSecond = _T("轿门中心线相对轿厢中心线偏右");
			else
				strSecond = _T("");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("Offset");
			strFirst = _T("Offset");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("DW");
			strFirst = _T("DW");
			strSecond.Format("%d",(int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("DH");
			strFirst = _T("DH");
			strSecond.Format("%d", (int)Holder);
			m_eData.insert(Str_Pair(strFirst,strSecond));
		}
		else
		{
			AfxMessageBox("此订单资料尚未添加轿厢数据!",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return FALSE;
		}
		m_pTempSet->Close();

		strSQL = "select * from PUpholster where MarkID = '"+m_sMarkID+"'";
		theApp.ADOExecute(m_pTempSet, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount!= 0)
		{
			Holder = m_pTempSet->GetCollect("Ceiling");
			strFirst = _T("Ceiling");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("FrontWall");
			strFirst = _T("FrontWall");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("SideWall");
			strFirst = _T("SideWall");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst, strSecond));

			Holder = m_pTempSet->GetCollect("RearWall");
			strFirst = _T("RearWall");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("HandRailCheck");
			strFirst = _T("HandRailCheck");
			if(Holder.boolVal)
				strSecond = _T("TRUE");
			else
				strSecond = _T("FALSE");
			m_eData.insert(Str_Pair(strFirst, strSecond));

			Holder = m_pTempSet->GetCollect("SideHandRail");
			strFirst = _T("SideHandRail");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("RearHandRail");
			strFirst = _T("RearHandRail");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("GlassType");
			strFirst = _T("GlassType");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("GlassPosition");
			strFirst = _T("GlassPosition");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CarDoor");
			strFirst = _T("CarDoor");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CarFloor");
			strFirst = _T("CarFloor");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

		}
		else
		{
			AfxMessageBox("此订单资料尚未添加轿厢装潢数据!",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return FALSE;
		}
		m_pTempSet->Close();

		strSQL = "select * from PElectric where MarkID = '"+m_sMarkID+"'";
		theApp.ADOExecute(m_pTempSet, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount!= 0)
		{
			Holder = m_pTempSet->GetCollect("Controller");
			strFirst = _T("Controller");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("DisaPanel");
			strFirst = _T("DisaPanel");
			if(Holder.boolVal)
				strSecond = _T("TRUE");
			else
				strSecond = _T("FALSE");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("PushButton");
			strFirst = _T("PushButton");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder  = m_pTempSet->GetCollect("VideoCable");
			strFirst = _T("VideoCable");
			if(Holder.boolVal)
				strSecond = _T("TRUE");
			else
				strSecond = _T("FALSE");
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CallBoardType");
			strFirst = _T("CallBoardType");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("CallBoardTypeRemark");
			strFirst = _T("CallBoardTypeRemark");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("ScreenMagic");
			strFirst = _T("ScreenMagic");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("ScreenMagicRemark");
			strFirst = _T("ScreenMagicRemark");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("InvertorType");
			strFirst = _T("InvertorType");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));

			Holder = m_pTempSet->GetCollect("InvertorPower");
			strFirst = _T("InvertorPower");
			strSecond = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			m_eData.insert(Str_Pair(strFirst,strSecond));
		}
		else
		{
			AfxMessageBox("此订单资料尚未添加电气参数!",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return FALSE;
		}
		m_pTempSet->Close();

		strSQL = "select * from Controller where MarkID = '"+m_sMarkID+"'";
		theApp.ADOExecute(m_pTempSet, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount!=0)
			m_pTempSet->MoveFirst();
		for (int iController = 0;iController<iCount ;iController++)
		{
          
			Holder = m_pTempSet->GetCollect("Function");
			strFirst =Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

            Holder = m_pTempSet->GetCollect("Check");
			if(Holder.boolVal)
				strSecond = _T("TRUE");
			else
				strSecond = _T("FALSE");
			m_eData.insert(Str_Pair(strFirst,strSecond));
			m_pTempSet->MoveNext();
		}
		if(iCount==0)
		{
			AfxMessageBox("此订单资料尚未添加控制柜功能!",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return FALSE;
		}
		m_pTempSet->Close();


		return TRUE;
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
	}*/
    return FALSE;
}

BOOL CItemExcelView::ExcelOutput(void)
{

	/*CString strTemplate;

	strTemplate = m_sElevatorModel;
	strTemplate.Replace("-","_");
	try{
		if(ExcelApp)
			ExcelApp.ReleaseDispatch();
		if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
		{ 
			AfxMessageBox("创建Excel服务失败!"); 
			exit(1); 
			return FALSE;
		}

		ExcelApp.SetVisible(FALSE);

		//用模板文件建立新文档
		CString strPath;
		strPath = m_sTemplatePath+strTemplate+".xlt";

		//得到Workbooks对象
		myBooks.AttachDispatch(ExcelApp.GetWorkbooks(),TRUE); 
		myBook.AttachDispatch(myBooks.Add(_variant_t(strPath)));

		//得到Worksheets对象
		mysheets.AttachDispatch(myBook.GetWorksheets(), TRUE);

		//写入数据
		int iWrite;
		if(m_sElevatorModel == _T("TE-E"))
			iWrite = 0;
		else if(m_sElevatorModel == _T("TE-ES"))
			iWrite = 1;
		else if(m_sElevatorModel == _T("TE-GL"))
			iWrite = 2;
		else if(m_sElevatorModel == _T("TE-GLS"))
			iWrite = 3;
		else if(m_sElevatorModel == _T("TE-MRL"))
			iWrite = 4;
		else if(m_sElevatorModel == _T("TE-MRLS"))
			iWrite = 5;
		else if(m_sElevatorModel == _T("TE-GLM"))
			iWrite = 6;
		else if(m_sElevatorModel == _T("TE-F"))
			iWrite = 7;
		else
		{
			mysheets.ReleaseDispatch();
			myBook.ReleaseDispatch();
			myBooks.ReleaseDispatch();
			ExcelApp.ReleaseDispatch();
			return FALSE;
		}

		switch(iWrite) {
   case 0:
	   WriteTEE();
	   break;
   case 1:
	   WriteTEES();
	   break;
   case 2:
	   WriteTEGL();
	   break;
   case 3:
	   WriteTEGLS();
	   break;
   case 4:
	   WriteTEMRL();
	   break;
   case 5:
	   WriteTEMRLS();
	   break;
   case 6:
	   WriteTEGLM();
	   break;
   case 7:
	   WriteTEF();
	   break;
   default:
	   break;
		}

		//保存表格
		CString strMarkID;
		strMarkID = m_sMarkID;
		strMarkID.Remove(' ');
		strPath = m_sObjectPath+strMarkID+_T(".xls");
		mysheet.SaveAs(strPath,vtMissing,vtMissing,vtMissing,vtMissing,
			vtMissing,vtMissing,vtMissing,vtMissing);

		ExcelApp.SetVisible(m_bCheck);

		if(!m_bCheck)
			ExcelApp.Quit();

		//释放对象 
		myRange.ReleaseDispatch(); 
		mysheet.ReleaseDispatch(); 
		mysheets.ReleaseDispatch(); 
		myBook.ReleaseDispatch(); 
		myBooks.ReleaseDispatch(); 
		ExcelApp.ReleaseDispatch(); 
		return TRUE;
	}
	catch (COleDispatchException * e) 
	{
		CString cStr;

		if (!e->m_strSource.IsEmpty())
			cStr = e->m_strSource + " - ";
		if (!e->m_strDescription.IsEmpty())
			cStr += e->m_strDescription;
		else
			cStr += "unknown error";

		AfxMessageBox(cStr, MB_OK, 
			(e->m_strHelpFile.IsEmpty())? 0:e->m_dwHelpContext);

		e->Delete();

		ExcelApp.Quit();
		myRange.ReleaseDispatch(); 
		mysheet.ReleaseDispatch(); 
		mysheets.ReleaseDispatch(); 
		myBook.ReleaseDispatch(); 
		myBooks.ReleaseDispatch(); 
		ExcelApp.ReleaseDispatch(); 

		return FALSE;
	}*/
    return FALSE;
}

void CItemExcelView::OnBnClickedCheckExcelOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CString strValue;
	if(((CButton*)GetDlgItem(IDC_CHECK_EXCEL_OPEN))->GetCheck())
	{
		m_bCheck = TRUE;
		strValue = _T("1");
	}
	else
	{
		m_bCheck = FALSE;
		strValue = _T("0");
	}

	char appPath[256];
	CString  FilePath;
	GetCurrentDirectory(256,appPath); //取得应用程序当前路径
	FilePath.Format("%s",appPath);
	FilePath+="\\Config.ini";

	CString strSection = _T("Path");
	CString strSectionKey  = _T("OpenCheck");

	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);*/
}

void CItemExcelView::WriteTEMRL(void)
{
	/*mysheet.AttachDispatch(mysheets.GetItem(_variant_t("配置表参数")),true);

	myRange.AttachDispatch(mysheet.GetCells(),true);

	CString str;

	str = GetMarkIDSimp();
	myRange.SetItem(_variant_t((long)1),_variant_t((long)2),_variant_t(str)); 

    str = m_sProjectName;
	myRange.SetItem(_variant_t((long)2), _variant_t((long)2),_variant_t(str));

	m_pIter = m_eData.find(_T("ExpectedDelivery"));
	str = m_pIter->second;
    myRange.SetItem(_variant_t((long)3), _variant_t((long)2), _variant_t(str));  

	str.Format("%d", m_iNum);
	myRange.SetItem(_variant_t((long)4), _variant_t((long)2), _variant_t(str));

	str = m_sRatedLoad;
	myRange.SetItem(_variant_t((long)5), _variant_t((long)2), _variant_t(str));

	str = m_sRatedSpeed;
	myRange.SetItem(_variant_t((long)6), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ElevatorType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)7), _variant_t((long)2), _variant_t(str));
    
	m_pIter = m_eData.find(_T("DragMode"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)8), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("TH"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)9), _variant_t((long)2), _variant_t(str));

    m_pIter = m_eData.find(_T("OH"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)10), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("PD"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)11), _variant_t((long)2), _variant_t(str));  

	m_pIter = m_eData.find(_T("ShaftWidth"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)12), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ShaftDepth"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)13), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ControlMode"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)14), _variant_t((long)2), _variant_t(str));   

	m_pIter = m_eData.find(_T("ControlModeRemark"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)15), _variant_t((long)2), _variant_t(str));  

	m_pIter = m_eData.find(_T("CounterWeight"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)16), _variant_t((long)2), _variant_t(str));  

    m_pIter = m_eData.find(_T("TractionPos"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)17), _variant_t((long)2), _variant_t(str));  


	m_pIter = m_eData.find(_T("OpenType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)18), _variant_t((long)2), _variant_t(str));

    m_pIter = m_eData.find(_T("Floor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)19), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Station"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)20), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Door"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)21), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("StopName"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)22), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Through"));
	if((m_pIter->second)==_T("TRUE"))
		str = _T("有");
	else if((m_pIter->second) == _T("FALSE"))
		str = _T("无");
	myRange.SetItem(_variant_t((long)23), _variant_t((long)2), _variant_t(str));

    m_pIter = m_eData.find(_T("CWGauge"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)25), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CW"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)26), _variant_t((long)2), _variant_t(str));

    m_pIter = m_eData.find(_T("CD"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)27), _variant_t((long)2), _variant_t(str));
  
	m_pIter = m_eData.find(_T("HostControlPanel"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)28), _variant_t((long)2), _variant_t(str));

    m_pIter = m_eData.find(_T("CarFloor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)1), _variant_t((long)4), _variant_t(str));

    m_pIter = m_eData.find(_T("FrontWall"));
    str = m_pIter->second;

	m_pIter = m_eData.find(_T("SideWall"));
	CString str1 = m_pIter->second;

	m_pIter = m_eData.find(_T("RearWall"));
	CString str2 = m_pIter->second;

	if(str != str1 && str != str2 )
	{
		myRange.SetItem(_variant_t((long)2), _variant_t((long)4), _variant_t(str));
		myRange.SetItem(_variant_t((long)2), _variant_t((long)5),                                                                                         _variant_t(str1));
		myRange.SetItem(_variant_t((long)2), _variant_t((long)6), _variant_t(str2));
	}
	else
		myRange.SetItem(_variant_t((long)2), _variant_t((long)4), _variant_t(str));

    m_pIter = m_eData.find(_T("Ceiling"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)3), _variant_t((long)4),_variant_t(str));

	m_pIter = m_eData.find(_T("HandRailCheck"));
	str = m_pIter->second;
	m_pIter = m_eData.find(_T("SideHandRail"));
	str1 = m_pIter->second;
	m_pIter = m_eData.find(_T("RearHandRail"));
	str2 = m_pIter->second;

	if(str == _T("FALSE"))
	{
		myRange.SetItem(_variant_t((long)4),_variant_t((long)4),_variant_t(_T("")));
		myRange.SetItem(_variant_t((long)5),_variant_t((long)4),_variant_t(_T("")));
	}
	else if(str == _T("TRUE"))
	{    
        if(!str1.IsEmpty())
		{
			if(!str2.IsEmpty())
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)4),_variant_t(_T("左,右,后三侧")));
				if(str1==str2)
				    myRange.SetItem(_variant_t((long)5),_variant_t((long)4),_variant_t(str1));
				else
				{
					myRange.SetItem(_variant_t((long)5),_variant_t((long)4),_variant_t(str1));
					myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(str2));
				}
			}
			else
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)4), _variant_t(_T("左、右两侧")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)4), _variant_t(str1));
			}  
		}
		else
		{
			if(!str2.IsEmpty())
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)4), _variant_t(_T("后侧")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)4), _variant_t(str2));

			}
			else
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)4),_variant_t(_T("")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)4),_variant_t(_T("")));
			}  
		}
	}

	m_pIter = m_eData.find(_T("GlassPosition"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)6), _variant_t((long)4), _variant_t(str));

    m_pIter = m_eData.find(_T("DW"));
	str = m_pIter->second;

	m_pIter = m_eData.find(_T("DH"));
	str1 = m_pIter->second;
	str = str +"*"+str1;
	myRange.SetItem(_variant_t((long)7), _variant_t((long)4), _variant_t(str));

	m_pIter = m_eData.find(_T("CarDoor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)8), _variant_t((long)4), _variant_t(str));
    

	m_pIter = m_eData.find(_T("CWGauge"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)14), _variant_t((long)4), _variant_t(str));

    m_pIter = m_eData.find(_T("CallBoardType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)15), _variant_t((long)4), _variant_t(str));

	m_pIter = m_eData.find(_T("JambXC"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)13), _variant_t((long)4), _variant_t(str));

	m_pIter = m_eData.find(_T("CS1"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)16), _variant_t((long)4), _variant_t(str));

	m_pIter = m_eData.find(_T("CS2"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)17), _variant_t((long)4), _variant_t(str));

	m_pIter = m_eData.find(_T("CWS"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)18), _variant_t((long)4), _variant_t(str));

    m_pIter = m_eData.find(_T("ScreenMagic"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)21), _variant_t((long)4), _variant_t(str));

    m_pIter = m_eData.find(_T("ScreenMagicRemark"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)22), _variant_t((long)4), _variant_t(str));

	m_pIter = m_eData.find(_T("CCW"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)23), _variant_t((long)4), _variant_t(str));

    m_pIter = m_eData.find(_T("VideoCable"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)2), _variant_t((long)7), _variant_t(str));

	m_pIter = m_eData.find(_T("OffsetDir"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)24), _variant_t((long)4), _variant_t(str));

	if(m_ddDoorMaterial)
	{
        myRange.SetItem(_variant_t((long)9), _variant_t((long)4), _variant_t(m_ddDoorMaterial[0].strDoorMaterial));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)4), _variant_t(m_ddDoorMaterial[1].strDoorMaterial));
		myRange.SetItem(_variant_t((long)9), _variant_t((long)6), _variant_t(m_ddDoorMaterial[0].iNum));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)6), _variant_t(m_ddDoorMaterial[1].iNum));
	}
	else
	{
		myRange.SetItem(_variant_t((long)9), _variant_t((long)4), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)4), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)9), _variant_t((long)6), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)6), _variant_t(_T("")));
	}

	if(m_ddJambMaterial)
	{
		myRange.SetItem(_variant_t((long)11), _variant_t((long)4), _variant_t(m_ddJambMaterial[0].strJambMaterial));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)4), _variant_t(m_ddJambMaterial[1].strJambMaterial));
		myRange.SetItem(_variant_t((long)11), _variant_t((long)6), _variant_t(m_ddJambMaterial[0].iNum));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)6), _variant_t(m_ddJambMaterial[1].iNum));
	}
	else
	{
		myRange.SetItem(_variant_t((long)11), _variant_t((long)4), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)4), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)11), _variant_t((long)6), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)6), _variant_t(_T("")));
	}

	myRange.SetItem(_variant_t((long)13), _variant_t((long)6), _variant_t(m_iWideJamb));
	myRange.SetItem(_variant_t((long)3), _variant_t((long)7), _variant_t(g_strUserName));

	m_pIter= m_eData.find(_T("FEO"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)2), _variant_t((long)26), _variant_t(str));

	m_pIter= m_eData.find(_T("TELES"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)5), _variant_t((long)26), _variant_t(str));

	m_pIter= m_eData.find(_T("VIPF"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)8), _variant_t((long)26), _variant_t(str));

	m_pIter= m_eData.find(_T("VAD"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)3), _variant_t((long)26), _variant_t(str));

	m_pIter= m_eData.find(_T("ICCP"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)4), _variant_t((long)26), _variant_t(str));

	m_pIter= m_eData.find(_T("ANUS"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)9), _variant_t((long)26), _variant_t(str));*/
}

void CItemExcelView::WriteTEE(void)
{
	/*mysheet.AttachDispatch(mysheets.GetItem(_variant_t("配置表参数")),true);

	myRange.AttachDispatch(mysheet.GetCells(),true);

	CString str;

	str = GetMarkIDSimp();
	myRange.SetItem(_variant_t((long)1),_variant_t((long)2),_variant_t(str)); 

	str = m_sProjectName;
	myRange.SetItem(_variant_t((long)2), _variant_t((long)2),_variant_t(str));

	m_pIter = m_eData.find(_T("ExpectedDelivery"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)3), _variant_t((long)2), _variant_t(str));  

	str.Format("%d", m_iNum);
	myRange.SetItem(_variant_t((long)4), _variant_t((long)2), _variant_t(str));

	str = m_sRatedLoad;
	myRange.SetItem(_variant_t((long)5), _variant_t((long)2), _variant_t(str));

	str = m_sRatedSpeed;
	myRange.SetItem(_variant_t((long)6), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ElevatorType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)7), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("DragMode"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)8), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("TH"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)9), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("OH"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)10), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("PD"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)11), _variant_t((long)2), _variant_t(str));  

	m_pIter = m_eData.find(_T("ShaftWidth"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)12), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ShaftDepth"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)13), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ControlMode"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)14), _variant_t((long)2), _variant_t(str));   

	m_pIter = m_eData.find(_T("ControlModeRemark"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)15), _variant_t((long)2), _variant_t(str));  

	m_pIter = m_eData.find(_T("CounterWeight"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)16), _variant_t((long)2), _variant_t(str));  

	m_pIter = m_eData.find(_T("MRPOS"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)17), _variant_t((long)2), _variant_t(str));  


	m_pIter = m_eData.find(_T("OpenType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)18), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Floor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)19), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Station"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)20), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Door"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)21), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("StopName"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)22), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Through"));
	if((m_pIter->second)==_T("TRUE"))
		str = _T("有");
	else if((m_pIter->second) == _T("FALSE"))
		str = _T("无");
	myRange.SetItem(_variant_t((long)23), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CWGauge"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)25), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CW"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)26), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CD"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)27), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("HostControlPanel"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)28), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CarFloor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)1), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("FrontWall"));
	str = m_pIter->second;

	m_pIter = m_eData.find(_T("SideWall"));
	CString str1 = m_pIter->second;

	m_pIter = m_eData.find(_T("RearWall"));
	CString str2 = m_pIter->second;

	if(str != str1 && str != str2 )
	{
		myRange.SetItem(_variant_t((long)2), _variant_t((long)5), _variant_t(str));
		myRange.SetItem(_variant_t((long)2), _variant_t((long)6), _variant_t(str1));
		myRange.SetItem(_variant_t((long)2), _variant_t((long)7), _variant_t(str2));
	}
	else
		myRange.SetItem(_variant_t((long)2), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("Ceiling"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)3), _variant_t((long)5),_variant_t(str));

	m_pIter = m_eData.find(_T("HandRailCheck"));
	str = m_pIter->second;
	m_pIter = m_eData.find(_T("SideHandRail"));
	str1 = m_pIter->second;
	m_pIter = m_eData.find(_T("RearHandRail"));
	str2 = m_pIter->second;

	if(str == _T("FALSE"))
	{
		myRange.SetItem(_variant_t((long)4),_variant_t((long)5),_variant_t(_T("")));
		myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(_T("")));
	}
	else if(str == _T("TRUE"))
	{    
		if(!str1.IsEmpty())
		{
			if(!str2.IsEmpty())
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)5),_variant_t(_T("左,右,后三侧")));
				if(str1==str2)
					myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(str1));
				else
				{
					myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(str1));
					myRange.SetItem(_variant_t((long)5),_variant_t((long)6),_variant_t(str2));
				}
			}
			else
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)5), _variant_t(_T("左、右两侧")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)5), _variant_t(str1));
			}  
		}
		else
		{
			if(!str2.IsEmpty())
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)5), _variant_t(_T("后侧")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)5), _variant_t(str2));

			}
			else
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)5),_variant_t(_T("")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(_T("")));
			}  
		}
	}

	m_pIter = m_eData.find(_T("GlassPosition"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)6), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("DW"));
	str = m_pIter->second;

	m_pIter = m_eData.find(_T("DH"));
	str1 = m_pIter->second;
	str = str +"*"+str1;
	myRange.SetItem(_variant_t((long)7), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CarDoor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)8), _variant_t((long)5), _variant_t(str));


	m_pIter = m_eData.find(_T("CWGauge"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)14), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CallBoardType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)15), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("JambXC"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)13), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CS1"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)16), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CS2"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)17), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CWS"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)18), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("ScreenMagic"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)21), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("ScreenMagicRemark"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)22), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CCW"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)23), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("VideoCable"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)2), _variant_t((long)8), _variant_t(str));

	if(m_ddDoorMaterial)
	{
		myRange.SetItem(_variant_t((long)9), _variant_t((long)5), _variant_t(m_ddDoorMaterial[0].strDoorMaterial));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)5), _variant_t(m_ddDoorMaterial[1].strDoorMaterial));
		myRange.SetItem(_variant_t((long)9), _variant_t((long)7), _variant_t(m_ddDoorMaterial[0].iNum));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)7), _variant_t(m_ddDoorMaterial[1].iNum));
	}
	else
	{
		myRange.SetItem(_variant_t((long)9), _variant_t((long)5), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)5), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)9), _variant_t((long)7), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)7), _variant_t(_T("")));
	}

	if(m_ddJambMaterial)
	{
		myRange.SetItem(_variant_t((long)11), _variant_t((long)5), _variant_t(m_ddJambMaterial[0].strJambMaterial));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)5), _variant_t(m_ddJambMaterial[1].strJambMaterial));
		myRange.SetItem(_variant_t((long)11), _variant_t((long)7), _variant_t(m_ddJambMaterial[0].iNum));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)7), _variant_t(m_ddJambMaterial[1].iNum));
	}
	else
	{
		myRange.SetItem(_variant_t((long)11), _variant_t((long)5), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)5), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)11), _variant_t((long)7), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)7), _variant_t(_T("")));
	}

	myRange.SetItem(_variant_t((long)13), _variant_t((long)7), _variant_t(m_iWideJamb));
	myRange.SetItem(_variant_t((long)3), _variant_t((long)8), _variant_t(g_strUserName));

	m_pIter= m_eData.find(_T("FERSF"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)38), _variant_t((long)2), _variant_t(str));*/

}

void CItemExcelView::WriteTEES(void)
{
	/*mysheet.AttachDispatch(mysheets.GetItem(_variant_t("配置表参数")),true);

	myRange.AttachDispatch(mysheet.GetCells(),true);

	CString str;

	str = GetMarkIDSimp();
	myRange.SetItem(_variant_t((long)1),_variant_t((long)2),_variant_t(str)); 

	str = m_sProjectName;
	myRange.SetItem(_variant_t((long)2), _variant_t((long)2),_variant_t(str));

	m_pIter = m_eData.find(_T("ExpectedDelivery"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)3), _variant_t((long)2), _variant_t(str));  

	str.Format("%d", m_iNum);
	myRange.SetItem(_variant_t((long)4), _variant_t((long)2), _variant_t(str));

	str = m_sRatedLoad;
	myRange.SetItem(_variant_t((long)5), _variant_t((long)2), _variant_t(str));

	str = m_sRatedSpeed;
	myRange.SetItem(_variant_t((long)6), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ElevatorType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)7), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("DragMode"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)8), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("TH"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)9), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("OH"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)10), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("PD"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)11), _variant_t((long)2), _variant_t(str));  

	m_pIter = m_eData.find(_T("ShaftWidth"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)12), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ShaftDepth"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)13), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("ControlMode"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)14), _variant_t((long)2), _variant_t(str));   

	m_pIter = m_eData.find(_T("ControlModeRemark"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)15), _variant_t((long)2), _variant_t(str));  

	m_pIter = m_eData.find(_T("CounterWeight"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)16), _variant_t((long)2), _variant_t(str));  

	m_pIter = m_eData.find(_T("MRPOS"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)17), _variant_t((long)2), _variant_t(str));  


	m_pIter = m_eData.find(_T("OpenType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)18), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Floor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)19), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Station"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)20), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Door"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)21), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("StopName"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)22), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("Through"));
	if((m_pIter->second)==_T("TRUE"))
		str = _T("有");
	else if((m_pIter->second) == _T("FALSE"))
		str = _T("无");
	myRange.SetItem(_variant_t((long)23), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CWGauge"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)25), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CW"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)26), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CD"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)27), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("HostControlPanel"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)28), _variant_t((long)2), _variant_t(str));

	m_pIter = m_eData.find(_T("CarFloor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)1), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("FrontWall"));
	str = m_pIter->second;

	m_pIter = m_eData.find(_T("SideWall"));
	CString str1 = m_pIter->second;

	m_pIter = m_eData.find(_T("RearWall"));
	CString str2 = m_pIter->second;

	if(str != str1 && str != str2 )
	{
		myRange.SetItem(_variant_t((long)2), _variant_t((long)5), _variant_t(str));
		myRange.SetItem(_variant_t((long)2), _variant_t((long)6), _variant_t(str1));
		myRange.SetItem(_variant_t((long)2), _variant_t((long)7), _variant_t(str2));
	}
	else
		myRange.SetItem(_variant_t((long)2), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("Ceiling"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)3), _variant_t((long)5),_variant_t(str));

	m_pIter = m_eData.find(_T("HandRailCheck"));
	str = m_pIter->second;
	m_pIter = m_eData.find(_T("SideHandRail"));
	str1 = m_pIter->second;
	m_pIter = m_eData.find(_T("RearHandRail"));
	str2 = m_pIter->second;

	if(str == _T("FALSE"))
	{
		myRange.SetItem(_variant_t((long)4),_variant_t((long)5),_variant_t(_T("")));
		myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(_T("")));
	}
	else if(str == _T("TRUE"))
	{    
		if(!str1.IsEmpty())
		{
			if(!str2.IsEmpty())
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)5),_variant_t(_T("左,右,后三侧")));
				if(str1==str2)
					myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(str1));
				else
				{
					myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(str1));
					myRange.SetItem(_variant_t((long)5),_variant_t((long)6),_variant_t(str2));
				}
			}
			else
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)5), _variant_t(_T("左、右两侧")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)5), _variant_t(str1));
			}  
		}
		else
		{
			if(!str2.IsEmpty())
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)5), _variant_t(_T("后侧")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)5), _variant_t(str2));

			}
			else
			{
				myRange.SetItem(_variant_t((long)4),_variant_t((long)5),_variant_t(_T("")));
				myRange.SetItem(_variant_t((long)5),_variant_t((long)5),_variant_t(_T("")));
			}  
		}
	}

	m_pIter = m_eData.find(_T("GlassPosition"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)6), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("DW"));
	str = m_pIter->second;

	m_pIter = m_eData.find(_T("DH"));
	str1 = m_pIter->second;
	str = str +"*"+str1;
	myRange.SetItem(_variant_t((long)7), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CarDoor"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)8), _variant_t((long)5), _variant_t(str));


	m_pIter = m_eData.find(_T("CWGauge"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)14), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CallBoardType"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)15), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("JambXC"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)13), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CS1"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)16), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CS2"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)17), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CWS"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)18), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("CH"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)21), _variant_t((long)5), _variant_t(str));

	m_pIter = m_eData.find(_T("DH"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)21), _variant_t((long)7), _variant_t(str));

	m_pIter = m_eData.find(_T("VideoCable"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)2), _variant_t((long)8), _variant_t(str));

	if(m_ddDoorMaterial)
	{
		myRange.SetItem(_variant_t((long)9), _variant_t((long)5), _variant_t(m_ddDoorMaterial[0].strDoorMaterial));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)5), _variant_t(m_ddDoorMaterial[1].strDoorMaterial));
		myRange.SetItem(_variant_t((long)9), _variant_t((long)7), _variant_t(m_ddDoorMaterial[0].iNum));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)7), _variant_t(m_ddDoorMaterial[1].iNum));
	}
	else
	{
		myRange.SetItem(_variant_t((long)9), _variant_t((long)5), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)5), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)9), _variant_t((long)7), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)10), _variant_t((long)7), _variant_t(_T("")));
	}

	if(m_ddJambMaterial)
	{
		myRange.SetItem(_variant_t((long)11), _variant_t((long)5), _variant_t(m_ddJambMaterial[0].strJambMaterial));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)5), _variant_t(m_ddJambMaterial[1].strJambMaterial));
		myRange.SetItem(_variant_t((long)11), _variant_t((long)7), _variant_t(m_ddJambMaterial[0].iNum));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)7), _variant_t(m_ddJambMaterial[1].iNum));
	}
	else
	{
		myRange.SetItem(_variant_t((long)11), _variant_t((long)5), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)5), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)11), _variant_t((long)7), _variant_t(_T("")));
		myRange.SetItem(_variant_t((long)12), _variant_t((long)7), _variant_t(_T("")));
	}

	myRange.SetItem(_variant_t((long)13), _variant_t((long)7), _variant_t(m_iWideJamb));
	myRange.SetItem(_variant_t((long)3), _variant_t((long)8), _variant_t(g_strUserName));

    m_pIter= m_eData.find(_T("FERSF"));
	str = m_pIter->second;
	myRange.SetItem(_variant_t((long)38), _variant_t((long)2), _variant_t(str));*/
}

void CItemExcelView::WriteTEGL(void)
{
}

void CItemExcelView::WriteTEGLS(void)
{
}

void CItemExcelView::WriteTEMRLS(void)
{
}
