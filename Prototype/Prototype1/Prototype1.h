
// Prototype1.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

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

// CPrototype1App:
// このクラスの実装については、Prototype1.cpp を参照してください
//

class CPrototype1App : public CWinApp
{
public:
	CPrototype1App();

	// ULONG_PTR	m_gdiplusToken;

// オーバーライド
public:
	virtual BOOL InitInstance();

	vector<mModelData> mModelDataList;
	vector<mUnitData> mUnitDataList;

	BOOL SetmModelData();		// CSVから機器一覧を取得、構造体にセットする
	BOOL SetmUnitData();		// CSVからユニット一覧を取得、構造体にセットする
	vector<mModelData>& GetmModelData() { return mModelDataList; }

// 実装

	DECLARE_MESSAGE_MAP()

};

extern CPrototype1App theApp;
