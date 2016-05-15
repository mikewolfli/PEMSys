#ifndef _MYBAR_H_
#define _MYBAR_H_


class CMyBar : public CPinDockBar
{
// Construction
public:
	CMyBar();

// Attributes
public:
//	CXTOutBarCtrl  m_wndOutlookBar;
	CGfxOutBarCtrl wndBar;
	
	// Operations
	void AddToDrawBar(CAutoHideBar * pDrawBar);
	void RemoveFromDrawBar(CAutoHideBar * pDrawBar);
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBar)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) ;
	DECLARE_MESSAGE_MAP()

	void InitializeOutlookBar() ;

	CImageList	   imaLarge;
	CImageList	   imaSmall;
	BOOL           m_bFloate ;
	HWND           m_hParentWnd ;
};


#endif