// ChildFrm.cpp : CChildFrame 类的实现
//
#include "stdafx.h"
#include "PEMSys.h"

#include "ChildFrm.h"
#include ".\childfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	// 为了能正常设置窗体的标题
	cs.style &= ~FWS_ADDTOTITLE;
	cs.style &= ~FWS_PREFIXTITLE;

	cs.style &= ~WS_THICKFRAME;
	cs.style |= WS_BORDER;
	//使子窗体无最大框
	cs.style &= ~(WS_MAXIMIZEBOX);
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame 消息处理程序

void CChildFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CMDIChildWnd::OnGetMinMaxInfo(lpMMI);

	CRect	rectClient;
	GetClientRect(&rectClient);

	CRect	rectWindow;
	GetWindowRect(&rectWindow);

	int nWidthOverhead = rectWindow.Width() - rectClient.Width();
	int nHeightOverhead = rectWindow.Height() - rectClient.Height();

	lpMMI->ptMinTrackSize.x = 600 + nWidthOverhead;
	lpMMI->ptMinTrackSize.y = 400 + nHeightOverhead;
}

void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// TODO: 在此添加专用代码和/或调用基类

//	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
}
