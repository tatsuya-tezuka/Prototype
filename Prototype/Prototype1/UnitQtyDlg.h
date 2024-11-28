#pragma once
#include "afxdialogex.h"
#include "UnitSelectionDlg.h"

/*
	◆UnitQtyDlgヘッダーファイル
	・アプリケーションクラス：UnitQtyDlg
	・実装ファイル：UnitQtyDlg.cpp
	・クラス内には「定義」「メンバ変数」「メンバ関数」のコメントを記述する
*/

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
protected:
	CComboBox m_cmbUnitQty;
private:
	sUnitData* m_unitdata;
	int m_unitRemaining;		// ユニット選択可能残
	CBrush	m_brsHead;			// ヘッダーの背景用ブラシ
	CBrush	m_brsUnitName;		// ユニット名の背景用ブラシ

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	void GetUnitData(sUnitData data, int remain) 
	{
		m_unitdata = &data; 
		m_unitRemaining = remain;
	}
protected:

	/* ------------------------------------------------------------------------------------ */

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
