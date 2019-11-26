#include "MenuScene.h"
#include"../GameScene/GameScene.h"

MenuScene::MenuScene()
{
	sceneSwitchEffectAlpha = 255;
	switchEffectTex = resourceManager->GetTexture("SceneSwitchEffect.png", 32, 32, NULL);
	D3DXMatrixTranslation(&switchEffectMat, 0, 0, 0);

	RightArrowPos = D3DXVECTOR3(10, SCRH / 2, 0);
	LeftArrowPos = D3DXVECTOR3(1270, SCRH / 2, 0);
}

MenuScene::~MenuScene()
{
}

void MenuScene::Render3D(void)
{
}

void MenuScene::SetCamera(void)
{
}

void MenuScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT RCRightArrow = {};

	RECT RcSwitchEffect = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&switchEffectMat);
	lpSprite->Draw(switchEffectTex, &RcSwitchEffect, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(sceneSwitchEffectAlpha, 255, 255, 255));


	// 描画終了
	lpSprite->End();
}

bool MenuScene::Update(void)
{
	sceneSwitchEffectAlpha -= 20;
	if (sceneSwitchEffectAlpha < 0)
	{
		sceneSwitchEffectAlpha = 0;
	}



	stageSelectFlag = true;
	if (stageSelectFlag == true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			sceneSwitcher.SwitchScene(new GameScene(1));
			return false;
		}
	}
	return true;
}
