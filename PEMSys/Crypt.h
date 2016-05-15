// Crypt.h: interface for the CCrypt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_)
#define AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCrypt  
{
public:
	CCrypt();
	virtual ~CCrypt();
public:
	static CString Encrypt(CString S, DWORD Key); // 加密函数
	static CString Decrypt(CString S, DWORD Key); // 解密函数
};

class CRegister
{
public:
	CRegister();
	virtual ~CRegister();
public:
    DWORD GetKey(CString user);
    CString CodeProving(CString user,CString seCode);
	CString CodeMade(CString user);
	void GetLimit(CString sCode);
private:
	CString gCode;
};

#endif // !defined(AFX_CRYPT_H__FEB16981_A853_11D6_8649_0088CC174723__INCLUDED_)
