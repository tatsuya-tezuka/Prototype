
#pragma once

/*
	◆アプリケーションヘッダーファイル
	・アプリケーションクラス：CPrototype1App
	・実装ファイル：Prototype1.cpp
	・クラス内には「定義」「メンバ変数」「メンバ関数」のコメントを記述する
*/

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#include "common.h"
#include <vector>
using namespace std;

//// サムネイル表示用
//#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma comment(lib, "gdiplus.lib")

class CPrototype1App : public CWinApp
{
public:
	CPrototype1App();

	// ULONG_PTR	m_gdiplusToken;

// オーバーライド
public:
	virtual BOOL InitInstance();

	/* ------------------------------------------------------------------------------------ */
	/* メンバ変数                                                                           */
	/* ------------------------------------------------------------------------------------ */
	vector<sModelData> sModelDataList;
	vector<sUnitData> sUnitDataList;
	sSelectedInfo sSelectinfo;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
	BOOL SetmModelDatafromCSV();		// CSVから機器一覧を取得、構造体にセットする
	BOOL SetmUnitDatafromCSV();		// CSVからユニット一覧を取得、構造体にセットする
	vector<sModelData>& GetsModelData() { return sModelDataList; }
	sSelectedInfo GetsSelectinfoData() { return sSelectinfo; }

// 実装

	DECLARE_MESSAGE_MAP()

};

extern CPrototype1App theApp;
