// NewClientWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PEMSys.h"
#include "NewClientWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewClientWnd

CNewClientWnd::CNewClientWnd()
{
	m_bitmap.LoadBitmap( IDB_BKGROUDMP );
}

CNewClientWnd::~CNewClientWnd()
{
}

BEGIN_MESSAGE_MAP(CNewClientWnd, CWnd)
	//{{AFX_MSG_MAP(CNewClientWnd)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNewClientWnd message handlers

BOOL CNewClientWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	// 1 - Create a memory DC and select our bitmap into it
	CDC dcMem;
	dcMem.CreateCompatibleDC( pDC );
	CBitmap* pOldBitmap = dcMem.SelectObject( &m_bitmap );

	// 2 - Retrieve the size of our bitmap...
	BITMAP bmp;
	m_bitmap.GetObject( sizeof( bmp ), &bmp );

	// 3 - ... and the size of our window's client area
	CRect rect;
	GetClientRect( &rect );

	// 4 - Fill the window's client area with our bitmap
	pDC->StretchBlt(	rect.left, rect.top,
						rect.Width(), rect.Height(),
						&dcMem,
						0, 0, bmp.bmWidth, bmp.bmHeight,
						SRCCOPY );

	dcMem.SelectObject( pOldBitmap );
	
	return TRUE;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CNewClientWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	Invalidate( TRUE );
	// TODO: Add your message handler code here
	
}
