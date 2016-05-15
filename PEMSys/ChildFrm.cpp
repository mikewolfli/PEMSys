// ChildFrm.cpp : CChildFrame ���ʵ��
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


// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	// Ϊ�����������ô���ı���
	cs.style &= ~FWS_ADDTOTITLE;
	cs.style &= ~FWS_PREFIXTITLE;

	cs.style &= ~WS_THICKFRAME;
	cs.style |= WS_BORDER;
	//ʹ�Ӵ���������
	cs.style &= ~(WS_MAXIMIZEBOX);
	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CChildFrame ���

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


// CChildFrame ��Ϣ�������

void CChildFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ����ר�ô����/����û���

//	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
}
