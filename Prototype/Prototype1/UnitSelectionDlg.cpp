// UnitSelectionDlg.cpp : 実装ファイル
//

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
}


BEGIN_MESSAGE_MAP(UnitSelectionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &UnitSelectionDlg::OnClickedButtonOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_UNITSELECTION, &UnitSelectionDlg::OnItemchangedListUnitselection)
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

	// TODO: ここに初期化を追加してください
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

	// 列を設定する
	for (int i = 0; i < mUnitlistHeader.size(); i++) 
	{
		// ヘッダー
		m_listunit.InsertColumn(i, mUnitlistHeader[i], LVCFMT_LEFT, mUnitlistHeaderSize[i]);
	}

	for (int i = 0; i < theApp.sUnitDataList.size(); i++)
	{
		//if (theApp.sUnitDataList.at(i).usage <= (mUnitMax - theApp.sSelectinfo.unitselecttotal))
		//{
			CString strusage;
			strusage.Format(_T("%dユニット"), theApp.sUnitDataList.at(i).usage);
			// 行の挿入
			m_listunit.InsertItem(i, theApp.sUnitDataList.at(i).unitname);
			m_listunit.SetItemText(i, 1, theApp.sUnitDataList.at(i).type);
			m_listunit.SetItemText(i, 2, theApp.sUnitDataList.at(i).spec);
			m_listunit.SetItemText(i, 3, strusage);
		//}
		//else if (m_selUnitType == (UINT)UnitSingle && 
		//	theApp.sUnitDataList.at(i).usage <= (UINT)UnitSingle - 1)
		//{
		//	CString strusage;
		//	strusage.Format(_T("%dユニット"), theApp.sUnitDataList.at(i).usage);
		//	// 行の挿入
		//	m_listunit.InsertItem(i, theApp.sUnitDataList.at(i).unitname);
		//	m_listunit.SetItemText(i, 1, theApp.sUnitDataList.at(i).type);
		//	m_listunit.SetItemText(i, 2, theApp.sUnitDataList.at(i).spec);
		//	m_listunit.SetItemText(i, 3, strusage);
		//}
		//else if (m_selUnitType == (UINT)UnitDouble &&
		//	theApp.sUnitDataList.at(i).usage <= (UINT)UnitDouble - 1)
		//{
		//	CString strusage;
		//	strusage.Format(_T("%dユニット"), theApp.sUnitDataList.at(i).usage);
		//	// 行の挿入
		//	m_listunit.InsertItem(i, theApp.sUnitDataList.at(i).unitname);
		//	m_listunit.SetItemText(i, 1, theApp.sUnitDataList.at(i).type);
		//	m_listunit.SetItemText(i, 2, theApp.sUnitDataList.at(i).spec);
		//	m_listunit.SetItemText(i, 3, strusage);
		//}
	}

	//for (int i = 0; i < theApp.sUnitDataList.size(); i++)
	//{
	//	CString strusage;
	//	strusage.Format(_T("%dユニット"), theApp.sUnitDataList.at(i).usage);
	//	// 行の挿入
	//	m_listunit.InsertItem(i, theApp.sUnitDataList.at(i).unitname);
	//	m_listunit.SetItemText(i, 1, theApp.sUnitDataList.at(i).type);
	//	m_listunit.SetItemText(i, 2, theApp.sUnitDataList.at(i).spec);
	//	m_listunit.SetItemText(i, 3, strusage);
	//}

	// 列数を取得して列幅を自動設定をする
	//for (int i = 0; i < m_listunit.GetHeaderCtrl()->GetItemCount(); i++)
	//{
	//	m_listunit.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	//}

	// ユニット選択可能残の取得
	m_unitRemaining = mUnitMax;
	int unitusagetotal = 0;
	for (int i = 0; i < theApp.sSelectinfo.unitselecttotal; i++)
	{
		unitusagetotal += theApp.sSelectinfo.sSelectedUnitInfo[i].unit.usage;
	}
	m_unitRemaining -= unitusagetotal;
	if (!(m_selUnitType == (UINT)UnitEmpty))
	{
		m_unitRemaining -= m_selUnitType - 1;
	}
	
	// 「OK」ボタン非活性
	m_btnOk.EnableWindow(FALSE);

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
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

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
			//unitqtydlg.SetUnitSelData(*itr);
			//theApp.sSelectinfo.sSelectedUnitInfo[theApp.sSelectinfo.unitselecttotal].unit = (*itr);
			//theApp.sSelectinfo.unitselecttotal += 1;
		}
	}

	// 選択ユニットの占有数チェック


	// 選択情報の格納準備
	unitqtydlg.SetUnitSelData(m_selUnitInfo);

	// メッセージ情報がある場合は表示

	///UnitQtyDlg unitqtydlg;
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
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	m_btnOk.EnableWindow(TRUE);

	*pResult = 0;


}
