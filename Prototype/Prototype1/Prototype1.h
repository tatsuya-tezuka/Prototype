
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
	UINT mSelectUnitId;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
	BOOL SetmModelDatafromCSV();			
	BOOL SetmUnitDatafromCSV();		
	vector<sModelData>& GetsModelData() { return sModelDataList; }

// 実装

	DECLARE_MESSAGE_MAP()

};

extern CPrototype1App theApp;
