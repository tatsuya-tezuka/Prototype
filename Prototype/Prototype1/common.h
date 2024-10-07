#pragma once

enum eImage {
	eModel,		// NoImage
	eBracket,
	eAddunit,
	eUnit1,
	eUnit2,
	eNumImage	// eImage���ڐ�
};

// �@��ꗗ�\����
struct mModelData {
	CString category;
	CString modelname;
	UINT bflg;		// 0:�����A1:�L��

	mModelData(CString cat, CString name, UINT flg) {
		category = cat;
		modelname = name;
		bflg = flg;
	}
};

// ���j�b�g�ꗗ�\����
struct mUnitData {
	CString category;
	CString unitname;
	CString type;
	CString spec;		// �d�l
	UINT usage;			// ���j�b�g��L��
	CString fignumber;	// ��z�}��
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

// �I�����j�b�g���\����
struct mSelectedInfo {
	mModelData model;
	UINT id;
	typedef struct {
		UINT unitselectnum;
		mUnitData unit;
	} mSelectedUnitInfo[10];
};
