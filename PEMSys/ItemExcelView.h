#pragma once
#include "afxwin.h"
#include "./ExcelType/excel9.h"
#include <map>
using namespace std;


// CItemExcelView 窗体视图
typedef pair<CString, CString> Str_Pair;

typedef struct _MarkID {
	int istr;  //行数
    CString sstr;
} MarkIDStr;

typedef struct _DoorMaterial{
	CString strDoorMaterial;
	int iNum;
} DoorMaterial;

typedef struct _JambMaterial{
	CString strJambMaterial;
	int iNum;
} JambMaterial;

class CItemExcelView : public CFormView
{
	DECLARE_DYNCREATE(CItemExcelView)

//protected:
public:
	CItemExcelView();           // 动态创建所使用的受保护的构造函数
	virtual ~CItemExcelView();

public:
	enum { IDD = IDD_DIALOG_ITEM_EXCEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	CButton m_cSearch;
	CButton m_cCancel;
	afx_msg void OnBnClickedButtonExcelOutput();
	afx_msg void OnBnClickedButtonExcelOpen();
	afx_msg void OnBnClickedButtonExcelOpen2();
	afx_msg void OnBnClickedButtonExcelFilepath();
	CString m_sTemplatePath;
	CString m_sObjectPath;
	map<CString,CString> m_eData;
	map<CString,CString>::const_iterator m_pIter;
	_variant_t strSQL;
	_variant_t Holder;
private:
	_RecordsetPtr m_pTempSet;
public:
	CComboBox m_cMarkID;
	CListBox m_cOrderList;
	CString m_sProjectName;
	CString m_sElevatorModel;
	CString m_sRatedLoad;
	CString m_sRatedSpeed;
	CString m_sMarkID;
	BOOL InitOrderList(const CString str);
	CString GetMarkID(CString str);
	void ClearEdit(void);
	afx_msg void OnCbnSelendokComboExcelMarkid();
	void RefreshEdit(_RecordsetPtr& pSet);
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonExcelCancel();
	afx_msg void
	OnBnClickedButtonExcelSearch();
	BOOL InsertMapData(void);
	BOOL ExcelOutput(void);

	Workbooks myBooks; 
	_Workbook myBook; 
	Worksheets mysheets; 
	_Worksheet mysheet; 
	Range myRange; 
	_Application ExcelApp;
	afx_msg void OnBnClickedCheckExcelOpen();
	BOOL m_bCheck;
	void WriteTEMRL(void);
	//CString GetMarkIDSimp(void);
	BOOL m_bCopy;
	int m_iNum;
	DoorMaterial m_ddDoorMaterial[2];
	JambMaterial m_ddJambMaterial[2];
	int m_iWideJamb;
	void WriteTEE(void);
	void WriteTEES(void);
	void WriteTEGL(void);
	void WriteTEGLS(void);
	void WriteTEMRLS(void);
	void WriteTEGLM(void);
	void WriteTEF(void);
};


