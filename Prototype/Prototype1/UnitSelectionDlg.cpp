// UnitSelectionDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "UnitSelectionDlg.h"


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
}


BEGIN_MESSAGE_MAP(UnitSelectionDlg, CDialogEx)
END_MESSAGE_MAP()


// UnitSelectionDlg メッセージ ハンドラー


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
		CString strusage;
		strusage.Format(_T("%d"), theApp.sUnitDataList.at(i).usage);
		// 行の挿入
		m_listunit.InsertItem(i, theApp.sUnitDataList.at(i).unitname);
		m_listunit.SetItemText(i, 1, theApp.sUnitDataList.at(i).type);
		m_listunit.SetItemText(i, 2, theApp.sUnitDataList.at(i).spec);
		m_listunit.SetItemText(i, 3, strusage);
	}

	// 列数を取得して列幅を自動設定をする
	//for (int i = 0; i < m_listunit.GetHeaderCtrl()->GetItemCount(); i++)
	//{
	//	m_listunit.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	//}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
