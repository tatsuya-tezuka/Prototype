// ModelSelectDlg.cpp : 実装ファイル
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
	ON_BN_CLICKED(IDCANCEL, &ModelSelectDlg::OnBnClickedCancel)
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

	// 機器カテゴリー設定
	HTREEITEM hSelectItem = NULL;
	CString stcategory = _T("");
	for (int i = 0; i < theApp.sModelDataList.size(); i++)
	{
		if (stcategory != theApp.sModelDataList.at(i).category)
		{
			// アイテムの追加
			stcategory = theApp.sModelDataList.at(i).category;
			HTREEITEM hItemPnt1 = m_treeModelCategory.InsertItem(stcategory);
			if (hSelectItem == NULL)
				hSelectItem = hItemPnt1;
		}
	}
	// 選択状態の設定
	if (hSelectItem != NULL) {
		m_treeModelCategory.SelectItem(hSelectItem);
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

	// 「選定を開始する」ボタン非活性
	m_btnStartSelection.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

/*============================================================================*/
/*! 機種選択画面

-# 構成画面を表示する

@param	なし

@retval なし
*/
/*============================================================================*/
void ModelSelectDlg::OnClickedStartselection()
{
	// 機種選択情報を選択情報構造体に格納
	theApp.sSelectinfo.model.setUnit(m_SelModelData);

	if (theApp.sSelectinfo.model.bflg == eEnable)
	{
		ConfigurationDlg ConfDlg;
		ConfDlg.DoModal();
	}
	else if (theApp.sSelectinfo.model.bflg == eDisable)
	{
		MessageBox(theApp.sSelectinfo.model.modelname + _T("は未対応です。"), _T("エラー"), MB_OK | MB_ICONERROR);
		return;
	}
}

/*============================================================================*/
/*! 機種選択画面

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
/*! 機種選択画面

-# 選択されたカテゴリーごとに機種リストに表示する機種を変更する

@param	なし

@retval なし
*/
/*============================================================================*/
void ModelSelectDlg::OnSelchangedTreeModelcategory(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	//カテゴリー取得
	HTREEITEM hItem = m_treeModelCategory.GetSelectedItem();
	if (hItem == nullptr) return;

	m_SelModelData.category = m_treeModelCategory.GetItemText(hItem);

	m_listModel.DeleteAllItems();

	// リスト作成
	vector<sModelData>::iterator itr;
	int item = 0;
	for (itr = theApp.sModelDataList.begin(); itr != theApp.sModelDataList.end(); itr++) {

		if (m_SelModelData.category == (*itr).category) {
			AddItem(item, 0, (*itr).modelname, 0, (*itr).bflg);
			item++;
		}
	}

	*pResult = 0;
}

/*============================================================================*/
/*! 機種選択画面

-# 「選定を開始する」ボタンを有効化、選択情報保持

@param  なし

@retval なし
*/
/*============================================================================*/
void ModelSelectDlg::OnItemchangedListModel(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// 「選定を開始する」ボタン活性
	m_btnStartSelection.EnableWindow(TRUE);

	// 機種選択情報を取得
	int idx = -1;
	while ((idx = m_listModel.GetNextItem(idx, LVNI_SELECTED)) != -1)
	{
		TCHAR seltext[256];
		m_listModel.GetItemText(idx, 0, seltext, 256);
		m_SelModelData.modelname = seltext;
	}

	theApp.GetsModelData();

	for (auto itr = theApp.sModelDataList.begin(); itr != theApp.sModelDataList.end(); ++itr)
	{
		if (itr->modelname == m_SelModelData.modelname)
		{
			m_SelModelData.bflg = itr->bflg;
			break;
		}
	}

	*pResult = 0;
}

/*============================================================================*/
/*! 機種選択画面

-# 選択情報をクリア

@param  なし

@retval なし
*/
/*============================================================================*/
void ModelSelectDlg::OnBnClickedCancel()
{
	theApp.sSelectinfo.clear();

	CDialogEx::OnCancel();
}
