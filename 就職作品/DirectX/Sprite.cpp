#include"Sprite.h"

void Sprite::CreateSprite(void)
{
	if (lpSprite != nullptr)
	{
		return;
	}

	D3DXCreateSprite(Direct3D::GetInstance().GetD3DDevice(), &lpSprite);
	lpSprite->OnResetDevice();
}

const LPD3DXSPRITE& Sprite::GetSprite(void)
{
	return lpSprite;
}


Sprite::Sprite(void)
{
	CreateSprite();
}

Sprite::~Sprite()
{
	lpSprite->Release();
}