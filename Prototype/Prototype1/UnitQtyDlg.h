#pragma once
#include "afxdialogex.h"


// UnitQtyDlg ダイアログ

class UnitQtyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UnitQtyDlg)

public:
	UnitQtyDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~UnitQtyDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UNITQTY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
