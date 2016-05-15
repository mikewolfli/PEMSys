// ItemCommerceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemCommerceDlg.h"
#include ".\itemcommercedlg.h"
#include "DataSameCopyDlg.h"


// CItemCommerceDlg 对话框
extern CString g_strUserID;
extern CString g_strAuthor;
IMPLEMENT_DYNAMIC(CItemCommerceDlg, CDialog)
CItemCommerceDlg::CItemCommerceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CItemCommerceDlg::IDD, pParent)
	, m_sID(_T(""))
	, m_sProjectName(_T(""))
	, m_sProjectNameEN(_T(""))
	, m_iNumber(0)
	, m_sOrderID(_T(""))
	, m_sELevatorID(_T(""))
	, m_sDisplay(_T("0of0"))
	, m_iCount(1)
	, m_iPos(0)
	, m_sInputPerson(_T(""))
	, m_sInputDate(_T(""))
	, m_sRePerson(_T(""))
	, m_sReDate(_T(""))
	, m_dCurrent(COleDateTime::GetCurrentTime())
	, m_bSave(FALSE)
	, m_sRemarks(_T(""))
	, m_bCopy(FALSE)
	, m_ssDeliveryProgramme(_T(""))
	, m_iCheck(0)
	, m_bCheck(TRUE)
	, m_iPage(0)
	, m_iCurrency(0)
{
}

CItemCommerceDlg::~CItemCommerceDlg()
{

}

void CItemCommerceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO_COMMERCE_ID, m_sID);
	DDX_Control(pDX, IDC_COMBO_COMMERCE_ID, m_cID);
	DDX_Text(pDX, IDC_EDIT_COMMERCE_PROJECTNAME, m_sProjectName);
	DDX_Text(pDX, IDC_COMMERCE_EDIT_CONTRACTEN, m_sProjectNameEN);
	DDX_Text(pDX, IDC_COMMERCE_EDIT_COMMERCE_NUM, m_iNumber);
	DDX_Control(pDX, IDC_COMBO_COMMERCE_ORDERID, m_cOrderID);
	DDX_CBString(pDX, IDC_COMBO_COMMERCE_ORDERID, m_sOrderID);
	DDX_Text(pDX, IDC_EDIT_COMMERCE_ELEVATORID, m_sELevatorID);
	DDX_Control(pDX, IDC_BUTTON_COMMERCE_FIRST, m_cFirst);
	DDX_Control(pDX, IDC_BUTTON_COMMERCE_PREVIOUS, m_cPrevious);
	DDX_Control(pDX, IDC_BUTTON_COMMERCE_NEXT, m_cNext);
	DDX_Control(pDX, IDC_BUTTON_COMMDERCE_LAST, m_cLast);
	DDX_Control(pDX, IDOK, m_cSave);
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	DDX_Control(pDX, IDC_BUTTON_COMMERCE_DELETE, m_cDelete);
	DDX_Text(pDX, IDC_EDIT_COMMERCE_DISPLAY, m_sDisplay);
	DDX_Control(pDX, IDC_BUTTON_COMMERCE_BACK, m_cBack);
	DDX_Text(pDX, IDC_EDIT_COMMERCE_INPUTPERSON, m_sInputPerson);
	DDX_Text(pDX, IDC_EDIT_COMMERCE_INPUTDATE, m_sInputDate);
	DDX_Text(pDX, IDC_EDIT_COMMERCE_REPERSON, m_sRePerson);
	DDX_Text(pDX, IDC_EDIT_COMMERCE_REDATE, m_sReDate);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_sRemarks);
	DDX_Control(pDX, IDC_BUTTON_SAMECOPY, m_cSameCopy);
	DDX_Check(pDX, IDC_CHECK_COPY, m_bCheck);
}


BEGIN_MESSAGE_MAP(CItemCommerceDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_COMMERCE_BACK, OnBnClickedButtonCommerceBack)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELENDOK(IDC_COMBO_COMMERCE_ORDERID, OnCbnSelendokComboCommerceOrderid)
	ON_CBN_SELENDOK(IDC_COMBO_COMMERCE_ID, OnCbnSelendokComboCommerceId)
	ON_BN_CLICKED(IDC_BUTTON_COMMERCE_SEARCH, OnBnClickedButtonCommerceSearch)
	ON_BN_CLICKED(IDC_BUTTON_COMMERCE_FIRST, OnBnClickedButtonCommerceFirst)
	ON_BN_CLICKED(IDC_BUTTON_COMMERCE_PREVIOUS, OnBnClickedButtonCommercePrevious)
	ON_BN_CLICKED(IDC_BUTTON_COMMERCE_NEXT, OnBnClickedButtonCommerceNext)
	ON_BN_CLICKED(IDC_BUTTON_COMMDERCE_LAST, OnBnClickedButtonCommderceLast)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_COMMERCE_DELETE, OnBnClickedButtonCommerceDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAMECOPY, OnBnClickedButtonSamecopy)
END_MESSAGE_MAP()


// CItemCommerceDlg 消息处理程序

BOOL CItemCommerceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
 	m_cDelete.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DELETE));
	m_cFirst.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_FIRST));
	m_cPrevious.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_PREVIOUS));
	m_cNext.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_NEXT));
	m_cLast.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LAST));
	m_cSave.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_SAVE));
	m_cCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_CANCEL));
	m_cBack.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_EXIT));

	((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);

	m_sheetData.AddPage(&m_pagePrice);
	m_sheetData.AddPage(&m_pagePayment);
	m_sheetData.AddPage(&m_pageCFollowup);
	m_sheetData.AddPage(&m_pageProduction);
	m_sheetData.AddPage(&m_pageDelivery);

	m_sheetData.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);

	RECT rect;
	m_sheetData.GetWindowRect(&rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	m_sheetData.SetWindowPos(NULL, 0, 135, 330,195, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	m_sheetData.SetActivePage(&m_pagePayment);
	m_sheetData.SetActivePage(&m_pageCFollowup);
	m_sheetData.SetActivePage(&m_pageProduction);
	m_sheetData.SetActivePage(&m_pageDelivery);
	m_sheetData.SetActivePage(&m_pagePrice);

	UpdateData(TRUE);
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
//		m_pTempSet->Close();



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

	if(!m_sID.IsEmpty())
	{
		InitOrderCtrl();            
	}	
	   
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CItemCommerceDlg::PreTranslateMessage(MSG* pMsg)
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
	return CDialog::PreTranslateMessage(pMsg);
}

void CItemCommerceDlg::EnableButton(void)
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
//void CItemCommerceDlg::OnCancel()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//
////	CDialog::OnCancel();
//}

void CItemCommerceDlg::OnBnClickedButtonCommerceBack()
{
	OnClose();
	// TODO: 在此添加控件通知处理程序代码
}

void CItemCommerceDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

	DestroyWindow();
//	CDialog::OnClose();
}

void CItemCommerceDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
//	OnCancel();
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

void CItemCommerceDlg::InitOrderCtrl(void)
{
	m_cOrderID.ResetContent();
	strSQL = "select  OrderID, ElevatorID from OrderOfProject where ID = '"+m_sID+"' and Status = FALSE";
	theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
	int iCount = m_pTempSet->GetRecordCount();
	if(iCount!=0)
	{
		CString str;
		m_pTempSet->MoveFirst();
		Holder = m_pTempSet->GetCollect("OrderID");
		str = (char*)(_bstr_t)Holder;
		m_sOrderID =str;
//		SetDlgItemText(IDC_COMBO_COMMERCE_ORDERID, m_sOrderID);
		
		m_cOrderID.AddString(str);

		Holder = m_pTempSet->GetCollect("ElevatorID");
		str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
		m_sELevatorID = str;
//		SetDlgItemText(IDC_EDIT_COMMERCE_ELEVATORID, m_sELevatorID);

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
		m_sELevatorID.Empty();
        m_pageCFollowup.ClearEdit();
		m_pagePrice.ClearEdit();
        m_pagePayment.ClearEdit();
		m_pageProduction.ClearEdit();
		m_pageDelivery.ClearEdit();
	}
	
	
	m_pTempSet->Close();

}

void CItemCommerceDlg::OnCbnSelendokComboCommerceOrderid()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	UpdateData(TRUE);

	try{

		int iIndex = m_cOrderID.GetCurSel();
		if(iIndex!=LB_ERR)
		{
			m_cOrderID.GetLBText(iIndex, str);
			SetDlgItemText(IDC_COMBO_COMMERCE_ORDERID, str);
            
			strSQL = " select ElevatorID from OrderOfProject where OrderID = '"+str+"'";
			theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
			int iCount = m_pTempSet->GetRecordCount();
			if(iCount!=0)
			{
				Holder = m_pTempSet->GetCollect("ElevatorID");
				str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
				m_sELevatorID = str;
	//			if(!str.IsEmpty())
		//		   SetDlgItemText(IDC_EDIT_COMMERCE_ELEVATORID, "L"+str);
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

void CItemCommerceDlg::OnCbnSelendokComboCommerceId()
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
					m_sProjectNameEN = str;

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

void CItemCommerceDlg::ClearEdit(void)
{
    m_sID.Empty();
	m_cOrderID.ResetContent();
	m_sOrderID.Empty();

	m_sProjectName.Empty();
	m_sProjectNameEN.Empty();
	m_iNumber=0;
	m_sDisplay.Format("0of0");
	m_sELevatorID.Empty();
	m_sInputPerson = g_strUserName;
	m_sRePerson = g_strUserName;
	m_sInputDate =  m_dCurrent.Format("%Y-%m-%d");
	m_sReDate =  m_dCurrent.Format("%Y-%m-%d");
    m_sRemarks.Empty();
	m_iCurrency=0;
	((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);

    m_pageCFollowup.ClearEdit();
	m_pagePayment.ClearEdit();
	m_pagePrice.ClearEdit();
	m_pageProduction.ClearEdit();
	m_pageDelivery.ClearEdit();
}

void CItemCommerceDlg::OnBnClickedButtonCommerceSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_sID.Trim();
	m_sProjectName.Trim();
	m_sProjectNameEN.Trim();
    m_sProjectName.Replace('\'','_');
	m_sProjectNameEN.Replace('\'','_');
	m_sProjectName.Replace('\"','_');
	m_sProjectNameEN.Replace('\"','_');

    CString strSQLTemp;

	if(!m_sProjectName.IsEmpty())
		strSQLTemp += "and ProjectName like '%"+m_sProjectName+"%'";
	if(!m_sProjectNameEN.IsEmpty())
		strSQLTemp +="and ProjectNameEn like'%"+m_sProjectNameEN+"%'";

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

void CItemCommerceDlg::DisplayCtrl(_RecordsetPtr& pSet)
{
	Holder = pSet->GetCollect("ID");
	m_sID= (char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ProjectName");
	m_sProjectName = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ProjectNameEn");
	m_sProjectNameEN  = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Number");
	m_iNumber = (int)Holder;
}

void CItemCommerceDlg::OnBnClickedButtonCommerceFirst()
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

void CItemCommerceDlg::OnBnClickedButtonCommercePrevious()
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

void CItemCommerceDlg::OnBnClickedButtonCommerceNext()
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

void CItemCommerceDlg::OnBnClickedButtonCommderceLast()
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

void CItemCommerceDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//	OnOK();
	UpdateData(TRUE);
	try{

		m_sOrderID.Remove(' ');
		if(m_sOrderID.IsEmpty())
		{
			AfxMessageBox("订单号不能为空!",MB_ICONEXCLAMATION);
			return;
		}

	    if(((CButton*)GetDlgItem(IDC_RADIO0))->GetCheck())
			m_iCurrency=0;
		else if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
			m_iCurrency=1;

		CString str1  = m_sOrderID.Left(2);
		int i=m_sOrderID.GetLength();
		CString str2 = m_sOrderID.Mid(2,i-6);
		m_sOrderID = str1+" "+str2+" "+m_sOrderID.Right(4);

		strSQL = "select * from Delivery where OrderID = '"+m_sOrderID+"'";
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
		strSQL = "select * from Delivery where PurchaseReturn Is not Null";
		theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
		int iCount = m_pTempSet->GetRecordCount();
		BOOL btemp = TRUE;
		if(iCount != 0)
		{
			m_pTempSet->MoveFirst();
			for(int i=0;i<iCount; i++)
			{
              m_pTempSet->Fields->GetItem("PurchaseReturnCheck")->PutValue((_variant_t)btemp);
			  m_pTempSet->Update();
			  m_pTempSet->MoveNext();
			}
		}
        
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

void CItemCommerceDlg::OnBnClickedButtonCommerceDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	strSQL = "select * from Delivery where OrderID = '"+m_sOrderID+"'";
	theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
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
			m_sRemarks.Empty();

 //			m_pageCFollowup.ClearEdit();
//			m_pageProDelivery.ClearEdit();
//			m_pagePPayment.ClearEdit();

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

void CItemCommerceDlg::UpdateRecord(_RecordsetPtr& pSet)
{

    m_pageCFollowup.UpdateDataPage(TRUE);
	m_pagePayment.UpdateDataPage(TRUE);
	m_pagePrice.UpdateDataPage(TRUE);
	m_pageProduction.UpdateDataPage(TRUE);
	m_pageDelivery.UpdateDataPage(TRUE);

	pSet->Fields->GetItem("OrderID")->PutValue(m_sOrderID.AllocSysString());
	pSet->Fields->GetItem("Currency")->PutValue((_variant_t)m_iCurrency);

	if(g_strAuthor.Mid(0,1)=="1"|| g_tUserType>=4)
	{	
		pSet->Fields->GetItem("Amount")->PutValue((_variant_t)m_pagePrice.m_dbAmount);
		pSet->Fields->GetItem("MaterialAmount")->PutValue((_variant_t)m_pagePrice.m_dbMaterialAmount);
		pSet->Fields->GetItem("FreightInsurance")->PutValue((_variant_t)m_pagePrice.m_dbFreightInsurance);
	}

    if(g_strAuthor.Mid(1,1)=="1" || g_tUserType>=4)
	{
		pSet->Fields->GetItem("Discount")->PutValue((_variant_t)m_pagePayment.m_dbDiscount);
		pSet->Fields->GetItem("InternalPrice")->PutValue((_variant_t)m_pagePayment.m_dbInternalPrice);
		pSet->Fields->GetItem("ActualGetFreightInsurance")->PutValue((_variant_t)m_pagePayment.m_dbAGetFreightInsurance);
        if(m_pagePayment.m_bPORelease)
		  pSet->Fields->GetItem("POReleaseDate")->PutValue((_variant_t)m_pagePayment.m_dPORelease);
		else if(!m_bSave)
          pSet->Fields->GetItem("POReleaseDate")->PutValue(VarTemp);

		if(m_pagePayment.m_bPOReturn)
		  pSet->Fields->GetItem("POReturnDate")->PutValue((_variant_t)m_pagePayment.m_dPOReturn);  
		else if(!m_bSave)
			pSet->Fields->GetItem("POReturnDate")->PutValue(VarTemp); 


	}

    if(g_strAuthor.Mid(2,1)=="1" || g_tUserType>=4)
	{
		if(m_pageCFollowup.m_bGADReceived)
		   pSet->Fields->GetItem("GADReceived")->PutValue((_variant_t)m_pageCFollowup.m_dGADReceived);
		else if(!m_bSave)
           pSet->Fields->GetItem("GADReceived")->PutValue(VarTemp);

		if(m_pageCFollowup.m_bLatestAmend)
		   pSet->Fields->GetItem("TheLatestAmendment")->PutValue((_variant_t)m_pageCFollowup.m_dLatestAmend);
		else if(!m_bSave)
            pSet->Fields->GetItem("TheLatestAmendment")->PutValue(VarTemp);

		pSet->Fields->GetItem("AmendmentRemark")->PutValue(m_pageCFollowup.m_sAmendRemark.AllocSysString());
		if(m_pageCFollowup.m_bCSRelease)
		   pSet->Fields->GetItem("ComfirmationSheetRelease")->PutValue((_variant_t)m_pageCFollowup.m_dCSRelease);
		else if(!m_bSave)
           pSet->Fields->GetItem("ComfirmationSheetRelease")->PutValue(VarTemp);

		if(m_pageCFollowup.m_bCSReply)
		{
           pSet->Fields->GetItem("ComfirmationSheetReply")->PutValue((_variant_t)m_pageCFollowup.m_dCSReply);
		   pSet->Fields->GetItem("ReplyRemark")->PutValue(m_pageCFollowup.m_sReplyRemark.AllocSysString());
		}
		else if(!m_bSave)
            pSet->Fields->GetItem("ComfirmationSheetReply")->PutValue(VarTemp);

		if(m_pageCFollowup.m_bACompleteDate)
		   pSet->Fields->GetItem("AssessmentCompleteDate")->PutValue((_variant_t)m_pageCFollowup.m_dACompleteDate);
		else if(!m_bSave)
           pSet->Fields->GetItem("AssessmentCompleteDate")->PutValue(VarTemp);
	}
    if(g_strAuthor.Mid(3,1)=="1" || g_tUserType>=4)
	{

		if(m_pageProduction.m_bProductionReceivedDate)
		   pSet->Fields->GetItem("ProductionReceivedDate")->PutValue((_variant_t)m_pageProduction.m_dProductionReceivedDate);
		else if(!m_bSave)
			pSet->Fields->GetItem("ProductionReceivedDate")->PutValue(VarTemp);

		if(m_pageProduction.m_bPlantProductionDate)
           pSet->Fields->GetItem("PlantProductionDate")->PutValue((_variant_t)m_pageProduction.m_dPlantProductionDate);
		else if(!m_bSave)
			pSet->Fields->GetItem("PlantProductionDate")->PutValue(VarTemp);

		if(m_pageProduction.m_bPDeliveryDate)
		{
		  pSet->Fields->GetItem("PDeliveryDate")->PutValue((_variant_t)m_pageProduction.m_dPDeliveryDate);
		  pSet->Fields->GetItem("PDeliveryRemark")->PutValue(m_pageProduction.m_sPDeliveryRemark.AllocSysString());
		}
		else if(!m_bSave)
			pSet->Fields->GetItem("PDeliveryDate")->PutValue(VarTemp);

	    pSet->Fields->GetItem("PBatchCheck")->PutValue((_variant_t)m_pageProduction.m_bPBatchCheck);
		if(m_pageProduction.m_bPBatchCheck)
		{
		   pSet->Fields->GetItem("PSecDeliveryDate")->PutValue((_variant_t)m_pageProduction.m_dPSecDeliveryDate);
		   pSet->Fields->GetItem("PSecDeliveryRemark")->PutValue(m_pageProduction.m_sPSecDeliveryRemark.AllocSysString());
		}
		else if(!m_bSave)
			pSet->Fields->GetItem("PSecDeliveryDate")->PutValue(VarTemp);

		if(m_pageProduction.m_bPThirdDeliveryDate)
		{

		   pSet->Fields->GetItem("PThirdDeliveryDate")->PutValue((_variant_t)m_pageProduction.m_dPThirdDeliveryDate);
		   pSet->Fields->GetItem("PThirdDeliveryRemark")->PutValue(m_pageProduction.m_sPThirdDeliveryRemark.AllocSysString());
		}
		else if(!m_bSave)
			pSet->Fields->GetItem("PThirdDeliveryDate")->PutValue(VarTemp);


		pSet->Fields->GetItem("ConfigureFinishCheck")->PutValue((_variant_t)m_pageProduction.m_bConfigureFinsh);
		if(m_pageProduction.m_bConfigureFinsh)
		{
		    pSet->Fields->GetItem("ConfigureFinish")->PutValue((_variant_t)m_pageProduction.m_dConfigureFinish);
		}
		else if(!m_bSave)
		{
			pSet->Fields->GetItem("ConfigureFinish")->PutValue(VarTemp);
		}


		pSet->Fields->GetItem("PurchaseReturnCheck")->PutValue((_variant_t)m_pageProduction.m_bPurchaseReturn);
		if(m_pageProduction.m_bPurchaseReturn)
		    pSet->Fields->GetItem("PurchaseReturn")->PutValue((_variant_t)m_pageProduction.m_dPurchaseReturn);
		else if(!m_bSave)
			pSet->Fields->GetItem("PurchaseReturn")->PutValue(VarTemp);

	}

	if(g_strAuthor.Mid(4,1)=="1" || g_tUserType>=4)
	{
		if(m_pageDelivery.m_bDeliveryReceived)
	        pSet->Fields->GetItem("DeliveryReceivedDate")->PutValue((_variant_t)m_pageDelivery.m_dDeliveryReceivedDate);
		else if(!m_bSave)
			pSet->Fields->GetItem("DeliveryReceivedDate")->PutValue(VarTemp);

		if(m_pageDelivery.m_bADeliveryDate)
		{			
		pSet->Fields->GetItem("ADeliveryDate")->PutValue((_variant_t)m_pageDelivery.m_dADeliveryDate);
		pSet->Fields->GetItem("ADeliveryRemark")->PutValue(m_pageDelivery.m_sADeliveryRemark.AllocSysString());
		}
		else if(!m_bSave)
			pSet->Fields->GetItem("ADeliveryDate")->PutValue(VarTemp);
		
		pSet->Fields->GetItem("ABatchCheck")->PutValue((_variant_t)m_pageDelivery.m_bBatchDelivery);
		if(m_pageDelivery.m_bBatchDelivery)
		{
		
		pSet->Fields->GetItem("ASecDeliveryDate")->PutValue((_variant_t)m_pageDelivery.m_dASecDeliveryDate);
		pSet->Fields->GetItem("ASecDeliveryRemark")->PutValue(m_pageDelivery.m_sASecDeliveryRemark.AllocSysString());
		}
		else if(!m_bSave)
			pSet->Fields->GetItem("ASecDeliveryDate")->PutValue(VarTemp);

		if(m_pageDelivery.m_bAThirdDeliveryDate)
		{

		pSet->Fields->GetItem("AThirdDeliveryDate")->PutValue((_variant_t)m_pageDelivery.m_dAThirdDeliveryDate);
		pSet->Fields->GetItem("AThirdDeliveryRemark")->PutValue(m_pageDelivery.m_sAThirdDeliveryRemark.AllocSysString());
		} 
		else if(!m_bSave)
			pSet->Fields->GetItem("AThirdDeliveryDate")->PutValue(VarTemp);

		pSet->Fields->GetItem("DeliveryDone")->PutValue((_variant_t)m_pageDelivery.m_bDeliveryDone);
	}

	pSet->Fields->GetItem("DDeliveryRemarks")->PutValue(m_sRemarks.AllocSysString());

	if(!m_bCopy)
	{
		pSet->Fields->GetItem("DReperson")->PutValue(g_strUserName.AllocSysString());
		pSet->Fields->GetItem("DReDate")->PutValue((_variant_t)m_dCurrent);

		if(m_bSave)
		{
			pSet->Fields->GetItem("DInputPerson")->PutValue(g_strUserName.AllocSysString());
			pSet->Fields->GetItem("DInputDate")->PutValue((_variant_t)m_dCurrent);
		}
	}

	m_pageCFollowup.UpdateDataPage(FALSE);
	m_pagePayment.UpdateDataPage(FALSE);
	m_pagePrice.UpdateDataPage(FALSE);
	m_pageProduction.UpdateDataPage(FALSE);
	m_pageDelivery.UpdateDataPage(FALSE);
}

void CItemCommerceDlg::ReadRecord(_RecordsetPtr& pSet)
{
	m_pageCFollowup.UpdateDataPage(TRUE);
	m_pagePayment.UpdateDataPage(TRUE);
	m_pagePrice.UpdateDataPage(TRUE);
	m_pageProduction.UpdateDataPage(TRUE);
	m_pageDelivery.UpdateDataPage(TRUE);
    CString str;
	COleDateTime dtemp;

	if(g_tUserType>=2)
	{
    	Holder = pSet->GetCollect("Amount");
     	m_pagePrice.m_dbAmount  = (double)Holder;

     	Holder = pSet->GetCollect("MaterialAmount");
	    m_pagePrice.m_dbMaterialAmount = (double)Holder;
 
	    Holder = pSet->GetCollect("FreightInsurance");
	    m_pagePrice.m_dbFreightInsurance = (double)Holder;

	   Holder = pSet->GetCollect("Discount");
	   m_pagePayment.m_dbDiscount = (double)Holder;

	   Holder = pSet->GetCollect("InternalPrice");
	  m_pagePayment.m_dbInternalPrice  = (double)Holder; 

	   Holder = pSet->GetCollect("ActualGetFreightInsurance");
	   m_pagePayment.m_dbAGetFreightInsurance = (double)Holder;
	}

	Holder = pSet->GetCollect("Currency");
	m_iCurrency= (int)Holder;
    switch(m_iCurrency) {
    case 0:
		((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
    	break;
    case 1:
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(FALSE);
    	break;
    default:
		break;
    }

	Holder = pSet->GetCollect("POReleaseDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pagePayment.m_bPORelease = FALSE;
		m_pagePayment.m_cPORelease.EnableWindow(FALSE);
		m_pagePayment.m_dPORelease = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pagePayment.m_bPORelease = TRUE;
		m_pagePayment.m_cPORelease.EnableWindow(TRUE);
		m_pagePayment.m_dPORelease = Holder.date;
	}

	Holder = pSet->GetCollect("POReturnDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pagePayment.m_bPOReturn= FALSE;
		m_pagePayment.m_cPOReturn.EnableWindow(FALSE);
		m_pagePayment.m_dPOReturn = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pagePayment.m_bPOReturn = TRUE;
		m_pagePayment.m_cPOReturn.EnableWindow(TRUE);
		m_pagePayment.m_dPOReturn = Holder;
	}

	Holder = pSet->GetCollect("GADReceived");
    str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageCFollowup.m_bGADReceived = FALSE;
		m_pageCFollowup.m_cGADReceived.EnableWindow(FALSE);
		m_pageCFollowup.m_dGADReceived = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageCFollowup.m_bGADReceived= TRUE;
		m_pageCFollowup.m_cGADReceived.EnableWindow(TRUE);
		m_pageCFollowup.m_dGADReceived = Holder.date;
	}

	Holder = pSet->GetCollect("TheLatestAmendment");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageCFollowup.m_bLatestAmend= FALSE;
		m_pageCFollowup.m_cLatestAmend.EnableWindow(FALSE);
		m_pageCFollowup.m_dLatestAmend = COleDateTime::GetCurrentTime();
		m_pageCFollowup.m_cAmendRemark.SetReadOnly(TRUE);
		m_pageCFollowup.m_sAmendRemark.Empty();
	}
	else
	{
		m_pageCFollowup.m_bLatestAmend= TRUE;
		m_pageCFollowup.m_cLatestAmend.EnableWindow(TRUE);
		m_pageCFollowup.m_dLatestAmend =Holder.date;

	    m_pageCFollowup.m_cAmendRemark.SetReadOnly(FALSE);
		Holder = pSet->GetCollect("AmendmentRemark");
		m_pageCFollowup.m_sAmendRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	}

	Holder = pSet->GetCollect("ComfirmationSheetRelease");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageCFollowup.m_bCSRelease = FALSE;
		m_pageCFollowup.m_cCSRelease.EnableWindow(FALSE);
		m_pageCFollowup.m_dCSRelease = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageCFollowup.m_bCSRelease = TRUE;
		m_pageCFollowup.m_cCSRelease.EnableWindow(TRUE);
		m_pageCFollowup.m_dCSRelease =Holder.date;
	}

	Holder = pSet->GetCollect("ComfirmationSheetReply");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageCFollowup.m_bCSReply = FALSE;
		m_pageCFollowup.m_cCSReply.EnableWindow(FALSE);
		m_pageCFollowup.m_cReplyRemark.SetReadOnly(TRUE);
		m_pageCFollowup.m_sReplyRemark.Empty();
		m_pageCFollowup.m_dCSReply = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageCFollowup.m_bCSReply = TRUE;
		m_pageCFollowup.m_cCSReply.EnableWindow(TRUE);
		m_pageCFollowup.m_dCSReply = Holder.date;

		m_pageCFollowup.m_cReplyRemark.SetReadOnly(FALSE);
		Holder = pSet->GetCollect("ReplyRemark");
		m_pageCFollowup.m_sReplyRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	}

	Holder = pSet->GetCollect("AssessmentCompleteDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageCFollowup.m_bACompleteDate = FALSE;
		m_pageCFollowup.m_cACompleteDate.EnableWindow(FALSE);
		m_pageCFollowup.m_dACompleteDate = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageCFollowup.m_bACompleteDate = TRUE;
		m_pageCFollowup.m_cACompleteDate.EnableWindow(TRUE);
		m_pageCFollowup.m_dACompleteDate = Holder.date;
	}

	Holder = pSet->GetCollect("ProductionReceivedDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageProduction.m_bProductionReceivedDate = FALSE;
		m_pageProduction.m_cProductionReceiveDate.EnableWindow(FALSE);
		m_pageProduction.m_dProductionReceivedDate = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageProduction.m_bProductionReceivedDate = TRUE;
		m_pageProduction.m_cProductionReceiveDate.EnableWindow(TRUE);
		m_pageProduction.m_dProductionReceivedDate = Holder.date;
	}



	Holder = pSet->GetCollect("PlantProductionDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageProduction.m_bPlantProductionDate = FALSE;
		m_pageProduction.m_cPlantProductionDate.EnableWindow(FALSE);
		m_pageProduction.m_dPlantProductionDate = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageProduction.m_bPlantProductionDate = TRUE;
		m_pageProduction.m_cPlantProductionDate.EnableWindow(TRUE);
		m_pageProduction.m_dPlantProductionDate = Holder.date;
	}

	Holder = pSet->GetCollect("PDeliveryDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageProduction.m_bPDeliveryDate = FALSE;
		m_pageProduction.m_cPDeliveryDate.EnableWindow(FALSE);
		m_pageProduction.m_cPDeliveryRemark.SetReadOnly(TRUE);
		m_pageProduction.m_sPDeliveryRemark.Empty();
		m_pageProduction.m_dPDeliveryDate = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageProduction.m_bPDeliveryDate = TRUE;
		m_pageProduction.m_cPDeliveryDate.EnableWindow(TRUE);
		m_pageProduction.m_dPDeliveryDate = Holder.date;

		m_pageProduction.m_cPDeliveryRemark.SetReadOnly(FALSE);
		Holder = pSet->GetCollect("PDeliveryRemark");
		m_pageProduction.m_sPDeliveryRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	}


	Holder = pSet->GetCollect("PBatchCheck");
	m_pageProduction.m_bPBatchCheck = (bool)Holder;
	if(m_pageProduction.m_bPBatchCheck)
	{
		m_pageProduction.m_cPSecDeliveryDate.EnableWindow(TRUE);
		Holder = pSet->GetCollect("PSecDeliveryDate");
		m_pageProduction.m_dPSecDeliveryDate = Holder.date;

		m_pageProduction.m_cPSecDeliveryRemark.SetReadOnly(FALSE);
		Holder = pSet->GetCollect("PSecDeliveryRemark");
		m_pageProduction.m_sPSecDeliveryRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	}
	else
	{
		m_pageProduction.m_cPSecDeliveryDate.EnableWindow(FALSE);
		m_pageProduction.m_dPSecDeliveryDate = COleDateTime::GetCurrentTime();

		m_pageProduction.m_cPSecDeliveryRemark.SetReadOnly(TRUE);
		m_pageProduction.m_sPSecDeliveryRemark.Empty();
	}

	Holder = pSet->GetCollect("PThirdDeliveryDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageProduction.m_bPThirdDeliveryDate = FALSE;
		m_pageProduction.m_cPThirdDeliveryDate.EnableWindow(FALSE);
		m_pageProduction.m_cPThirdDeliveryRemark.SetReadOnly(TRUE);
		m_pageProduction.m_dPThirdDeliveryDate = COleDateTime::GetCurrentTime();
		m_pageProduction.m_sPThirdDeliveryRemark.Empty();
	}
	else
	{
		m_pageProduction.m_bPThirdDeliveryDate = TRUE;
		m_pageProduction.m_cPThirdDeliveryDate.EnableWindow(TRUE);
		m_pageProduction.m_dPThirdDeliveryDate = Holder.date;

		m_pageProduction.m_cPThirdDeliveryRemark.SetReadOnly(FALSE);
		Holder = pSet->GetCollect("PThirdDeliveryRemark");
		m_pageProduction.m_sPThirdDeliveryRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	}

	Holder = pSet->GetCollect("ConfigureFinishCheck");
	BOOL bTemp = (bool)Holder;

	Holder= pSet->GetCollect("ConfigureFinish");
	if(!bTemp)
	{
		m_pageProduction.m_bConfigureFinsh = FALSE;
		m_pageProduction.m_cConfigureFinish.EnableWindow(FALSE);
		m_pageProduction.m_dConfigureFinish = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageProduction.m_bConfigureFinsh = TRUE;
		m_pageProduction.m_cConfigureFinish.EnableWindow(TRUE);
		m_pageProduction.m_dConfigureFinish = Holder.date;
	}

	Holder = pSet->GetCollect("PurchaseReturnCheck");
	bTemp = (bool)Holder;

	Holder= pSet->GetCollect("PurchaseReturn");
	if(!bTemp)
	{
		m_pageProduction.m_bPurchaseReturn = FALSE;
		m_pageProduction.m_cPurchaseReturn.EnableWindow(FALSE);
		m_pageProduction.m_dPurchaseReturn = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageProduction.m_bPurchaseReturn = TRUE;
		m_pageProduction.m_cPurchaseReturn.EnableWindow(TRUE);
		m_pageProduction.m_dPurchaseReturn = Holder.date;
	}

	Holder = pSet->GetCollect("DeliveryReceivedDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageDelivery.m_bDeliveryReceived  = FALSE;
		m_pageDelivery.m_cDeliveryReceivedDate.EnableWindow(FALSE);
		m_pageDelivery.m_dDeliveryReceivedDate = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_pageDelivery.m_bDeliveryReceived = TRUE;
		m_pageDelivery.m_cDeliveryReceivedDate.EnableWindow(TRUE);
		m_pageDelivery.m_dDeliveryReceivedDate = Holder.date;
	}

	Holder = pSet->GetCollect("ADeliveryDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageDelivery.m_bADeliveryDate = FALSE;
		m_pageDelivery.m_cADeliveryDate.EnableWindow(FALSE);
		m_pageDelivery.m_dADeliveryDate  = COleDateTime::GetCurrentTime();

		m_pageDelivery.m_cADeliveryRemark.SetReadOnly(TRUE);
		m_pageDelivery.m_sADeliveryRemark.Empty();
	}
	else
	{
		m_pageDelivery.m_bADeliveryDate = TRUE;
		m_pageDelivery.m_cADeliveryDate.EnableWindow(TRUE);
		m_pageDelivery.m_dADeliveryDate =Holder.date;

		m_pageDelivery.m_cADeliveryRemark.SetReadOnly(FALSE);
		Holder = pSet->GetCollect("ADeliveryRemark");
		m_pageDelivery.m_sADeliveryRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;		
	}
	

	Holder = pSet->GetCollect("ABatchCheck");
	m_pageDelivery.m_bBatchDelivery = (bool)Holder;
	if(m_pageDelivery.m_bBatchDelivery)
	{
		m_pageDelivery.m_cASecDeliveryDate.EnableWindow(TRUE);
		Holder = pSet->GetCollect("ASecDeliveryDate");
		m_pageDelivery.m_dASecDeliveryDate = Holder.date;

		m_pageDelivery.m_cASecDeliveryRemark.SetReadOnly(FALSE);
		Holder = pSet->GetCollect("ASecDeliveryRemark");
		m_pageDelivery.m_sASecDeliveryRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	}
	else
	{
		m_pageDelivery.m_cASecDeliveryDate.EnableWindow(FALSE);
		m_pageDelivery.m_dASecDeliveryDate = COleDateTime::GetCurrentTime();

		m_pageDelivery.m_cASecDeliveryRemark.SetReadOnly(TRUE);
		m_pageDelivery.m_sASecDeliveryRemark.Empty();
	}

	Holder = pSet->GetCollect("AThirdDeliveryDate");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_pageDelivery.m_bAThirdDeliveryDate = FALSE;
		m_pageDelivery.m_cAThirdDeliveryDate.EnableWindow(FALSE);
		m_pageDelivery.m_cAThirdDeliveryRemark.SetReadOnly(TRUE);
		m_pageDelivery.m_dAThirdDeliveryDate = COleDateTime::GetCurrentTime();
		m_pageDelivery.m_sAThirdDeliveryRemark.Empty();
	}
	else
	{
		m_pageDelivery.m_bAThirdDeliveryDate = TRUE;
		m_pageDelivery.m_cAThirdDeliveryDate.EnableWindow(TRUE);
		m_pageDelivery.m_dAThirdDeliveryDate = Holder.date;

		m_pageDelivery.m_cAThirdDeliveryRemark.SetReadOnly(FALSE);
		Holder = pSet->GetCollect("AThirdDeliveryRemark");
		m_pageDelivery.m_sAThirdDeliveryRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	}

	Holder = pSet->GetCollect("DeliveryDone");
	m_pageDelivery.m_bDeliveryDone = (bool)Holder;

   Holder = pSet->GetCollect("DDeliveryRemarks");
   m_sRemarks = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;


   Holder = pSet->GetCollect("DInputPerson");
   m_sInputPerson =  Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

   Holder = pSet->GetCollect("DInputDate");
   dtemp = Holder.date;
   m_sInputDate = dtemp.Format("%Y-%m-%d");

   Holder = pSet->GetCollect("DRePerson");
   m_sRePerson = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

   Holder = pSet->GetCollect("DReDate");
   dtemp = Holder.date;
   m_sReDate = dtemp.Format("%Y-%m-%d");

   Holder = pSet->GetCollect("TempDate");
   VarTemp = Holder;

   m_pageCFollowup.UpdateDataPage(FALSE);
   m_pagePayment.UpdateDataPage(FALSE);
   m_pagePrice.UpdateDataPage(FALSE);
   m_pageProduction.UpdateDataPage(FALSE);
   m_pageDelivery.UpdateDataPage(FALSE);
}

void CItemCommerceDlg::RecordSearch(void)
{
	try
	{
		m_sOrderID.Trim();

		strSQL = "select * from Delivery where OrderID = '"+m_sOrderID+"'";
		theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
		int iCount = m_pTempSet->GetRecordCount();
		if(iCount!=0)
		{
			m_pTempSet->MoveFirst();
			ReadRecord(m_pTempSet);
		}
		else
		{
	        m_pageCFollowup.ClearEdit();
			m_pagePayment.ClearEdit();
			m_pagePrice.ClearEdit();
			m_pageProduction.ClearEdit();
			m_pageDelivery.ClearEdit();

			m_sInputPerson = g_strUserName;
			m_sRePerson = g_strUserName;
			m_sInputDate =  m_dCurrent.Format("%Y-%m-%d");
			m_sReDate =  m_dCurrent.Format("%Y-%m-%d");
			m_sRemarks.Empty();

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

void CItemCommerceDlg::OnBnClickedButtonSamecopy()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	CDataSameCopyDlg m_dlg;
    m_iCheck = 1;
	m_dlg.m_iCheck = m_iCheck;
	if(m_bCheck)
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
		m_dlg.m_sProjectNameEn = m_sProjectNameEN;
	}
	if(!m_sOrderID.IsEmpty())
		m_dlg.m_sResource = m_sOrderID;
	m_dlg.DoModal();
	UpdateData(FALSE);

}


