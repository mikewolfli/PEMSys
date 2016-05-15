// PEMSysDoc.cpp :  CPEMSysDoc 类的实现
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

// 注意: 我们添加了对 IID_IPEMSys 的支持以
//  支持 VBA 中的类型安全绑定。此 IID 必须与附加在 .IDL 文件中的 
//  调度接口的 GUID 相匹配。

// {82CAAED5-C8C5-446E-B4C4-571A05A15303}
static const IID IID_IPEMSys =
{ 0x82CAAED5, 0xC8C5, 0x446E, { 0xB4, 0xC4, 0x57, 0x1A, 0x5, 0xA1, 0x53, 0x3 } };

BEGIN_INTERFACE_MAP(CPEMSysDoc, CDocument)
	INTERFACE_PART(CPEMSysDoc, IID_IPEMSys, Dispatch)
END_INTERFACE_MAP()


// CPEMSysDoc 构造/析构

CPEMSysDoc::CPEMSysDoc()
{
	// TODO: 在此添加一次性构造代码

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

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CPEMSysDoc 序列化

void CPEMSysDoc::Serialize(CArchive& ar)
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


// CPEMSysDoc 诊断

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


// CPEMSysDoc 命令
