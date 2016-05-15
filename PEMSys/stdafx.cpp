// stdafx.cpp : 只包括标准包含文件的源文件
// PEMSys.pch 将是预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include <string>


CFrameWnd* EkCreateNewWindow( CDocTemplate* pTemplate,
							 CDocument* pDocument )
{
	ASSERT_VALID( pTemplate );
	ASSERT_VALID( pDocument );

	// 1 - Create the new frame window
	// (will in turn create the associated view)
	CFrameWnd* pFrame = pTemplate->CreateNewFrame(
		pDocument, NULL );

	if( pFrame == NULL )
	{
		// Window creation failed
		TRACE0( "Warning: failed to create new frame.\n" );
		return NULL;
	}
	ASSERT_KINDOF( CFrameWnd, pFrame );

	// 2 - Tell the frame to update itself
	// (and its child windows)
	pTemplate->InitialUpdateFrame( pFrame, pDocument );

	// 3 - Return a pointer to the new frame window object
	return pFrame;
}

CDocument* EkGetActiveDocument()
{
	// 1 - Get a pointer to the application's
	// main frame window
	CWnd* pWnd = AfxGetMainWnd();
	if( pWnd == NULL )
		return NULL;

	// 2 - Make sure the pointer is valid and more
	// strongly typed
	ASSERT_VALID( pWnd );
	ASSERT_KINDOF( CFrameWnd, pWnd );
	CFrameWnd* pMainFrame = static_cast< CFrameWnd* >( pWnd );

	// 3 - Get a pointer to the active frame window
	// (may be 'this' for SDI application)
	CFrameWnd* pActiveFrame = pMainFrame->GetActiveFrame();
	if( pActiveFrame == NULL )
		return NULL;

	// 4 - Return a pointer to the active document object
	return pActiveFrame->GetActiveDocument();
}


