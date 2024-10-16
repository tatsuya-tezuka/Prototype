#pragma once

#include <vector>

/*
	◆共通定義
*/

// ユニット選択画面ヘッダー情報
const std::vector<CString> mUnitlistHeader = { {_T("形名")}, {_T("タイプ")}, {_T("仕様")}, {_T("ユニット占有数")} };


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


/* ------------------------------------------------------------------------------------ */
/* struct定義                                                                           */
/* ------------------------------------------------------------------------------------ */

// 機器一覧構造体
struct sModelData {
	CString category;
	CString modelname;
	UINT bflg;		// 0:無効、1:有効

	//sModelData(CString cat, CString name, UINT flg) {
	//	category = cat;
	//	modelname = name;
	//	bflg = flg;
	//}

	BOOL set(CString cat, CString name, UINT flg) {
		category = cat;
		modelname = name;
		bflg = flg;
		return true;
	}

	//operator UINT() 
	//{
	//	if (modelname.IsEmpty()) 
	//	{
	//		return -1;
	//	}
	//	else
	//	{
	//		return bflg;
	//	}
	//}
};

// ユニット一覧構造体
struct sUnitData {
	CString category;
	CString unitname;
	CString type;
	CString spec;		// 仕様
	UINT usage;			// ユニット占有数
	CString fignumber;	// 手配図番
	CString message;

	//sUnitData(CString cat, CString name, CString ctype, CString cspec, UINT cusage, CString num, CString msg) {
	//	category = cat;
	//	unitname = name;
	//	type = ctype;
	//	spec = cspec;
	//	usage = cusage;
	//	fignumber = num;
	//	message = msg;
	//}

	BOOL set(CString cat, CString name, CString ctype, CString cspec, UINT cusage, CString num, CString msg) {
		category = cat;
		unitname = name;
		type = ctype;
		spec = cspec;
		usage = cusage;
		fignumber = num;
		message = msg;
		return true;
	}
};

const static UINT mUnitMax = 10;

// 選択ユニット情報構造体
struct sSelectedInfo {
	sModelData model;
	UINT unitselecttotal;		// ユニット選択数
	struct {
		UINT unitid;			// ユニット選択順番	
		sUnitData unit;
	} sSelectedUnitInfo[mUnitMax];
};
