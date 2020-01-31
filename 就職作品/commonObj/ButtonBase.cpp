#include "ButtonBase.h"

ButtonBase::ButtonBase(void)
{
}

void ButtonBase::Draw()
{
	
}

void ButtonBase::Update()
{
	POINT Pt;

	GetCursorPos(&Pt);					//���݂̃J�[�\���̈ʒu�������
	ScreenToClient(hwnd, &Pt);		//�X�N���[�����W�ɕϊ�

	if (Pt.x >= buttonData.Pos.x && Pt.x <= (buttonData.Pos.x + buttonData.BoxSize.x) &&		//��`�Ɠ_�̓����蔻��
		Pt.y >= buttonData.Pos.y && Pt.y <= (buttonData.Pos.y + buttonData.BoxSize.y))
	{
		nowStae = true;
		OnMouseEvent();
	}
	else
	{
		nowStae = false;
		OffMouseEvent();
	}
}

bool ButtonBase::GetState(void)
{
	return nowStae;
}

void ButtonBase::OnMouseEvent(void)
{
}

void ButtonBase::OffMouseEvent(void)
{
}
