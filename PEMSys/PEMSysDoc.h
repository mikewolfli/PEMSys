// PEMSysDoc.h :  CPEMSysDoc 类的接口
//


#pragma once

class CPEMSysDoc : public CDocument
{
protected: // 仅从序列化创建
	DECLARE_DYNCREATE(CPEMSysDoc)

// 属性
public:

// 操作
public:
	CPEMSysDoc();

// 重写
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CPEMSysDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

	// 生成的 OLE 调度映射函数

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


