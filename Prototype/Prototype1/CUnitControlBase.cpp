#include "pch.h"
#include "Prototype1.h"
#include "CUnitControlBase.h"

/*
	ユニットコントロールベース：ユニットコントロールを表示する領域
*/

CUnitControlBase::CUnitControlBase()
{
	// 初期化
	mParent = NULL;
	for (UINT i = 0; i < UnitMax; i++) {
		mUnitImage[i] = 0;
	}
}

CUnitControlBase::~CUnitControlBase()
{
	delete mpStartBracket;
	delete mpEndBracket;

	map<UINT, CUnitControl*>::iterator itr;
	for (itr = mUnits.begin(); itr != mUnits.end(); itr++) {
		delete (*itr).second;
	}
	vector<HBITMAP>::iterator itrb;
	for (itrb = mImages.begin(); itrb != mImages.end(); itrb++) {
		DeleteObject((*itrb));
	}
}

BEGIN_MESSAGE_MAP(CUnitControlBase, CStatic)
END_MESSAGE_MAP()


/*============================================================================*/
/*! ユニットコントロールベース

-# ユニットを表示するための初期化

@param	hInstance	アプリケーションインスタンス
@param	parent		親ウィンドウ

@retval
*/
/*============================================================================*/
bool CUnitControlBase::CreateUnitBase(HINSTANCE hInstance, CWnd* parent)
{
	mInstance = hInstance;
	mParent = parent;

	// StartBracket+SingleDisabe+EndBrachetを作成する
	if (mUnitImage[UnitBracket] == 0)
		return false;
	if (mUnitImage[UnitEmpty] == 0)
		return false;

	// StartBracketの作成
	mpStartBracket = CreateUnit(UnitBracket, mUnitBracketCommand);

	// SingleDisableの作成
	CUnitControl* pEmpty = CreateUnit(UnitEmpty, mUnitStartCommand);
	pEmpty->SetType(UnitEmpty);
	pEmpty->SetName(_T("Unit"));
	mUnits.insert(map<UINT, CUnitControl*>::value_type(mUnitStartCommand, pEmpty));

	// EndBracketの作成
	mpEndBracket = CreateUnit(UnitBracket, mUnitBracketCommand + 1);

	UnitAlignment();

	return TRUE;
}

/*============================================================================*/
/*! ユニットコントロールベース

-# ユニットの登録

@param	command		コマンドID

@retval
*/
/*============================================================================*/
void CUnitControlBase::AddUnit(UINT command)
{
	if (IsEmpty() == false) {
		return;
	}
	//if (mUnits.size() == mUnitMax)
	//	return;

	// SingleDisableの作成
	CUnitControl* pEmpty = CreateUnit(UnitEmpty, command);
	pEmpty->SetType(UnitEmpty);
	pEmpty->SetName(_T("Unit"));
	mUnits.insert(map<UINT, CUnitControl*>::value_type(command, pEmpty));

	UnitAlignment();
}

/*============================================================================*/
/*! ユニットコントロールベース

-# ユニットの登録

@param	command			コマンドID
@param	size			ユニットサイズ
@param	strBitmapFile	表示ビットマップファイル名

@retval
*/
/*============================================================================*/
void CUnitControlBase::UpdateUnit(UINT command, UINT size, CString strBitmapFile/*=_T("")*/)
{
	map<UINT, CUnitControl*>::iterator itr = mUnits.find(command);
	if (itr == mUnits.end())
		return;

	(*itr).second->SetType((size == 2) ? UnitDouble : UnitSingle);
	HBITMAP hBitmap = NULL;
	hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strBitmapFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap == NULL) {
		strBitmapFile.Empty();
	}

	if (strBitmapFile.IsEmpty() == true) {
		CBitmap cbmp;
		cbmp.LoadBitmap(mUnitImage[(*itr).second->GetType()]);
		((CUnitControl*)(*itr).second)->SetBitmap((HBITMAP)cbmp.Detach());
	}
	else {
		CBitmap cbmp;
		cbmp.LoadBitmap(mUnitImage[UnitEmpty]);
		BITMAP bmp;
		cbmp.GetBitmap(&bmp);
		cbmp.DeleteObject();

		hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), strBitmapFile, IMAGE_BITMAP, 0, bmp.bmHeight, LR_LOADFROMFILE);
		// ビットマップを登録
		mImages.push_back(hBitmap);
		((CUnitControl*)(*itr).second)->SetBitmap((HBITMAP)hBitmap);
	}

	UnitAlignment();
}

/*============================================================================*/
/*! ユニットコントロールベース

-# ユニットの削除

@param	command		コマンドID

@retval
*/
/*============================================================================*/
void CUnitControlBase::DeleteUnit(UINT command)
{
	map<UINT, CUnitControl*>::iterator itr = mUnits.find(command);
	if (itr == mUnits.end())
		return;

	//if ((*itr).second->GetType() == UnitEmpty)
	//	return;

	// 対象ユニットを削除する
	delete (*itr).second;
	mUnits.erase(itr);
	// 空ユニットを削除する
	for (itr = mUnits.begin(); itr != mUnits.end(); itr++) {
		if ((*itr).second->GetType() == UnitEmpty) {
			delete (*itr).second;
			mUnits.erase(itr);
			break;
		}
	}

	// コマンドIDを振りなおす
	map<UINT, CUnitControl*> temp;
	mUnits.swap(temp);
	command = mUnitStartCommand;
	for (itr = temp.begin(); itr != temp.end(); itr++) {
		if ((*itr).second->GetType() == UnitEmpty) {
			break;
		}
		mUnits.insert(map<UINT, CUnitControl*>::value_type(command, (*itr).second));
		(*itr).second->SetDlgCtrlID(command);
		command++;
	}

	UnitAlignment();
}

/*============================================================================*/
/*! ユニットコントロールベース

-# ユニットの作成

@param	type	ユニット種類
@param	id		コマンドID

@retval
*/
/*============================================================================*/
CUnitControl* CUnitControlBase::CreateUnit(UINT type, UINT id)
{
	CPoint pt = CPoint(0, 0);
	CBitmap cbmp;

	cbmp.LoadBitmap(mUnitImage[type]);

	CUnitControl* ptr;
	ptr = new CUnitControl();
	ptr->Create(_T(""), WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(pt.x, pt.y, 0, 0), mParent, id);
	ptr->SetBitmap((HBITMAP)cbmp.Detach());

	return ptr;
}

/*============================================================================*/
/*! ユニットコントロールベース

-# ユニットの整列

@param

@retval
*/
/*============================================================================*/
void CUnitControlBase::UnitAlignment()
{
	if (mParent == NULL)
		return;

	// ボタン表示領域の取得
	CRect rect, rc;
	// 表示領域のウィンドウサイズ取得
	GetWindowRect(rect);

	// ダイアログのクライアント位置に変換
	mParent->ScreenToClient(rect);

	mpStartBracket->GetWindowRect(rc);
	int y = rect.top + ((rect.Height() - rc.Height()) / 2);

	CPoint pt;
	pt.x = rect.left;
	pt.y = rect.top + y;

	// StartBracketの配置
	::SetWindowPos(mpStartBracket->m_hWnd, HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
	mpStartBracket->Invalidate();
	mpStartBracket->GetWindowRect(rect);
	mParent->ScreenToClient(rect);
	pt.x = rect.right + mGap;
	pt.y = rect.top;

	map<UINT, CUnitControl*>::iterator itr;
	for (itr = mUnits.begin(); itr != mUnits.end(); itr++) {
		CUnitControl* ptr = (CUnitControl*)(*itr).second;
		::SetWindowPos(ptr->m_hWnd, HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
		ptr->Invalidate();
		ptr->GetWindowRect(rect);
		mParent->ScreenToClient(rect);
		pt.x = rect.right + mGap;
		pt.y = rect.top;
	}

	// EndBracketの配置
	::SetWindowPos(mpEndBracket->m_hWnd, HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
	mpEndBracket->Invalidate();
	mpEndBracket->GetWindowRect(rect);
	mParent->ScreenToClient(rect);
	pt.x = rect.right + mGap;
	pt.y = rect.top;
}

/*============================================================================*/
/*! ユニットコントロールベース

-# 空ユニットが必要かをチェックする

@param

@retval
*/
/*============================================================================*/
bool CUnitControlBase::IsEmpty()
{
	//if (mUnits.size() == mUnitMax)
	//	return false;

	// ユニットサイズの合計チェック
	map<UINT, CUnitControl*>::iterator itr;
	UINT unitnum = 0;
	for (itr = mUnits.begin(); itr != mUnits.end(); itr++) {
		if ((*itr).second->GetType() == UnitSingle)
			unitnum += 1;
		if ((*itr).second->GetType() == UnitDouble)
			unitnum += 2;
	}
	if (unitnum == mUnitMax)
		return false;

	return true;
}
