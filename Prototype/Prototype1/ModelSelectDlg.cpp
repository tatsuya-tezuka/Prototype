﻿// ModelSelectDlg.cpp : 実装ファイル
//
/******************************************************************************
* @file    ModelSelectDlg.cpp
* @brief   ModelSelectDlgクラス
* @auther  SCC
* @date    2024/10/03 新規作成
* @par
******************************************************************************/

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "ModelSelectDlg.h"
#include "ConfigurationDlg.h"


//------------------------------------------------------------------------------------------
//	概要：アプリケーション機種選択画面
//        画面左部ツリーコントロールに機種一覧構造体より機種カテゴリーを表示する
//        画面右部リストコントロールにカテゴリーごとの機種一覧を表示する
//------------------------------------------------------------------------------------------

IMPLEMENT_DYNAMIC(ModelSelectDlg, CDialogEx)

ModelSelectDlg::ModelSelectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODELSELECT_DIALOG, pParent)
{
	m_ImageHeight = 0;
	m_ImageWidth = 0;
}

ModelSelectDlg::~ModelSelectDlg()
{
}

void ModelSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_MODELCATEGORY, m_treeModelCategory);
	DDX_Control(pDX, IDC_LIST_MODEL, m_listModel);
	DDX_Control(pDX, IDC_STARTSELECTION, m_btnStartSelection);
}


BEGIN_MESSAGE_MAP(ModelSelectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_STARTSELECTION, &ModelSelectDlg::OnClickedStartselection)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MODELCATEGORY, &ModelSelectDlg::OnSelchangedTreeModelcategory)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MODEL, &ModelSelectDlg::OnItemchangedListModel)
END_MESSAGE_MAP()


// ModelSelectDlg メッセージ ハンドラー

/*============================================================================*/
/*! 機種選択画面

-# 初期化

@param  なし

@retval なし
*/
/*============================================================================*/
BOOL ModelSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください

	// 機器カテゴリー設定
	CString stcategory = _T("");
	for (int i = 0; i < theApp.sModelDataList.size(); i++)
	{
		if (stcategory != theApp.sModelDataList.at(i).category)
		{
			// アイテムの追加
			stcategory = theApp.sModelDataList.at(i).category;
			HTREEITEM hItemPnt1 = m_treeModelCategory.InsertItem(stcategory);
		}
	}

	// ビットマップをイメージリストに設定
	HBITMAP hBmp = NULL;
	BITMAP Bmp;

	m_bmpNoimage.LoadBitmap(IDB_BITMAP_NOIMAGE);
	m_bmpNoimage.GetBitmap(&Bmp);
	m_imageList.Create(Bmp.bmWidth, Bmp.bmHeight, ILC_COLOR24, 0, 1);
	m_imageList.SetImageCount(2);

	hBmp = (HBITMAP)m_bmpNoimage;

	CBitmap* pBmp = NULL;
	pBmp = new CBitmap();
	pBmp->Attach(hBmp);

	// イメージリストの再設定
	m_imageList.Replace(eDisableModel, pBmp, NULL);

	// メモリリーク予防
	delete pBmp;


	m_bmpimage.LoadBitmap(IDB_BITMAP_IMAGE);
	m_bmpimage.GetBitmap(&Bmp);
	
	hBmp = (HBITMAP)m_bmpimage;

	pBmp = new CBitmap();
	pBmp->Attach(hBmp);

	// イメージリストの再設定
	m_imageList.Replace(eEnableModel, pBmp, NULL);

	// メモリリーク予防
	delete pBmp;	


	// 機種リストにイメージを登録する
	m_listModel.SetImageList(&m_imageList, LVSIL_SMALL);


	////// 機種データの取得
	////mEqDataList.clear();
	////for (int i = 0; i < sizeof(mEqDataLIst) / sizeof(mEqDataLIst[0]); i++) {
	////	mEqDataList.push_back(mEqDataLIst[i]);
	////}

	//// リソースビットマップのサイズ取得
	//HBITMAP hBmp = NULL;
	//Gdiplus::Bitmap* pThumbnail = Gdiplus::Bitmap::FromResource((HINSTANCE)theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_NOIMAGE));
	//pThumbnail->GetHBITMAP(NULL, &hBmp);
	//// サイズ取得
	//BITMAP bm;
	//::ZeroMemory(&bm, sizeof(BITMAP));
	//if (::GetObject(hBmp, sizeof(BITMAP), &bm) != 0) {
	//	m_ImageWidth = bm.bmWidth;
	//	m_ImageHeight = bm.bmHeight;
	//}
	//DeleteObject(hBmp);
	//delete pThumbnail;

	//// 機種用のイメージリストの作成（一先ず２個とする）
	//m_imageList.Create(m_ImageWidth, m_ImageHeight, ILC_COLOR24, 0, 1);
	//m_imageList.SetImageCount(2);

	//CBitmap* pImage = NULL;
	//// ★機種イメージなしのビットマップを登録
	//pThumbnail = Gdiplus::Bitmap::FromResource((HINSTANCE)theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_NOIMAGE));
	//// ビットマップオブジェクトにアタッチする
	//pThumbnail->GetHBITMAP(NULL, &hBmp);
	//// ビットマップイメージの作成
	//pImage = new CBitmap();
	//pImage->Attach(hBmp);
	//// イメージリストの再設定
	//m_imageList.Replace(0, pImage, NULL);
	//delete pImage;
	//delete pThumbnail;
	//// ★機種I/O Sliceのビットマップを登録
	//pThumbnail = Gdiplus::Bitmap::FromResource((HINSTANCE)theApp.m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_NOIMAGE));
	//// ビットマップオブジェクトにアタッチする
	//pThumbnail->GetHBITMAP(NULL, &hBmp);
	//// ビットマップイメージの作成
	//pImage = new CBitmap();
	//pImage->Attach(hBmp);
	//// イメージリストの再設定
	//m_imageList.Replace(1, pImage, NULL);
	//delete pImage;
	//delete pThumbnail;

	//// 機種リストにイメージを登録する
	//m_listModel.SetImageList(&m_imageList, LVSIL_SMALL);

	////// リスト作成
	////vector<mModelData>::iterator itr;
	////int item = 0;
	////for (itr = theApp.mModelDataList.begin(); itr != theApp.mModelDataList.end(); itr++) {
	////	AddItem(item, 0, (*itr).modelname, 0, (*itr).bflg);
	////	item++;
	////}



	//// NoImage画像設定
	//// imageList設定
	//m_imageList.Create(90, 91, ILC_COLOR16 /* | ILC_MASK*/, 0, 1);
	//CBitmap bm;
	//bm.LoadBitmap(IDB_BITMAP_NOIMAGE);
	//m_imageList.Add(&bm, RGB(0, 0, 0));
	//// リストコントロール設定
	//// 拡張スタイルの適用
	//m_listModel.SetExtendedStyle(m_listModel.GetExtendedStyle() |
	//	// 行単位で選択する
	//	LVS_EX_FULLROWSELECT
	//);
	//m_listModel.SetImageList(&m_imageList, LVSIL_SMALL);

	//LVITEM lvItem;
	//lvItem.iItem = 0;
	//lvItem.iImage = 0;    // image index that refers to your image list
	//lvItem.pszText = L"Item 1";
	//lvItem.mask = LVIF_TEXT;

	//m_listModel.InsertItem(&lvItem);

	// 「選定を開始する」ボタン非活性
	m_btnStartSelection.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

/*============================================================================*/
/*! 「選定を開始する」ボタン押下時イベント

-# 構成画面を表示する

@param	なし

@retval なし
*/
/*============================================================================*/
void ModelSelectDlg::OnClickedStartselection()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	// 機種選択情報を選択情報構造体に格納
	int idx = -1;
	while ((idx = m_listModel.GetNextItem(idx, LVNI_SELECTED)) != -1)
	{
		TCHAR seltext[256];
		m_listModel.GetItemText(idx, 0, seltext, 256);
		m_selModel = seltext;
	}

	theApp.sSelectinfo.model.set(m_selCategory, m_selModel, 1);

	ConfigurationDlg ConfDlg;
	ConfDlg.DoModal();
}

/*============================================================================*/
/*! 機種選択

-# 機種リストに登録

@param	nItem		アイテム番号（０～）
@param	nSubItem	サブアイテム番号（０～）
@param	strItem		アイテム文字列
@param	dwParam		３２ビットデータ
@param	nSubItem	イメージリストの番号

@retval
*/
/*============================================================================*/
int ModelSelectDlg::AddItem(int nItem, int nSubItem, CString strItem, LPARAM dwParam/* = 0*/, int nImage/* = -1*/)
{
	LV_ITEM lv;
	memset(&lv, 0, sizeof(lv));
	lv.mask = LVIF_TEXT;
	lv.iItem = nItem;
	lv.iSubItem = nSubItem;
	if (nSubItem == 0) {
		lv.mask |= LVIF_PARAM;
		lv.lParam = dwParam;
	}
	if (nImage >= 0) {
		lv.mask |= LVIF_IMAGE;
		lv.iImage = nImage;
	}
	lv.pszText = (LPTSTR)(LPCTSTR)strItem;
	lv.cchTextMax = strItem.GetLength();

	if (nSubItem == 0)
		return m_listModel.InsertItem(&lv);
	return m_listModel.SetItem(&lv);
}

/*============================================================================*/
/*! 機種カテゴリー押下時イベント

-# 選択されたカテゴリーごとに機種リストに表示する機種を変更する

@param	なし

@retval なし
*/
/*============================================================================*/
void ModelSelectDlg::OnSelchangedTreeModelcategory(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	// 「選定を開始する」ボタン非活性
	m_btnStartSelection.EnableWindow(FALSE);

	//カテゴリー取得
	HTREEITEM hItem = m_treeModelCategory.GetSelectedItem();
	if (hItem == nullptr) return;

	m_selCategory = m_treeModelCategory.GetItemText(hItem);

	m_listModel.DeleteAllItems();

	// リスト作成
	vector<sModelData>::iterator itr;
	int item = 0;
	for (itr = theApp.sModelDataList.begin(); itr != theApp.sModelDataList.end(); itr++) {

		if (m_selCategory == (*itr).category) {
			AddItem(item, 0, (*itr).modelname, 0, (*itr).bflg);
			item++;
		}
	}

	*pResult = 0;
}

/*============================================================================*/
/*! 機種選択時イベント

-# 「選定を開始する」ボタンを有効化

@param  なし

@retval なし
*/
/*============================================================================*/
void ModelSelectDlg::OnItemchangedListModel(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// 「選定を開始する」ボタン活性化
	m_btnStartSelection.EnableWindow(TRUE);

	*pResult = 0;
}
