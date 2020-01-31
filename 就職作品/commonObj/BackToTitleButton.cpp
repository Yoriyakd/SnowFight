#include "BackToTitleButton.h"

void BackToTitleButton::Draw()
{
	RECT RECT = { 0, 0, 132, 132 };
	lpSprite->SetTransform(&mat);
	lpSprite->Draw(tex, &RECT, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void BackToTitleButton::Initialize(ButtonData& _ButtonData, LPDIRECT3DTEXTURE9 _Tex)
{
	tex = _Tex;
	buttonData = _ButtonData;
	D3DXMatrixTranslation(&mat, buttonData.Pos.x, buttonData.Pos.y, 0);
}
