// UnitSelectionDlg.cpp : 実装ファイル
//
/******************************************************************************
* @file    UnitSelectionDlg.cpp
* @brief   UnitSelectionDlgクラス
* @auther  SCC
* @date    2024/10/04 新規作成
* @par
******************************************************************************/

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "UnitSelectionDlg.h"
#include "UnitQtyDlg.h"


// UnitSelectionDlg ダイアログ

IMPLEMENT_DYNAMIC(UnitSelectionDlg, CDialogEx)

UnitSelectionDlg::UnitSelectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNITSELECTION_DIALOG, pParent)
{
	mListFont.CreateStockObject(DEFAULT_GUI_FONT);
	LOGFONT lf;
	if (mListFont.GetLogFont(&lf)) {
		lf.lfHeight = -(LONG)(mMaxLine * 12);
		mListFont.DeleteObject();
		mListFont.CreateFontIndirect(&lf);
	}
	mHeaderFont.CreateStockObject(DEFAULT_GUI_FONT);
	if (mListFont.GetLogFont(&lf)) {
		lf.lfHeight = -12;
		mHeaderFont.DeleteObject();
		mHeaderFont.CreateFontIndirect(&lf);
	}
}

UnitSelectionDlg::~UnitSelectionDlg()
{
	mListFont.DeleteObject();
	mHeaderFont.DeleteObject();
}

void UnitSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UNITSELECTION, m_listunit);
	DDX_Control(pDX, IDC_BUTTON_OK, m_btnOk);
	DDX_Control(pDX, IDC_TREE_UNITCATEGORY, m_treeUnitCategory);
}


BEGIN_MESSAGE_MAP(UnitSelectionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &UnitSelectionDlg::OnClickedButtonOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_UNITSELECTION, &UnitSelectionDlg::OnItemchangedListUnitselection)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_UNITCATEGORY, &UnitSelectionDlg::OnSelchangedTreeUnitcategory)
END_MESSAGE_MAP()


// UnitSelectionDlg メッセージ ハンドラー


/*============================================================================*/
/*! ユニット選択画面

-# 初期化

@param

@retval
*/
/*============================================================================*/
BOOL UnitSelectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ユニットカテゴリー取得・設定
	vector<sUnitData>::iterator itr;
	for (itr = theApp.sUnitDataList.begin(); itr != theApp.sUnitDataList.end(); itr++)
	{
		bool found = std::find(m_vecUnitCategory.begin(), m_vecUnitCategory.end(), (*itr).category) != m_vecUnitCategory.end();
		if (found == false)
			m_vecUnitCategory.push_back((*itr).category);
	}
	HTREEITEM hSelectItem = NULL;
	vector<CString>::iterator itrcat;
	for (itrcat = m_vecUnitCategory.begin(); itrcat != m_vecUnitCategory.end(); itrcat++)
	{
		HTREEITEM hItemPnt1 = m_treeUnitCategory.InsertItem(*itrcat);
		if (hSelectItem == NULL)
			hSelectItem = hItemPnt1;
		if ((*itrcat) == m_cfgUnitInfo.category)
			hSelectItem = hItemPnt1;
	}

	// ユニットリストコントロール設定
	// 拡張スタイルの適用
	m_listunit.SetExtendedStyle(m_listunit.GetExtendedStyle() |
		// 罫線の表示
		LVS_EX_GRIDLINES |
		// 行単位で選択する
		LVS_EX_FULLROWSELECT |
		// データはなくてもヘッダを表示する
		LVS_EX_HEADERINALLVIEWS
	);

	m_listunit.SetFont(&mListFont);
	m_listunit.GetHeaderCtrl()->SetFont(&mHeaderFont);

	// ヘッダーを設定する
	for (int i = 0; i < mUnitlistHeader.size(); i++) 
	{
		m_listunit.InsertColumn(i, mUnitlistHeader[i], LVCFMT_LEFT, mUnitlistHeaderSize[i]);
	}

	// ユニット選択可能残の取得
	m_unitRemaining = mUnitMax;
	int unitusagetotal = 0;
	for (int i = 0; i < theApp.sSelectinfo.unitselecttotal; i++)
	{
		unitusagetotal += theApp.sSelectinfo.sSelectedUnitInfo[i].unit.usage;
	}
	m_unitRemaining -= unitusagetotal;
	if (!(m_cfgUnitType == (UINT)UnitEmpty))
	{
		m_unitRemaining += (m_cfgUnitType - 1);
	}

	// カテゴリー選択状態の設定
	if (hSelectItem != NULL) 
		m_treeUnitCategory.SelectItem(hSelectItem);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

/*============================================================================*/
/*! ユニット選択画面

-# OKボタン押下時イベント

@param

@retval
*/
/*============================================================================*/
void UnitSelectionDlg::OnClickedButtonOk()
{
	// 選択されているアイテムのユニット名を取得
	int idx = -1;	
	TCHAR tszText[256];
	while ((idx = m_listunit.GetNextItem(idx, LVNI_SELECTED)) != -1)
	{
		m_listunit.GetItemText(idx, 0, tszText, 256);
		m_selUnitname = tszText;
	}

	UnitQtyDlg unitqtydlg;

	// 選択ユニット情報の取得
	vector<sUnitData>::iterator itr;
	for (itr = theApp.sUnitDataList.begin(); itr != theApp.sUnitDataList.end(); itr++)
	{
		if (m_selUnitname == (*itr).unitname)
		{
			m_selUnitInfo = (*itr);
		}
	}

	// 選択ユニットの占有数チェック
	if (m_selUnitInfo.usage > (UINT)m_unitRemaining)
	{
		MessageBox(_T("ユニット選択可能残を超過するため、このユニットは選択できません。"), _T("エラー"), MB_OK | MB_ICONERROR);
		return;
	}

	// 選択情報の格納準備
	unitqtydlg.GetUnitData(m_selUnitInfo, m_unitRemaining);

	// メッセージ情報がある場合は表示
	if (m_selUnitInfo.message.IsEmpty() == false)
	{
		MessageBox(m_selUnitInfo.message, m_selUnitInfo.unitname, MB_OK | MB_ICONINFORMATION);
	}

	INT_PTR ret = -1;
	ret = unitqtydlg.DoModal();

	// 数量選択画面で「OK」の場合は閉じる
	switch (ret)
	{
	case IDOK:
		this->EndDialog(IDOK);
		break;
	}
	
}

/*============================================================================*/
/*! ユニット選択画面

-# ユニットリスト選択時

@param

@retval
*/
/*============================================================================*/
void UnitSelectionDlg::OnItemchangedListUnitselection(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pNMLV->uNewState == 0)
		m_btnOk.EnableWindow(FALSE);
	else
		m_btnOk.EnableWindow(TRUE);
	
	*pResult = 0;
}

/*============================================================================*/
/*! ユニット選択画面

-# ユニットカテゴリー選択時、表示するユニット一覧を変更する

@param

@retval
*/
/*============================================================================*/
void UnitSelectionDlg::OnSelchangedTreeUnitcategory(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	//カテゴリー取得
	HTREEITEM hItem = m_treeUnitCategory.GetSelectedItem();
	if (hItem == nullptr) return;


	CString selectcategory = m_treeUnitCategory.GetItemText(hItem);

	m_listunit.DeleteAllItems();

	int selectidx = NULL;
	if (m_cfgUnitType == (UINT)UnitEmpty)
		selectidx = 0;

	// リスト作成
	int item = 0;
	vector<sUnitData>::iterator itr;
	for (itr = theApp.sUnitDataList.begin(); itr != theApp.sUnitDataList.end(); itr++) {

		if (selectcategory != (*itr).category)
			continue;

		CString strusage;
		strusage.Format(_T("%dユニット"), (*itr).usage);
		// 行の挿入
		m_listunit.InsertItem(item, (*itr).unitname);
		m_listunit.SetItemText(item, 1, (*itr).type);
		m_listunit.SetItemText(item, 2, (*itr).spec);
		m_listunit.SetItemText(item, 3, strusage);
		if (selectidx == NULL && m_cfgUnitInfo.unitname == (*itr).unitname)
				selectidx = item;
		item++;
	}

	// 選択状態の設定
	m_listunit.SetItemState(selectidx, LVIS_SELECTED, LVIS_SELECTED);

	*pResult = 0;
}
