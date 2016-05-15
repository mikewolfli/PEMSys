// ItemView.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemView.h"
#include ".\itemview.h"
#include "OrderIDDlg.h"

// CItemView
IMPLEMENT_DYNCREATE(CItemView, CFormView)

CItemView::CItemView()
	: CFormView(CItemView::IDD)
	, m_bAdd(FALSE)
	, m_bModify(FALSE)
	, m_sProjectID(_T(""))
	, m_sProjectName(_T(""))
	, m_sAddress(_T(""))
	, m_sSubCompany(_T(""))
	, m_iNumber(1)
	, m_sRemark(_T(""))
	, m_sInputPerson(_T(""))
	, m_sRePerson(_T(""))
	, m_sDisplay(_T("  of  "))
	, m_sInputDate(_T(""))
	, m_sReDate(_T(""))
	, m_dCurrentDate(COleDateTime::GetCurrentTime())
	, m_bCopy(FALSE)
	, m_iPos(0)
	, m_sID(_T(""))
	, m_iTotal(0)
	, m_sAddressEn(_T(""))
	, m_sProjectNameEn(_T(""))
    , m_bPartsContract(FALSE)
	, m_rhPartsContract(0)
	, m_bIntegrality(TRUE)
	, m_sProjectNOZS(_T(""))
	, m_dContractReceive(COleDateTime::GetCurrentTime())
	, m_dTheLatestAmendment(COleDateTime::GetCurrentTime())
	, m_bContractSigned(TRUE)
	, m_bContractRecieve(FALSE)
	, m_bLatestAmend(FALSE)
	, m_bProjectRequire(FALSE)
	, m_dProjectRequire(COleDateTime::GetCurrentTime())
	, m_bAffix(FALSE)
	, m_dAffix(COleDateTime::GetCurrentTime())
{
}

CItemView::~CItemView()
{
	if(m_pItemSet->State == adStateOpen)
	{
		m_pItemSet->Close();

	} 
	if(m_pTempSet->State == adStateOpen)
	{
		m_pTempSet->Close();
	}

	m_pItemSet.Release();
	m_pTempSet.Release();

	if (m_pCommerceDlg)
	{
		if (::IsWindow(m_pCommerceDlg->GetSafeHwnd()))
			m_pCommerceDlg->EndDialog(IDCANCEL);
		delete m_pCommerceDlg;
	}
}

void CItemView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_cAdd);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_cModify);
	DDX_Control(pDX, IDOK, m_cSave);
	DDX_Control(pDX, IDCANCEL, m_cCancel);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_cDelete);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_cNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_cLast);
	DDX_Control(pDX, IDC_BUTTON_FIRST, m_cFirst);
	DDX_Control(pDX, IDC_BUTTON_PREVIOUS, m_cPrevious);
	DDX_Text(pDX, IDC_EDIT_PROJECTID, m_sProjectID);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAME, m_sProjectName);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_sAddress);
	DDX_Control(pDX, IDC_COMBO_SUBCOMPANY, m_cSubCompany);
	DDX_CBString(pDX, IDC_COMBO_SUBCOMPANY, m_sSubCompany);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_iNumber);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_sRemark);
	DDX_Text(pDX, IDC_EDIT_INPUTPERSON, m_sInputPerson);
	DDX_Text(pDX, IDC_EDIT_REPERSON, m_sRePerson);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_cSearch);
	DDX_Text(pDX, IDC_EDIT_ITEM_DISPLAY, m_sDisplay);
	DDX_Text(pDX, IDC_EDIT_ITEM_INPUTDATE, m_sInputDate);
	DDX_Text(pDX, IDC_EDIT_ITEM_REDATE, m_sReDate);
	DDX_Text(pDX, IDC_EDIT_ID, m_sID);
	DDX_Text(pDX, IDC_EDIT_ADDRESSEN, m_sAddressEn);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAMEEN, m_sProjectNameEn);
	DDX_Check(pDX, IDC_CHECK_INTEGRALITY, m_bIntegrality);
	DDX_Text(pDX, IDC_EDIT_PROJECTIDZS, m_sProjectNOZS);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_CONTRACTRECEIVE, m_dContractReceive);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_THELATESTAMENDMENT, m_dTheLatestAmendment);
	DDX_Check(pDX, IDC_CHECK_INTEGRALITY2, m_bContractSigned);
	DDX_Check(pDX, IDC_CHECK_CONTRACTRECEIVE, m_bContractRecieve);
	DDX_Check(pDX, IDC_CHECK_THELATESTAMENDMENT, m_bLatestAmend);
	DDX_Control(pDX, IDC_DATETIMEPICKER_CONTRACTRECEIVE, m_cContractReceive);
	DDX_Control(pDX, IDC_DATETIMEPICKER_THELATESTAMENDMENT, m_cLatestAmend);
	DDX_Control(pDX, IDC_BUTTON_COMMERCE, m_cCommerce);
	DDX_Control(pDX, IDC_BUTTON_CREATORDERID, m_cCreatOrderID);
	DDX_Check(pDX, IDC_CHECK_PROJECTREQUIRE, m_bProjectRequire);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PROJECTREQUIRE, m_cProjectRequire);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PROJECTREQUIRE, m_dProjectRequire);
	DDX_Check(pDX, IDC_CHECK_PROJECTAFFIX, m_bAffix);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PROJECTAFFIX, m_dAffix);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PROJECTAFFIX, m_cAffix);
}

BEGIN_MESSAGE_MAP(CItemView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnBnClickedButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnBnClickedButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnBnClickedButtonModify)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_CREATORDERID, OnBnClickedButtonCreatorderid)
	ON_WM_CLOSE()
ON_BN_CLICKED(IDC_BUTTON_COMMERCE, OnBnClickedButtonCommerce)
ON_BN_CLICKED(IDC_CHECK_CONTRACTRECEIVE, OnBnClickedCheckContractreceive)
ON_BN_CLICKED(IDC_CHECK_THELATESTAMENDMENT, OnBnClickedCheckThelatestamendment)
ON_BN_CLICKED(IDC_CHECK_PROJECTREQUIRE, OnBnClickedCheckProjectrequire)
ON_BN_CLICKED(IDC_CHECK_PROJECTAFFIX, OnBnClickedCheckProjectaffix)
END_MESSAGE_MAP()


// CItemView 诊断

#ifdef _DEBUG
void CItemView::AssertValid() const
{
	CFormView::AssertValid();
}

void CItemView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CItemView 消息处理程序

void CItemView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	GetParentFrame()->RecalcLayout();
	//	 ResizeParentToFit();
	ResizeParentToFit(FALSE);
	ResizeParentToFit(TRUE);
	// TODO: 在此添加专用代码和/或调用基类                                                                                                                                                                                                                                                                                                  
	CString strTitle ;
	strTitle = "项目管理";
	GetParentFrame()->SetWindowText(strTitle);

	m_cAdd.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ADD));
	m_cModify.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_MODIFY));
	m_cDelete.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DELETE));
	m_cFirst.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_FIRST));
	m_cPrevious.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_PREVIOUS));
	m_cNext.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_NEXT));
	m_cLast.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LAST));
	m_cSave.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_SAVE));
	m_cCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_CANCEL));
    
	CRect rect,rect1;
	GetClientRect(rect);
	m_OldSize = CSize(rect.Width(), rect.Height());
    
	m_pCommerceDlg=NULL;
	UpdateData(TRUE);

	switch(g_tUserType)
	{
	case 1:
		m_cAdd.EnableWindow(FALSE);
		m_cModify.EnableWindow(FALSE);
		m_cDelete.EnableWindow(FALSE);
		m_cSave.EnableWindow(FALSE);;
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

	ClearEdit();
/*
//	m_cYear.ResetContent();
	int m_iYear;
	CString str;
	m_iYear = m_dCurrentDate.GetYear();
	for(int i=0;i<5;i++)
	{
		str.Format("%d",i+m_iYear);
		m_cYear.AddString(str);
	}
*/
	UpdateData(FALSE);
	int iCount;
	try{

		m_pItemSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例
		m_pTempSet.CreateInstance(__uuidof(Recordset));

		strSQL = "select DISTINCT SubCompanyName from SubCompany";
		theApp.ADOExecute(m_pItemSet, theApp.m_pConnect, strSQL);
		iCount = m_pItemSet->GetRecordCount();
		if(0!=iCount)
		{
			m_pItemSet->MoveFirst();
			for (int i=0; i<iCount; i++)
			{
				Holder = m_pItemSet->GetCollect("SubCompanyName");
				m_cSubCompany.InsertString(i, Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
				m_pItemSet->MoveNext();
			}
		}
		m_pItemSet->Close();
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
    
	// TODO: 在此添加专用代码和/或调用基类
}

void CItemView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
    
	if((cx-m_OldSize.cx < 0) && (cy - m_OldSize.cy <0))
		return;

	// TODO: 在此处添加消息处理程序代码
}

void CItemView::RefreshEdit(void)
{
    CString str;
	Holder = m_pItemSet->GetCollect(_T("ID"));
	m_sID = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect(_T("ProjectID"));
	m_sProjectID = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect("ProjectName");
	m_sProjectName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect("ProjectNameEn");
	m_sProjectNameEn = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect("Address");
	m_sAddress = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect("AddressEn");
	m_sAddressEn = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect("SubCompanyName");
	m_sSubCompany = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	 
	Holder = m_pItemSet->GetCollect("Number");
	m_iNumber = (int)Holder;

	Holder = m_pItemSet->GetCollect("InputPerson");
	m_sInputPerson = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect("InputDate");
	COleDateTime dDate = Holder.date;
	m_sInputDate = dDate.Format("%Y-%m-%d");

	Holder = m_pItemSet->GetCollect("RePerson");
	m_sRePerson = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect("ReDate");
	dDate = Holder.date;
	m_sReDate = dDate.Format("%Y-%m-%d");

	Holder = m_pItemSet->GetCollect("Remark");
	m_sRemark = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

    Holder = m_pItemSet->GetCollect("PartsContract");
	m_bPartsContract= (bool)Holder;
	if(m_bPartsContract)
	{
		m_rhPartsContract = 1;
		((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	}
	else
	{
		m_rhPartsContract = 0;
		((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
	}

    Holder = m_pItemSet->GetCollect("ContractReceive");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_dContractReceive = COleDateTime::GetCurrentTime();
		m_bContractRecieve = FALSE;
		m_cContractReceive.EnableWindow(FALSE);
	}
	else
	{
		m_bContractRecieve = TRUE;
		m_cContractReceive.EnableWindow(TRUE);
		m_dContractReceive = Holder.date;
	}

    Holder = m_pItemSet->GetCollect("Integrality");
	m_bIntegrality = (bool)Holder;

    Holder = m_pItemSet->GetCollect("TheLatestAmendment");
	str = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_dTheLatestAmendment = COleDateTime::GetCurrentTime();
		m_bLatestAmend = FALSE;
		m_cLatestAmend.EnableWindow(FALSE);
	}
	else
	{
		m_bLatestAmend = TRUE;
		m_cLatestAmend.EnableWindow(TRUE);
		m_dTheLatestAmendment = Holder.date;
	}

	Holder = m_pItemSet->GetCollect("ProjectNoZS");
	m_sProjectNOZS = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;

	Holder = m_pItemSet->GetCollect("ContractSigned");
    m_bContractSigned = (bool)Holder;

	Holder = m_pItemSet->GetCollect("TempDate");
	VarTemp = Holder;

	Holder = m_pItemSet->GetCollect("ProjectRequire");
	str = Holder.vt == VT_NULL?"":(char *)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_dProjectRequire= COleDateTime::GetCurrentTime();
		m_bProjectRequire = FALSE;
		m_cProjectRequire.EnableWindow(FALSE);

	}
	else
	{
		m_bProjectRequire = TRUE;
		m_dProjectRequire = Holder.date;
		m_cProjectRequire.EnableWindow(TRUE);
	}

	Holder = m_pItemSet->GetCollect("ProjectAffixDate");
	str = Holder.vt == VT_NULL?"":(char *)(_bstr_t)Holder;
	if(str.IsEmpty())
	{
		m_dAffix= COleDateTime::GetCurrentTime();
		m_bAffix = FALSE;
		m_cAffix.EnableWindow(FALSE);

	}
	else
	{
		m_bAffix = TRUE;
		m_dAffix = Holder.date;
		m_cAffix.EnableWindow(TRUE);
	}


	m_sDisplay.Format("%d of %d", m_iPos+1, m_pItemSet->GetRecordCount());

}

void CItemView::ClearEdit(void)
{
	UpdateData(TRUE);
	m_sID = _T("");
	m_sProjectID = _T("");
	m_sProjectName = _T("");
	m_sAddress = _T("");
	m_sSubCompany = _T("");
	m_iNumber = 1;
	m_sRemark = _T("");
	m_sProjectNameEn.Empty();
	m_sAddressEn.Empty();
    m_sInputPerson = g_strUserName;
    m_sRePerson = g_strUserName;
	m_sInputDate = m_dCurrentDate.Format("%Y-%m-%d");
	m_sReDate = m_dCurrentDate.Format("%Y-%m-%d");
	m_sDisplay = " of ";
	m_sProjectNOZS.Empty();
	m_dContractReceive = COleDateTime::GetCurrentTime();
	m_dTheLatestAmendment = COleDateTime::GetCurrentTime();
    m_bContractRecieve = FALSE;
	m_bLatestAmend = FALSE;
	m_cContractReceive.EnableWindow(FALSE);
	m_cLatestAmend.EnableWindow(FALSE);
	m_rhPartsContract = 0;
	m_bContractSigned = TRUE;
	m_bPartsContract = FALSE;
	m_bIntegrality = TRUE;
	((CButton*)GetDlgItem(IDC_RADIO0))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);

//	m_sYear.Format("%d",m_dCurrentDate.GetYear());
//	m_sMonth.Format("%d",m_dCurrentDate.GetMonth());
//	m_sDay.Format("%d",m_dCurrentDate.GetDay());

	UpdateData(FALSE);
}

void CItemView::OnBnClickedButtonFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(!(m_pItemSet->BOF))
	{   
		m_pItemSet->MoveFirst();
		m_iPos = 0;
		RefreshEdit();
		m_cNext.EnableWindow(TRUE);
		m_cLast.EnableWindow(TRUE);
		m_cPrevious.EnableWindow(FALSE);
		m_cFirst.EnableWindow(FALSE);
	}
	else
	{   
		return;
	}
	UpdateData(FALSE);
}

void CItemView::OnBnClickedButtonPrevious()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(0!=m_iPos)
	{
		m_pItemSet->MovePrevious();
		if(m_iPos>0)
			m_iPos-=1;
		else
			m_iPos = m_iPos;
		RefreshEdit();
		m_cNext.EnableWindow(TRUE);
		m_cLast.EnableWindow(TRUE);

	}
	else
	{
		m_cPrevious.EnableWindow(FALSE);
		m_cFirst.EnableWindow(FALSE);
		return;
	}
	UpdateData(FALSE);
}

void CItemView::OnBnClickedButtonNext()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_iPos!=m_pItemSet->GetRecordCount()-1)
	{
		m_pItemSet->MoveNext();
		m_iPos+=1;
		RefreshEdit();
		m_cFirst.EnableWindow(TRUE);
		m_cPrevious.EnableWindow(TRUE);
	}	
	else
	{
		m_cNext.EnableWindow(FALSE);
		m_cLast.EnableWindow(FALSE);
		return;		
	}
	UpdateData(FALSE);
}

void CItemView::OnBnClickedButtonLast()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(!(m_pItemSet->EndOfFile))
	{   
		m_pItemSet->MoveLast();
		m_iPos = m_pItemSet->GetRecordCount()-1;
		RefreshEdit();
		m_cLast.EnableWindow(FALSE);
		m_cNext.EnableWindow(FALSE);
		m_cFirst.EnableWindow(TRUE);
		m_cPrevious.EnableWindow(TRUE);
	}
	else
	{
		return;
	}
	UpdateData(FALSE);
}

void CItemView::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_bAdd = TRUE;
	m_cModify.EnableWindow(FALSE);
	m_cSave.EnableWindow(TRUE);
	m_cAdd.EnableWindow(FALSE);
	ClearEdit();
	m_cFirst.EnableWindow(FALSE);
	m_cNext.EnableWindow(FALSE);
	m_cPrevious.EnableWindow(FALSE);
	m_cLast.EnableWindow(FALSE);
	m_cDelete.EnableWindow(FALSE);
	m_cSearch.EnableWindow(FALSE);
	m_cCommerce.EnableWindow(FALSE);
	m_cCreatOrderID.EnableWindow(FALSE);
	m_sInputPerson = g_strUserName;
	m_sRePerson = g_strUserName;
	m_sInputDate = m_dCurrentDate.Format("%Y-%m-%d");
	m_sReDate = m_dCurrentDate.Format("%Y-%m-%d");

	strSQL = "select * from TotalProject";
	theApp.ADOExecute(m_pTempSet,theApp.m_pConnect,  strSQL);

	Holder = m_pTempSet->GetCollect("Total");
	m_iTotal = (long)Holder;

	m_iTotal +=1;
	m_sID.Format("%d",m_iTotal);

	((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(TRUE);

	VARIANT_BOOL bEmpty;
	HRESULT hr = theApp.get_Empty(m_pItemSet, &bEmpty);
	if(bEmpty) 
	{
//		return;
	}
	else
	{
		m_pItemSet->get_Bookmark(&m_BookMark);
	}

	UpdateData(FALSE);
}

void CItemView::OnBnClickedButtonModify()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_sID == _T(""))
	{
		AfxMessageBox("请选择要修改的数据",MB_ICONEXCLAMATION);
		return;
	}
	else
	{
		m_bModify = TRUE;
		m_cModify.EnableWindow(FALSE);
		m_cAdd.EnableWindow(FALSE);
		m_cFirst.EnableWindow(FALSE);
		m_cNext.EnableWindow(FALSE);
		m_cPrevious.EnableWindow(FALSE);
		m_cLast.EnableWindow(FALSE);
		m_cDelete.EnableWindow(FALSE);
		m_cSearch.EnableWindow(FALSE);
		m_cCommerce.EnableWindow(FALSE);
		m_cCreatOrderID.EnableWindow(FALSE);
		m_cSave.EnableWindow(TRUE);
		((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(TRUE);
		m_sRePerson = g_strUserName;
		m_sReDate = m_dCurrentDate.Format("%Y-%m-%d");
	}
	UpdateData(FALSE);

}

void CItemView::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_sID.Trim();
	m_sProjectID.Trim();
	m_sProjectName.Trim();
	m_sAddress.Trim();
	m_sSubCompany.Trim();
	m_sRemark.Trim();
	m_sInputPerson.Trim();
	m_sRePerson.Trim();
	m_sInputDate.Trim();
	m_sReDate.Trim();


	BOOL bJudge=FALSE;
	CString sWarning="";
	int iCount;
	CString strTemp;
	HRESULT hr;

	try
	{
		if(((CButton*)GetDlgItem(IDC_RADIO0))->GetCheck())
			m_rhPartsContract = 0;
		if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
			m_rhPartsContract = 1;

		if ( ""==m_sID ) 
		{
			sWarning=_T("合同流水编号");
			((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetSel(0,-1);
		}
		else if ( ""==m_sProjectName )
		{
			sWarning=_T("合同名称");
			((CEdit*)GetDlgItem(IDC_EDIT_PROJECTNAME))->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_PROJECTNAME))->SetSel(0,-1);
		}

		else if ( ""==m_sSubCompany ) 
		{
			sWarning=_T("分公司");
			m_cSubCompany.SetFocus();
			m_cSubCompany.SetEditSel(0,-1);
		}

		if ( ""!=sWarning ) 
		{
			sWarning += _T("不能为空");
			AfxMessageBox(sWarning, MB_ICONEXCLAMATION);
			return;
		}

		if(m_iNumber <=0)
		{
			AfxMessageBox("台数请输入大于0的正整数", MB_ICONEXCLAMATION);
			((CEdit*)GetDlgItem(IDC_EDIT_NUMBER))->SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT_NUMBER))->SetSel(0,-1);
			return;
		}

		if(m_bAdd)
		{     
			if(m_pItemSet->State == adStateClosed)
			{
				strSQL = _T("select * from PBInformation where ID = '"+m_sID+"'");
				theApp.ADOExecute(m_pItemSet,theApp.m_pConnect,  strSQL);
				bJudge = TRUE;
			}
			if(!bJudge)
			{
	
				strTemp = "ID = '"+m_sID+"'";
				_bstr_t strFind(strTemp);
				m_pItemSet->MoveFirst();
				hr = m_pItemSet->Find(strFind,0,adSearchForward);
			}

			if(m_pItemSet->EndOfFile)
			{

				m_pItemSet->AddNew();

                UpdateRecord(m_pItemSet);       
				m_pItemSet->Update();
				if(!bJudge)
				{	

					m_pItemSet->MoveLast();
					m_iPos = m_pItemSet->GetRecordCount()-1;
					RefreshEdit();
				}

				if(bJudge)
				{
					m_pItemSet->Close();
				    ClearEdit();
				}

				m_pTempSet->Fields->GetItem("Total")->PutValue(m_iTotal);
				m_pTempSet->Update();
				m_pTempSet->Close();

				m_cModify.EnableWindow(TRUE);
				m_cAdd.EnableWindow(TRUE);
				((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(FALSE);
//				ClearEdit();
				if(m_pItemSet->State == adStateOpen)
				{
					m_cFirst.EnableWindow(TRUE);
					m_cNext.EnableWindow(TRUE);
					m_cPrevious.EnableWindow(TRUE);
					m_cLast.EnableWindow(TRUE);
				}
				else
				{
					m_cFirst.EnableWindow(FALSE);
					m_cNext.EnableWindow(FALSE);
					m_cPrevious.EnableWindow(FALSE);
					m_cLast.EnableWindow(FALSE);
				}
				if(g_tUserType>2)
				{
					m_cDelete.EnableWindow(TRUE);
				}
				m_cSearch.EnableWindow(TRUE);
				m_cCommerce.EnableWindow(TRUE);
				m_cCreatOrderID.EnableWindow(TRUE);
				
				bJudge = FALSE;
			    m_bAdd = FALSE;
			}
			else
			{
				AfxMessageBox("此合同记录已经存在", MB_ICONEXCLAMATION);
				((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetFocus();
				((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetSel(0,-1);

				if(m_pTempSet->State == adStateOpen)
					m_pTempSet->Close();
				bJudge = FALSE;
				m_bAdd = FALSE;
				return;
			}
		}
		if(m_bModify)
		{ 
			if(m_pItemSet->State == adStateClosed )
			{
				strSQL = _T("select * from PBInformation where ID = '"+m_sID+"'");
				theApp.ADOExecute(m_pItemSet,theApp.m_pConnect,  strSQL);
				iCount = m_pItemSet->GetRecordCount();
				if(0==iCount)
				{
					m_pItemSet->Close();
					AfxMessageBox("此合同记录不存在\n请先添加!",MB_ICONEXCLAMATION);
					OnBnClickedCancel();
					((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetFocus();
					((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetSel(0,-1);	
					return;
				}

			}
			if(m_pItemSet->State == adStateOpen)
			{
                UpdateRecord(m_pItemSet);
				m_pItemSet->Update();
				m_bModify = FALSE;
				m_cModify.EnableWindow(TRUE);
				m_cAdd.EnableWindow(TRUE);
				if(m_pItemSet->State == adStateOpen)
				{
					m_cFirst.EnableWindow(TRUE);
					m_cNext.EnableWindow(TRUE);
					m_cPrevious.EnableWindow(TRUE);
					m_cLast.EnableWindow(TRUE);
				}
				if(g_tUserType>2)
				{
					m_cDelete.EnableWindow(TRUE);
				}
				m_cSearch.EnableWindow(TRUE);
				m_cCommerce.EnableWindow(TRUE);
				m_cCreatOrderID.EnableWindow(TRUE);
				((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(FALSE);
			}

		}
		m_cSave.EnableWindow(FALSE);
	}	catch(_com_error &e)
	{
		CString err;
		m_rhPartsContract=-1;
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

void CItemView::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_bAdd)
	{
		m_bAdd = FALSE;
		m_cModify.EnableWindow(TRUE);
		m_cAdd.EnableWindow(TRUE);
		if(m_pTempSet->State == adStateOpen)
		{
			m_pTempSet->Close();
			ClearEdit();
		}
		if(m_pItemSet->State == adStateOpen)
		{
		    RefreshEdit();
			m_cFirst.EnableWindow(TRUE);
			m_cNext.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(TRUE);
			m_cLast.EnableWindow(TRUE);
		}
		if(g_tUserType>2)
		{
		    m_cDelete.EnableWindow(TRUE);
		}

		if(!m_bCopy)
	       ((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(FALSE);
	
	}else
	if(m_bModify)
	{
		m_bModify = FALSE;
		m_cModify.EnableWindow(TRUE);
		m_cAdd.EnableWindow(TRUE);
		if(m_pItemSet->State == adStateOpen)
		{
			m_cFirst.EnableWindow(TRUE);
			m_cNext.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(TRUE);
			m_cLast.EnableWindow(TRUE);
		}
		if(g_tUserType>2)
		{
			m_cDelete.EnableWindow(TRUE);
		}
	}
	else
	if(m_bCopy)
	{
		if(m_pItemSet->State == adStateOpen)
			m_pItemSet->Close();
		m_cFirst.EnableWindow(FALSE);
		m_cNext.EnableWindow(FALSE);
		m_cPrevious.EnableWindow(FALSE);
		m_cLast.EnableWindow(FALSE);
		ClearEdit();
		m_bCopy = FALSE;	
	    ((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(FALSE);

	}

	m_cSearch.EnableWindow(TRUE);
	m_cCommerce.EnableWindow(TRUE);
	m_cCreatOrderID.EnableWindow(TRUE);
	m_cSave.EnableWindow(FALSE);

	UpdateData(FALSE);
}

void CItemView::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try
	{
		CString strTemp;

		HRESULT hr;
		int iCount;
		BOOL bJudge=FALSE;
		if(m_pItemSet->State == adStateClosed)
		{
			bJudge = TRUE;
			strSQL = "select * from PBInformation where ID = '"+m_sID+"'";
			theApp.ADOExecute(m_pItemSet, theApp.m_pConnect,strSQL);
			iCount = m_pItemSet->GetRecordCount();
			if(0== iCount)
			{
				AfxMessageBox("此记录不存在,无法删除",MB_ICONEXCLAMATION);
				m_pItemSet->Close();
				return;
			}
		}
		if(m_pItemSet->State == adStateOpen)
		{
			strTemp = "ID = '"+m_sID+"'";
			_bstr_t strFind(strTemp);
			m_pItemSet->MoveFirst();
			hr = m_pItemSet->Find(strFind,0,adSearchForward);
			if(!SUCCEEDED(hr))
			{
				AfxMessageBox("此记录不存在,无法删除",MB_ICONEXCLAMATION);
				return;
			}
		}

        strSQL = "select * from OrderOfProject where ID = '"+m_sID+"'";
		theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
		VARIANT_BOOL bEmpty;
		hr = theApp.get_Empty(m_pTempSet, &bEmpty);
		if(!bEmpty) 
		{
			AfxMessageBox("无法删除,订单表里已经生成此项目的订单!",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return;
		}
		m_pTempSet->Close();

		if(AfxMessageBox("是否确认删除当前记录",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{
			m_pItemSet->Delete(adAffectCurrent);
			m_pItemSet->Update();

			if(bJudge)
			{
				m_cFirst.EnableWindow(FALSE);
				m_cLast.EnableWindow(FALSE);
				m_cPrevious.EnableWindow(FALSE);
				m_cNext.EnableWindow(FALSE);
				m_pItemSet->Close();
				bJudge = FALSE;
				return;
			}
			int i = m_pItemSet->GetRecordCount();
			if(0!=i)
			{
				if (m_pItemSet->EndOfFile) 
				{
					m_pItemSet->MoveLast();
					m_iPos = m_pItemSet->GetRecordCount()-1;
				}
				else {
					m_pItemSet->MoveNext();
					if(m_pItemSet->EndOfFile)
					{
						m_pItemSet->MoveLast();
						m_iPos = m_pItemSet->GetRecordCount()-1;
					}
				}
				m_pItemSet->get_Bookmark(&m_BookMark);
				RefreshEdit();
			}
			else
			{
				m_cFirst.EnableWindow(FALSE);
				m_cLast.EnableWindow(FALSE);
				m_cPrevious.EnableWindow(FALSE);
				m_cNext.EnableWindow(FALSE);
				ClearEdit();
				return;
			}
		}else
			return;

	}
	catch (...) 
	{
		return;
	}
	UpdateData(TRUE);
}

void CItemView::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str,str1;

	m_sID.Trim();
	m_sProjectName.Trim();
	m_sProjectNameEn.Trim();
	m_sSubCompany.Trim();
	m_sProjectName.Replace('\'','_');
	m_sProjectNameEn.Replace('\'','_');
	m_sProjectName.Replace('\"','_');
	m_sProjectNameEn.Replace('\"','_');

	if(m_sID.IsEmpty() && m_sProjectName.IsEmpty() && m_sProjectNameEn.IsEmpty() && m_sSubCompany.IsEmpty())
		str = _T("");
	else 
	{
		str = _T(" where ");
//	if(!m_sID.IsEmpty())
		str =str + "ID like '%"+m_sID+"%'";
//	if(!m_sProjectName.IsEmpty())
		str = str +"and ProjectName like '%"+m_sProjectName+"%'";
//	if(!m_sProjectNameEn.IsEmpty())
		str = str + "and ProjectNameEn like '%"+m_sProjectNameEn+"%'";
//	if(!m_sSubCompany.IsEmpty())
		str = str +"and SubCompanyName like '%"+m_sSubCompany+"%'";
	}
	str1 = "order by ID ASC";

	strSQL = "select top 500 * from PBInformation "+str+str1;

	theApp.ADOExecute(m_pItemSet,theApp.m_pConnect,  strSQL);
	int iCount = m_pItemSet->GetRecordCount();
	if(0==iCount)
	{
		AfxMessageBox("没有所要查询的记录!",MB_ICONEXCLAMATION);
		m_pItemSet->Close();
		SetDlgItemText(IDC_EDIT_ID,_T(""));
		GetDlgItem(IDC_EDIT_ID)->SetFocus();
		m_bCopy = FALSE;
		return;
	}

	m_cPrevious.EnableWindow(TRUE);
	m_cNext.EnableWindow(TRUE);
	m_cFirst.EnableWindow(TRUE);
	m_cLast.EnableWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_EDIT_ID))->SetReadOnly(TRUE);

	m_pItemSet->MoveFirst();
	m_iPos = 0;
	m_bCopy = TRUE;
	RefreshEdit();
	UpdateData(FALSE);
}


void CItemView::OnBnClickedButtonCreatorderid()
{
	// TODO: 在此添加控件通知处理程序代码
	COrderIDDlg m_Dlg;
	UpdateData(TRUE);
	m_Dlg.m_stemp = m_sID;
	m_Dlg.DoModal();
	UpdateData(FALSE);

}

void CItemView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFormView::OnClose();
}

//void CItemView::OnBnClickedButtonItemlist()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}

BOOL CItemView::PreTranslateMessage(MSG* pMsg)
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

void CItemView::OnBnClickedButtonCommerce()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_pCommerceDlg=new CItemCommerceDlg();


	if(!m_sID.IsEmpty())
	{
		m_pCommerceDlg->m_sID= m_sID;
		m_pCommerceDlg->m_sProjectName = m_sProjectName;
		m_pCommerceDlg->m_sProjectNameEN= m_sProjectNameEn;
		m_pCommerceDlg->m_iNumber = m_iNumber;
		strSQL = "select ID from OrderOfProject where ID = '"+m_sID+"'";
		theApp.ADOExecute(m_pTempSet, theApp.m_pConnect, strSQL);
		VARIANT_BOOL bEmpty;
		HRESULT hr = theApp.get_Empty(m_pTempSet, &bEmpty);
		if(bEmpty) 
		{
			AfxMessageBox("警告:\t 1 或者此合同记录尚未保存\n\t 2 或者尚未生成此合同的订单\n\t 3 或者请先取消当前记录后直接进入",MB_ICONEXCLAMATION);
			m_pTempSet->Close();
			return;
		}
		m_pTempSet->Close();
	}


	if (!::IsWindow(m_pCommerceDlg->GetSafeHwnd()))
		m_pCommerceDlg->Create(IDD_DIALOG_COMMERCE,this);
	m_pCommerceDlg->ShowWindow(SW_SHOW);
	
//	m_Dlg.DoModal();
	UpdateData(FALSE);
}

void CItemView::OnBnClickedCheckContractreceive()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(((CButton*)GetDlgItem(IDC_CHECK_CONTRACTRECEIVE))->GetCheck())
	{
		m_bContractRecieve = TRUE;
		m_cContractReceive.EnableWindow(TRUE);
		m_dContractReceive = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_bContractRecieve = FALSE;
		m_cContractReceive.EnableWindow(FALSE);
		m_dContractReceive = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}

void CItemView::OnBnClickedCheckThelatestamendment()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_THELATESTAMENDMENT))->GetCheck())
	{
		m_bLatestAmend = TRUE;
		m_cLatestAmend.EnableWindow(TRUE);
		m_dTheLatestAmendment = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_bLatestAmend = FALSE;
		m_cLatestAmend.EnableWindow(FALSE);
		m_dTheLatestAmendment = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}

void CItemView::UpdateRecord(_RecordsetPtr& pSet)
{
	pSet->Fields->GetItem("ID")->PutValue(m_sID.AllocSysString());
	pSet->Fields->GetItem("ProjectID")->PutValue(m_sProjectID.AllocSysString());
	pSet->Fields->GetItem("ProjectName")->PutValue(m_sProjectName.AllocSysString());
	pSet->Fields->GetItem("Address")->PutValue(m_sAddress.AllocSysString());
	pSet->Fields->GetItem("SubCompanyName")->PutValue(m_sSubCompany.AllocSysString());
	pSet->Fields->GetItem("Number")->PutValue((_variant_t)m_iNumber);
	pSet->Fields->GetItem("Remark")->PutValue(m_sRemark.AllocSysString());
	pSet->Fields->GetItem("ProjectNameEn")->PutValue(m_sProjectNameEn.AllocSysString());
	pSet->Fields->GetItem("AddressEn")->PutValue(m_sAddressEn.AllocSysString());

	switch(m_rhPartsContract) {
				case 0:
					m_bPartsContract= FALSE;
					break;
				case 1:
					m_bPartsContract=TRUE;
					break;
				default:
					break;
	}

	pSet->Fields->GetItem("PartsContract")->PutValue((_variant_t)m_bPartsContract);
	pSet->Fields->GetItem("ProjectNoZS")->PutValue(m_sProjectNOZS.AllocSysString());
	pSet->Fields->GetItem("Integrality")->PutValue((_variant_t)m_bIntegrality);
	if(m_bContractRecieve)
	   pSet->Fields->GetItem("ContractReceive")->PutValue((_variant_t)m_dContractReceive);
	else if(m_bModify) 
	       pSet->Fields->GetItem("ContractReceive")->PutValue(VarTemp);

	if(m_bLatestAmend)
	   pSet->Fields->GetItem("TheLatestAmendment")->PutValue((_variant_t)m_dTheLatestAmendment);
	else if(m_bModify)
       pSet->Fields->GetItem("TheLatestAmendment")->PutValue(VarTemp);

	pSet->Fields->GetItem("ContractSigned")->PutValue((_variant_t)m_bContractSigned);

	if(m_bProjectRequire)
		pSet->Fields->GetItem("ProjectRequire")->PutValue((_variant_t)m_dProjectRequire);
	else if(m_bModify)
		pSet->Fields->GetItem("ProjectRequire")->PutValue(VarTemp);

	if(m_bAffix)
		pSet->Fields->GetItem("ProjectAffixDate")->PutValue((_variant_t)m_dAffix);
	else if(m_bModify)
		pSet->Fields->GetItem("ProjectAffixDate")->PutValue(VarTemp);

	if(m_bAdd)
	{
	    pSet->Fields->GetItem("InputPerson")->PutValue(m_sInputPerson.AllocSysString());
	    pSet->Fields->GetItem("InputDate")->PutValue((_variant_t)m_dCurrentDate);
	}
	pSet->Fields->GetItem("RePerson")->PutValue(m_sRePerson.AllocSysString());
	pSet->Fields->GetItem("ReDate")->PutValue((_variant_t)m_dCurrentDate);
}

void CItemView::OnBnClickedCheckProjectrequire()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_PROJECTREQUIRE))->GetCheck())
	{
		m_bProjectRequire = TRUE;
		m_cProjectRequire.EnableWindow(TRUE);
		m_dProjectRequire = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_bProjectRequire = FALSE;
		m_cProjectRequire.EnableWindow(FALSE);
		m_dProjectRequire = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);

}

void CItemView::OnBnClickedCheckProjectaffix()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if(((CButton*)GetDlgItem(IDC_CHECK_PROJECTAFFIX))->GetCheck())
	{
		m_bAffix = TRUE;
		m_cAffix.EnableWindow(TRUE);
		m_dAffix = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_bAffix = FALSE;
		m_cAffix.EnableWindow(FALSE);
		m_dAffix = COleDateTime::GetCurrentTime();
	}

	UpdateData(FALSE);
}
