#pragma once

static const UINT maxNameSize = 80;

class CUnitControl : public CStatic
{
public:
	CUnitControl();
	virtual ~CUnitControl();
	/* ------------------------------------------------------------------------------------ */
	/* íËã`                                                                                 */
	/* ------------------------------------------------------------------------------------ */
public:

protected:

	/* ------------------------------------------------------------------------------------ */
	/* ÉÅÉìÉoïœêî                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:

protected:
	HCURSOR		mCursor;
	HBITMAP		mUnitImage;

	UINT		mType;
	TCHAR		mName[maxNameSize];

	/* ------------------------------------------------------------------------------------ */
	/* ÉÅÉìÉoä÷êî                                                                           */
	/* ------------------------------------------------------------------------------------ */
public:
	void	SetType(UINT type) { mType = type; }
	UINT	GetType() { return mType; }
	void	SetName(TCHAR* name)
	{
		swprintf_s(mName, maxNameSize, _T("%s"), name);
	}

protected:

	/* ------------------------------------------------------------------------------------ */

	//{{AFX_VIRTUAL(CUnitControl)
public:
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CUnitControl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void PreSubclassWindow();
};
