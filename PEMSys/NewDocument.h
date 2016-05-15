#pragma once


// CNewDocument 文档

class CNewDocument : public CDocument
{
	DECLARE_DYNCREATE(CNewDocument)

public:
	CNewDocument();
	virtual ~CNewDocument();
	virtual void Serialize(CArchive& ar);   // 为文档 I/O 重写
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

	DECLARE_MESSAGE_MAP()
};
