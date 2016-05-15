// DisplayConfigureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "DisplayConfigureDlg.h"
#include ".\displayconfiguredlg.h"


// CDisplayConfigureDlg 对话框

IMPLEMENT_DYNAMIC(CDisplayConfigureDlg, CDialog)
CDisplayConfigureDlg::CDisplayConfigureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayConfigureDlg::IDD, pParent)
	, m_iCheck(0)
	, m_bEdit(TRUE)
{
}

CDisplayConfigureDlg::~CDisplayConfigureDlg()
{
}

void CDisplayConfigureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM1, m_cConfigure);
}


BEGIN_MESSAGE_MAP(CDisplayConfigureDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_CUSTOM1, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_CUSTOM1, OnGridEndEdit)
//	ON_WM_CLOSE()
ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDisplayConfigureDlg 消息处理程序

BOOL CDisplayConfigureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strTitle ;
	switch(m_iCheck) {
			strTitle = "查询条件设置";
			this->SetWindowText(strTitle);
		break;
	case 2:
		strTitle = "显示设置";
		this->SetWindowText(strTitle);
		break;
	default:
		break;
	}
	m_cConfigure.SetEditable(TRUE);
	m_cConfigure.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

	try
	{

		m_pTempSet.CreateInstance(__uuidof(Recordset));
	}
	catch(_com_error &e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
		return FALSE;
	} 
	catch(...)
	{
		AfxMessageBox("未知错误...");
		return FALSE;
	}

	try {
		m_cConfigure.SetColumnCount(4);
		m_cConfigure.SetRowCount(1);
		m_cConfigure.SetFixedRowCount(1);
		m_cConfigure.SetFixedColumnCount(1);
	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return FALSE;
	}


	GV_ITEM Item;
	//	Item.mask = GVIF_TEXT;
	Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
	Item.row = 0;
	Item.col =0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	m_cConfigure.SetAutoSizeStyle();
	m_cConfigure.SetRowHeight(0,30);
	m_cConfigure.SetColumnWidth(0,40);
	m_cConfigure.SetColumnWidth(3,40);
	m_cConfigure.SetColumnWidth(2,0);
	for (int i=0;i<4;i++)
	{

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
			Item.strText.Format(_T(""));
			break;
		case 3:
			Item.strText.Format(_T("判断"));
			break;
		default:
			break;
		}
		m_cConfigure.SetItem(&Item);
	}
    
   LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDisplayConfigureDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);
    	
	CString strName, strItem;
	GV_ITEM Item;
	try{
		switch(m_iCheck) {
		case 1:
			strSQL = "select * from SearchCase order by ID";
			break;
		case 2:
			strSQL = "select * from PrintDiplay order by ID";
			break;
		default:
			return;
		}
		theApp.ADOExecute(m_pTempSet, theApp.m_pSearchConn,  strSQL);

		int iCount = m_pTempSet->GetRecordCount();

		if(iCount!=0)
		{
		    m_pTempSet->MoveFirst();
			if(m_iCheck == 2)
			   m_pTempSet->MoveNext();
		}

		int i = 0;
		while(!m_pTempSet->EndOfFile)
		{
			InsertData(m_pTempSet, i+1, 3);
			m_pTempSet->Update();
			m_pTempSet->MoveNext();
			i++;
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

	OnOK();
	UpdateData(FALSE);
}

// GVN_BEGINLABELEDIT
void CDisplayConfigureDlg::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	BOOL bAllowEdit = !m_bEdit;

	*pResult = (bAllowEdit)? -1 : 0;
}

// GVN_ENDLABELEDIT
void CDisplayConfigureDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
	BOOL bAcceptChange = !m_bEdit;

	*pResult = (bAcceptChange)? -1 : 0;
}

void CDisplayConfigureDlg::LoadData(void)
{
    CGridCellCheck* pCellCheck;
    GV_ITEM Item;
	BOOL bCheck;

	m_cConfigure.DeleteNonFixedRows();
    CString str;
	try{
		switch(m_iCheck) {
		case 1:
			strSQL = "select * from SearchCase order by ID";
			break;
		case 2:
			strSQL = "select * from PrintDiplay order by ID";
			break;
		default:
			return;
		}
		theApp.ADOExecute(m_pTempSet, theApp.m_pSearchConn,  strSQL);

		int iCount = theApp.GetRecordCountEx(m_pTempSet);
		if(iCount != 0)
		{
			m_pTempSet->MoveFirst();
			if(m_iCheck == 2)
			 m_pTempSet->MoveNext();
		}

		int i=0;
		while(!m_pTempSet->EndOfFile)
		{
			str.Format("%d",i+1);
			m_cConfigure.InsertRow(str, -1);

			Item.row = i+1;
            
			for(int j= 0; j<4;j++)
			{
				Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
				Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;

				Item.col = j;

				switch(j) {
				case 0:
                    Item.strText.Format("%d",i+1);
					break;
				case 1:
					Holder = m_pTempSet->GetCollect("Name");
					Item.strText = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
					break;
				case 2:
					Holder = m_pTempSet->GetCollect("Item");
					Item.strText = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
					break;
				case 3:
					m_cConfigure.SetCellType(i+1,j, RUNTIME_CLASS(CGridCellCheck));
					pCellCheck = (CGridCellCheck*)m_cConfigure.GetCell(i+1,j);
				    Holder = m_pTempSet->GetCollect("Check");
                    bCheck = (bool)Holder;
					if(bCheck)
					   pCellCheck->SetCheck(TRUE);
					else
						pCellCheck->SetCheck(FALSE);
					Item.strText = _T("");
					break;
				default:
					break;
				}
			    m_cConfigure.SetItem(&Item);
			}   
			m_pTempSet->MoveNext();
			i++;
		}

		m_cConfigure.AutoSizeRows();
		m_cConfigure.AutoSizeColumns();

		m_cConfigure.SetColumnWidth(2,0);

		if(m_iCheck == 2)
			iCount = iCount -1;
		for(int m=0 ;m<iCount; m++)
		{
			m_cConfigure.SetItemState(m+1,3,m_cConfigure.GetItemState(m+1,3) & ~GVIS_READONLY);
			m_cConfigure.SetItemState(m+1,1,m_cConfigure.GetItemState(m+1,1) | GVIS_READONLY);
			m_cConfigure.SetItemState(m+1,2,m_cConfigure.GetItemState(m+1,2) | GVIS_READONLY);
		}
		m_pTempSet->Close();

		m_cConfigure.Invalidate();

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

void CDisplayConfigureDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CDisplayConfigureDlg::InsertData(_RecordsetPtr& pSet, int iRow, int iCol)
{
    GV_ITEM Item;
	BOOL bCheck;

   	CGridCellCheck* pCell; 

	switch(iCol) {
	case 3:
		pCell = (CGridCellCheck*)m_cConfigure.GetCell(iRow, iCol);
		bCheck = pCell->GetCheck();
		pSet->Fields->GetItem("Check")->PutValue((_variant_t)bCheck);
		break;
	default:
		break;
	}
}

void CDisplayConfigureDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_pTempSet->State == adStateOpen)
		m_pTempSet->Close();
	m_pTempSet.Release();


	CDialog::OnClose();
}
