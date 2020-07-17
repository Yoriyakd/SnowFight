#include "Cursor.h"
#include"../Window/Window.h"

void Cursor::Draw()
{
	if (isShow == false)return;

	lpSprite->SetTransform(&cursorMat);
	lpSprite->Draw(cursorTex, &RcCursor, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Cursor::Update()
{
	if (isShow == false)return;
	
	POINT Pt;

	GetCursorPos(&Pt);					//現在のカーソルの位置をいれる
	ScreenToClient(Window::GetInstance().GetHWND(), &Pt);		//スクリーン座標に変換

	D3DXMatrixTranslation(&cursorMat, (float)Pt.x, (float)Pt.y, 0);
}

void Cursor::ShowCursor(bool State)
{
	isShow = State;
}

Cursor::Cursor()
{
	cursorTex = GetResource.GetTexture(MenuCursor_Tex);
}

Cursor::~Cursor()
{
}
