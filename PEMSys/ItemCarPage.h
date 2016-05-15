#pragma once


// CItemCarPage �Ի���

class CItemCarPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemCarPage)

public:
	CItemCarPage();
	virtual ~CItemCarPage();

// �Ի�������
	enum { IDD = IDD_PAGE_ITEM_CAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_iCD;
	int m_iCW;
	int m_iCH;
	CString m_sOpenType;
	CString m_sOffsetDir;
	int m_iOffset;
	int m_iDW;
	int m_iDH;
	CString m_sHostControlPanel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	void ClearEdit(void);
	void UpdateDataPage(BOOL bCheck);
	virtual BOOL OnSetActive();
	BOOL m_bCheck;
};
