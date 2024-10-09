#pragma once
#include "afxdialogex.h"
#include "CUnitControl.h"
#include "CUnitControlBase.h"

// ConfigurationDlg ダイアログ

class ConfigurationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigurationDlg)

public:
	ConfigurationDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~ConfigurationDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIGURATION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	CUnitControlBase mUnitBase;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
