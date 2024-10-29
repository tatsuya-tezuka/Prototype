#pragma once

#include <vector>

/*
	◆共通定義
*/

// 入出力CSVヘッダー情報
const std::vector<CString> mUserCsvHeader = { {_T("カテゴリー")}, {_T("機種名")}, {_T("ユニット番号")}, {_T("ユニット名称")}, {_T("ユニット占有数")} };
// 機種一覧CSVヘッダー情報
const std::vector<CString> mModelCsvHeader = { {_T("カテゴリー")}, {_T("機種名")}, {_T("有効無効")} };
// ユニット一覧CSVヘッダー情報
const std::vector<CString> mUnitCsvHeader = { {_T("カテゴリー")}, {_T("名称")}, {_T("タイプ")}, {_T("仕様")}, {_T("占有数")}, {_T("手配図番")}, {_T("メッセージ")}, {_T("ビットマップファイル")} };
// ユニット選択画面ヘッダー情報
const std::vector<CString> mUnitlistHeader = { {_T("形名")}, {_T("タイプ")}, {_T("仕様")}, {_T("ユニット占有数")} };
const std::vector<UINT> mUnitlistHeaderSize = { {80}, {80}, {250}, {100} };

const UINT mMessage_UnitDelete = WM_USER + 100;

static const UINT mUnitMax = 10;
static const UINT mUnitStartCommand = 8000;

/* ------------------------------------------------------------------------------------ */
/* enum定義                                                                             */
/* ------------------------------------------------------------------------------------ */
enum eImage {
	eDisableModel,		// NoImage
	eEnableModel,		
	eBracket,
	eAddunit,
	eUnit1,
	eUnit2,
	eNumImage			// eImage項目数
};

enum eFlg {
	eDisable,
	eEnable
};

enum {
	UnitBracket,
	UnitEmpty,
	UnitSingle,
	UnitDouble,

	UnitMax,
};

/* ------------------------------------------------------------------------------------ */
/* struct定義                                                                           */
/* ------------------------------------------------------------------------------------ */

/*============================================================================*/
/*! 共通定義

-# 機器一覧構造体
*/
/*============================================================================*/
struct sModelData 
{
	CString category;
	CString modelname;
	UINT bflg;		// 0:無効、1:有効

	sModelData() 
	{
		category = _T("");
		modelname = _T("");
		bflg = 0;
	}

	BOOL set(CString cat, CString name, UINT flg) 
	{
		category = cat;
		modelname = name;
		bflg = flg;
		return true;
	}

	BOOL setUnit(sModelData data)
	{
		category = data.category;
		modelname = data.modelname;
		bflg = data.bflg;
		return true;
	}

	BOOL clear()
	{
		category = _T("");
		modelname = _T("");
		bflg = 0;
		return true;
	}
};

/*============================================================================*/
/*! 共通定義

-# ユニット一覧構造体
*/
/*============================================================================*/
struct sUnitData 
{
	CString category;
	CString unitname;
	CString type;
	CString spec;		// 仕様
	UINT usage;			// ユニット占有数
	CString fignumber;	// 手配図番
	CString message;
	CString bitmapfile;

	sUnitData() 
	{
		clear();
	}

	BOOL set(CString cat, CString name, CString ctype, CString cspec, UINT cusage, CString num, CString msg, CString bmp)
	{
		category = cat;
		unitname = name;
		type = ctype;
		spec = cspec;
		usage = cusage;
		fignumber = num;
		message = msg;
		bitmapfile = bmp;
		return true;
	}

	BOOL clear()
	{
		category = _T("");
		unitname = _T("");
		type = _T("");
		spec = _T("");
		usage = 0;
		fignumber = _T("");
		message = _T("");
		bitmapfile = _T("");
		return true;
	}
};

/*============================================================================*/
/*! 共通定義

-# 選択ユニット情報構造体
*/
/*============================================================================*/
struct sSelectedInfo 
{
	sModelData model;
	int unitselecttotal;		// ユニット選択数	
	struct {
		UINT unitid;			// ユニットid	
		sUnitData unit;
	} sSelectedUnitInfo[mUnitMax];

	sSelectedInfo()
	{
		unitselecttotal = 0;
		for (UINT i = 0; i < mUnitMax; i++)
		{
			sSelectedUnitInfo[i].unitid = mUnitStartCommand + i;
		}
	}

	// 全選択データのクリア
	BOOL clear()
	{
		model.clear();
		unitselecttotal = 0;
		for (UINT i = 0; i < mUnitMax; i++)
		{
			sSelectedUnitInfo[i].unit.clear();
		}
		return true;
	}

	// ユニット情報のクリア
	BOOL clearUnit(int id)
	{
		sSelectedUnitInfo[id].unit.clear();

		for (int i = id; i < unitselecttotal; i++)
		{
			if (i == mUnitMax - 1)
			{
				sSelectedUnitInfo[i].unit.clear();
			}
			else
			{
				sSelectedUnitInfo[i].unit = sSelectedUnitInfo[i + 1].unit;
			}
		}
		unitselecttotal -= 1;

		return true;
	}
	BOOL clearUnit()
	{
		unitselecttotal = 0;
		for (UINT i = 0; i < mUnitMax; i++)
		{
			sSelectedUnitInfo[i].unit.clear();
		}
		return true;
	}
};
