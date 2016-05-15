// PConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEMSys.h"
#include "PConfigDlg.h"


// CPConfigDlg 对话框

IMPLEMENT_DYNAMIC(CPConfigDlg, CDialog)
CPConfigDlg::CPConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPConfigDlg::IDD, pParent)
{
}

CPConfigDlg::~CPConfigDlg()
{
}

void CPConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPConfigDlg, CDialog)
END_MESSAGE_MAP()


// CPConfigDlg 消息处理程序
