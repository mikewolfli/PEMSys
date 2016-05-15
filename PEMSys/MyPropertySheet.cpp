// MyPropertySheet.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "MyPropertySheet.h"
#include ".\mypropertysheet.h"


// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)
CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}
CMyPropertySheet::CMyPropertySheet():CPropertySheet()
{
}

CMyPropertySheet::~CMyPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// CMyPropertySheet 消息处理程序

BOOL CMyPropertySheet::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
/*
	if(pMsg!=NULL && pMsg->message == WM_LBUTTONDOWN)
	{
		CWnd *pWnd = (CWnd*)CPropertySheet::GetTabControl();
		if(pWnd !=NULL &&pWnd->GetSafeHwnd() == pMsg->hwnd)
		{
			::SendMessage(pMsg->hwnd, pMsg->message, pMsg->wParam, pMsg->lParam);
			if(GetActiveIndex() == 0)
			{

			}else
			{

			}
			return TRUE;
		}
	}
*/
	if(pMsg->message == WM_KEYUP && pMsg->wParam ==  VK_PRIOR)
	{
		if(GetPageCount()>1)
		{
			if(GetActiveIndex()==0)
				SetActivePage(GetPageCount()-1);
			else
				SetActivePage(GetActiveIndex()-1);
		}
	}

	if(pMsg->message == WM_KEYUP && pMsg->wParam == VK_NEXT)
	{
		if(GetPageCount()>1)
		{
			if(GetActiveIndex()==(GetPageCount()-1))
				SetActivePage(0);
			else
				SetActivePage(GetActiveIndex()+1);
		}
	}


	return CPropertySheet::PreTranslateMessage(pMsg);
}

BOOL CMyPropertySheet::OnHelpInfo(HELPINFO* pHelpInfo)
{
	BOOL ret = FALSE;
	bool handled = false;

	if (GetStyle() & WS_CHILD)
	{
		// were an embedded property sheet, need to pass up 
		// the chain to get this message processed correctly
		CWnd * pWnd = GetParent();
		while (pWnd != NULL && pWnd->GetStyle() & WS_CHILD)
		{
			// move up the window heirarchy while 
			// finding child windows
			pWnd = pWnd->GetParent();
		}
		if (pWnd != NULL)
		{
			ret = GetParent()->GetParent()->SendMessage(WM_HELP, 
				0, (LPARAM)(pHelpInfo));
			handled = true;
		}
		// the sheet does not have a non child parent, 
		// some kind of problem!
		ASSERT(handled);    
	}
	if (!handled)
	{
		ret = CPropertySheet::OnHelpInfo(pHelpInfo);
	}
	return ret;
}

LRESULT CMyPropertySheet::OnQuerySiblings(WPARAM wParam, LPARAM lParam)
{
	// change the wParam and/or lParam values

	int nPages = GetPageCount();
	LRESULT result = 0;
	for (int page = 0; page < nPages && result == 0; ++page)
		result = GetPage(page)->SendMessage(PSM_QUERYSIBLINGS, wParam, lParam);

	return result;
}