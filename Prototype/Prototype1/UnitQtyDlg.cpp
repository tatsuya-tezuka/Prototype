// UnitQtyDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "UnitQtyDlg.h"


// UnitQtyDlg ダイアログ

IMPLEMENT_DYNAMIC(UnitQtyDlg, CDialogEx)

UnitQtyDlg::UnitQtyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UNITQTY, pParent)
{

}

UnitQtyDlg::~UnitQtyDlg()
{
}

void UnitQtyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(UnitQtyDlg, CDialogEx)
END_MESSAGE_MAP()


// UnitQtyDlg メッセージ ハンドラー
