#include "pch.h"
#include "CUnitControl.h"

/*
	���j�b�g�R���g���[��
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
/*! ���j�b�g�R���g���[��

-# �}�E�X�J�[�\���̐ݒ�

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
/*! ���j�b�g�R���g���[��

-# �T�u�N���X��

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
