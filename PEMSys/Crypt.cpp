// Crypt.cpp: implementation of the CCrypt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Crypt.h"
#include <Windows.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// 常量
#define C1 52845
#define C2 22719


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCrypt::CCrypt()
{

}

CCrypt::~CCrypt()
{

}

CString CCrypt::Encrypt(CString S, DWORD Key) // 加密函数
{
	CString Result,str;
	int i,j;

    S=S+"C";
	Result=S; // 初始化结果字符串
	for(i=0; i<S.GetLength(); i++) // 依次对字符串中各字符进行操作
	{
		Result.SetAt(i, S.GetAt(i)^(Key>>8)); // 将密钥移位后与字符异或
		Key = ((BYTE)Result.GetAt(i)+Key)*C1+C2; // 产生下一个密钥
	}
	S=Result; // 保存结果
	Result.Empty(); // 清除结果
	for(i=0; i<S.GetLength(); i++) // 对加密结果进行转换
	{
		j=(BYTE)S.GetAt(i); // 提取字符
		// 将字符转换为两个字母保存
		str="12"; // 设置str长度为2
		str.SetAt(0, 65+j/26);
		str.SetAt(1, 65+j%26);
		Result += str;
	}
	return Result;
}

CString CCrypt::Decrypt(CString S, DWORD Key) // 解密函数
{
	CString Result,str;
	int i,j;

	Result.Empty(); // 清楚结果
	for(i=0; i < S.GetLength()/2; i++) // 将字符串两个字母一组进行处理
	{
		j = ((BYTE)S.GetAt(2*i)-65)*26;
		j += (BYTE)S.GetAt(2*i+1)-65;
		str="1"; // 设置str长度为1
		str.SetAt(0, j);
		Result+=str; // 追加字符，还原字符串
	}
	S=Result; // 保存中间结果
	for(i=0; i<S.GetLength(); i++) // 依次对字符串中各字符进行操作
	{
		Result.SetAt(i, (BYTE)S.GetAt(i)^(Key>>8)); // 将密钥移位后与字符异或
		Key = ((BYTE)S.GetAt(i)+Key)*C1+C2; // 产生下一个密钥
	}

	int a = Result.GetLength();
	Result.Delete(a-1,1);
	return Result;
}

CRegister::CRegister()
{

}

CRegister::~CRegister()
{

}


DWORD CRegister::GetKey(CString user)
{
    DWORD wUser=NULL;
	int iIndex = user.GetLength();
	int iUser = 0;
	CString str;
	for(int i=0;i<iIndex;i++)
	{
		str = user.Mid(i,1);
		iUser +=((int)(*((LPTSTR)str.AllocSysString())));
	}

	wUser = (DWORD)iUser;

	SYSTEM_INFO info;

	DWORD SeriaNumber=NULL;

	DWORD Register=NULL; 

	GetSystemInfo(&info); //调用函数填SYSTEM_INFO结构 

	GetVolumeInformation("C:\\",NULL,NULL,&SeriaNumber,NULL,NULL,NULL,NULL);//获取C盘序列号 

	Register=SeriaNumber+info.wProcessorRevision; 

	wUser= Register^wUser;

	return wUser;
}

CString CRegister::CodeProving(CString user,CString seCode)
{
	DWORD key;
	CString sCode,rCode;
	key = GetKey(user);
	sCode = gCode;
    sCode.Remove('-');
	rCode = CCrypt::Decrypt(seCode, key);
   
    return rCode;
}

CString CRegister::CodeMade(CString user)
{
	CString strSerial,sCode;
	DWORD key;

	key = GetKey(user);

    sCode = gCode;
	sCode.Remove('-');

	strSerial = CCrypt::Encrypt(sCode, key);

	return strSerial;
}

void CRegister::GetLimit(CString sCode)
{
	gCode = sCode;
}