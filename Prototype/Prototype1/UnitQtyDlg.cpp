// UnitQtyDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "UnitQtyDlg.h"


// UnitQtyDlg ダイアログ

IMPLEMENT_DYNAMIC(UnitQtyDlg, CDialogEx)

UnitQtyDlg::UnitQtyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNITQTY_DIALOG, pParent)
{

}

UnitQtyDlg::~UnitQtyDlg()
{
}

void UnitQtyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_QTY, m_cmbUnitQty);
}


BEGIN_MESSAGE_MAP(UnitQtyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &UnitQtyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// UnitQtyDlg メッセージ ハンドラー


BOOL UnitQtyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	for (int i = 0; i < mUnitMax; i++)
	{
		// 初期値設定
		CString qty;
		qty.Format(_T("%d"), i+1);
		m_cmbUnitQty.AddString(qty);

		// 先頭項目を選択状態にする
		m_cmbUnitQty.SetCurSel(0);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void UnitQtyDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int idx = m_cmbUnitQty.GetCurSel() + 1;

	// 選択情報を構造体に格納
	for (int i = 0; i < idx; i++) 
	{
		int num = theApp.sSelectinfo.unitselecttotal;
		theApp.sSelectinfo.sSelectedUnitInfo[num].unit = *m_unitdata;
		theApp.sSelectinfo.unitselecttotal += 1;
	}

	CDialogEx::OnOK();

	
}
