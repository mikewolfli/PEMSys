#if !defined(AFX_NEWCLIENTWND_H__9188EE15_BA74_4BE5_AC2F_441EF4342F68__INCLUDED_)
#define AFX_NEWCLIENTWND_H__9188EE15_BA74_4BE5_AC2F_441EF4342F68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewClientWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewClientWnd window

class CNewClientWnd : public CWnd
{
// Construction
public:
	CNewClientWnd();

// Attributes
public:

// Operations
public:

private:
	CBitmap m_bitmap;  // ¶¨ÒåÎ»Í¼¾ä±ú

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewClientWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNewClientWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNewClientWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCLIENTWND_H__9188EE15_BA74_4BE5_AC2F_441EF4342F68__INCLUDED_)
