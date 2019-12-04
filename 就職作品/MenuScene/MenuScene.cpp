#include "MenuScene.h"
#include"../GameScene/GameScene.h"

MenuScene::MenuScene()
{
	sceneSwitchState = 1;		//1最初は明転させる

	//---------------------------------------
	//背景
	//---------------------------------------
	backTex = resourceManager->GetTexture("Menuback.jpeg", 1280, 720, NULL);
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	//---------------------------------------
	//ステージセレクトボード
	//---------------------------------------
	boardTex = resourceManager->GetTexture("StageSelect.png", 768, 540, NULL);
	D3DXMatrixTranslation(&boardMat, 370, 100, 0);

	stage1Button = new Stage1Button();
}

MenuScene::~MenuScene()
{
	delete stage1Button;
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

	RECT RcBack = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcBoard = { 0, 0, 768, 540 };
	lpSprite->SetTransform(&boardMat);
	lpSprite->Draw(boardTex, &RcBoard, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	stage1Button->Draw();

	sceneSwitchEffect->Draw();

	// 描画終了
	lpSprite->End();
}

bool MenuScene::Update(void)
{
	stage1Button->Update();
	
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (stage1Button->GetState() == true)
		{
			sceneSwitchState = -1;
			selectedStage = 1;
		}
	}

	if (sceneSwitchState == -1)
	{
		if (sceneSwitchEffect->ToDarkness() == true)			//暗転させる
		{
			sceneSwitcher.SwitchScene(new GameScene(selectedStage));
			return false;
		}
	}

	if (sceneSwitchState == 1)
	{
		if (sceneSwitchEffect->ToBrightness() == true)
		{
			sceneSwitchState = 0;
		}
	}
	return true;
}
