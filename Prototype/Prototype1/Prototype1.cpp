
/******************************************************************************
* @file    Prototype1.cpp
* @brief   アプリケーションクラス
* @auther  SCC
* @date    2024/10/01 新規作成
* @par
******************************************************************************/

#include "pch.h"
#include "framework.h"
#include "Prototype1.h"
#include "Prototype1Dlg.h"
#include "afxdialogex.h"
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPrototype1App

BEGIN_MESSAGE_MAP(CPrototype1App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


//------------------------------------------------------------------------------------ 
//	概要：アプリケーションクラス
//------------------------------------------------------------------------------------


CPrototype1App::CPrototype1App()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CPrototype1App オブジェクト

CPrototype1App theApp;

//------------------------------------------------------------------------------------ 
//	初期化
//------------------------------------------------------------------------------------
BOOL CPrototype1App::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// MFC コントロールでテーマを有効にするために、"Windows ネイティブ" のビジュアル マネージャーをアクティブ化
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	//// サムネイル表示でイメージを表示するための初期化（initialize GDI+）
	//GdiplusStartupInput gdiplusStartupInput;
	//GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	CPrototype1Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: ダイアログの作成に失敗しました。アプリケーションは予期せずに終了します。\n");
		TRACE(traceAppMsg, 0, "警告: ダイアログで MFC コントロールを使用している場合、#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS を指定できません。\n");
	}

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

/*============================================================================*/
/*! アプリケーションクラス

-# 機器一覧CSVから情報を取得し、機器一覧構造体に格納する

@param	

@retval	成功した場合はtrue、それ以外はfalseを返す
*/
/*============================================================================*/
BOOL CPrototype1App::SetmModelDatafromCSV()
{
	CString	readrow, cbuf, str;
	BOOL bHead = TRUE;	//ヘッダー判定
	vector<CString> inlist;

	TCHAR* ploc = _wsetlocale(LC_ALL, _T("japanese"));

	// オープンするファイル名
	CString fileName = _T("ModelList.CSV");

	// ファイルをオープン
	CStdioFile file(fileName, CFile::modeRead | CFile::typeText);

	while (file.ReadString(readrow))
	{
		int i = 0;
		while (AfxExtractSubString(str, readrow, i++, ',')) {
			str.Trim();
			str.Replace(_T("\""), _T(""));
			inlist.push_back(str);
		}

		// ヘッダー判定
		if (bHead)
		{
			// ヘッダ情報チェック
			for (int i = 0; i < mModelCsvHeader.size(); i++)
			{
				if (!(mModelCsvHeader[i] == inlist[i]))
				{
					file.Close();
					return false;
				}
			}

			bHead = FALSE;
			inlist.clear();
			continue;
		}

		// 構造体に格納
		UINT flg;
		flg = _ttoi(inlist[2]);
		sModelData model;
		model.set(inlist[0], inlist[1], flg);
		sModelDataList.push_back(model);
		inlist.clear();
	}
	file.Close();

	return true;
}

/*============================================================================*/
/*! アプリケーションクラス

-# ユニット一覧CSVから情報を取得し、ユニット一覧構造体に格納する

@param	

@retval	成功した場合はtrue、それ以外はfalseを返す
*/
/*============================================================================*/
BOOL CPrototype1App::SetmUnitDatafromCSV()
{
	CString	readrow, cbuf, str;
	BOOL bHead = TRUE;	//ヘッダー判定
	vector<CString> inlist;

	TCHAR* ploc = _wsetlocale(LC_ALL, _T("japanese"));

	// オープンするファイル名
	CString fileName = _T("UnitList.CSV");

	// ファイルをオープン
	CStdioFile file(fileName, CFile::modeRead | CFile::typeText);

	while (file.ReadString(readrow))
	{
		int i = 0;
		while (AfxExtractSubString(str, readrow, i++, ',')) {
			str.Trim();
			str.Replace(_T("\""), _T(""));
			inlist.push_back(str);
		}

		// ヘッダー数と明細数をチェック
		if (mUnitCsvHeader.size() != inlist.size()) {
			// 明細サイズに誤りがあるため、読み込みを中止する
			file.Close();
			return false;
		}

		// ヘッダー判定
		if (bHead)
		{
			// ヘッダ情報チェック
			for (int i = 0; i < mUnitCsvHeader.size(); i++)
			{
				if (!(mUnitCsvHeader[i] == inlist[i]))
				{
					file.Close();
					return false;
				}
			}

			bHead = FALSE;
			inlist.clear();
			continue;
		}
		
		// 構造体に格納
		UINT usage;
		usage = _ttoi(inlist[4]);
		sUnitData unit;
		unit.set(inlist[0], inlist[1], inlist[2], inlist[3], usage, inlist[5], inlist[6], inlist[7]);
		sUnitDataList.push_back(unit);
		inlist.clear();
	}
	file.Close();

	return true;
}

