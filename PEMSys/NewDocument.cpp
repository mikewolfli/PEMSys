// NewDocument.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "NewDocument.h"


// CNewDocument

IMPLEMENT_DYNCREATE(CNewDocument, CDocument)

CNewDocument::CNewDocument()
{
}

BOOL CNewDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CNewDocument::~CNewDocument()
{
}


BEGIN_MESSAGE_MAP(CNewDocument, CDocument)
END_MESSAGE_MAP()


// CNewDocument 诊断

#ifdef _DEBUG
void CNewDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void CNewDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CNewDocument 序列化

void CNewDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CNewDocument 命令
