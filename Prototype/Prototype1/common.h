#pragma once

/*
	�����ʒ�`
*/


/* ------------------------------------------------------------------------------------ */
/* enum��`                                                                             */
/* ------------------------------------------------------------------------------------ */
enum eImage {
	eModel,		// NoImage
	eBracket,
	eAddunit,
	eUnit1,
	eUnit2,
	eNumImage	// eImage���ڐ�
};

/* ------------------------------------------------------------------------------------ */
/* struct��`                                                                           */
/* ------------------------------------------------------------------------------------ */

// �@��ꗗ�\����
struct sModelData {
	CString category;
	CString modelname;
	UINT bflg;		// 0:�����A1:�L��

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
};

// ���j�b�g�ꗗ�\����
struct sUnitData {
	CString category;
	CString unitname;
	CString type;
	CString spec;		// �d�l
	UINT usage;			// ���j�b�g��L��
	CString fignumber;	// ��z�}��
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

// �I�����j�b�g���\����
struct sSelectedInfo {
	sModelData model;
	UINT id;
	struct {
		UINT unitselectnum;
		sUnitData unit;
	} sSelectedUnitInfo[10];
};
