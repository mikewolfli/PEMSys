// SysTipDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "SysTipDlg.h"
#include ".\systipdlg.h"


// CSysTipDlg 对话框

IMPLEMENT_DYNAMIC(CSysTipDlg, CDialog)
CSysTipDlg::CSysTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysTipDlg::IDD, pParent)
	, m_dCurrent(COleDateTime::GetCurrentTime())
	, m_bTip(FALSE)
	, FilePath(_T(""))
	, m_bTip2(FALSE)
	, m_iNum(0)
{
}

CSysTipDlg::~CSysTipDlg()
{
	if(m_pSet->State== adStateOpen)
		m_pSet->Close();
	m_pSet.Release();
}

void CSysTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_cList);
	DDX_Check(pDX, IDC_CHECK_NEXTTIPS, m_bTip);
	DDX_Check(pDX, IDC_CHECK_NEXTTIPS2, m_bTip2);
	DDX_Text(pDX, IDC_EDIT_NUM, m_iNum);
}


BEGIN_MESSAGE_MAP(CSysTipDlg, CDialog)
	ON_BN_CLICKED(IDC_CHECK_NEXTTIPS, OnBnClickedCheckNexttips)
	ON_BN_CLICKED(IDC_CHECK_NEXTTIPS2, OnBnClickedCheckNexttips2)
END_MESSAGE_MAP()


// CSysTipDlg 消息处理程序

BOOL CSysTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);


	CString strTitle ;

	char appPath[256];
	GetCurrentDirectory(256,appPath); //取得应用程序当前路径
	FilePath.Format("%s",appPath);
	FilePath+="\\Config.ini";;

	char chTip[80];
	CString sTip;

	CString strSection = _T("PathofDatabase");
	CString strSectionKey  = _T("Tips");
	BOOL lRet = GetPrivateProfileString (strSection,strSectionKey, NULL, chTip, 256, FilePath); 
	if(lRet)
	{
		sTip = *chTip;
		if(sTip=="1")
		{
			m_bTip = TRUE;
			m_bTip2=FALSE;
		}
		//		((CButton*)GetDlgItem(IDC_CHECK_TIPS))->SetCheck(TRUE);
		else  if(sTip=="2")
		{
			m_bTip=FALSE;
			m_bTip2=TRUE;
		}
		else
		{
			m_bTip= FALSE;
			m_bTip2=FALSE;
		}
		//		((CButton*)GetDlgItem(IDC_CHECK_TIPS))->SetCheck(FALSE);

	}

	if(m_bTip)
	    strTitle = "技术评审尚未完成项目";
	if(m_bTip2)
		strTitle = "配置已完成但采购尚未交还项目";
	
	this->SetWindowText(strTitle);

	m_cList.SetEditable(FALSE);
	m_cList.GetDefaultCell(FALSE,FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

	try {
		m_cList.SetColumnCount(1);
		m_cList.SetRowCount(0);
		m_cList.SetFixedRowCount(0);
		m_cList.SetFixedColumnCount(0);
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
	m_cList.SetAutoSizeStyle(3);
	m_cList.SetListMode(TRUE);
	m_cList.SetSingleRowSelection(FALSE);

	try

	{

		COleDateTime m_dCompare = m_dCurrent - (COleDateTimeSpan)15;
		CString strDate = m_dCompare.Format("%Y-%m-%d");
		CString str,strID,strNo,strSource,strName;
		CString strFind;
		int iCount,iIndex=0;
		m_pSet.CreateInstance(__uuidof(Recordset));  
		if(m_bTip)
		{
			strFind = "SELECT DISTINCT PBInformation.ID, PBInformation.ProjectName, OrderOfProject.ElevatorID, Delivery.DInputDate, Delivery.ComfirmationSheetRelease FROM (PBInformation INNER JOIN OrderOfProject ON PBInformation.ID=OrderOfProject.ID) INNER JOIN Delivery ON OrderOfProject.OrderID=Delivery.OrderID WHERE (((Delivery.DInputDate)<=#"+strDate+"#) AND ((Delivery.ComfirmationSheetRelease) Is Null)) ORDER BY PBInformation.ID";
			strSQL = strFind.AllocSysString();
			theApp.ADOExecute(m_pSet,theApp.m_pConnect, strSQL);
			iCount = m_pSet->GetRecordCount();
            
           
			if(iCount !=0)
			{
                m_iNum =0;
				m_pSet->MoveFirst();
				for(int i= 0 ;i<iCount;i++)
				{
					
					Holder = m_pSet->GetCollect("ID");
					strID = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

					if(strID == strSource)
					{

						Holder = m_pSet->GetCollect("ElevatorID");
						strNo = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;          

						str =str + _T(",")+strNo;
						Item.strText = str;

						if(iIndex == iCount-1)
							m_cList.InsertRow(str, -1);
					}
					else
					{  
						m_iNum+=1;
						if(iIndex!=0)
						   m_cList.InsertRow(str, -1);

						str = strID;
						
						
						Holder = m_pSet->GetCollect("ProjectName");
						strName = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

						str =str +  _T(" ") + strName;

						Holder = m_pSet->GetCollect("ElevatorID");
						strNo = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

						str = str + _T(" ") + strNo;


					}

					strSource = strID;
					iIndex+=1;
					m_pSet->MoveNext();
					
				}
				m_pSet->Close();
				m_cList.AutoSizeColumn(0,GVS_DEFAULT,TRUE);
				m_cList.Invalidate();

			}
			else
			{
				OnOK();

			}
		}

		if(m_bTip2)
		{
			strFind = "SELECT DISTINCT PBInformation.ID, PBInformation.ProjectName, OrderOfProject.ElevatorID, Delivery.ConfigureFinishCheck, Delivery.PurchaseReturnCheck  \
				FROM (Configuration LEFT JOIN Controller ON Configuration.OrderID = Controller.OrderID) RIGHT JOIN (PBInformation INNER JOIN (OrderOfProject LEFT JOIN Delivery ON OrderOfProject.OrderID = Delivery.OrderID) ON PBInformation.ID = OrderOfProject.ID) ON Configuration.OrderID = OrderOfProject.OrderID \
				WHERE (((Delivery.ConfigureFinishCheck)=True) AND ((Delivery.PurchaseReturnCheck)=False)) \
				ORDER BY Delivery.PurchaseReturnCheck;";
			strSQL = strFind.AllocSysString();
			theApp.ADOExecute(m_pSet,theApp.m_pConnect, strSQL);
			iCount = m_pSet->GetRecordCount();

			if(iCount !=0)
			{
				m_iNum=0;
				m_pSet->MoveFirst();

				for(int i= 0 ;i<iCount;i++)
				{

					Holder = m_pSet->GetCollect("ID");
					strID = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

					if(strID == strSource)
					{

						Holder = m_pSet->GetCollect("ElevatorID");
						strNo = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;          

						str =str + _T(",")+strNo;
						if(iIndex == iCount-1)
							m_cList.InsertRow(str, -1);
					}
					else
					{   
						if(iIndex!=0)
							m_cList.InsertRow(str, -1);
						
                        m_iNum+=1;
						str = strID;

						Holder = m_pSet->GetCollect("ProjectName");
						strName = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

						str =str +  _T(" ") + strName;

						Holder = m_pSet->GetCollect("ElevatorID");
						strNo = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

						str = str + _T(" ") + strNo;

	                    m_cList.InsertRow(str, -1);

					}

					strSource = strID;
					m_pSet->MoveNext();

				}
				m_pSet->Close();
				m_cList.AutoSizeColumn(0,GVS_DEFAULT,TRUE);
				m_cList.Invalidate();
				
			}
			else
			{
				OnOK();

			}
		}
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


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE

}

void CSysTipDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::OnOK();
}

void CSysTipDlg::OnBnClickedCheckNexttips()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CString strValue;
	if(((CButton*)GetDlgItem(IDC_CHECK_NEXTTIPS))->GetCheck())
	{

		strValue = _T("1");
		m_bTip2=FALSE;
	}
	else
	{

		strValue = _T("0");
	}


	CString strSection = _T("PathofDatabase");
	CString strSectionKey  = _T("Tips");

	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);
	UpdateData(FALSE);
}

void CSysTipDlg::OnBnClickedCheckNexttips2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CString strValue;
	if(((CButton*)GetDlgItem(IDC_CHECK_NEXTTIPS2))->GetCheck())
	{
		strValue = _T("2");
		m_bTip=FALSE;
	}
	else
	{


		strValue = _T("0");
	}


	CString strSection = _T("PathofDatabase");
	CString strSectionKey  = _T("Tips");

	WritePrivateProfileString(LPCSTR(strSection),LPCSTR(strSectionKey),LPCSTR(strValue), FilePath);
	UpdateData(FALSE);
}
