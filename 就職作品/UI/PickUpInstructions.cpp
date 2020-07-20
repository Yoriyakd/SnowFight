#include "PickUpInstructions.h"
#include"../DirectX/Sprite.h"

PickUpInstructions::PickUpInstructions()
{
	tex = GetResource.GetTexture(PickUpInstructions_Tex);
	D3DXMatrixTranslation(&mat, 300, 500, 0);
	displayFlag = false;
}

PickUpInstructions::~PickUpInstructions()
{
}

void PickUpInstructions::Draw()
{
	if (displayFlag == true)		//ƒtƒ‰ƒO‚ªtrue‚ÌŽž‚Ì‚Ý•\Ž¦
	{
		RECT RcPickUpInstructions = { 0, 0, 256, 64 };
		Sprite::GetInstance().GetSprite()->SetTransform(&mat);
		Sprite::GetInstance().GetSprite()->Draw(tex, &RcPickUpInstructions, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void PickUpInstructions::TurnOnDisplay(void)
{
	displayFlag = true;
}

void PickUpInstructions::TurnOffDisplay(void)
{
	displayFlag = false;
}




