#if !defined(AFX_ALPHACTRL_H__FB39898D_676D_4BD2_B576_542ABCA68021__INCLUDED_)
#define AFX_ALPHACTRL_H__FB39898D_676D_4BD2_B576_542ABCA68021__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlphaCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAlphaCtrl window

class CAlphaCtrl : public CStatic
{
// Construction
public:
	CAlphaCtrl();

// Attributes
public:

// Operations
public:
	BOOL bCanPaint;
	UINT nBmpID;
	int nTimer;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlphaCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL LoadAlphaBitmap(UINT uID, int iTimer);
	CBitmap Bmp;
	void AlphaDisplay(CDC& pDC, CClientDC& dc, BLENDFUNCTION& rBlendProps, int width, int heigh, byte nLevel);
	virtual ~CAlphaCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAlphaCtrl)
	afx_msg void OnPaint();
	//}}AFX_MSG
 
	DECLARE_MESSAGE_MAP()
protected:
	
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALPHACTRL_H__FB39898D_676D_4BD2_B576_542ABCA68021__INCLUDED_)
