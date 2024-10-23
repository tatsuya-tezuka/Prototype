#pragma once
#include "afxdialogex.h"
#include "CUnitControl.h"
#include "CUnitControlBase.h"

// ConfigurationDlg ダイアログ

class ConfigurationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigurationDlg)

public:
	ConfigurationDlg(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~ConfigurationDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIGURATION_DIALOG };
#endif

	/* ------------------------------------------------------------------------------------ */
	/* 定義                                                                                 */
	/* ------------------------------------------------------------------------------------ */
public:

protected:
	enum {
		ANCHORE_LEFTTOP = 0x0000,	// 左上は固定させる
		ANCHORE_RIGHT = 0x0001,	// 右側は固定させる
		ANCHORE_BOTTOM = 0x0002,	// 下側は固定させる
		RESIZE_HOR = 0x0004,	// 横のリサイズを可能にする
		RESIZE_VER = 0x0008,	// 縦のリサイズを可能にする
		RESIZE_BOTH = (RESIZE_HOR | RESIZE_VER),
	};

	/* ------------------------------------------------------------------------------------ */
	/* メンバ変数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	CStatic m_stcModelName;
	CEdit m_editUnitList;
	CStatic m_stcUnitNum;

protected:
	// コントロールのリサイズ
	vector<DWORD>		mControl;
	int					mSaveCx, mSaveCy;

	/* ------------------------------------------------------------------------------------ */
	/* メンバ関数                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:

protected:
	/// コントロールの登録
	void SetControlInfo(WORD id, WORD anchore)
	{
		if (anchore == ANCHORE_LEFTTOP)
			return;

		DWORD info = MAKELONG(id, anchore);
		mControl.push_back(info);
	}

	/* ------------------------------------------------------------------------------------ */

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	CUnitControlBase mUnitBase;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUnitCommand(UINT nID);
	afx_msg void OnBnClickedCancel();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
