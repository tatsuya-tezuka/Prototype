#pragma once
#include "afxdialogex.h"
#include "CUnitListCtrl.h"

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

	/* ------------------------------------------------------------------------------------ */
	/* 定義                                                                                 */
	/* ------------------------------------------------------------------------------------ */
public:
protected:

	/* ------------------------------------------------------------------------------------ */
	/* メンバ変数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	CString	m_selUnitname;
	sUnitData m_selUnitInfo;
protected:
	CFont	mListFont;
	CFont	mHeaderFont;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:

protected:

	/* ------------------------------------------------------------------------------------ */


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CUnitListCtrl m_listunit;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedButtonOk();
};
