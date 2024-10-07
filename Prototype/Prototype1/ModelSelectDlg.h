#pragma once
#include "afxdialogex.h"


// ModelSelectDlg ダイアログ

class ModelSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ModelSelectDlg)

public:
	ModelSelectDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~ModelSelectDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODELSELECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	int		AddItem(int nItem, int nSubItem, CString strItem, LPARAM dwParam = 0, int nImage = -1);

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl	m_treeModelCategory;
	CListCtrl	m_listModel;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedStartselection();
	CImageList	m_imageList;		// NoImage画像表示用
	UINT		m_ImageWidth;
	UINT		m_ImageHeight;
	CBitmap		m_bmpNoimage;
	afx_msg void OnSelchangedTreeModelcategory(NMHDR* pNMHDR, LRESULT* pResult);
};
