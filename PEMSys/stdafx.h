// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 标头中排除不常使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。
#ifndef WINVER				// 允许使用 Windows 95 和 Windows NT 4 或更高版本的特定功能。
#define WINVER 0x0400		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_WINNT		// 允许使用 Windows NT 4 或更高版本的特定功能。
#define _WIN32_WINNT 0x0400		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用 Windows 98 或更高版本的特定功能。
#define _WIN32_WINDOWS 0x0410 //为 Windows Me 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_IE			// 允许使用 IE 4.0 或更高版本的特定功能。
#define _WIN32_IE 0x0400	//为 IE 5.0 及更新版本改变为适当的值。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常被安全忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxdisp.h>        // MFC 自动化类
#include <math.h>

#import "C:\program files\common files\System\ado\msado15.dll" no_namespace \
	rename("EOF","EndOfFile") \
	rename("LockTypeEnum","newLockTypeEnum")\
	rename("DataTypeEnum","newDataTypeEnum")\
	rename("FieldAttributeEnum","newFieldAttributeEnum")\
	rename("EditModeEnum","newEditModeEnum")\
	rename("RecordStatusEnum","newRecordStatusEnum")\
	rename("ParameterDirectionEnum","newParameterDirectionEnum")

#include <afxdtctl.h>		// Internet Explorer 4 公共控件的 MFC 支持
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows 公共控件的 MFC 支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>


#include <afxsock.h>		// MFC 套接字扩展
#include <afxdhtml.h>
#include "PEMSysHeader.h"
#include "NewDocument.h"
#include <windows.h>
#include <afxdlgs.h>


///定义全局函数，用来打开特定的文档模板视图
CFrameWnd* EkCreateNewWindow( CDocTemplate* pTemplate,
							 CDocument* pDocument );

// 定义函数用来获取当前文档
CDocument* EkGetActiveDocument();

// 定义全局枚举变量，用来记录当前登录的用户类型
enum User_Type 
{
	UnLogin = 0,
	Limit_User =1,
	Common_User = 2,
	Manager = 3,
	Adm_All = 4,
	Superman = 5,
};
extern User_Type g_tUserType;

/////////////////////////////////////////////////////////

// 定义一个函数，用来创建一个窗口（若不存在）或打开一个窗口（若存在）

template<class T>
void EkNewOrOpenWnd(CDocTemplate* pTemplate, CDocument* pDocument, 
					CFrameWnd* pFrame, T* pFindView, CString strClassName)
{
	//pFindView = NULL; //所要找的视图的指针
	/*if(pFindView != NULL)
	{
	if(!(pFindView->IsKindOf( RUNTIME_CLASS(CView) )))
	{
	AfxMessageBox("第四个参数必须为视图类或者其派生类对象！", NULL, MB_OK);
	return;
	}
	}*/
	if(pFindView != NULL)
	{
		pFindView = NULL;
	}

	CView* pView=NULL ;

	pFrame = static_cast<CFrameWnd *>(AfxGetMainWnd())->GetActiveFrame();

	pDocument = pFrame->GetActiveDocument();

	if(pDocument != NULL)
	{
		POSITION pos = pDocument->GetFirstViewPosition();
		while(pos != NULL)
		{
			pView= pDocument->GetNextView(pos);
			//if (pView->IsKindOf( RUNTIME_CLASS(T)))  
			if(pView != NULL)
			{
				if( pView->GetRuntimeClass()->m_lpszClassName 
					== strClassName) 
					//pFindView->GetRuntimeClass()->m_lpszClassName)
					//if( typeid(pView) == typeid(pFindView))
				{
					pFindView = (T*)pView;
				}
				//else
				//{
				//	pFindView = NULL;
				//}
			}
		}
		if(pFindView == NULL)
		{
			//pDocument->SetTitle(strTitle);
			EkCreateNewWindow( pTemplate, pDocument );
		}
		else
		{
			pFindView->GetParentFrame()->ActivateFrame();
		}
	}

	if (pDocument == NULL)
	{
		pDocument = new CNewDocument();

		//pDocument->SetTitle(strTitle);
		EkCreateNewWindow( pTemplate, pDocument );		
	}
	//pFrame->  //SetWindowsText(strTitle);
	//pFrame->GetActiveWindow()->SetWindowText(strTitle);
}
