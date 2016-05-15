// PEMSys.h : PEMSys 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h” 
#endif

#include "resource.h"       // 主符号
#include "atlcomtime.h"
#include "RegisterDlg.h"
#include "Crypt.h"


// CPEMSysApp:
// 有关此类的实现，请参阅 PEMSys.cpp
//

class CPEMSysApp : public CWinApp
{
public:
	CPEMSysApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	COleTemplateServer m_server;
		// 用于文档创建的服务器对象
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	CMultiDocTemplate *m_pPEMSysTemplate;
	CMultiDocTemplate *m_pItemViewTemplate;
	CMultiDocTemplate *m_pItemDataInputTemplate;
	CMultiDocTemplate *m_pItemExcelTemplate;
	CMultiDocTemplate *m_pItemOrderConfigTemplate;
	CMultiDocTemplate *m_pItemCommerceSearchTemplate;
	CMultiDocTemplate *m_pItemInExortViewTempleate;
	_ConnectionPtr m_pConnect;
	_ConnectionPtr m_pSearchConn;
public:
	bool ADOExecute(_RecordsetPtr & ADOSet,_ConnectionPtr& pConn, _variant_t & strSQL);
	BOOL InitDataBaseConnect(void);
	CString m_strDataFile;
	CString m_strPassword;
private:
	BOOL lRet;
public:
	// 返回记录集记录数量
//	long TheGetRecordCount(_RecordsetPtr &m_pSet);
	HRESULT get_Empty(_RecordsetPtr& ADOSet, VARIANT_BOOL* bEmpty);
	COleDateTime m_dCurrent;
	int GetRecordCountEx(_RecordsetPtr& pSet);
	CRegister m_Register;
};

extern CPEMSysApp theApp;
extern CString g_strUserID;
extern CString g_strUserName;
extern CString g_strUserPsw;
extern User_Type g_tUserType;
extern CString g_strUserDepartment;
extern CString g_strAuthor;