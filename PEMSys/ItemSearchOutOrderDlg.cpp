// ItemSearchOutOrderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEMSys.h"
#include "ItemSearchOutOrderDlg.h"
#include ".\itemsearchoutorderdlg.h"


// CItemSearchOutOrderDlg �Ի���

IMPLEMENT_DYNAMIC(CItemSearchOutOrderDlg, CDialog)
CItemSearchOutOrderDlg::CItemSearchOutOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CItemSearchOutOrderDlg::IDD, pParent)
{
}

CItemSearchOutOrderDlg::~CItemSearchOutOrderDlg()
{
}

void CItemSearchOutOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DISPLAY, m_cList);
}


BEGIN_MESSAGE_MAP(CItemSearchOutOrderDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnBnClickedButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_BOTTOM, OnBnClickedButtonBottom)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CItemSearchOutOrderDlg ��Ϣ�������

void CItemSearchOutOrderDlg::MoveUpOrDown(BOOL bCheck)
{
	int iCount,iIndex, iOffset;

	//iCountѡ�м�¼������, iIndex ListBox�ؼ����¼����,iOffset�ƶ�����



	CArray<int,int> aryListBoxSel;//������ȡѡ�м�¼��ListBox�е�λ��(�б��ڼ���)

	/* CArray <Type, argType> �Cģ����,

	Type ָ��ϣ���ռ��Ķ�������

	argType ָ�������Ĳ�������

	*/

	CString str;



	if(bCheck)

	{

		iOffset = -1;//����һ��

	}

	else

	{

		iOffset = 1;//����һ��

	}

	iCount = m_cList.GetSelCount();//�õ�ѡ�еļ�¼����

	iIndex = m_cList.GetCount();//�õ��ؼ��ڵļ�¼����

	if(iCount==0 || iIndex==0)
		return;

	aryListBoxSel.SetSize(iCount);//���������С

	m_cList.GetSelItems(iCount,aryListBoxSel.GetData());

	//��ѡ�м�¼��λ����Ϣ�������黺����

	//ѭ���ƶ�ѡ�еļ�¼,

	for(int i =0; i<iCount ;i++)

	{

		if(bCheck&& aryListBoxSel[i]== 0 || !bCheck &&aryListBoxSel[i]==iIndex-1)

			continue;//����¼λ��������λ��ʱ,�����˼�¼

		m_cList.GetText(aryListBoxSel[i],str);//����Ӧλ�õļ�¼ȡ��

		m_cList.DeleteString(aryListBoxSel[i]);//ɾ���˼�¼

		m_cList.InsertString(aryListBoxSel[i]+iOffset,str);//���ϻ����²����¼

		m_cList.SetSel(aryListBoxSel[i]+iOffset,TRUE);//ѡ�в���ļ�¼

	} 
}

void CItemSearchOutOrderDlg::OnBnClickedButtonFirst()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
    MoveUporDownEnd(TRUE);
	UpdateData(FALSE);
}

void CItemSearchOutOrderDlg::OnBnClickedButtonUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
    MoveUpOrDown(TRUE);
	UpdateData(FALSE);
}

void CItemSearchOutOrderDlg::OnBnClickedButtonDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	MoveUpOrDown(FALSE);
	UpdateData(FALSE);
}

void CItemSearchOutOrderDlg::OnBnClickedButtonBottom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
    MoveUporDownEnd(FALSE);
	UpdateData(FALSE);
}

void CItemSearchOutOrderDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CItemSearchOutOrderDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CItemSearchOutOrderDlg::MoveUporDownEnd(BOOL bDir)
{
	int iCount,iIndex, iOffset;

	//iCountѡ�м�¼������, iIndex ListBox�ؼ����¼����,iOffset�ƶ�����



	CArray<int,int> aryListBoxSel;//������ȡѡ�м�¼��ListBox�е�λ��(�б��ڼ���)

	/* CArray <Type, argType> �Cģ����,

	Type ָ��ϣ���ռ��Ķ�������

	argType ָ�������Ĳ�������

	*/

	CString str;



	if(bDir)

	{

		iOffset = -1;//����һ��

	}

	else

	{

		iOffset = 1;//����һ��

	}

	iCount = m_cList.GetSelCount();//�õ�ѡ�еļ�¼����

	iIndex = m_cList.GetCount();//�õ��ؼ��ڵļ�¼����
	
	if(iCount==0 || iIndex==0)
		return;

	aryListBoxSel.SetSize(iCount);//���������С

	m_cList.GetSelItems(iCount,aryListBoxSel.GetData());

	//��ѡ�м�¼��λ����Ϣ�������黺����

	//ѭ���ƶ�ѡ�еļ�¼,

	for(int i =0; i<iCount ;i++)

	{

		while((bDir&& aryListBoxSel[i]!= 0) || (!bDir &&aryListBoxSel[i]!=iIndex-1))
		{
		m_cList.GetText(aryListBoxSel[i],str);//����Ӧλ�õļ�¼ȡ��

		m_cList.DeleteString(aryListBoxSel[i]);//ɾ���˼�¼

		m_cList.InsertString(aryListBoxSel[i]+iOffset,str);//���ϻ����²����¼

		m_cList.SetSel(aryListBoxSel[i]+iOffset,TRUE);//ѡ�в���ļ�¼
		}
	}
}

BOOL CItemSearchOutOrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
