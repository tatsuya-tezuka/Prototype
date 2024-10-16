#pragma once

#include <vector>

/*
	�����ʒ�`
*/

// ���j�b�g�I����ʃw�b�_�[���
const std::vector<CString> mUnitlistHeader = { {_T("�`��")}, {_T("�^�C�v")}, {_T("�d�l")}, {_T("���j�b�g��L��")} };


/* ------------------------------------------------------------------------------------ */
/* enum��`                                                                             */
/* ------------------------------------------------------------------------------------ */
enum eImage {
	eDisableModel,		// NoImage
	eEnableModel,		
	eBracket,
	eAddunit,
	eUnit1,
	eUnit2,
	eNumImage			// eImage���ڐ�
};

enum eFlg {
	eDisable,
	eEnable
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

const static UINT mUnitMax = 10;

// �I�����j�b�g���\����
struct sSelectedInfo {
	sModelData model;
	UINT unitselecttotal;		// ���j�b�g�I��
	struct {
		UINT unitid;			// ���j�b�g�I������	
		sUnitData unit;
	} sSelectedUnitInfo[mUnitMax];
};
