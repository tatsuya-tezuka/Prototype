// UnitQtyDlg.cpp : 実装ファイル
//
/******************************************************************************
* @file    UnitQtyDlg.cpp
* @brief   UnitQtyDlgクラス
* @auther  SCC
* @date    2024/10/07 新規作成
* @par
******************************************************************************/

#include "pch.h"
#include "Prototype1.h"
#include "afxdialogex.h"
#include "UnitQtyDlg.h"


// UnitQtyDlg ダイアログ

IMPLEMENT_DYNAMIC(UnitQtyDlg, CDialogEx)

UnitQtyDlg::UnitQtyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNITQTY_DIALOG, pParent)
{

}

UnitQtyDlg::~UnitQtyDlg()
{
}

void UnitQtyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_QTY, m_cmbUnitQty);
}


BEGIN_MESSAGE_MAP(UnitQtyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &UnitQtyDlg::OnBnClickedOk)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// UnitQtyDlg メッセージ ハンドラー


/*============================================================================*/
/*! 数量選択画面

-# 初期化

@param  なし

@retval なし
*/
/*============================================================================*/
BOOL UnitQtyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int opt = m_unitRemaining / m_unitdata->usage;

	for (int i = 0; i < opt; i++)
	{
		// 初期値設定
		CString qty;
		qty.Format(_T("%d"), i+1);
		m_cmbUnitQty.AddString(qty);

		// 先頭項目を選択状態にする
		m_cmbUnitQty.SetCurSel(0);
	}

	// ヘッダーラベルの設定
	// 背景色設定
	m_brsHead.CreateSolidBrush(RGB(100, 100, 100));
	
	// ユニット名ラベルの設定
	GetDlgItem(IDC_STATIC_UNITNAME)->SetWindowText(m_unitdata->unitname);
	// 背景色設定
	m_brsUnitName.CreateSolidBrush(RGB(255, 255, 255));

	return TRUE;  // return TRUE unless you set the focus to a control
}


/*============================================================================*/
/*! 数量選択画面

-# ★OKボタンイベント

@param  なし

@retval なし
*/
/*============================================================================*/
void UnitQtyDlg::OnBnClickedOk()
{
	int idx = m_cmbUnitQty.GetCurSel();

	int id = theApp.mSelectUnitId - mUnitStartCommand;

	// 既存更新
	if (!(theApp.sSelectinfo.sSelectedUnitInfo[id].unit.unitname.IsEmpty()))
	{
		if (idx > 0) 
		{
			int count = theApp.sSelectinfo.unitselecttotal - 1;
			int sum = idx;
			// Emptyではない場合はユニット情報を再配置
			for (int i = 0; i < (theApp.sSelectinfo.unitselecttotal - id - 1); i++)
			{
				int idxfm = count;
				int idxto = count + sum;
				theApp.sSelectinfo.sSelectedUnitInfo[idxto].unit = theApp.sSelectinfo.sSelectedUnitInfo[idxfm].unit;
				count--;
			}
			theApp.sSelectinfo.unitselecttotal += idx;
		}

		// 選択ユニットに更新
		for (int i = 0; i <= idx; i++)
		{
			theApp.sSelectinfo.sSelectedUnitInfo[id + i].unit = *m_unitdata;
		}
	}
	// 新規追加
	else
	{
		for (int i = 0; i <= idx; i++)
		{
			theApp.sSelectinfo.sSelectedUnitInfo[id + i].unit = *m_unitdata;
			theApp.sSelectinfo.unitselecttotal += 1;
			continue;
		}
	}
	CDialogEx::OnOK();
}


HBRUSH UnitQtyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: ここで DC の属性を変更してください。
	// コントロールのIDを取得
	int id = pWnd->GetDlgCtrlID();
	switch (id)
	{
		// ヘッダーユニット名ラベルの場合
	case IDC_STATIC_HDUNITNAME:
	case IDC_STATIC_HDUNITNUM:
		// 文字色を設定
		pDC->SetTextColor(RGB(255, 255, 255));
		// 文字の背景を設定
		pDC->SetBkColor(RGB(100, 100, 100));
		// ラベルの背景色用ブラシを返却
		return m_brsHead;
		break;

		// ユニット名ラベルの場合
	case IDC_STATIC_UNITNAME:
		// 文字の背景を設定
		pDC->SetBkColor(RGB(255, 255, 255));
		// ラベルの背景色用ブラシを返却
		return m_brsUnitName;
		break;

	default:
		break;
	}

	// TODO: 既定値を使用したくない場合は別のブラシを返します。
	return hbr;
}
