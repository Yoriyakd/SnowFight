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

	GetCursorPos(&Pt);					//現在のカーソルの位置をいれる
	ScreenToClient(hwnd, &Pt);		//スクリーン座標に変換

	if (Pt.x >= buttonData.Pos.x && Pt.x <= (buttonData.Pos.x + buttonData.BoxSize.x) &&		//矩形と点の当たり判定
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
