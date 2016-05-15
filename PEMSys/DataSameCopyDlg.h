#pragma once
#include "afxwin.h"
#include "atlcomtime.h"
#include "afxcmn.h"


// CDataSameCopyDlg 对话框

class CDataSameCopyDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataSameCopyDlg)

public:
	CDataSameCopyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataSameCopyDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SAMECOPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sResource;
	CComboBox m_cTarget;
	CListBox m_cTargetList;
	int m_iCheck;
	virtual BOOL OnInitDialog();
protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	_variant_t strSQL;
	_variant_t Holder;
private:
	_RecordsetPtr m_pTempSet;
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonRemove();
	BOOL m_bSaveCopy;
	COleDateTime m_dCurrent;

	_variant_t m_dDeliveryReceivedDate;
	_variant_t m_dADeliveryDate;
	_variant_t m_sADeliveryRemark;
	_variant_t m_dASecDeliveryDate;
	_variant_t m_sASecDeliveryRemark;
	_variant_t m_bBatchDelivery;
	_variant_t m_dAThirdDeliveryDate;
	_variant_t m_sAThirdDeliveryRemark; 
	_variant_t m_bDeliveryDone;
	_variant_t m_iCurrency;

	_variant_t m_dGADReceived;
	_variant_t m_dLatestAmend;
	_variant_t m_dCSRelease;
	_variant_t m_dCSReply;
	_variant_t m_dACompleteDate;
	_variant_t m_sAmendRemark;
	_variant_t m_sReplyRemark;

	_variant_t m_dbDiscount;
	_variant_t m_dbInternalPrice;
	_variant_t m_dbAGetFreightInsurance;
	_variant_t m_dPORelease;
	_variant_t m_dPOReturn;

	_variant_t m_dbAmount;
	_variant_t m_dbFreightInsurance;
	_variant_t m_dbMaterialAmount;

	_variant_t m_dProductionReceivedDate;
	_variant_t m_dPlantProductionDate;
	_variant_t m_dPDeliveryDate;
	_variant_t m_sPDeliveryRemark;
	_variant_t m_bPBatchCheck;
	_variant_t m_dPSecDeliveryDate;
	_variant_t m_sPSecDeliveryRemark;
	_variant_t m_dPThirdDeliveryDate;
	_variant_t m_sPThirdDeliveryRemark;

	_variant_t m_sRemarks;

	_variant_t m_sElevatorType;
	_variant_t m_sElevatorModel;

	_variant_t m_iRatedLoad;
	_variant_t m_fRatedSpeed;
	_variant_t m_sControlMode;
	_variant_t m_sDragMode;
	_variant_t m_sControlModeRemark;
	_variant_t m_iFloor;
	_variant_t m_iStop;
	_variant_t m_iDoor;
	_variant_t m_sStopName;
	_variant_t m_bThrough;

	_variant_t m_iCD;
	_variant_t m_iCW;
	_variant_t m_iCH;
	_variant_t m_sOpenType;
	_variant_t m_sOffsetDir;
	_variant_t m_iOffset;
	_variant_t m_iDW;
	_variant_t m_iDH;
	_variant_t m_sHostControlPanel;

	_variant_t m_sController;
	_variant_t m_bDisaPanel;
	_variant_t m_bVideoCable;
	_variant_t m_sCallBoardType;
	_variant_t m_sScreenMagic;
	_variant_t m_sPushButton;
	_variant_t m_sInvertorType;
	_variant_t m_sInvertorPower;
	_variant_t m_sCallboardtypeRemark;
	_variant_t m_sScreenMagicRemark;

	_variant_t m_sTraction;
	_variant_t m_sCarRail;
	_variant_t m_sEncode;
	_variant_t m_sCWRail;
	_variant_t m_sDoorSystem;
	_variant_t m_sSafety;
	_variant_t m_sSpeedGovernor;
	_variant_t m_sBuffer;
	_variant_t m_bNonstandardCheck;
	_variant_t m_sNonstandardRemark;

	_variant_t m_iSW;
	_variant_t m_iSD;
	_variant_t m_lTH;
	_variant_t m_lOH;
	_variant_t m_iPD;
	_variant_t m_sCounterWeight;
	_variant_t m_iCounterWeightHeight;
	_variant_t m_bWideJamb;
	_variant_t m_iCWGauge;
	_variant_t m_iJambXC;
	_variant_t m_sSGPosition;
	_variant_t m_sWJType;
	_variant_t m_iCCW;
	_variant_t m_iCS1;
	_variant_t m_iCS2;
	_variant_t m_iCWS;

	_variant_t m_sCeiling;
	_variant_t m_sFrontWall;
	_variant_t m_sSideWall;
	_variant_t m_sRearWall;
	_variant_t m_bHandRail;
	_variant_t m_bGlassPosition;
	_variant_t m_sSideHandRail;
	_variant_t m_sRearHandRail;
	_variant_t m_sGlassType;
	_variant_t m_sGlassPosition;
	_variant_t m_sDoor;
	_variant_t m_sFloor;

	_variant_t m_sRemark;
	_variant_t m_iFloorDoor1;
	_variant_t m_iFloorDoor2;
	_variant_t m_sFloorDoor1;
	_variant_t m_sFloorDoor2;

	void ReadRecord(_RecordsetPtr& pSet);
	void UpdateRecord(_RecordsetPtr& pSet);
	BOOL m_bSave;
	CString m_sOrderID;
	CListCtrl m_cTargetResouce;
	afx_msg void OnBnClickedButtonRemoveall();
	afx_msg void OnBnClickedButtonAddall();
	CString m_sProjectName;
	CString m_sProjectNameEn;
	afx_msg void OnBnClickedButtonFind();
	void LoadTargetResource(_RecordsetPtr& pSet);
	afx_msg void OnCbnSelendokCombo1();
	CString m_sID;
	_variant_t m_dConfigureFinish;
	_variant_t m_dPurchaseReturn;
	_variant_t m_bConfigureFinishCheck;
	_variant_t m_bPurchaseReturnCheck;
	int m_iPage;
};
