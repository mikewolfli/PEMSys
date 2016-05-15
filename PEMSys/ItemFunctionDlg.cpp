// ItemFunctionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemFunctionDlg.h"
#include ".\itemfunctiondlg.h"
#include "./NewCellTypes/GridCellCheck.h"


// CItemFunctionDlg 对话框

IMPLEMENT_DYNAMIC(CItemFunctionDlg, CDialog)
CItemFunctionDlg::CItemFunctionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CItemFunctionDlg::IDD, pParent)
	, m_bStandard(FALSE)
	, m_sElevatorModel(_T(""))
	, m_sOrderID(_T(""))
	, m_bAdd(FALSE)
	, m_dCurrent(COleDateTime::GetCurrentTime())
	, m_bEdit(TRUE)
	, m_iStandard(0)
	, m_iSelect(0)
	, m_sEM(_T(""))
	, m_sController(_T(""))
{
}

CItemFunctionDlg::~CItemFunctionDlg()
{
}

void CItemFunctionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_FUNCTION_GRID, m_cGrid);
	DDX_Check(pDX, IDC_CHECK_FUNCTION_STANDARD, m_bStandard);
	DDX_Text(pDX, IDC_EDIT_FUNCTION_ELEVATORMODEL, m_sElevatorModel);
	DDX_Control(pDX, IDOK, m_cSave);
	DDX_Text(pDX, IDC_EDIT_FUNCTION_CONTROLLER, m_sController);
}


BEGIN_MESSAGE_MAP(CItemFunctionDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_FUNCTION_STANDARD, OnBnClickedCheckFunctionStandard)
	ON_WM_CLOSE()
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_CUSTOM_FUNCTION_GRID, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_CUSTOM_FUNCTION_GRID, OnGridEndEdit)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CItemFunctionDlg 消息处理程序

// GVN_BEGINLABELEDIT
void CItemFunctionDlg::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	BOOL bAllowEdit = !m_bEdit;

	*pResult = (bAllowEdit)? -1 : 0;
}

// GVN_ENDLABELEDIT
void CItemFunctionDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	BOOL bAcceptChange = !m_bEdit;

	*pResult = (bAcceptChange)? -1 : 0;
}

void CItemFunctionDlg::OnBnClickedCheckFunctionStandard()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CString strValue;
    if(((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_STANDARD))->GetCheck())
	{
         m_bStandard = TRUE;
		 strValue = _T("1");
	}
	else
	{
		m_bStandard = FALSE;
		strValue = _T("0");
	}

	RefreshGrid();
	char appPath[256];
	CString  FilePath;
	GetCurrentDirectory(256,appPath); //取得应用程序当前路径
	FilePath.Format("%s",appPath);
	FilePath+="\\Config.ini";

	CString strSection = _T("StandardOfFunction");
	CString strSectionKey  = _T("Check");
	
	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);
	UpdateData(FALSE);
}

BOOL CItemFunctionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);

	CString  FilePath;
	FilePath+=".\\Config.ini";

	CString strSection = _T("StandardOfFunction");
	CString strSectionKey  = _T("Check");
	CString strValue       = _T("");
	char inBuf[80];
	BOOL bCheck = GetPrivateProfileString (strSection,strSectionKey, NULL, inBuf, 80, FilePath); 
	
	if(bCheck)
	{
		strValue=inBuf;
		if(strValue == _T("1"))
		{
			m_bStandard = TRUE;
			((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_STANDARD))->SetCheck(TRUE);

		}
		else if(strValue == _T("0"))
		{
			m_bStandard = FALSE;
			((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_STANDARD))->SetCheck(FALSE);
		}
		else 
		{
			strValue = _T("1");
			m_bStandard = TRUE;
            ((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_STANDARD))->SetCheck(TRUE);
           	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);
		}
	}
	else
	{
		strValue = _T("0");
		m_bStandard = FALSE;
		((CButton*)GetDlgItem(IDC_CHECK_FUNCTION_STANDARD))->SetCheck(FALSE);
		WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);
	}

	UpdateData(FALSE);

	image_Status.Create(MAKEINTRESOURCE(IDB_STATUS), 16, 0, RGB(255,255,255));

	// 填充数据
	m_cGrid.SetEditable(m_bEdit);
	m_cGrid.SetImageList(&image_Status);
	m_cGrid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

	try {
		m_cGrid.SetColumnCount(7);
		m_cGrid.SetRowCount(1);
		m_cGrid.SetFixedRowCount(1);
		m_cGrid.SetFixedColumnCount(1);
		m_cGrid.MergeCells(0,1,0,3);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}

	if(g_tUserType<2)
	{
		m_cSave.EnableWindow(FALSE);
	}
	else 
	{
		m_cSave.EnableWindow(TRUE);
	}

	GV_ITEM Item;
	//	Item.mask = GVIF_TEXT;
	Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
	Item.row = 0;
	Item.col =0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	m_cGrid.SetAutoSizeStyle();
	m_cGrid.SetColumnWidth(0,40);
	m_cGrid.SetColumnWidth(1,30);
	m_cGrid.SetColumnWidth(2,50);
	m_cGrid.SetColumnWidth(3,200);
	m_cGrid.SetColumnWidth(4,40);
	m_cGrid.SetColumnWidth(5,40);
	m_cGrid.SetColumnWidth(6,200);


	for (int i=0;i<7;i++)
	{
		Item.row=0;
		Item.col=i;
		switch(i)
		{
		case 0:
			Item.strText.Format(_T("序号"));
			break;
		case 1:
			Item.strText.Format(_T("功能"));
			break;
		case 4:
			Item.strText.Format(_T("标准"));
			break;
		case 5:
			Item.strText.Format(_T("可选"));
			break;
		case 6:
			Item.strText.Format(_T("备注"));
			break;
		default:
			break;
		}
		m_cGrid.SetItem(&Item);
	}

	try{
		m_pFunctionSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例
		m_pTempSet.CreateInstance(__uuidof(Recordset));

		m_sElevatorModel = GetElevatorModel();
		m_sEM = m_sElevatorModel;
		m_sEM.Remove('-');
/*		if(m_sElevatorModel == _T("TE-E"))
			m_sEM = _T("TEE");
		else if(m_sElevatorModel==_T("TE-ES"))
			m_sEM = _T("TEES");
		else if(m_sElevatorModel == _T("TE-GL"))
			m_sEM = _T("TEGL");
		else if(m_sElevatorModel == _T("TE-GLS"))
			m_sEM = _T("TEGLS");
		else if(m_sElevatorModel == _T("TE-MRL"))
			m_sEM = _T("TEMRL");
		else if(m_sElevatorModel == _T("TE-MRLS"))
		   m_sEM = _T("TEMRLS");
		else if(m_sElevatorModel == _T("TE-GLM"))
			m_sEM = _T("TEGLM");
		else if(m_sElevatorModel == _T("TE-F"))
		   m_sEM = _T("TEF");*/

		SetDlgItemText(IDC_EDIT_FUNCTION_ELEVATORMODEL, m_sElevatorModel);

		strSQL = "select * from Controller where OrderID = '"+m_sOrderID+"'";
		theApp.ADOExecute(m_pFunctionSet,theApp.m_pConnect, strSQL);

		if(m_pFunctionSet->GetRecordCount()==0)
		{
			m_bAdd = TRUE;
		}
		else
		{
			m_bAdd = FALSE; 
		}
		RefreshGrid();       
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
	// 异常: OCX 属性页应返回 FALSE
}

CString CItemFunctionDlg::GetElevatorModel(void)
{
	CString Result;
	strSQL = "select ElevatorModel from Configuration where OrderID = '"+m_sOrderID+"'";
	theApp.ADOExecute(m_pFunctionSet,theApp.m_pConnect, strSQL);
	int iCount = m_pFunctionSet->GetRecordCount();
	if(0!=iCount)
	{
		Holder = m_pFunctionSet->GetCollect("ElevatorModel");
		Result = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	}
	else
	{
		Result = _T("");
		AfxMessageBox("该订单主要技术参数尚未添加\n请先添加",MB_ICONEXCLAMATION);
	}
	m_pFunctionSet->Close();
	return Result;
//	return CString();
}

void CItemFunctionDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(m_pFunctionSet->State == adStateOpen)
		m_pFunctionSet->Close();
	if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();

	m_pTempSet.Release();
	m_pFunctionSet.Release();

	CDialog::OnClose();
}

void CItemFunctionDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//	OnOK();
    int  iRow;
	HRESULT hr;
	CGridCellCheck* pCell;
    CString str,strTemp;
	GV_ITEM Item;

	UpdateData(TRUE);

	iRow = m_cGrid.GetRowCount();
	if(m_bAdd)
	{
		strSQL = "select * from Controller where OrderID = '"+m_sOrderID+"'";
		theApp.ADOExecute(m_pFunctionSet,theApp.m_pConnect,  strSQL);

	}
    for(int i=1;i< iRow;i++)
	{
		
        if(m_bStatus[i-1])
		{
			 str = m_cGrid.GetItemText(i,2);
			 str.Trim();
             if(m_bAdd)
			 {
				 m_pFunctionSet->AddNew();
				 m_pFunctionSet->Fields->GetItem("OrderID")->PutValue(m_sOrderID.AllocSysString());
			 }
			 else
			 {
				
				 strTemp = "Function= '"+str+"'";
				 _bstr_t strFind(strTemp);
				 m_pFunctionSet->MoveFirst();
				 hr = m_pFunctionSet->Find(strFind,0,adSearchForward);
			 }

			 m_pFunctionSet->Fields->GetItem("Function")->PutValue(str.AllocSysString());

			 str = m_cGrid.GetItemText(i, 3);
			 m_pFunctionSet->Fields->GetItem("Description")->PutValue(str.AllocSysString());
	
			 pCell = (CGridCellCheck*)m_cGrid.GetCell(i,5);
			  if(pCell)
			  {
			     BOOL bCheck = pCell->GetCheck();
			     m_pFunctionSet->Fields->GetItem("Check")->PutValue((_variant_t)bCheck);
			   }
             
			 str = m_cGrid.GetItemText(i, 6);
			 m_pFunctionSet->Fields->GetItem("Remark")->PutValue(str.AllocSysString());
             
			 m_pFunctionSet->Update();

			 Item.row = i;
			 Item.col = 1;
			 Item.iImage = 0;
			 Item.mask |= (GVIF_IMAGE);
			 m_cGrid.SetItem(&Item);
		}
	}
	m_cGrid.Invalidate();
	m_bAdd = FALSE;
	UpdateData(FALSE);

}

void CItemFunctionDlg::RefreshGrid(void)
{
	UpdateData(TRUE);

	CGridCellCheck* pCell;
	int i,n,j,m;
	short iCheck;
	CString str,strTemp;
	HRESULT hr;
	BOOL bCheck;

	GV_ITEM Item;

	if(m_pFunctionSet->State == adStateOpen)
		m_pFunctionSet->Close();
	if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();

	try{
		int iCount;
/*		strSQL = "select * from FunctionOfController where Elevator like'%"+m_sElevatorModel+";%' \
					and Controller like '%"+m_sController+";%' Order by ID ASC";
		theApp.ADOExecute(m_pTempSet,strSQL);
		iCount = m_pTempSet->GetRecordCount();
		m_pTempSet->Close();*/

        if(m_bStandard)
		{
			if(m_bAdd)
			{
				strSQL = "select * from FunctionOfController where Elevator like'%"+m_sElevatorModel+";%' \
				and Controller like '%"+m_sController+";%' Order by ID ASC";
				theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
				m_iStandard = m_pTempSet->GetRecordCount();
				m_iSelect = 0;
				iCheck = 0;
				
			}
			else
			{
				strSQL = "select * from FunctionOfController where Elevator like'%"+m_sElevatorModel+";%' \
						and Controller like '%"+m_sController+";%'  Order by id ASC";
                theApp.ADOExecute(m_pTempSet,theApp.m_pConnect,  strSQL);
				m_iStandard = m_pTempSet->GetRecordCount();
                
				strSQL = "select * from Controller where OrderID = '"+m_sOrderID+"'";
				theApp.ADOExecute(m_pFunctionSet,theApp.m_pConnect, strSQL);
				m_iSelect = 0;
				iCheck = 1;
			}
		}
		else
		{
			if(m_bAdd)
			{
				strSQL = "select * from FunctionOfController where Elevator like'%"+m_sElevatorModel+";%' \
				and Controller like '%"+m_sController+";%' and  "+m_sEM+"  = FALSE Order by ID ASC";
				theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
				m_iSelect = m_pTempSet->GetRecordCount();
				m_iStandard = 0;
				iCheck = 2;
			}
			else
			{
				strSQL = "select * from FunctionOfController where Elevator like'%"+m_sElevatorModel+";%' \
				and Controller like '%"+m_sController+";%' and  "+m_sEM+"  = FALSE Order by ID ASC";
				theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
				
				strSQL = "select * from Controller where OrderID = '"+m_sOrderID+"'";
				theApp.ADOExecute(m_pFunctionSet, theApp.m_pConnect, strSQL);
				int test = m_pTempSet->GetRecordCount();
				m_iSelect = m_pFunctionSet->GetRecordCount();	
				m_iStandard = 0;
				iCheck = 3;
			}
			
		}

		iCount = m_iSelect+m_iStandard;
		i = m_cGrid.GetRowCount();
		//	Item.mask = GVIF_TEXT;
		Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

		for(j = i-1 ; j>0;j--)
    	{
			m_cGrid.DeleteRow(j);
		}

		for(j = 1;j<=iCount;j++)
		{
			str.Format("%d",j);
			m_cGrid.InsertRow(str,-1);
		}

		m_bStatus.RemoveAll();
		m_bStatus.SetSize(iCount);
	
		switch(iCheck) {
		case 0:
			{
				if(iCount!=0)
				m_pTempSet->MoveFirst();
					n = 0;
				while (!m_pTempSet->EndOfFile) 
				{ 
					Item.row = n+1;


					Holder = m_pTempSet->GetCollect(m_sEM.AllocSysString());
					bCheck = Holder.boolVal;
					if(bCheck)
						m_bStatus[n] = FALSE; 
					else
						m_bStatus[n] = TRUE;

					for(m=0; m<7;m++)
					{
						Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
						Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;


						Item.col = m;

						switch (m)
						{
						case 0:
							Item.strText.Format("%d",n+1);
							break;
						case 1:
							Item.strText = _T("");
							break;
						case 2:
							Holder =  m_pTempSet->GetCollect("Function");
							Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
							break;
						case 3:
							Holder = m_pTempSet->GetCollect("Remark");
							Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
							break;
						case 4:

							if(bCheck)
							{
								m_cGrid.SetCellType(n+1,4, RUNTIME_CLASS(CGridCellCheck));
								pCell = (CGridCellCheck*)m_cGrid.GetCell(n+1,4);
								pCell->SetCheck(TRUE);
							}
							Item.strText = _T("");
							break;
						case 5:
							if(m_bStatus[n])
							{
								m_cGrid.SetCellType(n+1,5, RUNTIME_CLASS(CGridCellCheck));
								pCell = (CGridCellCheck*)m_cGrid.GetCell(n+1,5);						
								pCell->SetCheck(FALSE);
							}
							Item.strText = _T("");
							break;
						case 6:
							Item.strText= _T("");
							break;
						default:
							break;

						}
						if(m==1)
						{
							if(!m_bStatus[n])
								Item.iImage = 2;
							else if(m_bAdd && m_bStatus[n])
								Item.iImage = 1;
							else if(!m_bAdd)
								Item.iImage = 0;
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
					m_pTempSet->MoveNext();
				}
			
			break;
			}
		case 1:
			{
				if(iCount!=0)
				m_pTempSet->MoveFirst();
					n = 0;
				while (!m_pTempSet->EndOfFile) 
				{ 
					Item.row = n+1;

					Holder = m_pTempSet->GetCollect(m_sEM.AllocSysString());
					bCheck = Holder.boolVal;
					if(bCheck)
						m_bStatus[n] = FALSE;
					else
						m_bStatus[n] = TRUE;

					for(m=0; m<7;m++)
					{
						Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
						Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
                    
						Item.col = m;

						switch (m)
						{
						case 0:
							Item.strText.Format("%d",n+1);
							break;
						case 1:
							Item.strText = _T("");
							break;
						case 2:
							Holder =  m_pTempSet->GetCollect("Function");
							str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
							Item.strText = str;
							break;
						case 3:
							Holder = m_pTempSet->GetCollect("Remark");
							Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
							break;
						case 4:

							if(!m_bStatus[n])
							{
								m_cGrid.SetCellType(n+1,4, RUNTIME_CLASS(CGridCellCheck));
								pCell = (CGridCellCheck*)m_cGrid.GetCell(n+1,4);
								pCell->SetCheck(TRUE);
							}

							Item.strText = _T("");
							break;
						case 5:
							{
								if(m_bStatus[n])
								{
								strTemp = "Function= '"+str+"'";
								_bstr_t strFind(strTemp);
								m_pFunctionSet->MoveFirst();
								hr = m_pFunctionSet->Find(strFind,0,adSearchForward);

								 Holder = m_pFunctionSet->GetCollect("Check");



									 m_cGrid.SetCellType(n+1,5, RUNTIME_CLASS(CGridCellCheck));
									 pCell = (CGridCellCheck*)m_cGrid.GetCell(n+1,5);						
									 if(Holder.boolVal)
										pCell->SetCheck(TRUE);
									 else
										 pCell->SetCheck(FALSE);
								  }
								Item.strText = _T("");

								break;
							}
						case 6:
							if(m_bStatus[n])
							{
                               Holder = m_pFunctionSet->GetCollect("Remark");
							   Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);

							}
							else
							   Item.strText= _T("");
							break;
						default:
							break;

						}
						if(m==1)
						{
							if(!m_bStatus[n])
								Item.iImage = 2;
							else if(m_bAdd)
								Item.iImage = 1;
							else 
								Item.iImage = 0;
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
					m_pTempSet->MoveNext();
				}

			
			break;
			}
		case 2:
			{
				if(iCount!=0)
				m_pTempSet->MoveFirst();
					n = 0;
				while (!m_pTempSet->EndOfFile) 
				{ 
					Item.row = n+1;

					 m_bStatus[n] = TRUE;
					for(m=0; m<7;m++)
					{
						Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
						Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;


						Item.col = m;

						switch (m)
						{
						case 0:
							Item.strText.Format("%d",n+1);
							break;
						case 1:
							Item.strText = _T("");
							break;
						case 2:
							Holder =  m_pTempSet->GetCollect("Function");
							Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
							break;
						case 3:
							Holder = m_pTempSet->GetCollect("Remark");
							Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
							break;
						case 4:
							Item.strText = _T("");
							break;
						case 5:
							if(m_bStatus[n])
							{
								m_cGrid.SetCellType(n+1,5, RUNTIME_CLASS(CGridCellCheck));
								pCell = (CGridCellCheck*)m_cGrid.GetCell(n+1,5);						
								pCell->SetCheck(FALSE);
							}
							Item.strText = _T("");
							break;
						case 6:
							Item.strText= _T("");
							break;
						default:
							break;

						}
						if(m==1)
						{
							if(!m_bStatus[n])
								Item.iImage = 2;
							else if(m_bAdd && m_bStatus[n])
								Item.iImage = 1;
							else if(!m_bAdd)
								Item.iImage = 0;
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
					m_pTempSet->MoveNext();
				}
			
			break;
			}
		case 3:
			{
				if(iCount!=0)
				m_pFunctionSet->MoveFirst();
					n = 0;
				while (!m_pFunctionSet->EndOfFile) 
				{ 
					Item.row = n+1;

		            m_bStatus[n] = TRUE;

					for(m=0; m<7;m++)
					{
						Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
						Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;


						Item.col = m;

						switch (m)
						{
						case 0:
							Item.strText.Format("%d",n+1);
							break;
						case 1:
							Item.strText = _T("");
							break;
						case 2:
							Holder =  m_pFunctionSet->GetCollect("Function");
							str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
							Item.strText = str;
							break;
						case 3:
							{					
								strTemp = "Function= '"+str+"'";
								strTemp.Trim();
								_bstr_t strFind(strTemp);
								if(m_pTempSet->GetRecordCount()!=0)
									m_pTempSet->MoveFirst();
								hr = m_pTempSet->Find(strFind,0,adSearchForward);

								if(SUCCEEDED(hr))
								{
									Holder=m_pTempSet->GetCollect("Remark");
									Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
								}
								else
									Item.strText.Format(_T(""));
							
							break;
							}
						case 4:
							Item.strText = _T("");
							break;
						case 5:
							if(m_bStatus[n])
							{
								m_cGrid.SetCellType(n+1,5, RUNTIME_CLASS(CGridCellCheck));
								pCell = (CGridCellCheck*)m_cGrid.GetCell(n+1,5);						
								Holder = m_pFunctionSet->GetCollect("Check");
								if(Holder.boolVal)
									pCell->SetCheck(TRUE);
								else
									pCell->SetCheck(FALSE);
							}
							Item.strText = _T("");
							break;
						case 6:
							Holder = m_pFunctionSet->GetCollect("Remark");
							Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
							break;
						default:
							break;

						}
						if(m==1)
						{
							if(!m_bStatus[n])
								Item.iImage = 2;
							else if(m_bAdd)
								Item.iImage = 1;
							else 
								Item.iImage = 0;
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
					m_pFunctionSet->MoveNext();
				}
			
			break;
			}
		default:
			break;
		}

		for(m=1;m<=iCount;m++)
		{
			m_cGrid.SetItemState(m,1,m_cGrid.GetItemState(m,1) | GVIS_READONLY);
			m_cGrid.SetItemState(m,2,m_cGrid.GetItemState(m,2) | GVIS_READONLY);
			m_cGrid.SetItemState(m,3,m_cGrid.GetItemState(m,3) | GVIS_READONLY);
			m_cGrid.SetItemState(m,4,m_cGrid.GetItemState(m,4) | GVIS_READONLY);
			if(m_bStatus[m-1] == FALSE)
			{
				m_cGrid.SetItemState(m,5,m_cGrid.GetItemState(m,5) | GVIS_READONLY);
			}
			else
			{
				m_cGrid.SetItemState(m,5, m_cGrid.GetItemState(m,5) & ~GVIS_READONLY);
			}
		}
	}
	catch(CMemoryException* e)
	{
		e->ReportError();
		return;
	}
	m_cGrid.Invalidate();
	UpdateData(FALSE);

}
/*
void CItemFunctionDlg::UpdateGrid(_RecordsetPtr& pSet,int iRow)
{
	GV_ITEM Item;

	CGridCellCheck* pCell;
	COleDateTime dDate;

	for(int i=0;i<11;i++)
	{ 
		Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

		Item.col = i;
		switch(i) {
				   case 0:
					   Item.strText.Format("%d",iRow+1);
					   break;
				   case 1:
					   Item.strText = _T("");
					   break;
				   case 2:
					   Holder =  pSet->GetCollect("Function");
					   Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					   break;
				   case 3:
					   Holder = pSet->GetCollect("Remark");
					   Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					   break;
				   case 4:
					   Item.strText = _T("");
					   break;
				   case 5:
					   m_cGrid.SetCellType(iRow+1,5, RUNTIME_CLASS(CGridCellCheck));
					   pCell = (CGridCellCheck*)m_cGrid.GetCell(iRow+1,5);
					   if(m_bAdd)
						   pCell->SetCheck(FALSE);
					   else
					   {
						   Holder = pSet->GetCollect("Check");
						   if(Holder.boolVal)
							   pCell->SetCheck(TRUE);
						   else
							   pCell->SetCheck(FALSE);
					   }
					   break;
				   case 6:
					   if(m_bAdd)
						   Item.strText= _T("");
					   else
					   {
						   Holder = pSet->GetCollect("Remark");
						   Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
					   }
					   break;
				   case 7:
					   if(!m_bAdd)
					   {
						   Holder= m_pTempSet->GetCollect("InputPerson");
						   Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);  
					   }
					   else
						   Item.strText.Format(g_strUserName);
					   break;
				   case 8:
					   if(!m_bAdd)
					   {
						   Holder = m_pTempSet->GetCollect("InputDate");
						   dDate = Holder.date;
					   }
					   else
						   dDate = m_dCurrent;
					   Item.strText.Format(dDate.Format("%Y-%m-%d"));
					   break;
				   case 9:
					   if(!m_bAdd)
					   {
						   Holder = m_pTempSet->GetCollect("RePerson");
						   Item.strText.Format(Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder);
					   }
					   else
						   Item.strText.Format(g_strUserName);
					   break;
				   case 10:
					   if(!m_bAdd)
					   {

						   Holder = m_pTempSet->GetCollect("ReDate");
						   dDate = Holder.date;
					   }
					   else
						   dDate = m_dCurrent;
					   Item.strText.Format(dDate.Format("%Y-%m-%d"));
					   break;
				   default:
					   break;
		}
		if(i==1)
		{
			if(m_bStatus[m_iPos])
			    Item.iImage = 0;
			else
				Item.iImage = 1;
			Item.mask |= (GVIF_IMAGE);
		}
		else
		{
			Item.iImage = -1;
		}
		m_cGrid.SetItem(&Item);
		m_cGrid.AutoSizeRows();
	}

}
*/
void CItemFunctionDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
