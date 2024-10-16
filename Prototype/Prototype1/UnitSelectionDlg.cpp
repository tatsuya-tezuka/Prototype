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

}

UnitSelectionDlg::~UnitSelectionDlg()
{
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



	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
