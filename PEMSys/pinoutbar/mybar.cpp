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

	//Blue Sky����Ŀ���
//	wndBar.SetIfQueryRemove(true);

	wndBar.AddFolder("��Ŀ����", 0);
	wndBar.AddFolder("��ͬ����", 1);
	wndBar.AddFolder("������Դ����", 2);
	wndBar.AddFolder("��Ӧ�̹���", 3);
	wndBar.AddFolder("�ֹ�˾/�ͻ�����",4);
	//	wndBar.AddFolder("�ɹ�����",5);
	//	wndBar.AddFolder("���۹���",6);
	//	wndBar.AddFolder("��������",7);
	//	wndBar.AddFolder("��������",8);
	//	wndBar.AddFolder("������",9);
	//	wndBar.AddFolder("�û�ά��",10);
	//	wndBar.AddFolder("ϵͳά��",11);
//	wndBar.AddFolder("�û�ά��",5);
//	wndBar.AddFolder("ϵͳά��",6);


//	wndBar.InsertItem(0, 0, "��", 0, 0);
	wndBar.InsertItem(0, 0, "��Ŀ", 1, 0);
//	wndBar.InsertItem(0, 1, "��������",9, 0);
	wndBar.InsertItem(0, 1, "���ݲ���", 5, 0);
	wndBar.InsertItem(0, 2, "�����ѯ", 14, 0);
	wndBar.InsertItem(0, 3, "������", 0, 0);
//	wndBar.InsertItem(0, 3, "Excel���", 24, 0);
//	wndBar.InsertItem(0, 2, "����", 3, 0);
//	wndBar.InsertItem(0, 3, "¥��", 4, 0);
//	wndBar.InsertItem(0, 4, "����", 5, 0);
//	wndBar.InsertItem(0, 5, "����", 6, 0);
//	wndBar.InsertItem(0, 6, "װ��", 7, 0);
//	wndBar.InsertItem(0, 7, "����", 8, 0);


//	wndBar.InsertItem(1, 0, "��", 0, 0);
	wndBar.InsertItem(1, 0, "MOL����", 9, 0);
	wndBar.InsertItem(1, 1, "��ͬMOL", 10, 0);
	wndBar.InsertItem(1, 2, "��׼MOL", 11, 0);
	wndBar.InsertItem(1, 3, "MOL���", 12, 0);

	wndBar.InsertItem(2, 0, "�㲿��", 5, 0);
	wndBar.InsertItem(2, 1, "�����", 13, 0);
	wndBar.InsertItem(2, 3, "����BOM", 10, 0);
	wndBar.InsertItem(2, 4, "BOM���", 12, 0);

	wndBar.InsertItem(3, 1, "��������", 9, 0);
	wndBar.InsertItem(3, 2, "�����ѯ", 14, 0);
	wndBar.InsertItem(3, 3, "��Ʒ����", 15, 0);

	wndBar.InsertItem(4, 0, "��������", 9, 0);
	wndBar.InsertItem(4, 1, "��Ϣ��ѯ", 14, 0);

	//	wndBar.InsertItem(5, 0, "��", 8, 0);

	//	wndBar.InsertItem(6, 0, "��", 8, 0);

	//	wndBar.InsertItem(7, 0, "��", 8, 0);

	//	wndBar.InsertItem(8, 0, "��", 8, 0);

	//	wndBar.InsertItem(9, 0, "��", 8, 0);

	//	wndBar.InsertItem(10, 0, "��¼", 18, 0);
	//	wndBar.InsertItem(10, 1, "ע��", 19, 0);
	//	wndBar.InsertItem(10, 2, "�޸�����",21,0);
	//	wndBar.InsertItem(10, 3, "�˳�ϵͳ", 20, 0);

	//	wndBar.InsertItem(11, 0, "��Աά��", 17, 0);
	//	wndBar.InsertItem(11, 1, "ϵͳ����", 16, 0);
	//	wndBar.InsertItem(11, 2, "���淽��", 15, 0);
	//	wndBar.InsertItem(11, 3, "���ݿⱸ��",22,0);
	//	wndBar.InsertItem(11, 4, "��ԭ���ݿ�",23,0);

//	wndBar.InsertItem(5, 0, "��¼", 18, 0);
//	wndBar.InsertItem(5, 1, "ע��", 19, 0);
//	wndBar.InsertItem(5, 2, "�޸�����",21,0);
//	wndBar.InsertItem(5, 3, "�˳�ϵͳ", 20, 0);

//	wndBar.InsertItem(6, 0, "��Աά��", 17, 0);
//	wndBar.InsertItem(6, 1, "ϵͳ����", 16, 0);
//	wndBar.InsertItem(6, 2, "���淽��", 15, 0);
//	wndBar.InsertItem(6, 3, "���ݿⱸ��",22,0);
//	wndBar.InsertItem(6, 4, "��ԭ���ݿ�",23,0);

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
	pDrawBar->AddButton("��ݹ����� ", DRAWBTNSTYLE_GROUP | DRAWBTNSTYLE_SELECT, &wndBar, this, &rt, this, 0);
	
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
