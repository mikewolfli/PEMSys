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

// ����
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

CString CCrypt::Encrypt(CString S, DWORD Key) // ���ܺ���
{
	CString Result,str;
	int i,j;

    S=S+"C";
	Result=S; // ��ʼ������ַ���
	for(i=0; i<S.GetLength(); i++) // ���ζ��ַ����и��ַ����в���
	{
		Result.SetAt(i, S.GetAt(i)^(Key>>8)); // ����Կ��λ�����ַ����
		Key = ((BYTE)Result.GetAt(i)+Key)*C1+C2; // ������һ����Կ
	}
	S=Result; // ������
	Result.Empty(); // ������
	for(i=0; i<S.GetLength(); i++) // �Լ��ܽ������ת��
	{
		j=(BYTE)S.GetAt(i); // ��ȡ�ַ�
		// ���ַ�ת��Ϊ������ĸ����
		str="12"; // ����str����Ϊ2
		str.SetAt(0, 65+j/26);
		str.SetAt(1, 65+j%26);
		Result += str;
	}
	return Result;
}

CString CCrypt::Decrypt(CString S, DWORD Key) // ���ܺ���
{
	CString Result,str;
	int i,j;

	Result.Empty(); // ������
	for(i=0; i < S.GetLength()/2; i++) // ���ַ���������ĸһ����д���
	{
		j = ((BYTE)S.GetAt(2*i)-65)*26;
		j += (BYTE)S.GetAt(2*i+1)-65;
		str="1"; // ����str����Ϊ1
		str.SetAt(0, j);
		Result+=str; // ׷���ַ�����ԭ�ַ���
	}
	S=Result; // �����м���
	for(i=0; i<S.GetLength(); i++) // ���ζ��ַ����и��ַ����в���
	{
		Result.SetAt(i, (BYTE)S.GetAt(i)^(Key>>8)); // ����Կ��λ�����ַ����
		Key = ((BYTE)S.GetAt(i)+Key)*C1+C2; // ������һ����Կ
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

	GetSystemInfo(&info); //���ú�����SYSTEM_INFO�ṹ 

	GetVolumeInformation("C:\\",NULL,NULL,&SeriaNumber,NULL,NULL,NULL,NULL);//��ȡC�����к� 

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