
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
