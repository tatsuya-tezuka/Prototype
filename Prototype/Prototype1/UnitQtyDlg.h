﻿#pragma once
#include "afxdialogex.h"
#include "UnitSelectionDlg.h"

// UnitQtyDlg ダイアログ

class UnitQtyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UnitQtyDlg)

public:
	UnitQtyDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~UnitQtyDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITQTY_DIALOG };
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
	CComboBox m_cmbUnitQty;
protected:
private:
	sUnitData* m_unitdata;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	void SetUnitSelData(sUnitData data) { m_unitdata = &data; }
protected:

	/* ------------------------------------------------------------------------------------ */

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};