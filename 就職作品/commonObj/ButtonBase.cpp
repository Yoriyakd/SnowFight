#include "ButtonBase.h"

void ButtonBase::Draw()
{
	RECT Rc = { 0, 0, size.x, size.y };
	lpSprite->SetTransform(&mat);
	lpSprite->Draw(tex, &Rc, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

bool ButtonBase::CheckState(void)
{
	POINT Pt;

	GetCursorPos(&Pt);					//���݂̃J�[�\���̈ʒu�������

	if (Pt.x >= pos.x && Pt.x <= (pos.x + size.x) &&		//��`�Ɠ_�̓����蔻��
		Pt.y >= pos.y && Pt.y <= (pos.y + size.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}
