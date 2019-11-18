#include "TitleScene.h"
#include"../GameScene/GameScene.h"

TitleScene::TitleScene()
{
	logoTex = resourceManager->GetTexture("TitleLogo.png", logoTexX, 170, NULL);
	D3DXMatrixTranslation(&logoMat, SCRW / 2, 0, 0);

	backTex = resourceManager->GetTexture("BackTex.jpg", SCRW, SCRH, NULL);		//仮の背景サイズが大きすぎる
	D3DXMatrixTranslation(&backMat, 0, 0, 0);
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
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rcBack = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &rcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcLogo = { 0, 0, logoTexX, 170 };
	lpSprite->SetTransform(&logoMat);
	lpSprite->Draw(logoTex, &rcLogo, &D3DXVECTOR3((float)logoTexX / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	// 描画終了
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
