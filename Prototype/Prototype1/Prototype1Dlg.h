
// Prototype1Dlg.h : ヘッダー ファイル
//

#pragma once


// CPrototype1Dlg ダイアログ
class CPrototype1Dlg : public CDialogEx
{
// コンストラクション
public:
	CPrototype1Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROTOTYPE1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_btnSelect;
	CButton m_btnSelectCsv;
	CButton m_btnSelectDum;
	afx_msg void OnClickedBtnSelectDum();
	afx_msg void OnClickedBtnSelectCsv();
	afx_msg void OnClickedBtnSelect();
};
