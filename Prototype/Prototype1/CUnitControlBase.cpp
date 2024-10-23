#include "pch.h"
#include "Prototype1.h"
#include "CUnitControlBase.h"

/*
	���j�b�g�R���g���[���x�[�X�F���j�b�g�R���g���[����\������̈�
*/

CUnitControlBase::CUnitControlBase()
{
	// ������
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
/*! ���j�b�g�R���g���[���x�[�X

-# ���j�b�g��\�����邽�߂̏�����

@param	hInstance	�A�v���P�[�V�����C���X�^���X
@param	parent		�e�E�B���h�E

@retval
*/
/*============================================================================*/
bool CUnitControlBase::CreateUnitBase(HINSTANCE hInstance, CWnd* parent)
{
	mInstance = hInstance;
	mParent = parent;

	// StartBracket+SingleDisabe+EndBrachet���쐬����
	if (mUnitImage[UnitBracket] == 0)
		return false;
	if (mUnitImage[UnitEmpty] == 0)
		return false;

	// StartBracket�̍쐬
	mpStartBracket = CreateUnit(UnitBracket, mUnitBracketCommand);

	// SingleDisable�̍쐬
	CUnitControl* pEmpty = CreateUnit(UnitEmpty, mUnitStartCommand);
	pEmpty->SetType(UnitEmpty);
	pEmpty->SetName(_T("Unit"));
	mUnits.insert(map<UINT, CUnitControl*>::value_type(mUnitStartCommand, pEmpty));

	// EndBracket�̍쐬
	mpEndBracket = CreateUnit(UnitBracket, mUnitBracketCommand + 1);

	UnitAlignment();

	return TRUE;
}

/*============================================================================*/
/*! ���j�b�g�R���g���[���x�[�X

-# ���j�b�g�̓o�^

@param	command		�R�}���hID

@retval
*/
/*============================================================================*/
void CUnitControlBase::AddUnit(UINT command)
{
	if (mUnits.size() == mUnitMax)
		return;

	// SingleDisable�̍쐬
	CUnitControl* pEmpty = CreateUnit(UnitEmpty, command);
	pEmpty->SetType(UnitEmpty);
	pEmpty->SetName(_T("Unit"));
	mUnits.insert(map<UINT, CUnitControl*>::value_type(command, pEmpty));

	UnitAlignment();
}

/*============================================================================*/
/*! ���j�b�g�R���g���[���x�[�X

-# ���j�b�g�̓o�^

@param	command		�R�}���hID
@param	size		���j�b�g�T�C�Y

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
/*! ���j�b�g�R���g���[���x�[�X

-# ���j�b�g�̍폜

@param	command		�R�}���hID

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

	// �R�}���hID��U��Ȃ���
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
/*! ���j�b�g�R���g���[���x�[�X

-# ���j�b�g�̍쐬

@param	type	���j�b�g���
@param	id		�R�}���hID

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
/*! ���j�b�g�R���g���[���x�[�X

-# ���j�b�g�̐���

@param

@retval
*/
/*============================================================================*/
void CUnitControlBase::UnitAlignment()
{
	if (mParent == NULL)
		return;

	// �{�^���\���̈�̎擾
	CRect rect, rc;
	// �\���̈�̃E�B���h�E�T�C�Y�擾
	GetWindowRect(rect);

	// �_�C�A���O�̃N���C�A���g�ʒu�ɕϊ�
	mParent->ScreenToClient(rect);

	mpStartBracket->GetWindowRect(rc);
	int y = rect.top + ((rect.Height() - rc.Height()) / 2);

	CPoint pt;
	pt.x = rect.left;
	pt.y = rect.top + y;

	// StartBracket�̔z�u
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

	// EndBracket�̔z�u
	::SetWindowPos(mpEndBracket->m_hWnd, HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
	mpEndBracket->Invalidate();
	mpEndBracket->GetWindowRect(rect);
	mParent->ScreenToClient(rect);
	pt.x = rect.right + mGap;
	pt.y = rect.top;
}
