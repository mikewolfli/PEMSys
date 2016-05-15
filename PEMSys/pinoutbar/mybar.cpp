#include "stdafx.h"
//#include "AutoHideBar.h"
//#include "gncase2.h"


#include "mybar.h"
#include "..\resource.h"
/////////////////////////////////////////////////////////////////////////////
// CMyBar

void CMyBar::InitializeOutlookBar()
{
	imaLarge.Create(IDB_ITEM, 32, 0, RGB(128,128,128));
	imaSmall.Create(IDB_SMALL_ITEM, 16, 0, RGB(0,128,128));

	wndBar.SetImageList(&imaLarge, CGfxOutBarCtrl::fLargeIcon);
	wndBar.SetImageList(&imaSmall, CGfxOutBarCtrl::fSmallIcon);

	wndBar.SetAnimationTickCount(5);

	wndBar.SetAnimSelHighlight(200);

	//Blue Sky加入的控制
//	wndBar.SetIfQueryRemove(true);

	wndBar.AddFolder("项目管理", 0);
	wndBar.AddFolder("合同管理", 1);
	wndBar.AddFolder("物料资源管理", 2);
	wndBar.AddFolder("供应商管理", 3);
	wndBar.AddFolder("分公司/客户管理",4);
	//	wndBar.AddFolder("采购管理",5);
	//	wndBar.AddFolder("销售管理",6);
	//	wndBar.AddFolder("质量管理",7);
	//	wndBar.AddFolder("生产管理",8);
	//	wndBar.AddFolder("库存管理",9);
	//	wndBar.AddFolder("用户维护",10);
	//	wndBar.AddFolder("系统维护",11);
//	wndBar.AddFolder("用户维护",5);
//	wndBar.AddFolder("系统维护",6);


//	wndBar.InsertItem(0, 0, "向导", 0, 0);
	wndBar.InsertItem(0, 0, "项目", 1, 0);
//	wndBar.InsertItem(0, 1, "订单配置",9, 0);
	wndBar.InsertItem(0, 1, "电梯参数", 5, 0);
	wndBar.InsertItem(0, 2, "商务查询", 14, 0);
	wndBar.InsertItem(0, 3, "进出口", 0, 0);
//	wndBar.InsertItem(0, 3, "Excel输出", 24, 0);
//	wndBar.InsertItem(0, 2, "井道", 3, 0);
//	wndBar.InsertItem(0, 3, "楼层", 4, 0);
//	wndBar.InsertItem(0, 4, "轿厢", 5, 0);
//	wndBar.InsertItem(0, 5, "电气", 6, 0);
//	wndBar.InsertItem(0, 6, "装潢", 7, 0);
//	wndBar.InsertItem(0, 7, "其它", 8, 0);


//	wndBar.InsertItem(1, 0, "向导", 0, 0);
	wndBar.InsertItem(1, 0, "MOL生成", 9, 0);
	wndBar.InsertItem(1, 1, "合同MOL", 10, 0);
	wndBar.InsertItem(1, 2, "标准MOL", 11, 0);
	wndBar.InsertItem(1, 3, "MOL输出", 12, 0);

	wndBar.InsertItem(2, 0, "零部件", 5, 0);
	wndBar.InsertItem(2, 1, "特殊件", 13, 0);
	wndBar.InsertItem(2, 3, "部件BOM", 10, 0);
	wndBar.InsertItem(2, 4, "BOM输出", 12, 0);

	wndBar.InsertItem(3, 1, "基本资料", 9, 0);
	wndBar.InsertItem(3, 2, "分类查询", 14, 0);
	wndBar.InsertItem(3, 3, "产品关联", 15, 0);

	wndBar.InsertItem(4, 0, "基本资料", 9, 0);
	wndBar.InsertItem(4, 1, "信息查询", 14, 0);

	//	wndBar.InsertItem(5, 0, "无", 8, 0);

	//	wndBar.InsertItem(6, 0, "无", 8, 0);

	//	wndBar.InsertItem(7, 0, "无", 8, 0);

	//	wndBar.InsertItem(8, 0, "无", 8, 0);

	//	wndBar.InsertItem(9, 0, "无", 8, 0);

	//	wndBar.InsertItem(10, 0, "登录", 18, 0);
	//	wndBar.InsertItem(10, 1, "注销", 19, 0);
	//	wndBar.InsertItem(10, 2, "修改密码",21,0);
	//	wndBar.InsertItem(10, 3, "退出系统", 20, 0);

	//	wndBar.InsertItem(11, 0, "人员维护", 17, 0);
	//	wndBar.InsertItem(11, 1, "系统配置", 16, 0);
	//	wndBar.InsertItem(11, 2, "界面方案", 15, 0);
	//	wndBar.InsertItem(11, 3, "数据库备份",22,0);
	//	wndBar.InsertItem(11, 4, "还原数据库",23,0);

//	wndBar.InsertItem(5, 0, "登录", 18, 0);
//	wndBar.InsertItem(5, 1, "注销", 19, 0);
//	wndBar.InsertItem(5, 2, "修改密码",21,0);
//	wndBar.InsertItem(5, 3, "退出系统", 20, 0);

//	wndBar.InsertItem(6, 0, "人员维护", 17, 0);
//	wndBar.InsertItem(6, 1, "系统配置", 16, 0);
//	wndBar.InsertItem(6, 2, "界面方案", 15, 0);
//	wndBar.InsertItem(6, 3, "数据库备份",22,0);
//	wndBar.InsertItem(6, 4, "还原数据库",23,0);

	wndBar.SetSelFolder(0);

}

CMyBar::CMyBar()
{
	m_bFloate = FALSE;
	m_hParentWnd =NULL ;
}

CMyBar::~CMyBar()
{
}

BEGIN_MESSAGE_MAP(CMyBar, CPinDockBar)
	//{{AFX_MSG_MAP(CMyBar)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


void CMyBar::AddToDrawBar(CAutoHideBar * pDrawBar)
{
	CRect rt;
	wndBar.GetClientRect(&rt);
    wndBar.ShowWindow(SW_SHOW);
	pDrawBar->AddButton("快捷工具栏 ", DRAWBTNSTYLE_GROUP | DRAWBTNSTYLE_SELECT, &wndBar, this, &rt, this, 0);
	
};

void CMyBar::RemoveFromDrawBar(CAutoHideBar * pDrawBar)
{
	CRect rt;
	pDrawBar->RemoveButton(&wndBar);
	pDrawBar->Shrink();
	pDrawBar->CalcLayout();
	pDrawBar->Invalidate();
	GetParentFrame()->ShowControlBar(this, TRUE, FALSE);
};

/////////////////////////////////////////////////////////////////////////////
// CMyBar message handlers

int CMyBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPinDockBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DWORD dwf = CGfxOutBarCtrl::fDragItems|CGfxOutBarCtrl::fEditGroups|CGfxOutBarCtrl::fEditItems|CGfxOutBarCtrl::fRemoveGroups|
				CGfxOutBarCtrl::fRemoveItems|CGfxOutBarCtrl::fAddGroups|CGfxOutBarCtrl::fAnimation;

	if(!wndBar.Create(WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), 
		this, 102, dwf))

	{
		TRACE0("Failed to create outlook bar.");
		return -1;
	}


	InitializeOutlookBar() ;

	// TODO: Add your specialized creation code here
	return 0;
}

void CMyBar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CPinDockBar::OnWindowPosChanged(lpwndpos);

	// should only be called once, when floated.
	if( IsFloating() )
	{
		if( m_pDockBar && !m_bFloate )
		{
			m_bFloate = TRUE ;
			CWnd* pParent = m_pDockBar->GetParent();
			if( pParent->IsKindOf(RUNTIME_CLASS(CMiniFrameWnd)))
			{
				HWND h = pParent->m_hWnd ;
				if(h != m_hParentWnd)
				{
					m_hParentWnd = h ;
					g_af.SkinWindow(m_hParentWnd,SKIN_CLASS_NOSKIN) ;
				}

			}
		}
		else if( m_bFloate ) 
		{
			m_bFloate = FALSE;		
		}
	}
}
