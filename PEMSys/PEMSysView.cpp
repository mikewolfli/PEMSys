// PEMSysView.cpp : CPEMSysView 类的实现
//

#include "stdafx.h"
#include "PEMSys.h"

#include "PEMSysDoc.h"
#include "PEMSysView.h"
#include ".\pemsysview.h"
#include "Crypt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPEMSysView

IMPLEMENT_DYNCREATE(CPEMSysView, CFormView)

BEGIN_MESSAGE_MAP(CPEMSysView, CFormView)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnBnClickedButtonLast)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PREVIOUS, OnBnClickedButtonPrevious)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, OnBnClickedButtonModify)
END_MESSAGE_MAP()

// CPEMSysView 构造/析构

CPEMSysView::CPEMSysView()
: CFormView(CPEMSysView::IDD)
, m_sUserID(_T(""))
, m_sName(_T(""))
, m_sPassword(_T(""))
, m_sCPassword(_T(""))
, m_sTelSubNum(_T(""))
, m_sMobileNum(_T(""))
, m_sDepartment(_T(""))
, m_sRemark(_T(""))
, m_sDisplay(_T(" of "))
, m_bAdd(FALSE)
, m_bEdit(FALSE)
, m_bMove(FALSE)
, m_iPos(0)
, m_strAuthor(_T(""))
, m_bPrice(FALSE)
, m_bPay(FALSE)
, m_bTrack(FALSE)
, m_bProduction(FALSE)
, m_bDelivery(FALSE)
, m_bBasic(FALSE)
, m_bShaft(FALSE)
, m_bCar(FALSE)
, m_bDecoration(FALSE)
, m_bElectric(FALSE)
, m_bPart(FALSE)
{
	// TODO: 在此处添加构造代码
}

CPEMSysView::~CPEMSysView()
{
	if(m_pUsersSet->State == adStateOpen)
	{
		m_pUsersSet->Close();
		m_pUsersSet.Release();
	}
}

void CPEMSysView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_GRIDCTRL, m_cGrid);
	DDX_Control(pDX, IDC_BUTTON_SEARCH, m_cSearch);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_cAdd);
	DDX_Control(pDX, IDC_BUTTON_MODIFY, m_cModify);
	DDX_Control(pDX, IDC_BUTTON_FIRST, m_cFirst);
	DDX_Control(pDX, IDC_BUTTON_PREVIOUS, m_cPrevious);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_cNext);
	DDX_Control(pDX, IDC_BUTTON_LAST, m_cLast);
	DDX_Control(pDX, IDC_EDIT_USERID, m_cUserID);
	DDX_Text(pDX, IDC_EDIT_USERID, m_sUserID);
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_sPassword);
	DDX_Text(pDX, IDC_EDIT_PWCONFIRM, m_sCPassword);
	DDX_Text(pDX, IDC_EDIT_TELSUBNUM, m_sTelSubNum);
	DDX_Text(pDX, IDC_EDIT_MOBILENUM, m_sMobileNum);
	DDX_CBString(pDX, IDC_COMBO_DEPARTMENT, m_sDepartment);
	DDX_Text(pDX, IDC_EDIT_REMARK, m_sRemark);
	DDX_Text(pDX, IDC_EDIT_DISPLAY, m_sDisplay);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_cPassword);
	DDX_Control(pDX, IDC_EDIT_PWCONFIRM, m_cPConfirm);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_cDelete);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cSave);
	DDX_Control(pDX, IDC_BUTTON_CANCEL, m_cCancel);
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_cDepartment);
	DDX_Control(pDX, IDC_EDIT_NAME, m_cName);
	DDX_Check(pDX, IDC_CHECK_USER_PRICE, m_bPrice);
	DDX_Check(pDX, IDC_CHECK_USER_PAY, m_bPay);
	DDX_Check(pDX, IDC_CHECK_USER_TRACK, m_bTrack);
	DDX_Check(pDX, IDC_CHECK_USER_PRODUCTION, m_bProduction);
	DDX_Check(pDX, IDC_CHECK_USER_DELIVERY, m_bDelivery);
	DDX_Check(pDX, IDC_CHECK_USER_BASIC, m_bBasic);
	DDX_Check(pDX, IDC_CHECK_USER_SHAFT, m_bShaft);
	DDX_Check(pDX, IDC_CHECK_USER_CAR, m_bCar);
	DDX_Check(pDX, IDC_CHECK_USER_DECORATION, m_bDecoration);
	DDX_Check(pDX, IDC_CHECK_USER_ELECTRIC, m_bElectric);
	DDX_Check(pDX, IDC_CHECK_USER_PART, m_bPart);
}

// CPEMSysView 诊断

#ifdef _DEBUG
void CPEMSysView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPEMSysView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPEMSysDoc* CPEMSysView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPEMSysDoc)));
	return (CPEMSysDoc*)m_pDocument;
}
#endif //_DEBUG

void CPEMSysView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	GetParentFrame()->RecalcLayout();
	//	 ResizeParentToFit();
	ResizeParentToFit(FALSE);
	ResizeParentToFit(TRUE);
	// TODO: 在此添加专用代码和/或调用基类                                                                                                                                                                                                                                                                                                  
	CString strTitle ;
	strTitle = "人员维护";
	GetParentFrame()->SetWindowText(strTitle);

	m_cSearch.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_FIND));
	m_cAdd.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_ADD));
	m_cModify.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_MODIFY));
	m_cDelete.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_DELETE));
	m_cFirst.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_FIRST));
	m_cPrevious.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_PREVIOUS));
	m_cNext.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_NEXT));
	m_cLast.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LAST));
	m_cSave.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_SAVE));
	m_cCancel.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_CANCEL));


	m_cUserID.SetFocus();

	m_pUsersSet.CreateInstance(__uuidof(Recordset)); // 创建Recordset对象实例

	CRect rect,rect1;
	GetClientRect(rect);
	m_OldSize = CSize(rect.Width(), rect.Height());


	LOGFONT lf;

	memset(&lf, 0, sizeof(LOGFONT));
	strcpy(lf.lfFaceName, "仿宋体");
	lf.lfCharSet = GB2312_CHARSET;
	lf.lfHeight = 16;
	lf.lfWeight = 700;



	// 填充数据
	m_cGrid.SetEditable(FALSE);

	try {
		m_cGrid.SetColumnCount(9);
		m_cGrid.SetRowCount(2);
		m_cGrid.SetFixedRowCount(2);
		m_cGrid.SetFixedColumnCount(1);
		m_cGrid.MergeCells(0,0,0,8);

	}
	catch (CMemoryException* e)
	{
		e->ReportError();
		e->Delete();
		return;
	}


	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
	Item.row = 0;
	Item.col =0;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.strText.Format(_T("用户信息浏览"));
	m_cGrid.SetItemFont(0,0,&lf);
	m_cGrid.SetRowHeight(0,30);
	m_cGrid.SetAutoSizeStyle(GVS_BOTH);
	m_cGrid.SetColumnWidth(0,30);
	m_cGrid.SetColumnWidth(8,100);
	m_cGrid.SetRowHeight(1,30);
	m_cGrid.SetItem(&Item);

	for (int i=1;i<9;i++)
	{
		Item.row=1;
		Item.col=i;
		//		m_cGrid.SetItemFont(1,i,&lf1);
		switch(i)
		{
			//		case 0:
			//			Item.strText.Format(_T("序号"));
			//			m_cGrid.SetItem(&Item);
			//			break;
		case 1:
			Item.strText.Format(_T("用户编号"));
			m_cGrid.SetItem(&Item);
			break;
		case 2:
			Item.strText.Format(_T("用户姓名"));
			m_cGrid.SetItem(&Item);
			break;
		case 3:
			Item.strText.Format(_T("密码"));
			m_cGrid.SetItem(&Item);
			break;
		case 4:
			Item.strText.Format(_T("分机号"));
			m_cGrid.SetItem(&Item);
			break;
		case 5:
			Item.strText.Format(_T("移动电话"));
			m_cGrid.SetItem(&Item);
			break;
		case 6:
			Item.strText.Format(_T("部门"));
			m_cGrid.SetItem(&Item);
			break;
		case 7:
			Item.strText.Format(_T("用户权限"));
			m_cGrid.SetItem(&Item);
			break;
		case 8:
			Item.strText.Format(_T("说明"));
			m_cGrid.SetItem(&Item);
			break;
		default:
			break;
		}
	}

	strSQL="select * from Users";
	theApp.ADOExecute(m_pUsersSet,theApp.m_pConnect, strSQL);


    m_pUsersSet->MoveFirst();
	m_pUsersSet->get_Bookmark(&m_BookMark);
	RefreshList();
	m_iPos = 0;
	m_cPrevious.EnableWindow(FALSE);
	m_cFirst.EnableWindow(FALSE);

	RefreshEdit();


	//	m_cGrid.AutoSize();
}

BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam)
{
/*	CWnd* pWnd = CWnd::FromHandle(hwnd);
	CSize* pTranslate = (CSize*) lParam;

	CPEMSysView* pView = (CPEMSysView*) pWnd->GetParent();
	if (!pView) return FALSE;

	CRect rect;
	pWnd->GetWindowRect(rect);

	pView->ScreenToClient(rect);
	if(hwnd == pView->GetDlgItem(IDC_STATIC_GROUP)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left,rect.top,
			rect.Width()+pTranslate->cx,rect.Height());
	}
	if(hwnd == pView->GetDlgItem(IDC_CUSTOM_GRIDCTRL)->GetSafeHwnd())
	{  
		if(rect.Height() <=100)
		{
			pWnd->MoveWindow(rect.left,rect.top,
				rect.Width()+pTranslate->cx,100);
		}
		else
			pWnd->MoveWindow(rect.left,rect.top,
			rect.Width()+pTranslate->cx,rect.Height()+pTranslate->cy);
	}
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_SEARCH)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width(),rect.Height());
	} 
	if(hwnd == pView->GetDlgItem(IDC_EDIT_DISPLAY)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width(),rect.Height());
	} 
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_DELETE)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width(),rect.Height());
	} 
	if(hwnd == pView->GetDlgItem(IDC_STATIC_DELETE)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width(),rect.Height());
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC_SEARCH)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width(),rect.Height());
	}
	if(hwnd == pView->GetDlgItem(IDC_EDIT_USERID)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width()+pTranslate->cx/2, rect.Height(), FALSE);

	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC_USERID)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width(), rect.Height(), FALSE);

	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC_PASSWORD)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width(), rect.Height(), FALSE);

	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC_DEPART)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width(), rect.Height(), FALSE);

	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC_REMARK)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width(), rect.Height(), FALSE);

	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC_SUBNUM)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width(), rect.Height(), FALSE);

	} 
	if(hwnd == pView->GetDlgItem(IDC_STATIC_NAME)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_EDIT_NAME)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width()+pTranslate->cx/2,rect.Height(),FALSE);
	} 
	if(hwnd == pView->GetDlgItem(IDC_EDIT_PASSWORD)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width()+pTranslate->cx/2, rect.Height(), FALSE);
	} 
	if(hwnd == pView->GetDlgItem(IDC_EDIT_TELSUBNUM)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width()+pTranslate->cx/2, rect.Height(), FALSE);
	}
	if(hwnd  == pView->GetDlgItem(IDC_COMBO_DEPARTMENT)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width()+pTranslate->cx/2, rect.Height(), FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_EDIT_REMARK)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left, rect.top, 
			rect.Width()+pTranslate->cx/2, rect.Height(), FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC_CONFIRM)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_EDIT_PWCONFIRM)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width()+pTranslate->cx/2,rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC_MOBILE)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_EDIT_MOBILENUM)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width()+pTranslate->cx/2,rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_GROUP1)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width()+pTranslate->cx/2,rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_RADIO_LIMIT)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+2*pTranslate->cx/3,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_RADIO_MANAGE)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+2*pTranslate->cx/3,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_RADIO_COMMON)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+5*pTranslate->cx/6,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_RADIO_SYSTEM)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+5*pTranslate->cx/6,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_GROUP2)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left,rect.top,
			rect.Width()+pTranslate->cx/2,rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_GROUP3)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/2,rect.top,
			rect.Width()+pTranslate->cx/2,rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_ADD)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC1)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_MODIFY)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+3*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC2)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+3*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_SAVE)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+5*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC3)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+5*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_CANCEL)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+7*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC4)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+7*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_FIRST)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+9*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC5)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+9*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_PREVIOUS)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+11*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	} 
	if(hwnd == pView->GetDlgItem(IDC_STATIC6)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+11*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	} 
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_NEXT)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+13*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC7)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+13*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_BUTTON_LAST)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+15*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	if(hwnd == pView->GetDlgItem(IDC_STATIC8)->GetSafeHwnd())
	{
		pWnd->MoveWindow(rect.left+15*pTranslate->cx/16,rect.top,
			rect.Width(),rect.Height(),FALSE);
	}
	pView->Invalidate();*/

	return TRUE;
}


void CPEMSysView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (cx <= 600 || cy <=400) 
		return;

	//	Invalidate(false);         // this is for ensuring the controls to be redrawn correctly 

	CSize Translate(cx - m_OldSize.cx, cy - m_OldSize.cy);
	::EnumChildWindows(GetSafeHwnd(), EnumProc, (LPARAM)&Translate);
	m_OldSize = CSize(cx,cy);

}


void CPEMSysView::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	CFormView::OnClose();
}

void CPEMSysView::RefreshList()
{
	int i,j,n;
	i = m_cGrid.GetRowCount();
	j = m_pUsersSet->GetRecordCount();
	CString str;

	int iUserType;
	GV_ITEM Item;
	Item.mask = GVIF_TEXT|GVIF_FORMAT|GVL_BOTH|GVL_VERT ;
	Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	if(j>i-2)
	{
		for(n = i-1;n<j+1;n++)
		{
			str.Format("%d",n);
			m_cGrid.InsertRow(str,-1);
		}
	}
	else if(j<i-2)
	{
		for(n = i-1 ; n>j+1;n--)
		{
			m_cGrid.DeleteRow(n);
		}
	}

	if(!m_pUsersSet -> BOF) 
		m_pUsersSet->MoveFirst();
	n=2;
	while (!m_pUsersSet->EndOfFile) 
	{
		Item.row = n;
		for(int m=0;m<9;m++)
		{
			Item.col = m;
			switch(m)
			{
			case 0:
				Item.strText.Format("%d",n-1);
				m_cGrid.SetItem(&Item);
				break;
			case 1:
				Holder = m_pUsersSet->GetCollect(_T("UserID"));
				Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
				m_cGrid.SetItem(&Item);
				break;
			case 2:
				Holder = m_pUsersSet->GetCollect("Name");
				Item.strText.Format(Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder);
				m_cGrid.SetItem(&Item);
				break;
			case 3:
				Holder = m_pUsersSet->GetCollect("Password");
				Item.strText.Format(CCrypt::Decrypt(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder,1980));
				m_cGrid.SetItem(&Item);
				break;
			case 4:
				Holder = m_pUsersSet->GetCollect("TelSubNum");
				Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
				m_cGrid.SetItem(&Item);
				break;
			case 5:
				Holder = m_pUsersSet->GetCollect("MobileNum");
				Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
				m_cGrid.SetItem(&Item);
				break;
			case 6:
				Holder = m_pUsersSet->GetCollect("Department");
				Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
				m_cGrid.SetItem(&Item);
				break;
			case 7:
				iUserType = m_pUsersSet->GetCollect("UserType").iVal;
				switch(iUserType) 
				{
				case 1:
					str = _T("受限级");
					break;
				case 2:
					str = _T("普通级");
					break;
				case 3:
					str =  _T("管理级");
					break;
				case 4:
					str =  _T("系统管理级");
					break;
				case 5:
					str = _T("超级用户");
					break;
				default:
					break;
				}
				Item.strText.Format(str);
				m_cGrid.SetItem(&Item);
				break;
			case 8:
				Holder = m_pUsersSet->GetCollect("Remarks");
				Item.strText.Format(Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder);
				m_cGrid.SetItem(&Item);
				break;
			default:
				break;
			}	
		}

		++n;
		m_pUsersSet->MoveNext();
	}
    
	m_cGrid.AutoSizeColumn(8,GVS_BOTH,TRUE);
	m_pUsersSet->put_Bookmark(m_BookMark);
	m_bAdd = FALSE;
	m_bEdit = FALSE;
	m_bMove = FALSE;
	m_cGrid.Invalidate();

}

void CPEMSysView::RefreshEdit(void)
{
	UpdateData(TRUE);
	int iUserType;
	CString str;

	if(m_pUsersSet->State == adStateOpen && m_pUsersSet->GetRecordCount()!=0)
	{
		Holder = m_pUsersSet->GetCollect(_T("UserID"));
		m_sUserID = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

		Holder = m_pUsersSet->GetCollect("Name");
		m_sName = Holder.vt == VT_NULL?"":(char*)(_bstr_t)Holder;


		Holder = m_pUsersSet->GetCollect("Password");
		str = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
		m_sPassword = CCrypt::Decrypt(str, 1980);

		Holder = m_pUsersSet->GetCollect("TelSubNum");
		m_sTelSubNum = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;


		Holder = m_pUsersSet->GetCollect("MobileNum");
		m_sMobileNum = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

		Holder = m_pUsersSet->GetCollect("Department");
		m_sDepartment = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

		iUserType = m_pUsersSet->GetCollect("UserType").iVal;
		if(iUserType >= 4)
			iUserType = 4;
		switch(iUserType-1)
		{
		case 0:
			((CButton*)GetDlgItem(IDC_RADIO_LIMIT))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_RADIO_COMMON))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_MANAGE))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_SYSTEM))->SetCheck(FALSE);
			break;
		case 1:
			((CButton*)GetDlgItem(IDC_RADIO_COMMON))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_RADIO_LIMIT))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_MANAGE))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_SYSTEM))->SetCheck(FALSE);
			break;
		case 2:
			((CButton*)GetDlgItem(IDC_RADIO_MANAGE))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_RADIO_LIMIT))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_COMMON))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_SYSTEM))->SetCheck(FALSE);

			break;
		case 3:
			((CButton*)GetDlgItem(IDC_RADIO_SYSTEM))->SetCheck(TRUE);
			((CButton*)GetDlgItem(IDC_RADIO_LIMIT))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_COMMON))->SetCheck(FALSE);
			((CButton*)GetDlgItem(IDC_RADIO_MANAGE))->SetCheck(FALSE);
			break;
		default:
			break;
		}

		Holder = m_pUsersSet->GetCollect("Remarks");
		m_sRemark = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;

		Holder = m_pUsersSet->GetCollect("Authorization");
		m_strAuthor = Holder.vt==VT_NULL?"":(char*)(_bstr_t)Holder;
		
		AuthorParse();

		m_sDisplay.Format("%d of %d", m_iPos+1, m_pUsersSet->GetRecordCount());
		m_bAdd = FALSE;
		m_bEdit = FALSE;
		m_bMove = FALSE;
	}
	else
		ClearEdit();
	UpdateData(FALSE);

}

void CPEMSysView::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_cFirst.EnableWindow(TRUE);
	m_cNext.EnableWindow(TRUE);
	m_cFirst.EnableWindow(TRUE);
	m_cLast.EnableWindow(TRUE);

	m_sUserID.Trim();
	m_sName.Trim();
	m_sDepartment.Trim();

	if(m_sUserID== _T(""))
		m_sUserID = _T("%");
	if(m_sName == _T(""))
		m_sName = _T("%");
	if(m_sDepartment == _T(""))
		m_sDepartment = _T("%");

	strSQL=_T("select * from Users where UserID like'"+m_sUserID+"'\
		    and Name like'"+m_sName+"' and Department like'"+m_sDepartment+"'");

	theApp.ADOExecute(m_pUsersSet,theApp.m_pConnect, strSQL);

	int iCount = m_pUsersSet->GetRecordCount();

	if(0==iCount)
	{
		AfxMessageBox("没有所要查询的记录!", MB_ICONEXCLAMATION);
		return;
	}
	else
	{
		RefreshList();
		m_pUsersSet->MoveFirst();
		m_iPos = 0;
		m_cPrevious.EnableWindow(FALSE);
		m_cFirst.EnableWindow(FALSE);
		m_cNext.EnableWindow(TRUE);
		m_cLast.EnableWindow(TRUE);

		RefreshEdit();

	}
	UpdateData(FALSE);
}

void CPEMSysView::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
    m_bAdd = TRUE;
	m_cModify.EnableWindow(FALSE);
	m_cAdd.EnableWindow(FALSE);
	ClearEdit();
	m_cFirst.EnableWindow(FALSE);
	m_cNext.EnableWindow(FALSE);
	m_cPrevious.EnableWindow(FALSE);
	m_cLast.EnableWindow(FALSE);
	m_cDelete.EnableWindow(FALSE);
	m_cSearch.EnableWindow(FALSE);
	m_cSave.EnableWindow(TRUE);
    VARIANT_BOOL bEmpty;
    HRESULT hr = theApp.get_Empty(m_pUsersSet, &bEmpty);
	if(bEmpty) 
	{
		return;
	}
	else
	{
        m_pUsersSet->get_Bookmark(&m_BookMark);
		return;
	}
	UpdateData(FALSE);
}

void CPEMSysView::OnBnClickedButtonModify()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_sUserID == _T(""))
	{
		AfxMessageBox("请选择要修改的数据",MB_ICONEXCLAMATION);
		return;
	}
	else
	{
		m_bEdit = TRUE;
		m_cUserID.SetReadOnly(TRUE);
		m_cAdd.EnableWindow(FALSE);
		m_cModify.EnableWindow(FALSE);
		m_cFirst.EnableWindow(FALSE);
		m_cNext.EnableWindow(FALSE);
		m_cPrevious.EnableWindow(FALSE);
		m_cLast.EnableWindow(FALSE);
		m_cSearch.EnableWindow(FALSE);
		m_cSave.EnableWindow(TRUE);

	}
	UpdateData(FALSE);

}

void CPEMSysView::OnBnClickedButtonNext()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_iPos!=m_pUsersSet->GetRecordCount()-1)
	{
		m_bMove = TRUE;
		m_pUsersSet->MoveNext();
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

void CPEMSysView::OnBnClickedButtonLast()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(!(m_pUsersSet->EndOfFile))
	{   
		m_bMove = TRUE;
		m_pUsersSet->MoveLast();
		m_iPos = m_pUsersSet->GetRecordCount()-1;
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

void CPEMSysView::OnBnClickedButtonFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(!(m_pUsersSet->BOF))
	{   
		m_bMove = TRUE;
		m_pUsersSet->MoveFirst();
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

void CPEMSysView::OnBnClickedButtonPrevious()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(0!=m_iPos)
	{
		m_bMove = TRUE;
		m_pUsersSet->MovePrevious();
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

void CPEMSysView::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(FALSE);

	try
	{
		CString strTemp;

		HRESULT hr;
		strTemp = "UserID = '"+m_sUserID+"'";
		_bstr_t strFind(strTemp);
		m_pUsersSet->MoveFirst();
		hr = m_pUsersSet->Find(strFind,0,adSearchForward);
		if(!SUCCEEDED(hr))
		{
			AfxMessageBox("此用户不存在,无法删除",MB_ICONEXCLAMATION);
			m_cUserID.SetFocus();
			m_cUserID.SetSel(0,-1);
			return;
		}
		if(AfxMessageBox("是否确认删除当前记录",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
		{
			m_pUsersSet->Delete(adAffectCurrent);
			m_pUsersSet->Update();

			int i = m_pUsersSet->GetRecordCount();
			if(0!=i)
			{
				if (m_pUsersSet->EndOfFile) 
				{
					m_pUsersSet->MoveLast();
					m_iPos = m_pUsersSet->GetRecordCount()-1;
				}
				else {
					m_pUsersSet->MoveNext();
					if(m_pUsersSet->EndOfFile)
					{
						m_pUsersSet->MoveLast();
						m_iPos = m_pUsersSet->GetRecordCount()-1;
					}
				}
				m_pUsersSet->get_Bookmark(&m_BookMark);
				RefreshEdit();
				RefreshList();
			}
			else
			{
				m_cFirst.EnableWindow(FALSE);
				m_cLast.EnableWindow(FALSE);
				m_cPrevious.EnableWindow(FALSE);
				m_cNext.EnableWindow(FALSE);
				RefreshEdit();
				RefreshList();
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
void CPEMSysView::ClearEdit(void)
{
	UpdateData(TRUE);
	m_sUserID = _T("");
	m_sName = _T("");
	m_sPassword = _T("");
	m_sCPassword = _T("");
    m_sDepartment= _T("");
	m_sRemark = _T("");
	m_sTelSubNum = _T("");
	m_sMobileNum = _T("");
	((CButton*)GetDlgItem(IDC_RADIO_COMMON))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_RADIO_LIMIT))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_MANAGE))->SetCheck(FALSE);
	((CButton*)GetDlgItem(IDC_RADIO_SYSTEM))->SetCheck(FALSE);
	m_sDisplay.Format(" of ");
	UpdateData(FALSE);
}

void CPEMSysView::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_sUserID.Trim();
	m_sName.Trim();
	m_sDepartment.Trim();
	m_sPassword.Trim();
	m_sCPassword.Trim();
	m_sRemark.Trim();
	m_sTelSubNum.Trim();
	m_sMobileNum.Trim();

	CString sWarning="";
	CString strTemp;

	HRESULT hr;

	if ( ""==m_sUserID ) 
	{
		sWarning=_T("用户编号");
		m_cUserID.SetFocus();
		m_cUserID.SetSel(0,-1);
	}
	else if ( ""==m_sName )
	{
		sWarning=_T("用户姓名");
		((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetFocus();
		((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetSel(0,-1);
	}

	else if ( ""==m_sDepartment ) 
	{
		sWarning=_T("部门");
		m_cDepartment.SetFocus();
		m_cDepartment.SetEditSel(0,-1);
	}

	if ( ""!=sWarning ) 
	{
		sWarning += _T("不能为空");
		AfxMessageBox(sWarning, MB_ICONEXCLAMATION);
		return;
	}

	if(strlen(m_sPassword)>20)
	{
		AfxMessageBox("密码长度不能超过20个字符...",MB_ICONEXCLAMATION);
		m_cPassword.SetFocus();
		m_cPassword.SetSel(0,-1);
		return;
	}

	if(m_sPassword != m_sCPassword)
	{
		AfxMessageBox("请确认指定密码和确认密码是否一致...",MB_ICONEXCLAMATION);
		m_cPConfirm.SetFocus();
		m_cPConfirm.SetSel(0,-1);
		return;
	}


	m_cSave.EnableWindow(FALSE);

	if(m_bAdd)
	{

		CString strTemp;
		HRESULT hr;
		strTemp = "UserID = '"+m_sUserID+"'";
		_bstr_t strFind(strTemp);
		m_pUsersSet->MoveFirst();
		hr = m_pUsersSet->Find(strFind,0,adSearchForward);

		if(m_pUsersSet->EndOfFile)
		{

			m_pUsersSet->AddNew();
			AuthorDeParse();
            UpdateRecord(m_pUsersSet);

			m_pUsersSet->Update();
			m_iPos = m_pUsersSet->GetRecordCount()-1;
			m_pUsersSet->get_Bookmark(&m_BookMark);
			RefreshEdit();
			RefreshList();
			m_cModify.EnableWindow(TRUE);
			m_cAdd.EnableWindow(TRUE);
			m_cFirst.EnableWindow(TRUE);
			m_cNext.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(TRUE);
			m_cLast.EnableWindow(TRUE);
			m_cDelete.EnableWindow(TRUE);
			m_cSearch.EnableWindow(TRUE);
		}
		else
		{
			AfxMessageBox("此用户已经存在",MB_ICONEXCLAMATION);
			m_cUserID.SetFocus();
			m_cUserID.SetSel(0,-1);
			return;
		}
	} 

	if(m_bEdit)
	{
		m_bEdit = TRUE;

		try
		{
			strTemp = "UserID = '"+m_sUserID+"'";
			_bstr_t strFind(strTemp);
			m_pUsersSet->MoveFirst();
			hr = m_pUsersSet->Find(strFind,0,adSearchForward);
			if(m_pUsersSet->EndOfFile)
			{
				AfxMessageBox("此用户不存在,请先添加",MB_ICONEXCLAMATION);
				m_cUserID.EnableWindow(TRUE);
				m_cUserID.SetFocus();
				m_cUserID.SetSel(0,-1);
				return;
			}

			if(strlen(m_sPassword)>20)
			{
				AfxMessageBox("密码长度不能超过20个字符...",MB_ICONEXCLAMATION);
				m_cPassword.SetFocus();
				m_cPassword.SetSel(0,-1);
				return;
			}

			if(m_sPassword != m_sCPassword)
			{
				AfxMessageBox("请确认指定密码和确认密码是否一致...",MB_ICONEXCLAMATION);
				m_cPConfirm.SetFocus();		
				m_cPConfirm.SetSel(0,-1);
				return;
			}



			AuthorDeParse();
            UpdateRecord(m_pUsersSet);

			m_pUsersSet->Update();
			RefreshList();
			strTemp = "UserID = '"+m_sUserID+"'";
			_bstr_t strFindLast(strTemp);
			m_pUsersSet->MoveFirst();
			hr = m_pUsersSet->Find(strFindLast,0,adSearchForward);
//			m_iPos = m_pUsersSet->GetBookmark().iVal;

			m_cUserID.SetReadOnly(FALSE);
			m_cAdd.EnableWindow(TRUE);
			m_cModify.EnableWindow(TRUE);
			m_cFirst.EnableWindow(TRUE);
			m_cNext.EnableWindow(TRUE);
			m_cPrevious.EnableWindow(TRUE);
			m_cLast.EnableWindow(TRUE);
			m_cSearch.EnableWindow(TRUE);
		}
		catch(...)
		{
			return;
		}

	}

	UpdateData(FALSE);
}

void CPEMSysView::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_bAdd && AfxMessageBox("是否确认取消添加?",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	{
		m_bAdd = FALSE;
		m_cModify.EnableWindow(TRUE);
		m_cAdd.EnableWindow(TRUE);
		m_cFirst.EnableWindow(TRUE);
		m_cNext.EnableWindow(TRUE);
		m_cPrevious.EnableWindow(TRUE);
		m_cLast.EnableWindow(TRUE);
		m_cDelete.EnableWindow(TRUE);
		m_cSearch.EnableWindow(TRUE);

		VARIANT_BOOL bEmpty;
		HRESULT hr = theApp.get_Empty(m_pUsersSet, &bEmpty);
		if(bEmpty) 
		{
			return;
		}
		else
		{
			m_pUsersSet->put_Bookmark(m_BookMark);
			return;
		}      
		RefreshEdit();
	}
	if(m_bEdit&&AfxMessageBox("是否确认取消修改?",MB_OKCANCEL|MB_ICONQUESTION)==IDOK)
	{
		m_bEdit = FALSE;
		m_cUserID.SetReadOnly(FALSE);
		m_cAdd.EnableWindow(TRUE);
		m_cModify.EnableWindow(TRUE);
		m_cFirst.EnableWindow(TRUE);
		m_cNext.EnableWindow(TRUE);
		m_cPrevious.EnableWindow(TRUE);
		m_cLast.EnableWindow(TRUE);
		m_cSearch.EnableWindow(TRUE);
		RefreshEdit();

	}

	m_cSave.EnableWindow(FALSE);
	UpdateData(FALSE);
}


BOOL CPEMSysView::PreTranslateMessage(MSG* pMsg)
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

void CPEMSysView::UpdateRecord(_RecordsetPtr& pSet)
{

	int   iUserType;
	if(((CButton*)GetDlgItem(IDC_RADIO_LIMIT))->GetCheck())
		iUserType = 1;
	else if(((CButton*)GetDlgItem(IDC_RADIO_COMMON))->GetCheck())
		iUserType = 2;
	else if(((CButton*)GetDlgItem(IDC_RADIO_MANAGE))->GetCheck())
		iUserType = 3;
	else if(((CButton*)GetDlgItem(IDC_RADIO_SYSTEM))->GetCheck())
		iUserType = 4;
	else iUserType = 0;

	g_strAuthor = m_strAuthor;
	CString strPassword = CCrypt::Encrypt(m_sPassword, 1980);
	pSet->Fields->GetItem("UserID")->PutValue(m_sUserID.AllocSysString());
	pSet->Fields->GetItem("Name")->PutValue(m_sName.AllocSysString());
	pSet->Fields->GetItem("Password")->PutValue(strPassword.AllocSysString());
	pSet->Fields->GetItem("Department")->PutValue(m_sDepartment.AllocSysString());
	pSet->Fields->GetItem("TelSubNum")->PutValue(m_sTelSubNum.AllocSysString());
	pSet->Fields->GetItem("MobileNum")->PutValue(m_sMobileNum.AllocSysString());
	pSet->Fields->GetItem("UserType")->PutValue(iUserType);
	pSet->Fields->GetItem("Remarks")->PutValue(m_sRemark.AllocSysString());
	pSet->Fields->GetItem("Authorization")->PutValue(m_strAuthor.AllocSysString());
}

void CPEMSysView::AuthorParse(void)
{
	CString str;
    int lens= m_strAuthor.GetLength();
	if(lens==0)
	{
		m_bPrice = FALSE;
		m_bPay =FALSE;
		m_bTrack=FALSE;
		m_bProduction=FALSE;
		m_bDelivery=FALSE;
		m_bBasic=FALSE;
		m_bShaft=FALSE;
		m_bCar=FALSE;
		m_bDecoration=FALSE;
		m_bElectric=FALSE;
		m_bPart=FALSE;
		return;
	}
    
	UpdateData(FALSE);
    for(int i=0;i<lens; i++)
	{
       str=m_strAuthor.Mid(i,1);
	   if(str=="1")
	     ((CButton*)GetDlgItem(10443+i))->SetCheck(TRUE);
	   else if(str=="0"|| str=="")
		 ((CButton*)GetDlgItem(10443+i))->SetCheck(FALSE);
	}
	UpdateData(TRUE);
	return;
}

void CPEMSysView::AuthorDeParse(void)
{
	m_strAuthor="";
	CString str="";
	for(int i=0;i<11;i++)
	{
		if(((CButton*)GetDlgItem(10443+i))->GetCheck())
			str="1";
		else
			str="0";
		m_strAuthor+=str;
	}
	return;
}
