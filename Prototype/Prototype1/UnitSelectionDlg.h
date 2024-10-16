#pragma once
#include "afxdialogex.h"


// UnitSelectionDlg ダイアログ

class UnitSelectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UnitSelectionDlg)

public:
	UnitSelectionDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~UnitSelectionDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITSELECTION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listunit;
	virtual BOOL OnInitDialog();
};
