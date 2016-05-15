#pragma once


// CNewDocument �ĵ�

class CNewDocument : public CDocument
{
	DECLARE_DYNCREATE(CNewDocument)

public:
	CNewDocument();
	virtual ~CNewDocument();
	virtual void Serialize(CArchive& ar);   // Ϊ�ĵ� I/O ��д
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
