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

protected:
	CString	m_selUnitname;
	sUnitData m_cfgUnitInfo;
	sUnitData m_selUnitInfo;
	CFont	mListFont;
	CFont	mHeaderFont;
	CButton m_btnOk;
private:
	UINT m_cfgUnitType;
	int m_unitRemaining;		// ユニット選択可能残
	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	void SetUnitInfo(UINT type, sUnitData unit) { m_cfgUnitType = type, m_cfgUnitInfo = unit; }
protected:

	/* ------------------------------------------------------------------------------------ */


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CUnitListCtrl m_listunit;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedButtonOk();
	
	afx_msg void OnItemchangedListUnitselection(NMHDR* pNMHDR, LRESULT* pResult);
};
