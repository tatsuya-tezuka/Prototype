#include "pch.h"
#include "CUnitControl.h"

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
