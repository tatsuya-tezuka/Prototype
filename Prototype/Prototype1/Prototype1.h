
// Prototype1.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#include <vector>
using namespace std;

// サムネイル表示用
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

// CPrototype1App:
// このクラスの実装については、Prototype1.cpp を参照してください
//

// 機器一覧構造体
struct mModelData {
	CString category;
	CString modelname;
	UINT bflg;		// 0:無効、1:有効

	mModelData(CString cat, CString name, UINT flg) {
		category = cat;
		modelname = name;
		bflg = flg;
	}
};

// ユニット一覧構造体
struct mUnitData {
	CString category;
	CString unitname;
	CString type;		
	CString spec;		// 仕様
	UINT usage;			// ユニット占有数
	CString fignumber;	// 手配図番
	CString message;

	mUnitData(CString cat, CString name, CString ctype, CString cspec, UINT cusage, CString num, CString msg) {
		category = cat;
		unitname = name;
		type = ctype;
		spec = cspec;
		usage = cusage;
		fignumber = num;
		message = msg;
	}
};

// 選択ユニット情報構造体
struct mSelectedInfo {
	mModelData model;
	UINT id;
	typedef struct {
		UINT unitselectnum;
		mUnitData unit;
	} mSelectedUnitInfo[10];
} ;

class CPrototype1App : public CWinApp
{
public:
	CPrototype1App();

	ULONG_PTR	m_gdiplusToken;

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
