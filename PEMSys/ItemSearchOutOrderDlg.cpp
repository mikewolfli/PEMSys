// ItemSearchOutOrderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemSearchOutOrderDlg.h"
#include ".\itemsearchoutorderdlg.h"


// CItemSearchOutOrderDlg 对话框

IMPLEMENT_DYNAMIC(CItemSearchOutOrderDlg, CDialog)
CItemSearchOutOrderDlg::CItemSearchOutOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CItemSearchOutOrderDlg::IDD, pParent)
{
}

CItemSearchOutOrderDlg::~CItemSearchOutOrderDlg()
{
}

void CItemSearchOutOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DISPLAY, m_cList);
}


BEGIN_MESSAGE_MAP(CItemSearchOutOrderDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_BOTTOM, OnBnClickedButtonBottom)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CItemSearchOutOrderDlg 消息处理程序

void CItemSearchOutOrderDlg::MoveUpOrDown(BOOL bCheck)
{
	int iCount,iIndex, iOffset;

	//iCount选中记录的数量, iIndex ListBox控件类记录数量,iOffset移动步数



	CArray<int,int> aryListBoxSel;//用来存取选中记录在ListBox中的位置(行标或第几行)

	/* CArray <Type, argType> –模板类,

	Type 指定希望收集的对象类型

	argType 指定函数的参数类型

	*/

	CString str;



	if(bCheck)

	{

		iOffset = -1;//上移一步

	}

	else

	{

		iOffset = 1;//下移一步

	}

	iCount = m_cList.GetSelCount();//得到选中的记录数量

	iIndex = m_cList.GetCount();//得到控件内的记录数量

	if(iCount==0 || iIndex==0)
		return;

	aryListBoxSel.SetSize(iCount);//设置数组大小

	m_cList.GetSelItems(iCount,aryListBoxSel.GetData());

	//将选中记录的位置信息填入数组缓冲区

	//循环移动选中的记录,

	for(int i =0; i<iCount ;i++)

	{

		if(bCheck&& aryListBoxSel[i]== 0 || !bCheck &&aryListBoxSel[i]==iIndex-1)

			continue;//当记录位于最顶或最底位置时,跳过此记录

		m_cList.GetText(aryListBoxSel[i],str);//将相应位置的记录取出

		m_cList.DeleteString(aryListBoxSel[i]);//删除此记录

		m_cList.InsertString(aryListBoxSel[i]+iOffset,str);//向上或向下插入记录

		m_cList.SetSel(aryListBoxSel[i]+iOffset,TRUE);//选中插入的记录

	} 
}

void CItemSearchOutOrderDlg::OnBnClickedButtonFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
    MoveUporDownEnd(TRUE);
	UpdateData(FALSE);
}

void CItemSearchOutOrderDlg::OnBnClickedButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
    MoveUpOrDown(TRUE);
	UpdateData(FALSE);
}

void CItemSearchOutOrderDlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	MoveUpOrDown(FALSE);
	UpdateData(FALSE);
}

void CItemSearchOutOrderDlg::OnBnClickedButtonBottom()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
    MoveUporDownEnd(FALSE);
	UpdateData(FALSE);
}

void CItemSearchOutOrderDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CItemSearchOutOrderDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

void CItemSearchOutOrderDlg::MoveUporDownEnd(BOOL bDir)
{
	int iCount,iIndex, iOffset;

	//iCount选中记录的数量, iIndex ListBox控件类记录数量,iOffset移动步数



	CArray<int,int> aryListBoxSel;//用来存取选中记录在ListBox中的位置(行标或第几行)

	/* CArray <Type, argType> –模板类,

	Type 指定希望收集的对象类型

	argType 指定函数的参数类型

	*/

	CString str;



	if(bDir)

	{

		iOffset = -1;//上移一步

	}

	else

	{

		iOffset = 1;//下移一步

	}

	iCount = m_cList.GetSelCount();//得到选中的记录数量

	iIndex = m_cList.GetCount();//得到控件内的记录数量
	
	if(iCount==0 || iIndex==0)
		return;

	aryListBoxSel.SetSize(iCount);//设置数组大小

	m_cList.GetSelItems(iCount,aryListBoxSel.GetData());

	//将选中记录的位置信息填入数组缓冲区

	//循环移动选中的记录,

	for(int i =0; i<iCount ;i++)

	{

		while((bDir&& aryListBoxSel[i]!= 0) || (!bDir &&aryListBoxSel[i]!=iIndex-1))
		{
		m_cList.GetText(aryListBoxSel[i],str);//将相应位置的记录取出

		m_cList.DeleteString(aryListBoxSel[i]);//删除此记录

		m_cList.InsertString(aryListBoxSel[i]+iOffset,str);//向上或向下插入记录

		m_cList.SetSel(aryListBoxSel[i]+iOffset,TRUE);//选中插入的记录
		}
	}
}

BOOL CItemSearchOutOrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
