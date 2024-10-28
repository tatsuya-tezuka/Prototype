#pragma once
#include <afxwin.h>

#include "CUnitControl.h"
#include "common.h"

// ビットマップ用
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#include <vector>
#include <map>
using namespace std;

static const UINT mUnitBracketCommand = 4000;
//static const UINT mUnitStartCommand = 8000;
//static const UINT mUnitMax = 10;

class CUnitControlBase : public CStatic
{
public:
	CUnitControlBase();
	virtual ~CUnitControlBase();
	/* ------------------------------------------------------------------------------------ */
	/* 定義                                                                                 */
	/* ------------------------------------------------------------------------------------ */
public:
	const UINT mGap = 1;
	//enum {
	//	UnitBracket,
	//	UnitEmpty,
	//	UnitSingle,
	//	UnitDouble,

	//	UnitMax,
	//};

protected:

	/* ------------------------------------------------------------------------------------ */
	/* メンバ変数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:

protected:
	HINSTANCE			mInstance;
	CWnd				*mParent;
	UINT				mUnitImage[UnitMax];
	CUnitControl* mpStartBracket;
	CUnitControl* mpEndBracket;

	map<UINT, CUnitControl*>	mUnits;
	vector<HBITMAP>	mImages;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	void	SetUnitImage(UINT type, UINT bitmap) { mUnitImage[type] = bitmap; }
	bool	CreateUnitBase(HINSTANCE hInstance, CWnd* parent);
	CUnitControl* CreateUnit(UINT type, UINT id);
	void	UnitAlignment();
	bool	FindUnit(UINT command)
	{
		map<UINT, CUnitControl*>::iterator itr = mUnits.find(command);
		if (itr == mUnits.end())
			return false;
		return true;
	}
	UINT	GetUnitType(UINT command)
	{
		map<UINT, CUnitControl*>::iterator itr = mUnits.find(command);
		if (itr == mUnits.end())
			return UnitMax;
		return (*itr).second->GetType();
	}
	UINT	GetUnitCount()
	{
		return (UINT)mUnits.size();
	}
	void	AddUnit(UINT command);
	void	UpdateUnit(UINT command, UINT size, CString strBitmapFile=_T(""));
	void	DeleteUnit(UINT command);
	bool	IsEmpty();

protected:

	/* ------------------------------------------------------------------------------------ */

public:

protected:
	DECLARE_MESSAGE_MAP()
public:
};

