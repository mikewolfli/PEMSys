// NewDocument.cpp : ʵ���ļ�
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


// CNewDocument ���

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


// CNewDocument ���л�

void CNewDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CNewDocument ����
