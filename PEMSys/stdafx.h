// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// ��Ŀ�ض��İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ��ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ�� Windows 95 �� Windows NT 4 ����߰汾���ض����ܡ�
#define WINVER 0x0400		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_WINNT		// ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
#define _WIN32_WINNT 0x0400		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ�� Windows 98 ����߰汾���ض����ܡ�
#define _WIN32_WINDOWS 0x0410 //Ϊ Windows Me �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_IE			// ����ʹ�� IE 4.0 ����߰汾���ض����ܡ�
#define _WIN32_IE 0x0400	//Ϊ IE 5.0 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ��������������ȫ���Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����
#include <math.h>

#import "C:\program files\common files\System\ado\msado15.dll" no_namespace \
	rename("EOF","EndOfFile") \
	rename("LockTypeEnum","newLockTypeEnum")\
	rename("DataTypeEnum","newDataTypeEnum")\
	rename("FieldAttributeEnum","newFieldAttributeEnum")\
	rename("EditModeEnum","newEditModeEnum")\
	rename("RecordStatusEnum","newRecordStatusEnum")\
	rename("ParameterDirectionEnum","newParameterDirectionEnum")

#include <afxdtctl.h>		// Internet Explorer 4 �����ؼ��� MFC ֧��
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows �����ؼ��� MFC ֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.h>


#include <afxsock.h>		// MFC �׽�����չ
#include <afxdhtml.h>
#include "PEMSysHeader.h"
#include "NewDocument.h"
#include <windows.h>
#include <afxdlgs.h>


///����ȫ�ֺ������������ض����ĵ�ģ����ͼ
CFrameWnd* EkCreateNewWindow( CDocTemplate* pTemplate,
							 CDocument* pDocument );

// ���庯��������ȡ��ǰ�ĵ�
CDocument* EkGetActiveDocument();

// ����ȫ��ö�ٱ�����������¼��ǰ��¼���û�����
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

// ����һ����������������һ�����ڣ��������ڣ����һ�����ڣ������ڣ�

template<class T>
void EkNewOrOpenWnd(CDocTemplate* pTemplate, CDocument* pDocument, 
					CFrameWnd* pFrame, T* pFindView, CString strClassName)
{
	//pFindView = NULL; //��Ҫ�ҵ���ͼ��ָ��
	/*if(pFindView != NULL)
	{
	if(!(pFindView->IsKindOf( RUNTIME_CLASS(CView) )))
	{
	AfxMessageBox("���ĸ���������Ϊ��ͼ����������������", NULL, MB_OK);
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
