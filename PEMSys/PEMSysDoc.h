// PEMSysDoc.h :  CPEMSysDoc ��Ľӿ�
//


#pragma once

class CPEMSysDoc : public CDocument
{
protected: // �������л�����
	DECLARE_DYNCREATE(CPEMSysDoc)

// ����
public:

// ����
public:
	CPEMSysDoc();

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPEMSysDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


