#include "pch.h"
#include "Prototype1.h"
#include "CUnitListCtrl.h"

/*============================================================================*/
/*! ���j�b�g���\�����X�g�R���g���[��

-# �R���X�g���N�^�[

@param
@retval

*/
/*============================================================================*/
CUnitListCtrl::CUnitListCtrl()
{
	mDrawFont.CreateStockObject(DEFAULT_GUI_FONT);
	LOGFONT lf;
	if (mDrawFont.GetLogFont(&lf)) {
		lf.lfHeight = -12;
		mDrawFont.DeleteObject();
		mDrawFont.CreateFontIndirect(&lf);
	}
}

/*============================================================================*/
/*! ���j�b�g���\�����X�g�R���g���[��

-# �f�X�g���N�^�[

@param
@retval

*/
/*============================================================================*/
CUnitListCtrl::~CUnitListCtrl()
{
	mDrawFont.DeleteObject();
}

BEGIN_MESSAGE_MAP(CUnitListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CUnitListCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()


/*============================================================================*/
/*! ���j�b�g���\�����X�g�R���g���[��

-# �J�X�^���`��

@param
@retval

*/
/*============================================================================*/
void CUnitListCtrl::OnNMCustomdraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* nmcd = (NMLVCUSTOMDRAW*)pNMHDR;
	*pResult = CDRF_DODEFAULT;

	switch (nmcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		return;

	case CDDS_ITEMPREPAINT:
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		return;

	case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
	{
		*pResult = 0;

		CDC dc;
		dc.Attach(nmcd->nmcd.hdc);

		// �A�C�e�����`�悳�ꂽ��ɌĂ΂��
		int nItem = (int)nmcd->nmcd.dwItemSpec;
		int nSubItem = nmcd->iSubItem;

		// �I����Ԃ̎擾
		bool bSelected = (GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED);

		CRect rectBounds, rect;
		GetItemRect(nItem, &rectBounds, LVIR_BOUNDS);

		// ���x�����ڂ̓h��Ԃ�
		if (bSelected == true) {
			dc.FillSolidRect(&rectBounds, ::GetSysColor(COLOR_HIGHLIGHT));
			dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
			nmcd->clrTextBk = ::GetSysColor(COLOR_HIGHLIGHT);
			nmcd->clrText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
		}
		else {
			dc.FillSolidRect(&rectBounds, ::GetSysColor(COLOR_WINDOW));
			dc.SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
			nmcd->clrTextBk = ::GetSysColor(COLOR_WINDOW);
			nmcd->clrText = ::GetSysColor(COLOR_WINDOWTEXT);
		}

		dc.SetBkMode(TRANSPARENT);

		// �`��p�̃t�H���g�̐ݒ�
		CFont* pfont = dc.SelectObject(&mDrawFont);

		// �J���������`�悷��
		int nColumns = GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumns; i++) {
			// �T�u�A�C�e���̃e�L�X�g�擾
			CString str = GetItemText(nItem, i);
			// �^�u�����s�ɕύX
			str.Replace(_T("\t"), _T("\n"));

			// �w�b�_�[����Z���t�H�[�}�b�g���擾����
			int nFmt;
			UINT nFormat;
			HDITEM hditem;
			hditem.mask = HDI_FORMAT;
			GetHeaderCtrl()->GetItem(i, &hditem);
			nFmt = hditem.fmt & HDF_JUSTIFYMASK;
			nFormat = DT_VCENTER | DT_WORDBREAK/*���̃t���O�����s��������*/;
			if (nFmt == HDF_CENTER) {
				nFormat |= DT_CENTER;
			}
			else if (nFmt == HDF_LEFT) {
				nFormat |= DT_LEFT;
			}
			else {
				nFormat |= DT_RIGHT;
			}
			// �T�u�A�C�e���̈���擾
			GetSubItemRect(nItem, i, LVIR_LABEL, rect);

			// ������`��
			int offset = dc.GetTextExtent(_T("W"), 1).cx;
			rect.left += 6;
			dc.DrawText(str, &rect, nFormat);
		}
		dc.SelectObject(pfont);
		dc.Detach();


		*pResult = CDRF_SKIPDEFAULT;

		break;
	}
	}
}
