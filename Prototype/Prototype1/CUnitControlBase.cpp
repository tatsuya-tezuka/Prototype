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
	if (mUnits.size() == mUnitMax)
		return;

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

@param	command		コマンドID
@param	size		ユニットサイズ

@retval
*/
/*============================================================================*/
void CUnitControlBase::UpdateUnit(UINT command, UINT size)
{
	map<UINT, CUnitControl*>::iterator itr = mUnits.find(command);
	if (itr == mUnits.end())
		return;

	CBitmap cbmp;
	(*itr).second->SetType((size == 2) ? UnitDouble : UnitSingle);
	cbmp.LoadBitmap(mUnitImage[(*itr).second->GetType()]);
	((CUnitControl*)(*itr).second)->SetBitmap((HBITMAP)cbmp.Detach());

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

	if ((*itr).second->GetType() == UnitEmpty)
		return;

	delete (*itr).second;
	mUnits.erase(itr);

	// コマンドIDを振りなおす
	map<UINT, CUnitControl*> temp;
	mUnits.swap(temp);
	command = mUnitStartCommand;
	for (itr = temp.begin(); itr != temp.end(); itr++) {
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
