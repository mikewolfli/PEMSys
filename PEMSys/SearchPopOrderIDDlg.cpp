// SearchPopOrderIDDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "SearchPopOrderIDDlg.h"
#include ".\searchpoporderiddlg.h"


// CSearchPopOrderIDDlg 对话框

IMPLEMENT_DYNAMIC(CSearchPopOrderIDDlg, CDialog)
CSearchPopOrderIDDlg::CSearchPopOrderIDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchPopOrderIDDlg::IDD, pParent)
	, m_sOrderID(_T(""))
{
}

CSearchPopOrderIDDlg::~CSearchPopOrderIDDlg()
{
}

void CSearchPopOrderIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ORDERID, m_cList);
}


BEGIN_MESSAGE_MAP(CSearchPopOrderIDDlg, CDialog)
END_MESSAGE_MAP()


// CSearchPopOrderIDDlg 消息处理程序

BOOL CSearchPopOrderIDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cList.SetBkColor(RGB(177, 151, 240));
	m_cList.SetTextColor(RGB(0,0,0));
	m_cList.SetTextBkColor(RGB(177, 151, 240));

	// Set EX-Style
	m_cList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_HEADERDRAGDROP);


	// Create Header
	m_cList.InsertColumn(0,_T("订单号"), LVCFMT_LEFT,100);
	m_cList.InsertColumn(1,_T("梯号"), LVCFMT_LEFT,50);
	m_cList.InsertColumn(2,_T("说明"), LVCFMT_LEFT,100);

	try{

		m_pOrderID.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例

		strSQL = "select * from OrderOfProject where ID = (select ID from OrderOfProject where OrderID ='"+m_sOrderID+"') and Status = FALSE";
		theApp.ADOExecute(m_pOrderID,theApp.m_pConnect, strSQL);
		int iCount = m_pOrderID->GetRecordCount();
		if(iCount!=0)
		{
			m_pOrderID->MoveFirst();
			for(int i= 0;i<iCount;i++)
			{
				LoadData(m_pOrderID, i);
				m_pOrderID->MoveNext();
			}

		}
		else
		{
			return FALSE;
		}
		m_pOrderID->Close();

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
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CSearchPopOrderIDDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((pMsg->message == WM_LBUTTONDBLCLK) | (pMsg->message == WM_RBUTTONDBLCLK))
	{
		OnCancel();
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSearchPopOrderIDDlg::LoadData(_RecordsetPtr& pSet,int i)
{
	CString str;
	Holder = pSet->GetCollect("OrderID");
	str = (char*)(_bstr_t)Holder;
	m_cList.InsertItem(i, str);
	//获得电梯梯号
	Holder = pSet->GetCollect("ElevatorID");
	str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
	m_cList.SetItemText(i, 1, str);
	// 获得说明
	Holder = pSet->GetCollect("Remark");
	str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
	m_cList.SetItemText(i, 2, str);
}

void CSearchPopOrderIDDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
    if(m_pOrderID->State == adStateOpen)
	{
		m_pOrderID->Close();
	}
	m_pOrderID.Release();
	CDialog::OnCancel();
}
