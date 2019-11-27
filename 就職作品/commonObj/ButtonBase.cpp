#include "ButtonBase.h"

ButtonBase::ButtonBase()
{
}

void ButtonBase::Draw()
{
	RECT Rc = { 0, 0, (long)texSize.x, (long)texSize.y };
	lpSprite->SetTransform(&mat);
	lpSprite->Draw(tex, &Rc, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void ButtonBase::Update()
{
	POINT Pt;

	GetCursorPos(&Pt);					//現在のカーソルの位置をいれる
	ScreenToClient(hwnd, &Pt);		//スクリーン座標に変換

	if (Pt.x >= pos.x && Pt.x <= (pos.x + boxSize.x) &&		//矩形と点の当たり判定
		Pt.y >= pos.y && Pt.y <= (pos.y + boxSize.y))
	{
		nowStae = true;
	}
	else
	{
		nowStae = false;
	}
}

bool ButtonBase::GetState(void)
{
	return nowStae;
}
