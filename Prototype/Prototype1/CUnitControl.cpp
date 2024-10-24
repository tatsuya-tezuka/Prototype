#include "pch.h"
#include "Prototype1.h"
#include "CUnitControl.h"
#include "CUnitControlBase.h"

/*
	ユニットコントロール
*/

CUnitControl::CUnitControl()
{
}

CUnitControl::~CUnitControl()
{
}

BEGIN_MESSAGE_MAP(CUnitControl, CStatic)
	ON_WM_SETCURSOR()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_UNIT_DELETE, &CUnitControl::OnUnitDelete)
END_MESSAGE_MAP()

/*============================================================================*/
/*! ユニットコントロール

-# マウスカーソルの設定

@param

@retval
*/
/*============================================================================*/
BOOL CUnitControl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(mCursor);
	//SetCursor(mCursor);
	return TRUE;

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

/*============================================================================*/
/*! ユニットコントロール

-# サブクラス化

@param

@retval
*/
/*============================================================================*/
void CUnitControl::PreSubclassWindow()
{
	mCursor = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	DWORD dwStyle = GetStyle();
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	CStatic::PreSubclassWindow();
}


void CUnitControl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if (mType == /*CUnitControlBase::*/UnitBracket || mType == /*CUnitControlBase::*/UnitEmpty) {
		// 空ユニットの場合は何もしない
		return;
	}

	// 削除メニューの表示
	CMenu menu;
	if (menu.LoadMenu(IDR_MENU_DELETE)){
		CMenu* pSubMenu = menu.GetSubMenu(0);
		if (pSubMenu == NULL)
			return;
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}


void CUnitControl::OnUnitDelete()
{
	GetParent()->PostMessage(mMessage_UnitDelete, (WPARAM)GetDlgCtrlID(), 0);
}
