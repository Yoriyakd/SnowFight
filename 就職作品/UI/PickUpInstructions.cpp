#include "PickUpInstructions.h"

PickUpInstructions::PickUpInstructions()
{
	tex = GetResource.GetTexture("PickUpInstructions.png", 256, 64, NULL);
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
		lpSprite->SetTransform(&mat);
		lpSprite->Draw(tex, &RcPickUpInstructions, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
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




