#include "ButtonBase.h"

ButtonBase::ButtonBase(int Stage)
{
	switch (Stage)
	{
	case 1:
		Stage1Initialize();
		break;
	case 2:
		Stage2Initialize();
	default:
		break;
	}
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

void ButtonBase::Stage1Initialize(void)
{
	tex = GetResource.GetTexture(Button_Tex);
	pos = D3DXVECTOR2(480, 190);
	texSize = D3DXVECTOR2(132, 132);
	boxSize = D3DXVECTOR2(132, 132);
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
}

void ButtonBase::Stage2Initialize(void)
{
	tex = GetResource.GetTexture(Button_Tex);
	pos = D3DXVECTOR2(620, 190);
	texSize = D3DXVECTOR2(132, 132);
	boxSize = D3DXVECTOR2(132, 132);
	D3DXMatrixTranslation(&mat, pos.x, pos.y, 0);
}
