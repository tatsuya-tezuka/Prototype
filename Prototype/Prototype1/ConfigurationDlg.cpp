
// ConfigurationDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "ConfigurationDlg.h"
#include "UnitSelectionDlg.h"
#include <fstream>


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
	DDX_Control(pDX, IDC_STATIC_UNITLABEL5, m_stcUnitSizeTotal);
}


BEGIN_MESSAGE_MAP(ConfigurationDlg, CDialogEx)
	ON_WM_SIZE()
	//ON_COMMAND_RANGE(mUnitStartCommand, mUnitStartCommand + mUnitMax, OnUnitCommand)
	ON_COMMAND_RANGE(mUnitStartCommand, mUnitStartCommand + (mUnitMax - 1), OnUnitCommand)
	ON_BN_CLICKED(IDCANCEL, &ConfigurationDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CSVEXPORT, &ConfigurationDlg::OnClickedButtonCsvexport)
	ON_WM_GETMINMAXINFO()
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

	// 各種別のビットマップリソースを登録
	mUnitBase.SetUnitImage(UnitBracket, IDB_BITMAP_BRACKET);
	mUnitBase.SetUnitImage(UnitEmpty, IDB_BITMAP_ADDUNIT);
	mUnitBase.SetUnitImage(UnitSingle, IDB_BITMAP_UNIT1);
	mUnitBase.SetUnitImage(UnitDouble, IDB_BITMAP_UNIT2);
	// ユニットベースの作成
	mUnitBase.CreateUnitBase(theApp.m_hInstance, this);

	// ログフォント情報の取得
	CFont* pfont;
	pfont = GetFont();
	
	pfont->GetLogFont(&m_lfs);
	pfont->GetLogFont(&m_lfm);
	pfont->GetLogFont(&m_lfl);
	
	// フォントサイズ設定
	m_lfs.lfHeight = -11;
	m_lfs.lfWeight = 400;
	m_lfm.lfHeight = -13;
	m_lfm.lfWeight = 450;
	m_lfl.lfHeight = -20;
	m_lfl.lfWeight = 800;

	m_fnts.CreateFontIndirect(&m_lfs);
	SetUnitNum(m_fnts);
	SetUnitSizeTotal(m_fnts);

	m_fntm.CreateFontIndirect(&m_lfm);
	SetUnitList(m_fntm);

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
	UINT selectUnitTypeBf = mUnitBase.GetUnitType(nID);
	bool ret = mUnitBase.FindUnit(nID);

	if (ret == false) {
		// 存在しない場合は何もしない
		return;
	}

	theApp.mSelectUnitId = nID;

	// ユニット選択画面を表示
	UnitSelectionDlg unitseldlg;

	unitseldlg.SetUnitType(selectUnitTypeBf);

	if(unitseldlg.DoModal() != IDOK) return;

	// 選択ユニット数、サイズ合計の更新
	SetUnitNum(m_fnts);
	SetUnitSizeTotal(m_fnts);
	// 選択ユニットリストの更新
	SetUnitList(m_fntm);

	for (int i = nID - mUnitStartCommand; i < theApp.sSelectinfo.unitselecttotal; i++)
	{
		if (!mUnitBase.FindUnit(nID)){
			// 新たに空ユニットを登録する
			mUnitBase.AddUnit(nID);
		}
		UINT selectUnitTypeAf = mUnitBase.GetUnitType(nID);

		mUnitBase.UpdateUnit(nID, theApp.sSelectinfo.sSelectedUnitInfo[i].unit.usage, theApp.sSelectinfo.sSelectedUnitInfo[i].unit.bitmapfile);

		if (selectUnitTypeAf == UnitEmpty) {
			// 新たに空ユニットを登録する
			mUnitBase.AddUnit(nID + 1);
		}
		nID++;
	}
	if (!mUnitBase.IsEmpty())
	{
		mUnitBase.DeleteUnit(nID);
	}
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
	int ret;
	// 確認メッセージ表示
	ret = MessageBox(_T("ユニット情報を保存する場合は「CSV出力」を行ってください。\n機種選択画面に戻りますか？"), _T("警告"), MB_YESNO | MB_ICONWARNING);

	if (ret == IDNO) return;

	// ユニット選択情報をクリア
	theApp.sSelectinfo.clearUnit();

	CDialogEx::OnCancel();
}


LRESULT ConfigurationDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == mMessage_UnitDelete) {
		// ユニットの削除
		mUnitBase.DeleteUnit((UINT)wParam);
		theApp.sSelectinfo.clearUnit((UINT)wParam - mUnitStartCommand);
		if (mUnitBase.IsEmpty() == true) {
			// 格納されているユニット数から空ユニット位置を求める
			mUnitBase.AddUnit(mUnitStartCommand + (mUnitBase.GetUnitCount()));
		}

		// 選択ユニット数、サイズ合計の更新
		SetUnitNum(m_fnts);
		SetUnitSizeTotal(m_fnts);
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

/*============================================================================*/
/*! 構成画面

-# ユニットサイズ合計設定関数

@param

@retval
*/
/*============================================================================*/
void ConfigurationDlg::SetUnitSizeTotal(CFont& font)
{
	UINT unitsizetotal = 0;
	CString strunitsize;

	for (int i = 0; i < mUnitMax; i++)
	{
		unitsizetotal += theApp.sSelectinfo.sSelectedUnitInfo[i].unit.usage;
	}

	strunitsize.Format(_T("%d"), unitsizetotal);
	m_stcUnitSizeTotal.SetWindowText(strunitsize);
	m_stcUnitSizeTotal.SetFont(&font);
}

/*============================================================================*/
/*! 構成画面

-# CSV出力処理

@param

@retval
*/
/*============================================================================*/
void ConfigurationDlg::OnClickedButtonCsvexport()
{
	if (theApp.sSelectinfo.unitselecttotal < 1)
	{
		MessageBox(_T("ユニットが選択されていません。"), _T("エラー"), MB_OK | MB_ICONERROR);
		return;
	}

	// CSV出力処理

	CFileDialog filedlg(false, _T("csv"), nullptr, OFN_OVERWRITEPROMPT ,_T("CSVファイル (*.csv)|*.csv||"));

	if (filedlg.DoModal() != IDOK)	return;

	CString fullpathname = filedlg.GetPathName();

	CStdioFile file;
	if (file.Open(fullpathname, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive | CFile::typeText))
	{
		// ヘッダー
		CString header = _T("");
		for (int i = 0; i < mUserCsvHeader.size(); i++)
		{
			header += mUserCsvHeader.at(i);
			if (i != (mUserCsvHeader.size() - 1))
			{
				header += _T(",");
			}
		}
		file.WriteString(header + _T("\n"));

		// データ
		CString data = _T("");
		for (int i = 0; i < theApp.sSelectinfo.unitselecttotal; i++)
		{
			sModelData tmpmodel = theApp.sSelectinfo.model;
			sUnitData tmpunit = theApp.sSelectinfo.sSelectedUnitInfo[i].unit;

			CString unitnum, unitsize;
			unitnum.Format(_T("%d"), i+1);
			unitsize.Format(_T("%d"), tmpunit.usage);

			data += tmpmodel.category + _T(",") + tmpmodel.modelname + _T(",") + unitnum + _T(",") + tmpunit.unitname + _T(",") + unitsize + _T("\n");
		}
		file.WriteString(data);
	}

	file.Close();
	MessageBox(_T("CSV出力を行いました。"), _T("情報"), MB_OK | MB_ICONINFORMATION);
}

/*============================================================================*/
/*! 構成画面

-# 画面のリサイズを管理する

@param

@retval
*/
/*============================================================================*/
void ConfigurationDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// 初期ウィンドウサイズより小さくしない
	// 幅のみ拡張できるようにする
	CRect rect;
	GetWindowRect(rect);
	if (rect.Width() != 0 && mFrameRect.IsRectEmpty()) {
		mFrameRect = rect;
	}

	if (mFrameRect.IsRectEmpty() == false) {
		lpMMI->ptMinTrackSize.x = mFrameRect.Width();
		lpMMI->ptMinTrackSize.y = mFrameRect.Height();
		lpMMI->ptMaxTrackSize.y = mFrameRect.Height();
	}

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
