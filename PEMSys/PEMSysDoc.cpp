// PEMSysDoc.cpp :  CPEMSysDoc ���ʵ��
//

#include "stdafx.h"
#include "PEMSys.h"

#include "PEMSysDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPEMSysDoc

IMPLEMENT_DYNCREATE(CPEMSysDoc, CDocument)

BEGIN_MESSAGE_MAP(CPEMSysDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CPEMSysDoc, CDocument)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IPEMSys ��֧����
//  ֧�� VBA �е����Ͱ�ȫ�󶨡��� IID �����븽���� .IDL �ļ��е� 
//  ���Ƚӿڵ� GUID ��ƥ�䡣

// {82CAAED5-C8C5-446E-B4C4-571A05A15303}
static const IID IID_IPEMSys =
{ 0x82CAAED5, 0xC8C5, 0x446E, { 0xB4, 0xC4, 0x57, 0x1A, 0x5, 0xA1, 0x53, 0x3 } };

BEGIN_INTERFACE_MAP(CPEMSysDoc, CDocument)
	INTERFACE_PART(CPEMSysDoc, IID_IPEMSys, Dispatch)
END_INTERFACE_MAP()


// CPEMSysDoc ����/����

CPEMSysDoc::CPEMSysDoc()
{
	// TODO: �ڴ����һ���Թ������

	EnableAutomation();

	AfxOleLockApp();
}

CPEMSysDoc::~CPEMSysDoc()
{
	AfxOleUnlockApp();
}

BOOL CPEMSysDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPEMSysDoc ���л�

void CPEMSysDoc::Serialize(CArchive& ar)
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


// CPEMSysDoc ���

#ifdef _DEBUG
void CPEMSysDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPEMSysDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPEMSysDoc ����
