
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
	
	pfont->GetLogFont(&m_lfs);
	pfont->GetLogFont(&m_lfm);
	pfont->GetLogFont(&m_lfl);
	
	// ユニット選択数フォント設定
	m_lfs.lfHeight = -11;
	m_lfs.lfWeight = 400;
	m_fnts.CreateFontIndirect(&m_lfs);
	SetUnitNum(m_fnts);
	//m_stcUnitNum.SetWindowText(_T("0"));
	//m_stcUnitNum.SetFont(&m_fnts);

	// ユニットリストフォント設定
	m_lfm.lfHeight = -13;
	m_lfm.lfWeight = 450;
	m_fntm.CreateFontIndirect(&m_lfm);
	SetUnitList(m_fntm);

	// 機種名フォント設定
	m_lfl.lfHeight = -20;
	m_lfl.lfWeight = 800;
	m_fntl.CreateFontIndirect(&m_lfl);
	m_stcModelName.SetWindowText(theApp.sSelectinfo.model.modelname);
	m_stcModelName.SetFont(&m_fntl);

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

	theApp.mSelectUnitId = nID;

	// ユニット選択画面を表示
	UnitSelectionDlg unitseldlg;
	if(unitseldlg.DoModal() != IDOK) return;

	// 選択ユニット数の更新
	SetUnitNum(m_fnts);
	/*CString unitnum;
	unitnum.Format(_T("%d"), theApp.sSelectinfo.unitselecttotal);
	m_stcUnitNum.SetWindowText(unitnum);*/

	for (int i = nID - mUnitStartCommand; i < theApp.sSelectinfo.unitselecttotal; i++)
	{
		UINT selectUnitType = mUnitBase.GetUnitType(nID);

		mUnitBase.UpdateUnit(nID, theApp.sSelectinfo.sSelectedUnitInfo[i].unit.usage);
		if (selectUnitType == CUnitControlBase::UnitEmpty) {
			// 新たに空ユニットを登録する
			mUnitBase.AddUnit(nID + 1);
		}
		nID++;
	}
	// 選択ユニットリストの更新
	SetUnitList(m_fntm);

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
/*! 構成画面

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


LRESULT ConfigurationDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == mMessage_UnitDelete) {
		// ユニットの削除
		mUnitBase.DeleteUnit((UINT)wParam);
		//theApp.sSelectinfo.unitselecttotal -= 1;
		theApp.sSelectinfo.clearUnit((UINT)wParam - mUnitStartCommand);
		if (theApp.sSelectinfo.unitselecttotal == mUnitMax - 1)
		{
			// 新たに空ユニットを登録する
			mUnitBase.AddUnit(mUnitStartCommand + mUnitMax);
		}

		// 選択ユニット数の更新
		SetUnitNum(m_fnts);
		/*CString unitnum;
		unitnum.Format(_T("%d"), theApp.sSelectinfo.unitselecttotal);
		m_stcUnitNum.SetWindowText(unitnum);*/

		// 選択ユニットリストの更新
		SetUnitList(m_fntm);

		return TRUE;
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}

/*============================================================================*/
/*! 構成画面

-# ユニットリスト設定関数

@param

@retval
*/
/*============================================================================*/
void ConfigurationDlg::SetUnitList(CFont &font)
{
	// ユーザ選択情報構造体からユニット情報を取得
	CString strunit = _T("");
	for (int i = 0; i < mUnitMax; i++)
	{
		strunit += theApp.sSelectinfo.sSelectedUnitInfo[i].unit.unitname;
		strunit += _T("\r\n\r\n");
	}
	m_editUnitList.SetWindowText(strunit);
	m_editUnitList.SetFont(&font);
}

/*============================================================================*/
/*! 構成画面

-# ユニット数設定関数

@param

@retval
*/
/*============================================================================*/
void ConfigurationDlg::SetUnitNum(CFont& font)
{
	CString unitnum;
	unitnum.Format(_T("%d"), theApp.sSelectinfo.unitselecttotal);
	m_stcUnitNum.SetWindowText(unitnum);
	m_stcUnitNum.SetFont(&font);
}