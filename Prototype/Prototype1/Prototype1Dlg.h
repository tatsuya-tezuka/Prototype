
#pragma once

/*
	◆CPrototype1Dlgヘッダーファイル
	・アプリケーションクラス：CPrototype1Dlg
	・実装ファイル：CPrototype1Dlg.cpp
	・クラス内には「定義」「メンバ変数」「メンバ関数」のコメントを記述する
*/

class CPrototype1Dlg : public CDialogEx
{
	/* ------------------------------------------------------------------------------------ */
	/* コンストラクション                                                                   */
	/* ------------------------------------------------------------------------------------ */
public:
	CPrototype1Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROTOTYPE1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート



// 実装
	/* ------------------------------------------------------------------------------------ */
	/* メンバ変数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	CButton m_btnSelect;
	CButton m_btnSelectCsv;
	CButton m_btnSelectDum;

protected:
	HICON m_hIcon;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	afx_msg void OnClickedBtnSelectDum();
	afx_msg void OnClickedBtnSelectCsv();
	afx_msg void OnClickedBtnSelect();

protected:
	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
