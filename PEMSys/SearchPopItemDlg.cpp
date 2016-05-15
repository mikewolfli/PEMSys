// SearchPopItemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "SearchPopItemDlg.h"
#include ".\searchpopitemdlg.h"


// CSearchPopItemDlg 对话框

IMPLEMENT_DYNAMIC(CSearchPopItemDlg, CDialog)
CSearchPopItemDlg::CSearchPopItemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchPopItemDlg::IDD, pParent)
	, m_sOrderID(_T(""))
	, m_sID(_T(""))
	, m_sProjectID(_T(""))
	, m_sProjectIDZS(_T(""))
	, m_sProjectName(_T(""))
	, m_sProjectNameEn(_T(""))
	, m_sAddress(_T(""))
	, m_sAddressEn(_T(""))
	, m_sSubCompany(_T(""))
	, m_iNumber(0)
	, m_bIntegrality(FALSE)
	, m_bContractSigned(FALSE)
	, m_sContractReceive(_T(""))
	, m_sTheLatestAmd(_T(""))
	, m_sRemarks(_T(""))
	, m_sAmount(_T(""))
{
}

CSearchPopItemDlg::~CSearchPopItemDlg()
{
}

void CSearchPopItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_sID);
	DDX_Text(pDX, IDC_EDIT_PROJECTID, m_sProjectID);
	DDX_Text(pDX, IDC_EDIT_PROJECTIDZS, m_sProjectIDZS);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAME, m_sProjectName);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAMEEN, m_sProjectNameEn);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_sAddress);
	DDX_Text(pDX, IDC_EDIT_ADDRESSEN, m_sAddressEn);
	DDX_Text(pDX, IDC_EDIT_SUBCOMPANY, m_sSubCompany);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_iNumber);
	DDX_Check(pDX, IDC_CHECK_INTEGRALITY, m_bIntegrality);
	DDX_Check(pDX, IDC_CHECK_INTEGRALITY2, m_bContractSigned);
	DDX_Text(pDX, IDC_EDIT_CONTRACTRECEIVE, m_sContractReceive);
	DDX_Text(pDX, IDC_EDIT_THELATESTAMENDMENT, m_sTheLatestAmd);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_sRemarks);
	DDX_Text(pDX, IDC_EDIT_SEARCH_AMOUNT, m_sAmount);
}


BEGIN_MESSAGE_MAP(CSearchPopItemDlg, CDialog)
END_MESSAGE_MAP()


// CSearchPopItemDlg 消息处理程序

BOOL CSearchPopItemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	try{

		m_pItemSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例
		m_pTempSet.CreateInstance(__uuidof(Recordset));


		strSQL = "select * from PBInformation where ID = (select ID from OrderOfProject where OrderID ='"+m_sOrderID+"')";
		theApp.ADOExecute(m_pItemSet, theApp.m_pConnect, strSQL);
		int iCount = m_pItemSet->GetRecordCount();
		if(0!=iCount)
		{
			m_pItemSet->MoveFirst();
			for (int i=0; i<iCount; i++)
			{
				RefreshEdit(m_pItemSet);
				m_pItemSet->MoveNext();
			}
		}
		m_pItemSet->Close();

		strSQL = "select OrderID from OrderOfProject where ID = (select ID from OrderOfProject where OrderID ='"+m_sOrderID+"') and Status = FALSE";
		theApp.ADOExecute(m_pItemSet, theApp.m_pConnect, strSQL);
		iCount = m_pItemSet->GetRecordCount();
		int iIndex;
		double Amount = 0.0,dbtemp;
		CString sOrderID;
		if(0!=iCount)
		{
			m_pItemSet->MoveFirst();
			for(int i= 0;i<iCount;i++)
			{
				Holder = m_pItemSet->GetCollect("OrderID");
                sOrderID =  Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
				strSQL = "select Amount from CDUnion where OrderID = '"+sOrderID+"'";
				theApp.ADOExecute(m_pTempSet,theApp.m_pConnect, strSQL);
				iIndex = m_pTempSet->GetRecordCount();
				if(0!=iIndex)
				{
					m_pTempSet->MoveFirst();
					for(int j=0;j<iIndex;j++)
					{
				        Holder = m_pTempSet->GetCollect("Amount");
				        dbtemp = (double)Holder;
				        Amount = Amount + dbtemp;
					}
					m_pTempSet->MoveNext();
				}
				 m_pItemSet->MoveNext();			
			}
		}
		m_pTempSet->Close();
		m_pItemSet->Close();
		UpdateData(TRUE);
		m_sAmount.Format("%.2f",Amount);

		UpdateData(FALSE);
		
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

BOOL CSearchPopItemDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((pMsg->message == WM_LBUTTONDBLCLK) | (pMsg->message == WM_RBUTTONDBLCLK))
	{
		OnCancel();
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSearchPopItemDlg::RefreshEdit(_RecordsetPtr& pSet)
{
	UpdateData(TRUE);
	COleDateTime dTemp;
	COleDateTime dCompare;
	dCompare.SetDate(9999,12,31);
	Holder = pSet->GetCollect(_T("ID"));
	m_sID = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect(_T("ProjectID"));
	m_sProjectID = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ProjectName");
	m_sProjectName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ProjectNameEn");
	m_sProjectNameEn = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Address");
	m_sAddress = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("AddressEn");
	m_sAddressEn = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("SubCompanyName");
	m_sSubCompany = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("Number");
	m_iNumber = (int)Holder;

	Holder = pSet->GetCollect("Remark");
	m_sRemarks = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("PartsContract");
	m_bPartsContract= (bool)Holder;
	if(m_bPartsContract)
	{
		((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
	}

	Holder = pSet->GetCollect("ContractReceive");
	dTemp= Holder.date;
	if(dTemp == dCompare)
	{
        m_sContractReceive.Empty();
	}
	else
	{
        m_sContractReceive = dTemp.Format("%Y-%m-%d");
	}

	Holder = pSet->GetCollect("Integrality");
	m_bIntegrality = (bool)Holder;

	Holder = pSet->GetCollect("TheLatestAmendment");
	dTemp = Holder.date;
	if(dTemp == dCompare)
	{
		m_sTheLatestAmd.Empty();
	}
	else
	{
		m_sTheLatestAmd = dTemp.Format("%Y-%m-%d");
	}

	Holder = pSet->GetCollect("ProjectNoZS");
	m_sProjectIDZS = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = pSet->GetCollect("ContractSigned");
	m_bContractSigned = (bool)Holder;

	UpdateData(FALSE);

}

void CSearchPopItemDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
 
	if(m_pItemSet->State == adStateOpen)
		m_pItemSet->Close();
	m_pItemSet.Release();

	if(m_pTempSet->State== adStateOpen)
		m_pTempSet->Close();
	m_pTempSet.Release();
	CDialog::OnCancel();
}
