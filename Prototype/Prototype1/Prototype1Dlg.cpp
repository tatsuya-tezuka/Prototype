﻿

/******************************************************************************
* @file    Prototype1Dlg.cpp
* @brief   Prototype1Dlgクラス
* @auther  SCC
* @date    2024/10/03 新規作成
* @par
******************************************************************************/

#include "pch.h"
#include "framework.h"
#include "Prototype1.h"
#include "Prototype1Dlg.h"
#include "afxdialogex.h"
#include "ModelSelectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


//------------------------------------------------------------------------------------------
//	概要：アプリケーショントップ画面
//        「機種から選定」「CSVから選定」「サンプル構成から選定」ボタン押下時の各処理を記述
//------------------------------------------------------------------------------------------


CPrototype1Dlg::CPrototype1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROTOTYPE1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrototype1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BTN_SELECT_CSV, m_btnSelectCsv);
	DDX_Control(pDX, IDC_BTN_SELECT_DUM, m_btnSelectDum);
}

BEGIN_MESSAGE_MAP(CPrototype1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SELECT_DUM, &CPrototype1Dlg::OnClickedBtnSelectDum)
	ON_BN_CLICKED(IDC_BTN_SELECT_CSV, &CPrototype1Dlg::OnClickedBtnSelectCsv)
	ON_BN_CLICKED(IDC_BTN_SELECT, &CPrototype1Dlg::OnClickedBtnSelect)
END_MESSAGE_MAP()


// CPrototype1Dlg メッセージ ハンドラー

/*============================================================================*/
/*! トップ画面

-# 初期化

@param  なし

@retval なし
*/
/*============================================================================*/
BOOL CPrototype1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	if ( (!theApp.SetmModelDatafromCSV()) || (!theApp.SetmUnitDatafromCSV()))
	{
		MessageBox(_T("CSVファイルが不正です。\nファイル内容を確認してください。"), _T("エラー"), MB_OK | MB_ICONERROR);
	};

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CPrototype1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CPrototype1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CPrototype1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*============================================================================*/
/*! トップ画面

-# 機種選択画面を表示する

@param  なし			

@retval	なし
*/
/*============================================================================*/
void CPrototype1Dlg::OnClickedBtnSelect()
{
	ModelSelectDlg mdlselDlg;
	mdlselDlg.DoModal();
}

/*============================================================================*/
/*! トップ画面

-# 選択されたCSVファイルより情報を取得し、構成画面を表示する

@param	なし

@retval なし
*/
/*============================================================================*/
void CPrototype1Dlg::OnClickedBtnSelectCsv()
{	
	//CSVファイル選択ダイアログ
	CFileDialog csvfileDlg(true, _T("csv"), nullptr, OFN_FILEMUSTEXIST, _T("CSVファイル(*.csv)|*.csv|| "));

	if (csvfileDlg.DoModal() == IDOK)
	{
		// フルパス取得
		CString fullPathName = csvfileDlg.GetPathName();
	}
}

/*============================================================================*/
/*! トップ画面

-# メッセージの表示

@param	なし

@retval なし
*/
/*============================================================================*/
void CPrototype1Dlg::OnClickedBtnSelectDum()
{
	MessageBox(_T("「サンプル構成から選定」は未対応です。"), _T("警告"), MB_OK | MB_ICONWARNING);
}
