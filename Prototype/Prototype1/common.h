#pragma once

/*
	◆共通定義

*/

enum eImage {
	eModel,		// NoImage
	eBracket,
	eAddunit,
	eUnit1,
	eUnit2,
	eNumImage	// eImage項目数
};

// 機器一覧構造体
struct sModelData {
	CString category;
	CString modelname;
	UINT bflg;		// 0:無効、1:有効

	sModelData(CString cat, CString name, UINT flg) {
		category = cat;
		modelname = name;
		bflg = flg;
	}
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

	sUnitData(CString cat, CString name, CString ctype, CString cspec, UINT cusage, CString num, CString msg) {
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
	sModelData model;
	UINT id;
	typedef struct {
		UINT unitselectnum;
		sUnitData unit;
	} mSelectedUnitInfo[10];
};
