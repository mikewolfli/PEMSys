// ItemCommerceSearchView.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemCommerceSearchView.h"
#include ".\itemcommercesearchview.h"
#include ".\gridctrl\gridctrl.h"
#include "DisplayConfigureDlg.h"
#include ".\excel\CSpreadSheet.h"
#include ".\NewCellTypes\GridCellDateTime.h"


// CItemCommerceSearchView

IMPLEMENT_DYNCREATE(CItemCommerceSearchView, CFormView)

CItemCommerceSearchView::CItemCommerceSearchView()
	: CFormView(CItemCommerceSearchView::IDD)
	, m_iCheck(0)
	, m_bEdit(TRUE)
	, m_iTotalCount(0)
	, m_dCurrent(COleDateTime::GetCurrentTime())
	, m_sOrderID(_T(""))
	, m_bSearch(FALSE)
	, m_iType(NULL)
	, m_iName(NULL)
	, m_iLink(0)
{
}

CItemCommerceSearchView::~CItemCommerceSearchView()
{
	if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();
	m_pTempSet.Release();
	if(m_pResult->State == adStateOpen)
		m_pResult->Close();
	m_pResult.Release();
	if(m_iType)
		delete [] m_iType;
	if(m_iName)
		delete [] m_iName;
}

void CItemCommerceSearchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_DISPLAY, m_cDisplay);
	DDX_Control(pDX, IDC_CUSTOM2, m_cSearchCase);
	DDX_Text(pDX, IDC_EDIT_TOTAL, m_iTotalCount);
}

BEGIN_MESSAGE_MAP(CItemCommerceSearchView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_PRINTCONFIGURE, OnBnClickedButtonPrintconfigure)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHCONFIGURE, OnBnClickedButtonSearchconfigure)
	ON_BN_CLICKED(IDC_BUTTON_SAVEAS, OnBnClickedButtonSaveas)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_CUSTOM2, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_CUSTOM2, OnGridEndEdit)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_PRINTVIEW, OnBnClickedButtonPrintview)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnBnClickedButtonPrint)
	ON_NOTIFY(NM_RCLICK, IDC_CUSTOM_DISPLAY, OnNMRclickGridData)
	ON_COMMAND(ID_SEARCH_ITEM, OnSearchItem)
	ON_COMMAND(ID_SEARCH_SAMEORDERID, OnSearchSameorderid)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUTORDER, OnBnClickedButtonOutputorder)
	ON_BN_CLICKED(IDC_RADIO_INNER, OnBnClickedRadioInner)
	ON_BN_CLICKED(IDC_RADIO_OUTER, OnBnClickedRadioOuter)
END_MESSAGE_MAP()


// CItemCommerceSearchView 诊断

#ifdef _DEBUG
void CItemCommerceSearchView::AssertValid() const
{
	CFormView::AssertValid();
}

void CItemCommerceSearchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CItemCommerceSearchView 消息处理程序

void CItemCommerceSearchView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	GetParentFrame()->RecalcLayout();
	//	 ResizeParentToFit();
	ResizeParentToFit(FALSE);
	ResizeParentToFit(TRUE);
	// TODO: 在此添加专用代码和/或调用基类                                                                                                                                                                                                                                                                                                  
	CString strTitle ;
	strTitle = "商务查询";
	GetParentFrame()->SetWindowText(strTitle);
   

	UpdateData(TRUE);
	try
	{
		m_pTempSet.CreateInstance(__uuidof(Recordset));
		m_pResult.CreateInstance(__uuidof(Recordset));
	}
	catch(_com_error &e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
		return;
	} 
	catch(...)
	{
		AfxMessageBox("未知错误...");
		return;
	}

	m_cSearchCase.SetEditable(m_bEdit);
	m_cSearchCase.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

	m_cDisplay.SetEditable(m_bEdit);
	m_cDisplay.GetDefaultCell(FALSE,FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

	try {
		m_cSearchCase.SetColumnCount(6);
		m_cSearchCase.SetRowCount(1);
		m_cSearchCase.SetFixedRowCount(1);
		m_cSearchCase.SetFixedColumnCount(1);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return;
	}


	GV_ITEM Item;
	//	Item.mask = GVIF_TEXT;
	Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
	Item.row = 0;
	Item.col =0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	m_cSearchCase.SetAutoSizeStyle();
	m_cSearchCase.SetRowHeight(0,30);
	m_cSearchCase.SetColumnWidth(0,40);
	m_cSearchCase.SetColumnWidth(5,40);


	for (int i=0;i<6;i++)
	{
		
		if(i>1&& i!=5)
		   m_cSearchCase.SetColumnWidth(i,100);
		Item.row=0;
		Item.col=i;
		switch(i)
		{
		case 0:
			Item.strText.Format(_T("序号"));
			break;
		case 1:
			Item.strText.Format(_T("查询条件"));
			break;
		case 2:
			Item.strText.Format(_T(">="));
			break;
		case 3:
			Item.strText.Format(_T("<="));
			break;
		case 4:
			Item.strText.Format(_T("="));
			break;
		case 5:
			Item.strText.Format(_T("判断"));
			break;
		default:
			break;
		}
		m_cSearchCase.SetItem(&Item);
	}
	LoadData();
	LoadDisplay();

	
	((CButton*)GetDlgItem(IDC_RADIO_INNER))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_OUTER))->SetCheck(FALSE);

	UpdateData(FALSE);
}

void CItemCommerceSearchView::OnBnClickedButtonPrintconfigure()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDisplayConfigureDlg m_dlg;
    m_iCheck = 2;
	m_dlg.m_iCheck = m_iCheck;
	int InitRet;
	InitRet = m_dlg.DoModal();

	switch(InitRet) 
	{
	case -1: 
		MessageBox("对话框创建失败！","Client Error:", MB_OK);
		return;
		break;
	case IDCANCEL:
		return;
		break;
	case IDOK:
		LoadDisplay();
		if(m_bSearch)
		  OnBnClickedOk();
		break;
	default:
		break;
	}

	UpdateData(FALSE);

}

BOOL CItemCommerceSearchView::PreTranslateMessage(MSG* pMsg)
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


	return CFormView::PreTranslateMessage(pMsg);
}

void CItemCommerceSearchView::OnBnClickedButtonSearchconfigure()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDisplayConfigureDlg m_dlg;
	m_iCheck = 1;
	m_dlg.m_iCheck = m_iCheck;
	int InitRet;
	InitRet = m_dlg.DoModal();
	switch(InitRet) 
	{
	case -1: 
		MessageBox("对话框创建失败！","Client Error:", MB_OK);
		return;
		break;
	case IDCANCEL:
        return;
		break;
	case IDOK:
		LoadData();
		break;
	default:
		break;
	}

//	if(InitRet == IDOK)
//		 LoadData();
	UpdateData(FALSE);
}

void CItemCommerceSearchView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值



	CFormView::OnClose();
}

// GVN_BEGINLABELEDIT
void CItemCommerceSearchView::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	BOOL bAllowEdit = !m_bEdit;

	*pResult = (bAllowEdit)? -1 : 0;
}

// GVN_ENDLABELEDIT
void CItemCommerceSearchView::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	BOOL bAcceptChange = !m_bEdit;

	*pResult = (bAcceptChange)? -1 : 0;
}

void CItemCommerceSearchView::LoadData(void)
{
	CGridCellCheck* pCellCheck;
	CGridCellDateTime* pCellDate;
	GV_ITEM Item;

	m_cSearchCase.DeleteNonFixedRows();



	try{

		int iCount ;

		strSQL = " select * from SearchCase  where Check = TRUE order by ID";
		theApp.ADOExecute(m_pTempSet, theApp.m_pSearchConn,  strSQL);
        iCount  = theApp.GetRecordCountEx(m_pTempSet);
		
	//	if(m_iType)
	//		delete [] m_iType;
	//	m_iType = new int[iCount];
		CString str;
		if(iCount !=0)
			m_pTempSet->MoveFirst();
		int i = 0;
		if(m_iType)
			delete [] m_iType;
		m_iType = new ItemRow[iCount];
		while(!m_pTempSet->EndOfFile)
		{

			str.Format("%d",i+1);

			m_cSearchCase.InsertRow(str, -1);
			
			Holder = m_pTempSet->GetCollect(_T("Name"));
			m_iType[i].sName  = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			
			Holder = m_pTempSet->GetCollect(_T("Item"));
			m_iType[i].sItem  = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

			Holder = m_pTempSet->GetCollect(_T("Type"));
			m_iType[i].tType  = (int)Holder;
           
			Holder = m_pTempSet->GetCollect(_T("Table"));
			m_iType[i].sTable = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

			Item.row = i+1;
			for(int j = 0;j<6; j++)
			{
				Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

				Item.col = j;

				switch(j) {
			case 0:
				Item.strText.Format("%d",i+1);
				break;
			case 1:				
				Item.strText = m_iType[i].sName;
				break;
			case 2:
				if(m_iType[i].tType==2)
				{
					m_cSearchCase.SetCellType(i+1,j, RUNTIME_CLASS(CGridCellDateTime));

					pCellDate = (CGridCellDateTime*) m_cSearchCase.GetCell(i+1,j);
					pCellDate->SetTime(CTime::GetCurrentTime());
				//	Item.strText = _T("1900-1-1");
				}
			//	else
					Item.strText = _T("");
				break;
			case 3:
				if(m_iType[i].tType == 2)
				{
					m_cSearchCase.SetCellType(i+1,j, RUNTIME_CLASS(CGridCellDateTime));

					pCellDate = (CGridCellDateTime*) m_cSearchCase.GetCell(i+1,j);
					pCellDate->SetTime(CTime::GetCurrentTime());
				//	Item.strText = m_dCurrent.Format("%Y-%m-%d");
				}
			//	else
					Item.strText = _T("");
				
				break;
			case 4:
				Item.strText = _T("");
				break;
			case 5:
                if(m_iType[i].tType == 4)
				{
					m_cSearchCase.SetCellType(i+1,j, RUNTIME_CLASS(CGridCellCheck));
					pCellCheck = (CGridCellCheck*)m_cSearchCase.GetCell(i+1,j);
					pCellCheck->SetCheck(FALSE);
				}
				Item.strText = _T("");
				break;
			default:
				break;
				}
				m_cSearchCase.SetItem(&Item);
				
			}

			m_cSearchCase.Invalidate();
			m_pTempSet->MoveNext();
			i++;
		}
		m_cSearchCase.AutoSizeRows();
        
		m_cSearchCase.SetColumnWidth(2,100);
		m_cSearchCase.SetColumnWidth(3,100);
		m_cSearchCase.SetColumnWidth(4,100);
		for(int m= 0; m<iCount;m++)
		{
			switch(m_iType[m].tType) {
				//RGB(0xFF, 0xFF, 0xE0)
		case 1:
			m_cSearchCase.SetItemBkColour(m+1,2,RGB(0,0,0));
			m_cSearchCase.SetItemBkColour(m+1,3,RGB(0,0,0));
			m_cSearchCase.SetItemBkColour(m+1,5,RGB(0,0,0));
            m_cSearchCase.SetItemBkColour(m+1,4,RGB(0xFF, 0xFF, 0xE0));
			m_cSearchCase.SetItemState(m+1,4,m_cSearchCase.GetItemState(m+1,4) & ~GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,2,m_cSearchCase.GetItemState(m+1,2) | GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,3,m_cSearchCase.GetItemState(m+1,3) | GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,5,m_cSearchCase.GetItemState(m+1,5) | GVIS_READONLY);
			break;
		case 2:
			m_cSearchCase.SetItemBkColour(m+1,2,RGB(0xFF, 0xFF, 0xE0));
			m_cSearchCase.SetItemBkColour(m+1,3,RGB(0xFF, 0xFF, 0xE0));
			m_cSearchCase.SetItemBkColour(m+1,5,RGB(0,0,0));
			m_cSearchCase.SetItemBkColour(m+1,4,RGB(0, 0, 0));
			m_cSearchCase.SetItemState(m+1,4,m_cSearchCase.GetItemState(m+1,4) | GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,2,m_cSearchCase.GetItemState(m+1,2) & ~GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,3,m_cSearchCase.GetItemState(m+1,3) & ~GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,5,m_cSearchCase.GetItemState(m+1,5) | GVIS_READONLY);
			break;
		case 3:
			m_cSearchCase.SetItemBkColour(m+1,2,RGB(0xFF, 0xFF, 0xE0));
			m_cSearchCase.SetItemBkColour(m+1,3,RGB(0xFF, 0xFF, 0xE0));
			m_cSearchCase.SetItemBkColour(m+1,5,RGB(0,0,0));
			m_cSearchCase.SetItemBkColour(m+1,4,RGB(0, 0, 0));
			m_cSearchCase.SetItemState(m+1,4, m_cSearchCase.GetItemState(m+1,4) | GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,2,m_cSearchCase.GetItemState(m+1,2) & ~GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,3,m_cSearchCase.GetItemState(m+1,3) & ~GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,5,m_cSearchCase.GetItemState(m+1,5) | GVIS_READONLY);
			break;
		case 4:
			m_cSearchCase.SetItemBkColour(m+1,2,RGB(0, 0, 0));
			m_cSearchCase.SetItemBkColour(m+1,3,RGB(0, 0, 0));
			m_cSearchCase.SetItemBkColour(m+1,5,RGB(0xFF, 0xFF, 0xE0));
			m_cSearchCase.SetItemBkColour(m+1,4,RGB(0, 0, 0));
			m_cSearchCase.SetItemState(m+1,4, m_cSearchCase.GetItemState(m+1,4) | GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,2, m_cSearchCase.GetItemState(m+1,2) | GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,3, m_cSearchCase.GetItemState(m+1,3) | GVIS_READONLY);
			m_cSearchCase.SetItemState(m+1,5, m_cSearchCase.GetItemState(m+1,5) & ~GVIS_READONLY);
			break;
		default:
			break;
			}
			m_cSearchCase.SetItemState(m+1,1,m_cSearchCase.GetItemState(m+1,1) | GVIS_READONLY);
		}

		m_pTempSet->Close();
      
	}
	catch(_com_error &e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信
		return;
	} 
	catch(...)
	{
		AfxMessageBox("未知错误...");
		return;
	}
}

void CItemCommerceSearchView::OnBnClickedButtonSaveas()
{
	// TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);
	CString strFileName,str,strPath;
	int iName;
	time_t t;

	int iCol,iRow;
	iRow= m_cDisplay.GetRowCount();
    iCol = m_cDisplay.GetColumnCount();
	if(iRow ==1)
	{
		AfxMessageBox("列表中无记录,无法保存!",MB_ICONEXCLAMATION);
		return;
	}
	else
	{
		srand((unsigned) time(&t));
		iName =rand()+1000;
		str.Format("%4d",iName);
		strFileName = g_strUserID +"_"+str;

		CFileDialog fileDlg( FALSE,_T("XLS"),strFileName,
			OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT,
			_T("Excel (*.XLS)|*.XLS|Word (*.DOC)|*.DOC|文本文件 (*.TXT)|*.TXT|"));
        
		strPath  = ".\\OutFile\\";
		SetCurrentDirectory((LPCSTR)strPath);
		if( fileDlg.DoModal ()==IDOK )
		{
            str = fileDlg.GetFileExt();
			strPath = fileDlg.GetPathName();
			strFileName = fileDlg.GetFileName();
			if(str.MakeUpper() == "XLS")
			{
                OnExcelOut(strPath, strFileName);
			}
			else if(str.MakeUpper() == "DOC")
			{

			}
			else if(str.MakeUpper() == "TXT")
			{

			}
		}
		else
			return;

	}
    
	UpdateData(FALSE);

}

void CItemCommerceSearchView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
    

	int iCase = m_cSearchCase.GetRowCount()-1;
    int iDispay = m_cDisplay.GetColumnCount()-1;

	m_cDisplay.DeleteNonFixedRows();
    CString str,strCase1,strCase2,str1,str2;

	CGridCellCheck* pCell; 
	BOOL bCheck;

	if(iCase == 0)
	{
		AfxMessageBox("查询条目为空,请先定制查询条件!",MB_ICONEXCLAMATION);
		return;
	}
	if(iDispay==0)
	{
		AfxMessageBox("显示条目为空,请先显示设置!",MB_ICONEXCLAMATION);
		return;
	}
	str = "select DISTINCT";
    for(int i= 0;i<iDispay;i++)
	{
        str = str + " " +m_iName[i].sTable+"."+m_iName[i].sItem + " ";
//		str = str + " " +m_iName[i].sItem + " ";
		if(i<iDispay-1)
			str = str+", ";

	}

	switch(m_iLink)
	{
	case 0:
//	   str  = str+"from (PBInformation INNER JOIN (Configuration INNER JOIN  OrderOfProject ON Configuration.OrderID = OrderOfProject.OrderID) ON PBInformation.ID = OrderOfProject.ID) INNER JOIN Delivery ON (Configuration.OrderID = Delivery.OrderID) AND (OrderOfProject.OrderID = Delivery.OrderID)  where (";
	   str  = str+"from (Configuration LEFT JOIN Controller ON Configuration.OrderID = Controller.OrderID) INNER JOIN (PBInformation INNER JOIN (OrderOfProject INNER JOIN Delivery ON OrderOfProject.OrderID = Delivery.OrderID) ON PBInformation.ID = OrderOfProject.ID) ON Configuration.OrderID = OrderOfProject.OrderID  where (";
       break;
	case 1:
		str= str + " from (Configuration LEFT JOIN Controller ON Configuration.OrderID = Controller.OrderID) RIGHT JOIN (PBInformation INNER JOIN (OrderOfProject LEFT JOIN Delivery ON OrderOfProject.OrderID = Delivery.OrderID) ON PBInformation.ID = OrderOfProject.ID) ON Configuration.OrderID = OrderOfProject.OrderID where (";
//	   str= str + " from (PBInformation OUTER JOIN (Configuration OUTER JOIN OrderOfProject ON Configuration.OrderID = OrderOfProject.OrderID) ON PBInformation.ID = OrderOfProject.ID) OUTER JOIN Delivery ON OrderOfProject.OrderID = Delivery.OrderID where (";
		break;
	default:
		break;
	}

//	str  = str+"from OrderOfProject INNER JOIN Delivery (INNER JOIN Configuration ON Delivery.OrderID = Configuration.OrderID)   where ";

	for(int j= 0;j<iCase;j++)
	{
		
		  if(j!=0)
			str = str + " and ";
          switch(m_iType[j].tType) {
          case 1:
            strCase1 = m_cSearchCase.GetItemText(j+1,4);
			strCase2= strCase1;
			if(m_iType[j].sItem == _T("OrderID"))
			{
				strCase2.Remove(' ');
				if(strCase2.GetLength()==8)
				{
				  str1= strCase2.Left(2);
				  str2 = strCase2.Mid(2,2);
				  strCase2 = strCase2.Right(4);
				  strCase2 = str1 + " " + str2 + " " +strCase2;
				  strCase1 = strCase2 ;
				}
			}
			str = str + " " + m_iType[j].sTable +"."+m_iType[j].sItem +" like  '%"+strCase1+"%'";
          	break;
          case 2:
            strCase1 =  m_cSearchCase.GetItemText(j+1, 2);
			strCase2 = m_cSearchCase.GetItemText(j+1,3);
			if(strCase1.IsEmpty()&&strCase2.IsEmpty())
				str= str +" " + m_iType[j].sTable+"."+m_iType[j].sItem+" Is Null";
			else{
			if(strCase1.IsEmpty())
				strCase1 = "1900-01-01";
			if(strCase2.IsEmpty())
				strCase2 = "9999-12-31";
			str = str+" " +  m_iType[j].sTable +"."+m_iType[j].sItem+ " >= #"+strCase1+"# and "+ m_iType[j].sTable +"."+m_iType[j].sItem+" <= #"+strCase2+"#";
			}
          	break;
		  case 3:
            strCase1 = m_cSearchCase.GetItemText(j+1, 2);
			strCase2 = m_cSearchCase.GetItemText(j+1, 3);
            if(strCase1.IsEmpty())
                 strCase1 = "0";
			if(strCase2.IsEmpty())
				strCase2 = "999999999";
			str = str + " " +  m_iType[j].sTable +"."+ m_iType[j].sItem+">= "+strCase1 + " and " +  m_iType[j].sTable +"."+ m_iType[j].sItem+" <= "+strCase2;
			break;
		  case 4:
			 pCell = (CGridCellCheck*)m_cSearchCase.GetCell(j+1, 5);
			 bCheck = pCell->GetCheck();
             if(bCheck)
				 strCase1 = "TRUE";
			 else 
				 strCase1 = "FALSE";
			 str = str +" " +  m_iType[j].sTable +"."+ m_iType[j].sItem + " = " + strCase1;
			break;
          default:
		    break;
          }
  
	}

	str= str +")";
	strSQL = str.AllocSysString();

	try{
		theApp.ADOExecute(m_pResult, theApp.m_pConnect, strSQL);
		int iCount  = theApp.GetRecordCountEx(m_pResult);
		m_iTotalCount = iCount;
	
		if(iCount==0)
		{
			AfxMessageBox(_T("没有所要查询的内容!"),MB_ICONEXCLAMATION);
			m_cDisplay.DeleteNonFixedRows();
			m_iTotalCount = 0;
			m_bSearch = FALSE;
			return;
		}
		else
		{
			m_bSearch = TRUE;
			m_pResult->MoveFirst();
            for(int i=1;i<=iCount;i++)
			{
				str.Format("%d",i);

				m_cDisplay.InsertRow(str, -1);
				RefreshGrid(m_pResult, i);
				m_pResult->MoveNext();
			}
		}

	}
	catch(_com_error &e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信
		return;
	} 
	catch(...)
	{
		AfxMessageBox("未知错误...");
		return;
	}
	UpdateData(FALSE);

}

void CItemCommerceSearchView::RefreshGrid(_RecordsetPtr& pSet,int row)
{
	int iCol = m_cDisplay.GetColumnCount()-1;
    GV_ITEM Item;
	COleDateTime dTemp,dCompare;
    CGridCellCheck* pCell;
	BOOL bCheck;
	CString str;

	Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	m_cDisplay.SetListMode(TRUE);
	m_cDisplay.SetSingleRowSelection(FALSE);
	Item.row = row;
	Item.col = 0;
	Item.strText.Format("%d",row);
	m_cDisplay.SetItem(&Item);
	for(int i = 0; i<iCol; i++)
	{

		Item.col = i+1;

		Holder = pSet->GetCollect(m_iName[i].sItem.AllocSysString());
		switch(m_iName[i].tType) {
		case 1:
			Item.strText = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			break;
		case 2:
			dTemp = Holder.date;
			str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			if(str.IsEmpty())
			{
				Item.strText = _T("- -");
			}
			else
			    Item.strText = dTemp.Format("%Y-%m-%d");
			break;
		case 3:
		//	dbNum = (double)Holder;
		//	Item.strText.Format("%f",dbNum);
			Item.strText = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
			break;
		case  4:
			m_cDisplay.SetCellType(row,i+1, RUNTIME_CLASS(CGridCellCheck));
			pCell = (CGridCellCheck*)m_cDisplay.GetCell(row,i+1);
			bCheck = (bool)Holder;
			if(bCheck)
				pCell->SetCheck(TRUE);
			else
				pCell->SetCheck(FALSE);
			Item.strText = "";
			break;
		default:
			break;
		}

		m_cDisplay.SetItem(&Item);
	} 
	m_cDisplay.Invalidate();
    m_cDisplay.AutoSizeColumns();
}

void CItemCommerceSearchView::LoadDisplay(void)
{
    
	m_cDisplay.DeleteAllItems();

	try{
		int iCount;

		strSQL = " select * from PrintDiplay  where Check = TRUE order by ID";
		theApp.ADOExecute(m_pTempSet,theApp.m_pSearchConn,strSQL);

        iCount = theApp.GetRecordCountEx(m_pTempSet);

		m_cDisplay.SetColumnCount(iCount+1);
		m_cDisplay.SetRowCount(1);
		m_cDisplay.SetFixedRowCount(1);
		m_cDisplay.SetFixedColumnCount(1);


		GV_ITEM Item;
		//	Item.mask = GVIF_TEXT;
		Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
		Item.row = 0;
		Item.col =0;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
		m_cDisplay.SetAutoSizeStyle();
		m_cDisplay.SetRowHeight(0,30);
		m_cDisplay.SetColumnWidth(0,30);

		m_cDisplay.SetListMode(TRUE);
		m_cDisplay.SetSingleRowSelection(TRUE);

		if(iCount!=0)
			m_pTempSet->MoveFirst();

		if(m_iName)
			delete [] m_iName;
		m_iName = new ItemRow[iCount];
        int i = 0;
		while(!m_pTempSet->EndOfFile)
		{
			

			Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
			Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
			

			Holder = m_pTempSet->GetCollect(_T("Name"));
			m_iName[i].sName  = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

			Holder = m_pTempSet->GetCollect(_T("Item"));
			m_iName[i].sItem  = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

			Holder = m_pTempSet->GetCollect(_T("Type"));
			m_iName[i].tType  = (int)Holder;

			Holder = m_pTempSet->GetCollect(_T("Table"));
			m_iName[i].sTable = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

			Item.row = 0;

			Item.col = i+1;

			
			Item.strText = m_iName[i].sName;
			m_cDisplay.SetItem(&Item);
			m_cSearchCase.Invalidate();

			m_pTempSet->MoveNext();
			i++;
		}
        m_cDisplay.AutoSizeColumns();
		m_pTempSet->Close();


	} 
	catch(_com_error &e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信
		return;
	} 
	catch(...)
	{
		AfxMessageBox("未知错误...");
		return;
	}
}

void CItemCommerceSearchView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	LoadData();
	LoadDisplay();
	m_iTotalCount = 0;
	m_bSearch = FALSE;
	if(m_pResult->State == adStateOpen)
		m_pResult->Close();
	UpdateData(FALSE);
}

void CItemCommerceSearchView::OnBnClickedButtonPrintview()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CItemCommerceSearchView::OnBnClickedButtonPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	

}

void CItemCommerceSearchView::OnNMRclickGridData(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码 
	CPoint PointCellRelative;
    CCellID pCell,pStart;
	pStart = CCellID(0,0);
	int nCol = m_cDisplay.GetColumnCount()-1;
	pCell = m_cDisplay.GetNextItem(pStart, GVNI_BELOW | GVNI_FOCUSED | GVNI_TORIGHT);
	if(pCell.row==0xffffffff)
	{
		m_sOrderID.Empty();
		return;
	}
	else
	{    
	/*	m_cDisplay.SetSelectedRange(pCell.row,1,pCell.row,nCol,FALSE,TRUE);
		m_sOrderID = m_cDisplay.GetItemText(pCell.row,1);
		::GetCursorPos(&PointCellRelative); //where is the mouse?
		CMenu menu; //lets display out context menu :) 
//		DWORD dwSelectionMade;                                       
		VERIFY(menu.LoadMenu(IDR_MENU_POP_SEARCH));  
		CMenu *pmenuPopup = menu.GetSubMenu(0);
		ASSERT(pmenuPopup != NULL);                                       
//		dwSelectionMade = pmenuPopup->TrackPopupMenu( (TPM_LEFTALIGN|TPM_LEFTBUTTON|
//			TPM_NONOTIFY|TPM_RETURNCMD),
//			PointCellRelative.x, PointCellRelative.y, this
//			);   
		
		pmenuPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,PointCellRelative.x,PointCellRelative.y,this);

        pmenuPopup->DestroyMenu(); */
	}
		// Exercise for the reader...deal with the user's choice here :)                                      
}

void CItemCommerceSearchView::OnSearchItem()
{
	// TODO: 在此添加命令处理程序代码
	CSearchPopItemDlg lDlg;
	lDlg.m_sOrderID = m_sOrderID;
	if(!m_sOrderID.IsEmpty())
		lDlg.DoModal();
	else
		return;

}

void CItemCommerceSearchView::OnSearchSameorderid()
{
	// TODO: 在此添加命令处理程序代码
	CSearchPopOrderIDDlg lDlg;
	lDlg.m_sOrderID = m_sOrderID;
	if(!m_sOrderID.IsEmpty())
		lDlg.DoModal();
	else
		return;

}

void CItemCommerceSearchView::OnExcelOut(CString filepath, CString filename)
{
	CSpreadSheet sOutFile(filepath, "ListSheet");

	CStringArray readArray;
	CGridCellCheck *pCell;
	BOOL bCheck;

	sOutFile.BeginTransaction();
  // 加入标题
	int iCol = m_cDisplay.GetColumnCount();
	int iRow = m_cDisplay.GetRowCount();
    readArray.RemoveAll();
	int i,j;
	CString str;
    for(i =0; i< iCol;i++)
	{
        str = m_cDisplay.GetItemText(0,i);
		if(str =="")
			str= "0";
	     readArray.Add(str);
	}
	sOutFile.AddHeaders(readArray);

	// 加入数据

	for(i = 1; i < iRow; i++)
	{
		readArray.RemoveAll();
        for(j=0;j<iCol;j++) 
		{
			if(j>=1 && m_iName[j-1].tType == 4)
			{
				 pCell = (CGridCellCheck*)m_cDisplay.GetCell(i,j);
                bCheck = pCell->GetCheck();
				if(bCheck)
					str = "TRUE";
				else
					str = "FALSE";
			}
			else
			{
			   str = m_cDisplay.GetItemText(i,j);
			   if(str=="")
				   str = "/";
			}

			readArray.Add(str);
		}
		sOutFile.AddRow(readArray,i+1);
	}
  
	sOutFile.Commit();	

	AfxMessageBox("查询结果已经保存为文件:\n "+filename);
    
}

void CItemCommerceSearchView::OnBnClickedButtonOutputorder()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CItemCommerceSearchView::OnBnClickedRadioInner()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_iLink!=0)
	{
		m_iLink = 0;
	}


	UpdateData(FALSE);
}

void CItemCommerceSearchView::OnBnClickedRadioOuter()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(m_iLink!=1)
	{
		m_iLink =1;
	}

	UpdateData(FALSE);
}
