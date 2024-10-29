#pragma once

#include <vector>

/*
	�����ʒ�`
*/

// ���o��CSV�w�b�_�[���
const std::vector<CString> mUserCsvHeader = { {_T("�J�e�S���[")}, {_T("�@�햼")}, {_T("���j�b�g�ԍ�")}, {_T("���j�b�g����")}, {_T("���j�b�g��L��")} };
// �@��ꗗCSV�w�b�_�[���
const std::vector<CString> mModelCsvHeader = { {_T("�J�e�S���[")}, {_T("�@�햼")}, {_T("�L������")} };
// ���j�b�g�ꗗCSV�w�b�_�[���
const std::vector<CString> mUnitCsvHeader = { {_T("�J�e�S���[")}, {_T("����")}, {_T("�^�C�v")}, {_T("�d�l")}, {_T("��L��")}, {_T("��z�}��")}, {_T("���b�Z�[�W")}, {_T("�r�b�g�}�b�v�t�@�C��")} };
// ���j�b�g�I����ʃw�b�_�[���
const std::vector<CString> mUnitlistHeader = { {_T("�`��")}, {_T("�^�C�v")}, {_T("�d�l")}, {_T("���j�b�g��L��")} };
const std::vector<UINT> mUnitlistHeaderSize = { {80}, {80}, {250}, {100} };

const UINT mMessage_UnitDelete = WM_USER + 100;

static const UINT mUnitMax = 10;
static const UINT mUnitStartCommand = 8000;

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

enum {
	UnitBracket,
	UnitEmpty,
	UnitSingle,
	UnitDouble,

	UnitMax,
};

/* ------------------------------------------------------------------------------------ */
/* struct��`                                                                           */
/* ------------------------------------------------------------------------------------ */

/*============================================================================*/
/*! ���ʒ�`

-# �@��ꗗ�\����
*/
/*============================================================================*/
struct sModelData 
{
	CString category;
	CString modelname;
	UINT bflg;		// 0:�����A1:�L��

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
/*! ���ʒ�`

-# ���j�b�g�ꗗ�\����
*/
/*============================================================================*/
struct sUnitData 
{
	CString category;
	CString unitname;
	CString type;
	CString spec;		// �d�l
	UINT usage;			// ���j�b�g��L��
	CString fignumber;	// ��z�}��
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
/*! ���ʒ�`

-# �I�����j�b�g���\����
*/
/*============================================================================*/
struct sSelectedInfo 
{
	sModelData model;
	int unitselecttotal;		// ���j�b�g�I��	
	struct {
		UINT unitid;			// ���j�b�gid	
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

	// �S�I���f�[�^�̃N���A
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

	// ���j�b�g���̃N���A
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
