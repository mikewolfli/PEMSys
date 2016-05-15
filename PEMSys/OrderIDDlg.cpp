// OrderIDDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "OrderIDDlg.h"
#include ".\orderiddlg.h"


// COrderIDDlg 对话框

IMPLEMENT_DYNAMIC(COrderIDDlg, CDialog)
COrderIDDlg::COrderIDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COrderIDDlg::IDD, pParent)
	, m_sID(_T(""))
	, m_sProjectName(_T(""))
	, m_stemp(_T(""))
	, m_bEdit(TRUE)
	, m_iOrderNum(0)
	, m_iNum(0)
	, m_iRow(0)
	, m_dCurrent(COleDateTime::GetCurrentTime())
	, m_sYear(_T(""))
	, m_sSubCompanyName(_T(""))
	, m_sSubCompanyID(_T(""))
	, RStatus(NULL)
{
}

COrderIDDlg::~COrderIDDlg()
{
	if(m_pOrderID->State == adStateOpen)
		m_pOrderID->Close();
	if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();

	m_pOrderID.Release();
	m_pTempSet.Release();
	if(RStatus)
		delete [] RStatus;

}

void COrderIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_cSave);
	DDX_Control(pDX, IDCANCEL, m_cExit);
	DDX_Control(pDX, IDC_COMBO_ORDER_ID, m_cID);
	DDX_CBString(pDX, IDC_COMBO_ORDER_ID, m_sID);
	DDX_Text(pDX, IDC_EDIT_ORDER_PROJECTNAME, m_sProjectName);
	DDX_Control(pDX, IDC_CUSTOM_ORDERID_GRIDCTRL, m_cGrid);
}


BEGIN_MESSAGE_MAP(COrderIDDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_CBN_SELENDOK(IDC_COMBO_ORDER_ID, OnCbnSelendokComboOrderId)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_CUSTOM_ORDERID_GRIDCTRL, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_CUSTOM_ORDERID_GRIDCTRL, OnGridEndEdit)
END_MESSAGE_MAP()


// COrderIDDlg 消息处理程序

void COrderIDDlg::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int year,month,day,iCount;
	try{
		if(m_sID == _T(""))
		{
			AfxMessageBox("请输入定位查询条件!", MB_ICONEXCLAMATION);
			m_cID.SetFocus();
			m_cID.SetEditSel(0,-1);
			return;
		}

		year = m_dCurrent.GetYear();
		month = m_dCurrent.GetMonth();
		day = m_dCurrent.GetDay();
		if(month == 12 && day >=28)
			year = year + 1;

		m_sYear.Format("%d",year);
		m_sYear = m_sYear.Right(2);

		strSQL = "select ID, ProjectName, SubCompanyName, Number from PBInformation where ID = '"+m_sID+"'";
		theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount!=0)
		{
			Holder = m_pTempSet->GetCollect("ProjectName");
			m_sProjectName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
			SetDlgItemText(IDC_EDIT_ORDER_PROJECTNAME, m_sProjectName);

			Holder = m_pTempSet->GetCollect("SubCompanyName");
			m_sSubCompanyName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

			Holder = m_pTempSet->GetCollect("Number");
			m_iNum = (int)Holder;

			m_pTempSet->Close();
		}
		else
		{
			ClearGrid();
			AfxMessageBox("请重新选择或输入定位查询条件!", MB_ICONEXCLAMATION);
			m_cID.SetFocus();
			m_cID.SetEditSel(0,-1);
			m_pTempSet->Close();
			return;
		}

		strSQL = "select * from TotalElevator where Year = '"+m_sYear+"'";
		theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount == 0)
		{
			m_iOrderNum = 0;
		}
		else 
		{
			Holder = m_pTempSet->GetCollect("CurrentTotal");
			m_iOrderNum = (int)Holder;
		}
		m_pTempSet->Close();

		strSQL = "select * from OrderOfProject where ID = '"+m_sID+"'";
		theApp.ADOExecute(m_pOrderID, theApp.m_pConnect, strSQL);
		RefreshGrid();
		m_pOrderID->Close();

	}catch(_com_error &e)
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

void COrderIDDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	int iCount;
	GV_ITEM Item;
	m_iRow = m_cGrid.GetRowCount()-1;
	if(m_sID == _T(""))
	{
		AfxMessageBox("请先选择项目合同!", MB_ICONEXCLAMATION);
		m_cID.SetFocus();
		m_cID.SetEditSel(0,-1);
		return;
	}

	if(m_iRow == 0)
	{
		AfxMessageBox("项目流水号不存在\n 请先返回上级窗口添加项目!", MB_ICONEXCLAMATION);
		return;
	}
	try
	{
		if(AfxMessageBox("是否确认保存?",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{
			strSQL = "select * from TotalElevator where Year = '"+m_sYear+"'";
			theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
			iCount = m_pTempSet->GetRecordCount();
			if(iCount == 0)
			{
				m_pTempSet->AddNew();
			}
			m_pTempSet->Fields->GetItem("Year")->PutValue(m_sYear.AllocSysString());
			m_pTempSet->Fields->GetItem("CurrentTotal")->PutValue((_variant_t)m_iOrderNum);
			m_pTempSet->Update();
			m_pTempSet->Close();

			strSQL = "select * from OrderOfProject where ID = '"+m_sID+"'";
			theApp.ADOExecute(m_pOrderID, theApp.m_pConnect, strSQL);			

			int i = 0;
			if(!m_pOrderID->BOF)
				m_pOrderID->MoveFirst();
			while(i<m_iRow)
			{
				if(RStatus[i].b_Status)
				{  
					for (int col=1;col<9; col++)
					{
						InsertData(i+1,col);
					}
					m_pOrderID->Update();
					m_pOrderID->MoveNext();
				} 
				else
				{

					m_pOrderID->AddNew();
					for (int col=1;col<9; col++)
					{
						InsertData(i+1,col);
					}
					m_pOrderID->Update();
					RStatus[i].b_Status = TRUE;			  
				}
				++i;
			}   
			RefreshGrid();

			m_pOrderID->Close();
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
//	OnOK();
}

void COrderIDDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	OnCancel();
}

void COrderIDDlg::OnCbnSelendokComboOrderId()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
	int iCount, iIndex,year,month,day;
	CString str;

	try
	{
		iIndex = m_cID.GetCurSel();
		if (iIndex != LB_ERR )
		{
			m_cID.GetLBText(iIndex,str);

			m_sID = str;
			SetDlgItemText(IDC_COMBO_ORDER_ID, str);
			year = m_dCurrent.GetYear();
			month = m_dCurrent.GetMonth();
			day = m_dCurrent.GetDay();
			if(month == 12 && day >=28)
				year = year + 1;

			m_sYear.Format("%d",year);
			m_sYear = m_sYear.Right(2);

			strSQL = "select * from TotalElevator where Year = '"+m_sYear+"'";
			theApp.ADOExecute(m_pTempSet,theApp.m_pConnect,  strSQL);
			iCount = m_pTempSet->GetRecordCount();
			if(iCount == 0)
			{
				m_iOrderNum = 0;
			}
			else 
			{
				Holder = m_pTempSet->GetCollect("CurrentTotal");
				m_iOrderNum = (int)Holder;
			}
			m_pTempSet->Close();

			strSQL = "select ID, ProjectName, SubCompanyName, Number from PBInformation where ID = '"+m_sID+"'";
			theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);

			Holder = m_pTempSet->GetCollect("ProjectName");
			m_sProjectName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
			SetDlgItemText(IDC_EDIT_ORDER_PROJECTNAME, m_sProjectName);

			Holder = m_pTempSet->GetCollect("SubCompanyName");
			m_sSubCompanyName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

			Holder = m_pTempSet->GetCollect("Number");
			m_iNum = (int)Holder;

			m_pTempSet->Close();

			strSQL = "select * from OrderOfProject where ID = '"+m_sID+"'";
			theApp.ADOExecute(m_pOrderID, theApp.m_pConnect, strSQL);
			RefreshGrid();
			m_pOrderID->Close();

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

// GVN_BEGINLABELEDIT
void COrderIDDlg::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	BOOL bAllowEdit = !m_bEdit;

	*pResult = (bAllowEdit)? -1 : 0;
}

// GVN_ENDLABELEDIT
void COrderIDDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	BOOL bAcceptChange = !m_bEdit;

	*pResult = (bAcceptChange)? -1 : 0;
}
void COrderIDDlg::RefreshGrid(void)
{
	CGridCellCheck* pCell;
	int i,j,n,zero,f;

	CString str,str1,str2;
	GV_ITEM Item;

 	if(m_pOrderID->State == adStateClosed)
		return;

	try{
		int iCount = m_pOrderID->GetRecordCount();
		j = m_iNum;
		i = m_cGrid.GetRowCount();
		Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

		if(j>iCount)
			m_iRow = j;
		else
			m_iRow = iCount;

		if(m_iRow>i-1)
		{
			for(f = i;f<m_iRow+1;f++)
			{
				str.Format("%d",f);
				m_cGrid.InsertRow(str,-1);
			}
		}
		else if(m_iRow<i-1)
		{
			for(f = i-1 ; f>m_iRow;f--)
			{
				m_cGrid.DeleteRow(f);
			}
		}

	
//		RowStatus *pTemp = NULL;
//		if(RStatus)
//			pTemp = RStatus;
		if(RStatus)
            delete [] RStatus;
		RStatus = new RowStatus[m_iRow];

//		if(pTemp)
//			delete [] pTemp;
//		m_iStatus = m_iRow;

		n= 0;
		if(iCount!=0 && !m_pOrderID->BOF)
		{
			m_pOrderID->MoveFirst();
		}
		while (!m_pOrderID->EndOfFile) 
		{
			RStatus[n].i_Row = n;
			RStatus[n].b_Judge = FALSE;
			RStatus[n].b_Status = TRUE;

			for(int m=8;m>=0;m--)
			{
				Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

				Item.row = n+1;
				Item.col = m;

				switch(m)
				{
				case 0:
					Item.strText.Format("%d",n+1);
					break;
				case 1:
					Holder = m_pOrderID->GetCollect(_T("OrderID"));
					Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					break;
				case 2:
					Holder = m_pOrderID->GetCollect("ElevatorID");
					str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
					Item.strText.Format(str);
					break;
				case 3:
					Holder = m_pOrderID->GetCollect("Remark");
					Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					break;
				case 4:
					Holder = m_pOrderID->GetCollect("Status");
					m_cGrid.SetCellType(n+1,4, RUNTIME_CLASS(CGridCellCheck));
					pCell = (CGridCellCheck*)m_cGrid.GetCell(n+1,4);
					if(Holder.boolVal)
					{
						pCell->SetCheck(TRUE);
						RStatus[n].b_Judge = TRUE;
					}
					else
					{
						pCell->SetCheck(FALSE);
						RStatus[n].b_Judge = FALSE;
					}
					Item.strText = _T("");
					break;
				case 5:
					Holder = m_pOrderID->GetCollect("InputPerson");
					Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					break;
				case 6:
					Holder = m_pOrderID->GetCollect("InputDate");
					Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					break;
				case 7:
					Holder = m_pOrderID->GetCollect("RePerson");
					Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					break;
				case 8:
					Holder = m_pOrderID->GetCollect("ReDate");
					Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					break;
				default:
					break;
				}
				if(m ==1)
				{
					if(RStatus[n].b_Status)
						Item.iImage = 0;

					if(RStatus[n].b_Judge)
						Item.iImage = 2;

					Item.mask |= (GVIF_IMAGE);
				}
				else 
				{
					Item.iImage = -1;
				}
				m_cGrid.SetItem(&Item);
				m_cGrid.AutoSizeRows();

			}

			++n;
			m_pOrderID->MoveNext();
		}
		if(m_iRow>iCount)
		{
			strSQL = "select SubCompanyID from SubCompany where SubCompanyName = '"+m_sSubCompanyName+"'";
			theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);

			Holder = m_pTempSet->GetCollect("SubCompanyID");
			str2 = (char*)(_bstr_t)Holder;
			m_pTempSet->Close();

			str1 = m_sYear;

			for(int t = 0;t<m_iRow-n;t++)
			{      
				RStatus[t+n].i_Row = t+n;
				RStatus[t+n].b_Judge = FALSE;
				RStatus[i+n].b_Status = FALSE;
				for(int m=0;m<9;m++)
				{

					Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
					Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

					Item.row = t+n+1;
					Item.col = m;

					switch(m)
					{
					case 0:				
						Item.strText.Format("%d",t+n+1);
						break;
					case 1:
						m_iOrderNum = m_iOrderNum+1;
						str.Format("%d",m_iOrderNum);
						zero = strlen(str);
						switch(zero)
						{
						case 0:
							str = "0000"+str;
							break;
						case 1:
							str = "000"+str;
							break;
						case 2:
							str = "00"+str;
							break;
						case 3:
							str= "0"+str;
							break;
						default:
							break;
						}
						str = str1 +" "+str2 +" "+str;
						Item.strText = str;
						break;
					case 2:
						Item.strText.Format("L%d",t+n+1);
						break;
					case 3:
						Item.strText = _T("");
						break;
					case 4:
						m_cGrid.SetCellType(t+n+1,4, RUNTIME_CLASS(CGridCellCheck));
						pCell = (CGridCellCheck*)m_cGrid.GetCell(t+n+1,4);
						pCell->SetCheck(FALSE);
						RStatus[t+n].b_Status = FALSE;
						Item.strText = _T("");
						break;
					case 5:
						Item.strText = g_strUserName;
						break;
					case 6:
						Item.strText = m_dCurrent.Format("%Y-%m-%d");
						break;
					case 7:
						Item.strText = g_strUserName;
						break;
					case 8:
						Item.strText = m_dCurrent.Format("%Y-%m-%d");
						break;
					default:
						break;
					}	
					if(m ==1)
					{
						Item.iImage = 1;
						Item.mask |= (GVIF_IMAGE);
					}
					else
					{
						Item.iImage = -1;
					}
					m_cGrid.SetItem(&Item);
				}
			}
			m_cGrid.AutoSizeRows();
		}
		for(int r=1;r<=m_iRow;r++)
		{
			m_cGrid.SetItemState(r,1,m_cGrid.GetItemState(r,1) | GVIS_READONLY);
			if(!RStatus[r-1].b_Status)
			{
				m_cGrid.SetItemState(r,4,m_cGrid.GetItemState(r,4) | GVIS_READONLY);
			}
			else
			{
				m_cGrid.SetItemState(r,4, m_cGrid.GetItemState(r,4) & ~GVIS_READONLY);
			}
			m_cGrid.SetItemState(r,5,m_cGrid.GetItemState(r,5) | GVIS_READONLY);
			m_cGrid.SetItemState(r,6,m_cGrid.GetItemState(r,6) | GVIS_READONLY);
			m_cGrid.SetItemState(r,7,m_cGrid.GetItemState(r,7) | GVIS_READONLY);
			m_cGrid.SetItemState(r,8,m_cGrid.GetItemState(r,8) | GVIS_READONLY);
		}

		m_cGrid.Invalidate();

	}
	catch(CMemoryException* e)
	{
		e->ReportError();
		return;
	}
	
}

void COrderIDDlg::ClearGrid(void)
{
	UpdateData(TRUE);

	m_sProjectName.Empty();
	m_sID.Empty();
	m_stemp.Empty();
	m_cGrid.DeleteNonFixedRows();
	m_cGrid.Invalidate();
	UpdateData(FALSE);
}

BOOL COrderIDDlg::PreTranslateMessage(MSG* pMsg)
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

BOOL COrderIDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cSave.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_SAVE));
	m_cExit.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_EXIT));

	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_ORDER);
	ASSERT(hIcon != NULL);
	SetIcon(hIcon, TRUE);

	image_Status.Create(MAKEINTRESOURCE(IDB_STATUS), 16, 0, RGB(255,255,255));

	m_cID.SetFocus();

	// 填充数据
	m_cGrid.SetEditable(m_bEdit);
	m_cGrid.SetImageList(&image_Status);
	m_cGrid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

	try {
		m_cGrid.SetColumnCount(9);
		m_cGrid.SetRowCount(1);
		m_cGrid.SetFixedRowCount(1);
		m_cGrid.SetFixedColumnCount(1);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}


	switch(g_tUserType)
	{
	case 1:
		m_cSave.EnableWindow(FALSE);;
		break;
	default:
		break;
	}


	GV_ITEM Item;
	//	Item.mask = GVIF_TEXT;
	Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
	Item.row = 0;
	Item.col =0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	m_cGrid.SetAutoSizeStyle();
	m_cGrid.SetColumnWidth(0,40);
	m_cGrid.SetColumnWidth(1,100);
	m_cGrid.SetColumnWidth(4,40);
	m_cGrid.SetRowHeight(0,30);

	for (int i=0;i<9;i++)
	{
		Item.row=0;
		Item.col=i;
		switch(i)
		{
		case 0:
			Item.strText.Format(_T("序号"));
			break;
		case 1:
			Item.strText.Format(_T("订单号"));
			break;
		case 2:
			Item.strText.Format(_T("梯号"));
			break;
		case 3:
			Item.strText.Format(_T("说明"));
			break;
		case 4:
			Item.strText.Format(_T("作废"));
			break;
		case 5:
			Item.strText.Format(_T("录入人"));
			break;
		case 6:
			Item.strText.Format(_T("录入日期"));
			break;
		case 7:
			Item.strText.Format(_T("修改人"));
			break;
		case 8:
			Item.strText.Format(_T("修改日期"));			
			break;
		default:
			break;
		}
		m_cGrid.SetItem(&Item);
	}


	LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void COrderIDDlg::InsertData(int row, int col)
{
	GV_ITEM Item;
	BOOL bCheck;

	CGridCellCheck* pCell;

	m_pOrderID->Fields->GetItem("ID")->PutValue(m_sID.AllocSysString());
	CString str ;
	str = m_cGrid.GetItemText(row,col);
	switch(col)
	{
	case 1:
		m_pOrderID->Fields->GetItem("OrderID")->PutValue(str.AllocSysString());
		break;
	case 2:
		m_pOrderID->Fields->GetItem("ElevatorID")->PutValue(str.AllocSysString());
		break;
	case 3:
		m_pOrderID->Fields->GetItem("Remark")->PutValue(str.AllocSysString());
		break;
	case 4:
		pCell = (CGridCellCheck*)m_cGrid.GetCell(row,4);
		bCheck = pCell->GetCheck();
		m_pOrderID->Fields->GetItem("Status")->PutValue((_variant_t)bCheck);
		break;
	case 5:
		if(!RStatus[row-1].b_Judge)
		{
			m_pOrderID->Fields->GetItem("InputPerson")->PutValue(str.AllocSysString());
		}
		break;
	case 6:
		if(!RStatus[row-1].b_Judge)
		{
			m_pOrderID->Fields->GetItem("InputDate")->PutValue(str.AllocSysString());
		}
		break;
	case 7:
		m_pOrderID->Fields->GetItem("RePerson")->PutValue(g_strUserName.AllocSysString());
		break;
	case 8:
		str = m_dCurrent.Format("%Y-%m-%d");
		m_pOrderID->Fields->GetItem("ReDate")->PutValue(str.AllocSysString());
		break;
	default:
		break;
	}
}

void COrderIDDlg::LoadData(void)
{
	UpdateData(TRUE);
	CString str;
	int iCount,year,month,day;
	year = m_dCurrent.GetYear();
	month = m_dCurrent.GetMonth();
	day = m_dCurrent.GetDay();
	if(month == 12 && day >=28)
		year = year + 1;

	m_sYear.Format("%d",year);
	m_sYear = m_sYear.Right(2);
	try{

		m_pOrderID.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例
		m_pTempSet.CreateInstance(__uuidof(Recordset));

		strSQL = "select top 10 ID from PBInformation order by ID DESC ";
		theApp.ADOExecute(m_pTempSet,theApp.m_pConnect,  strSQL);
		iCount = m_pTempSet->GetRecordCount();
		m_cID.ResetContent();
		if(0!=iCount)
			m_pTempSet->MoveFirst();
		for(int j=0;j<iCount;j++)
		{
			Holder = m_pTempSet->GetCollect("ID");
			m_cID.InsertString(j,Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
			m_pTempSet->MoveNext();
		}
		m_pTempSet->Close();

		strSQL = "select * from TotalElevator where Year = '"+m_sYear+"'";
		theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
		iCount = m_pTempSet->GetRecordCount();
		if(iCount == 0)
		{
			m_iOrderNum = 0;
		}
		else 
		{
			Holder = m_pTempSet->GetCollect("CurrentTotal");
			m_iOrderNum = (int)Holder;
		}
		m_pTempSet->Close();

		if(!m_stemp.IsEmpty())
		{
			m_sID = m_stemp;

			strSQL = "select ID, ProjectName, SubCompanyName, Number from PBInformation where ID = '"+m_stemp+"'";
			theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
			iCount = m_pTempSet->GetRecordCount();
			if(iCount !=0)
			{
				m_pTempSet->MoveFirst();
				Holder = m_pTempSet->GetCollect("ID");
				m_sID = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
				SetDlgItemText(IDC_COMBO_ORDER_ID, m_sID);


				Holder = m_pTempSet->GetCollect("ProjectName");
				m_sProjectName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
				SetDlgItemText(IDC_EDIT_ORDER_PROJECTNAME, m_sProjectName);

				Holder = m_pTempSet->GetCollect("SubCompanyName");
				m_sSubCompanyName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

				Holder = m_pTempSet->GetCollect("Number");
				m_iNum = (int)Holder;

				m_pTempSet->Close();

				strSQL = "select * from OrderOfProject where ID = '"+m_sID+"'";
				theApp.ADOExecute(m_pOrderID, theApp.m_pConnect, strSQL);
				RefreshGrid();
				m_pOrderID->Close();

			}
			else
			{
				m_pTempSet->Close();
				return;
			}
		}
		else 
			return;

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
