#include "TitleScene.h"
#include"../GameScene/GameScene.h"

TitleScene::TitleScene()
{
	logoTex = resourceManager->GetTexture("TitleLogo.png", logoTexX, 170, NULL);
	D3DXMatrixTranslation(&logoMat, SCRW / 2, 0, 0);

	backTex = resourceManager->GetTexture("BackTex.jpg", SCRW, SCRH, NULL);		//‰¼‚Ì”wŒiƒTƒCƒY‚ª‘å‚«‚·‚¬‚é
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	kyeInstructionTex = resourceManager->GetTexture("PushSpase.png", kyeInstructionX, 128, NULL);
	D3DXMatrixTranslation(&kyeInstructionMat, SCRW / 2, 500, 0);
}

TitleScene::~TitleScene()
{
}

void TitleScene::Render3D(void)
{
}

void TitleScene::SetCamera(void)
{
}

void TitleScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	ƒXƒvƒ‰ƒCƒg‚Ì•`‰æˆ—
	//////////////////////////////////////////////////
	// •`‰æŠJŽn
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT RcBack = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcLogo = { 0, 0, logoTexX, 170 };
	lpSprite->SetTransform(&logoMat);
	lpSprite->Draw(logoTex, &RcLogo, &D3DXVECTOR3((float)logoTexX / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcKyeInstruction = { 0, 0, 548, 128 };
	lpSprite->SetTransform(&kyeInstructionMat);
	lpSprite->Draw(kyeInstructionTex, &RcKyeInstruction, &D3DXVECTOR3((float)kyeInstructionX / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	// •`‰æI—¹
	lpSprite->End();
}

bool TitleScene::Update(void)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		sceneSwitcher.SwitchScene(new GameScene(1));
		return false;
	}
	return true;
}
