
// ConfigurationDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "ConfigurationDlg.h"


// ConfigurationDlg ダイアログ

IMPLEMENT_DYNAMIC(ConfigurationDlg, CDialogEx)

ConfigurationDlg::ConfigurationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONFIGURATION_DIALOG, pParent)
{

}

ConfigurationDlg::~ConfigurationDlg()
{
}

void ConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ConfigurationDlg, CDialogEx)
END_MESSAGE_MAP()


// ConfigurationDlg メッセージ ハンドラー

/*============================================================================*/
/*! 構成画面

-# 初期化

@param  なし

@retval なし
*/
/*============================================================================*/
BOOL ConfigurationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください

	// ★ユニットベースの作成
	// 各種別のビットマップリソースを登録
	mUnitBase.SetUnitImage(CUnitControlBase::UnitBracket, IDB_BITMAP_BRACKET);
	mUnitBase.SetUnitImage(CUnitControlBase::UnitEmpty, IDB_BITMAP_ADDUNIT);
	mUnitBase.SetUnitImage(CUnitControlBase::UnitSingle, IDB_BITMAP_UNIT1);
	mUnitBase.SetUnitImage(CUnitControlBase::UnitDouble, IDB_BITMAP_UNIT2);
	// ユニットベースの作成
	mUnitBase.CreateUnitBase(theApp.m_hInstance, this);
	// ★ユニットベースの作成

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
