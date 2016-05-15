//==================================================================
// Author:		Ma811 
// Email:		Ma811@yeah.net
// Verison:		0.9
// Date:		2002-2-11
//==================================================================


#include "stdafx.h"
#include "AlphaCtrl.h"
#include ".\alphactrl.h"

#pragma comment(lib, "msimg32")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT tdDisplay(LPVOID lpParam);
/////////////////////////////////////////////////////////////////////////////
// CAlphaCtrl

CAlphaCtrl::CAlphaCtrl()
{
	bCanPaint = 0;
	nTimer    = 100; 
}

CAlphaCtrl::~CAlphaCtrl()
{
}


BEGIN_MESSAGE_MAP(CAlphaCtrl, CStatic)
	//{{AFX_MSG_MAP(CAlphaCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlphaCtrl message handlers

void CAlphaCtrl::AlphaDisplay(CDC &pDC, CClientDC &dc, BLENDFUNCTION& rBlendProps, int width, int heigh, byte nLevel)
{
	rBlendProps.SourceConstantAlpha = nLevel;

	AlphaBlend( dc.m_hDC, 0, 0, width, heigh, pDC.m_hDC, 0, 0, 
		width, heigh, rBlendProps );
}

/*显示线程*/
UINT tdDisplay(LPVOID lpParam)
{
	CAlphaCtrl* AlphaCtrl = (CAlphaCtrl*)lpParam;

	CClientDC dc(AlphaCtrl);
	CDC pDC;
	pDC.CreateCompatibleDC(&dc); 
	pDC.SelectObject(&AlphaCtrl->Bmp);

	BLENDFUNCTION rBlendProps;
	rBlendProps.BlendOp = AC_SRC_OVER;
	rBlendProps.BlendFlags = 0;
	rBlendProps.AlphaFormat = 0;

	BITMAP bmInfo;
	::GetObject( AlphaCtrl->Bmp.m_hObject, sizeof(BITMAP), &bmInfo );
	INT nWidth, nHeigh;
	nWidth = bmInfo.bmWidth;
	nHeigh = bmInfo.bmHeight;

	AlphaCtrl->SetWindowPos(NULL, 0, 0, nWidth, nHeigh, SWP_NOMOVE);

	int i = 0;
	while(i <= 255)
	{
		AlphaCtrl->AlphaDisplay(pDC, dc, rBlendProps, nWidth, nHeigh, i);
		i += 5;
		Sleep(AlphaCtrl->nTimer);
	}

	AlphaCtrl->bCanPaint = 1;		//Make OnPaint Word

	AfxEndThread(0);
	return 0;
}

//******************************************************************
//Name: LoadAlphaBitmap
//参数: nID 位图资源ID，iTimer 显示时间间隔，值愈小显示愈快
//返回: 成功返回1，失败返回0
//******************************************************************
BOOL CAlphaCtrl::LoadAlphaBitmap(UINT uID, int iTimer)
{
	int i = Bmp.LoadBitmap(uID);
	
	if(i)
	{
		AfxBeginThread(tdDisplay, this);
		nBmpID = uID;
		nTimer = iTimer;
		return 1;
	}
	else
	{
		TRACE("Load Bitmap Failed\n");
		return 0;
	}
	
	return 1;
}

void CAlphaCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(bCanPaint)
	{
		Bmp.Detach();
		Bmp.LoadBitmap(nBmpID);
		
		BITMAP bmInfo;
		::GetObject( Bmp.m_hObject, sizeof(BITMAP), &bmInfo );
		INT nWidth, nHeigh;
		nWidth = bmInfo.bmWidth;
		nHeigh = bmInfo.bmHeight;
	
		CDC pDC;
		pDC.CreateCompatibleDC(&dc);
		pDC.SelectObject(&Bmp);
		dc.BitBlt(0, 0, nWidth, nHeigh, &pDC, 0, 0, SRCCOPY);
	}
	// Do not call CStatic::OnPaint() for painting messages
}

BOOL CAlphaCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

//	return TRUE;
	return CStatic::OnEraseBkgnd(pDC);
}
