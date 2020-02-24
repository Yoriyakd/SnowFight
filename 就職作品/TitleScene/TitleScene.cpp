#include "TitleScene.h"
#include"../GameScene/GameScene.h"
#include"../MenuScene/MenuScene.h"

TitleScene::TitleScene():ESCFlag(false)
{
	logoTex = GetResource.GetTexture(TitleLogo_Tex);
	D3DXMatrixTranslation(&logoMat, SCRW / 2, 0, 0);

	backTex = GetResource.GetTexture(TitleBack_Tex);
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	kyeInstructionTex = GetResource.GetTexture(TitleInstructions_Tex);
	D3DXMatrixTranslation(&kyeInstructionMat, SCRW / 2, 500, 0);

	BeginScene();		//シーン開始時1度呼ぶ
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

	RECT RcBack = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcLogo = { 0, 0, logoTexX, 170 };
	lpSprite->SetTransform(&logoMat);
	lpSprite->Draw(logoTex, &RcLogo, &D3DXVECTOR3((float)logoTexX / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcKyeInstruction = { 0, 0, kyeInstructionX, 116 };
	lpSprite->SetTransform(&kyeInstructionMat);
	lpSprite->Draw(kyeInstructionTex, &RcKyeInstruction, &D3DXVECTOR3((float)kyeInstructionX / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	GetSceneSwitchEffect.Draw();


	// 描画終了
	lpSprite->End();
}

bool TitleScene::Update(void)
{
	if (endSceneState == true)
	{
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			GetSceneSwitcher.SwitchScene(new MenuScene());
			return false;
		}
		return true;
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (ESCFlag == true)
		{
			PostQuitMessage(0);		//終了する
			return false;
		}
	}
	else
	{
		ESCFlag = true;
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000 || GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (isClick == true)
		{
			GetSound.Play2D(Success_Sound);
			EndScene();
		}
	}
	else
	{
		isClick = true;		//クリックできる
	}
	return true;
}

void TitleScene::BeginScene(void)
{
	GetSceneSwitchEffect.PlayFadeIn();		//明るくする
}

void TitleScene::EndScene(void)
{
	GetSceneSwitchEffect.PlayFadeOut();		//暗くする
	endSceneState = true;
}
