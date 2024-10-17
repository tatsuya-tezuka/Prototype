#include "pch.h"
#include "Prototype1.h"
#include "CUnitListCtrl.h"

/*============================================================================*/
/*! ユニット情報表示リストコントロール

-# コンストラクター

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
/*! ユニット情報表示リストコントロール

-# デストラクター

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
/*! ユニット情報表示リストコントロール

-# カスタム描画

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

		// アイテムが描画された後に呼ばれる
		int nItem = (int)nmcd->nmcd.dwItemSpec;
		int nSubItem = nmcd->iSubItem;

		// 選択状態の取得
		bool bSelected = (GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED);

		CRect rectBounds, rect;
		GetItemRect(nItem, &rectBounds, LVIR_BOUNDS);

		// ラベル項目の塗りつぶし
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

		// 描画用のフォントの設定
		CFont* pfont = dc.SelectObject(&mDrawFont);

		// カラム数分描画する
		int nColumns = GetHeaderCtrl()->GetItemCount();
		for (int i = 0; i < nColumns; i++) {
			// サブアイテムのテキスト取得
			CString str = GetItemText(nItem, i);
			// タブを改行に変更
			str.Replace(_T("\t"), _T("\n"));

			// ヘッダーからセルフォーマットを取得する
			int nFmt;
			UINT nFormat;
			HDITEM hditem;
			hditem.mask = HDI_FORMAT;
			GetHeaderCtrl()->GetItem(i, &hditem);
			nFmt = hditem.fmt & HDF_JUSTIFYMASK;
			nFormat = DT_VCENTER | DT_WORDBREAK/*このフラグが改行を許可する*/;
			if (nFmt == HDF_CENTER) {
				nFormat |= DT_CENTER;
			}
			else if (nFmt == HDF_LEFT) {
				nFormat |= DT_LEFT;
			}
			else {
				nFormat |= DT_RIGHT;
			}
			// サブアイテム領域を取得
			GetSubItemRect(nItem, i, LVIR_LABEL, rect);

			// 文字列描画
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
