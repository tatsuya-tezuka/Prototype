
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
	// 初期化
	mSaveCx = mSaveCy = 0;
}

ConfigurationDlg::~ConfigurationDlg()
{
}

void ConfigurationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_UNITBASE, mUnitBase);
}


BEGIN_MESSAGE_MAP(ConfigurationDlg, CDialogEx)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(mUnitStartCommand, mUnitStartCommand + mUnitMax, OnUnitCommand)
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

	// ユニットバースコントロールを登録してダイアログのリサイズ時に同期させる
	// WM_SIZEをオーバライドしてユニットを表示させる
	SetControlInfo(IDC_STATIC_UNITBASE, ANCHORE_LEFTTOP | RESIZE_BOTH);
	SetControlInfo(IDOK, ANCHORE_BOTTOM);
	SetControlInfo(IDCANCEL, ANCHORE_BOTTOM);

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


void ConfigurationDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType == SIZE_MINIMIZED)
		return;

	if (GetSafeHwnd() == NULL)
		return;

	if (mControl.size() == 0)
		return;

	if (mSaveCx == 0) {
		mSaveCx = cx;
		mSaveCy = cy;
		return;
	}

	int dx = cx - mSaveCx;
	int dy = cy - mSaveCy;

	CRect rect, rectClient;
	GetClientRect(rectClient);

	CWnd* pWnd;
	DWORD info;
	WORD anchore;

	vector<DWORD>::iterator itr;
	for (itr = mControl.begin(); itr != mControl.end(); itr++) {
		info = (*itr);
		pWnd = GetDlgItem(LOWORD(info));
		if (!pWnd) {
			continue;
		}

		if (!HIWORD(info))
			continue;

		anchore = HIWORD(info);
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);

		if (anchore & RESIZE_HOR)
			rect.right += dx;
		else if (anchore & ANCHORE_RIGHT)
			rect.OffsetRect(dx, 0);

		if (anchore & RESIZE_VER)
			rect.bottom += dy;
		else if (anchore & ANCHORE_BOTTOM)
			rect.OffsetRect(0, dy);

		pWnd->MoveWindow(rect);
		mUnitBase.UnitAlignment();
	}

	mSaveCx = cx;
	mSaveCy = cy;
}
/*============================================================================*/
/*! 構成画面

-# ★ユニットボタン押下イベント

@param  なし

@retval なし
*/
/*============================================================================*/
void ConfigurationDlg::OnUnitCommand(UINT nID)
{
	bool ret = mUnitBase.FindUnit(nID);

	if (ret == false) {
		// 存在しない場合は何もしない
		return;
	}

	UINT selectUnitType = mUnitBase.GetUnitType(nID);

	if (MessageBox(_T("Singleですか？"), _T(""), MB_YESNO | MB_ICONQUESTION) == IDNO) {
		if (MessageBox(_T("Doubleですか？"), _T(""), MB_YESNO | MB_ICONQUESTION) == IDNO) {
			if (MessageBox(_T("削除ですか？"), _T(""), MB_YESNO | MB_ICONQUESTION) == IDNO) {
				return;
			}
			// ユニットの削除
			mUnitBase.DeleteUnit(nID);
			return;
		}
		// ダブルユニットで更新する
		mUnitBase.UpdateUnit(nID, 2); // 実際はユニット選択画面で選定されたユニットサイズを指定する
		if (selectUnitType == CUnitControlBase::UnitEmpty) {
			// 新たに空ユニットを登録する
			mUnitBase.AddUnit(nID + 1);
		}
		return;
	}
	// シングルユニットで更新する
	mUnitBase.UpdateUnit(nID, 1); // 実際はユニット選択画面で選定されたユニットサイズを指定する
	if (selectUnitType == CUnitControlBase::UnitEmpty) {
		// 新たに空ユニットを登録する
		mUnitBase.AddUnit(nID + 1);
	}
}
