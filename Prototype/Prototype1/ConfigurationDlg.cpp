
// ConfigurationDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "ConfigurationDlg.h"
#include "UnitSelectionDlg.h"

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
	DDX_Control(pDX, IDC_STATIC_MODELNAME, m_stcModelName);
	DDX_Control(pDX, IDC_EDIT_UNITLIST, m_editUnitList);
	DDX_Control(pDX, IDC_STATIC_UNITLABEL3, m_stcUnitNum);
}


BEGIN_MESSAGE_MAP(ConfigurationDlg, CDialogEx)
	ON_WM_SIZE()
	ON_COMMAND_RANGE(mUnitStartCommand, mUnitStartCommand + mUnitMax, OnUnitCommand)
	ON_BN_CLICKED(IDCANCEL, &ConfigurationDlg::OnBnClickedCancel)
	ON_WM_CONTEXTMENU()
//	ON_COMMAND(IDD_CONFIGURATION_DIALOG, &ConfigurationDlg::OnIddConfigurationDialog)
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

	// ログフォント情報の取得
	CFont* pfont;
	pfont = GetFont();
	LOGFONT lfl, lfm, lfs;
	pfont->GetLogFont(&lfl);
	pfont->GetLogFont(&lfm);
	pfont->GetLogFont(&lfs);

	CFont fntModelName, fntUnitList, fntUnitNum;

	// ユニット選択数フォント設定
	lfs.lfHeight = -10;
	lfs.lfWeight = 200;
	fntUnitNum.CreateFontIndirect(&lfs);
	m_stcUnitNum.SetWindowText(_T("0"));
	m_stcUnitNum.SetFont(&fntUnitNum);

	// ユニットリストフォント設定
	lfs.lfHeight = -15;
	lfs.lfWeight = 400;
	fntUnitList.CreateFontIndirect(&lfm);
	// ユーザ選択情報構造体からユニット情報を取得
	CString strunit = _T("");
	for (int i = 0; i < mUnitMax; i++) 
	{
		//theApp.sSelectinfo.sSelectedUnitInfo[i].unit.unitname = _T("ユニット");
		if (!theApp.sSelectinfo.sSelectedUnitInfo[i].unit.unitname.IsEmpty()) 
		{
			strunit += theApp.sSelectinfo.sSelectedUnitInfo[i].unit.unitname;
			strunit += _T("\r\n\r\n");
		}
	}
	m_editUnitList.SetWindowText(strunit);
	m_editUnitList.SetFont(&fntUnitList);

	// 機種名フォント設定
	lfl.lfHeight = -20;
	lfl.lfWeight = 800;
	fntModelName.CreateFontIndirect(&lfl);
	m_stcModelName.SetWindowText(theApp.sSelectinfo.model.modelname);
	m_stcModelName.SetFont(&fntModelName);

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

	int seltotalBf, seltotalAf; 
	// ユニット選択前の選択済み数を取得
	seltotalBf = theApp.sSelectinfo.unitselecttotal;

	// ユニット選択画面を表示
	UnitSelectionDlg unitseldlg;
	unitseldlg.DoModal();

	seltotalAf = theApp.sSelectinfo.unitselecttotal;

	// 選択済み数が変わっていなければ何もしない
	if (seltotalBf == seltotalAf) return;

	UINT selectUnitType = mUnitBase.GetUnitType(nID);

	// 選択ユニット数の更新
	CString unitnum;
	unitnum.Format(_T("%d"), theApp.sSelectinfo.unitselecttotal);
	m_stcUnitNum.SetWindowText(unitnum);

	for (int i = seltotalBf; i < seltotalAf; i++)
	{
		mUnitBase.UpdateUnit(nID, theApp.sSelectinfo.sSelectedUnitInfo[i].unit.usage);
		if (selectUnitType == CUnitControlBase::UnitEmpty) {
			// 新たに空ユニットを登録する
			mUnitBase.AddUnit(nID + 1);
		}
		nID++;
	}

	/*
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
	*/
}

/*============================================================================*/
/*! 戻るボタン押下時イベント

-# ユニット選択情報のクリア

@param

@retval
*/
/*============================================================================*/
void ConfigurationDlg::OnBnClickedCancel()
{
	// ユニット選択情報をクリア
	theApp.sSelectinfo.clearUnit();

	CDialogEx::OnCancel();
}


/*============================================================================*/
/*! 右クリック時イベント

-# 削除メニュー表示

@param

@retval
*/
/*============================================================================*/
void ConfigurationDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// 削除メニューの表示
	CMenu menu;
	if (menu.LoadMenu(IDR_MENU_DELETE))
	{
		CMenu* pSubMenu = menu.GetSubMenu(0);
		
		if (pSubMenu == NULL) return;
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

}


LRESULT ConfigurationDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == mMessage_UnitDelete) {
		// ユニットの削除
		mUnitBase.DeleteUnit((UINT)wParam);
		theApp.sSelectinfo.unitselecttotal -= 1;
		CString unitnum;
		unitnum.Format(_T("%d"), theApp.sSelectinfo.unitselecttotal + 1);
		m_stcUnitNum.SetWindowText(unitnum);
		return TRUE;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}
