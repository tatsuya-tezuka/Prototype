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
}


BEGIN_MESSAGE_MAP(UnitSelectionDlg, CDialogEx)
END_MESSAGE_MAP()


// UnitSelectionDlg メッセージ ハンドラー
