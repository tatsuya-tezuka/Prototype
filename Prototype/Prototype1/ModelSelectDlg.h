#pragma once
#include "afxdialogex.h"

/*
	◆ModelSelectDlgヘッダーファイル
	・アプリケーションクラス：ModelSelectDlg
	・実装ファイル：ModelSelectDlg.cpp
	・クラス内には「定義」「メンバ変数」「メンバ関数」のコメントを記述する
*/

class ModelSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModelSelectDlg)

public:
	/* ------------------------------------------------------------------------------------ */
	/* コンストラクション                                                                   */
	/* ------------------------------------------------------------------------------------ */
	ModelSelectDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~ModelSelectDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODELSELECT_DIALOG };
#endif


	/* ------------------------------------------------------------------------------------ */
	/* メンバ変数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	CTreeCtrl	m_treeModelCategory;
	CListCtrl	m_listModel;
	CImageList	m_imageList;		// 機種画像表示用
	UINT		m_ImageWidth;
	UINT		m_ImageHeight;
	CBitmap		m_bmpNoimage;
	CBitmap		m_bmpimage;
	CString		m_selCategory;		// ユーザ選択カテゴリー
	CString		m_selModel;			// ユーザ選択機種
	CButton		m_btnStartSelection;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedStartselection();
	afx_msg void OnSelchangedTreeModelcategory(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListModel(NMHDR* pNMHDR, LRESULT* pResult);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	int		AddItem(int nItem, int nSubItem, CString strItem, LPARAM dwParam = 0, int nImage = -1);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCancel();
};
