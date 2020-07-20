#include "MenuScene.h"
#include"../GameScene/GameScene.h"
#include"../TitleScene/TitleScene.h"
#include"../DirectX/Sprite.h"

MenuScene::MenuScene()
{
	//---------------------------------------
	//背景
	//---------------------------------------
	backTex = GetResource.GetTexture(MenuBack_Tex);
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	//---------------------------------------
	//ステージセレクトボード
	//---------------------------------------
	boardTex = GetResource.GetTexture(MenuBoard_Tex);
	D3DXMatrixTranslation(&boardMat, 370, 100, 0);

	//---------------------------------------
	//ステージセレクト文字
	//---------------------------------------
	headCharTex = GetResource.GetTexture(MenuHeadChar_Tex);
	D3DXMatrixTranslation(&headCharMat, 430, 100, 0);

	//---------------------------------------
	//サンタ服
	//---------------------------------------
	SantaWearTex = GetResource.GetTexture(SantaWear_Tex);
	D3DXMatrixTranslation(&santaWearMat, 20, 100, 0);

	stage1Button = new StageSelectButton();
	stage1Button->Stage1Initialize();		//とりあえずこれで(CSVとかから読み込むように変更する☆)

	stage2Button = new StageSelectButton();
	stage2Button->Stage2Initialize();

	BeginScene();

}

MenuScene::~MenuScene()
{
	delete stage1Button;
	delete stage2Button;	
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
	Sprite::GetInstance().GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);


	RECT RcBack = { 0, 0, SCRW, SCRH };
	Sprite::GetInstance().GetSprite()->SetTransform(&backMat);
	Sprite::GetInstance().GetSprite()->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcBoard = { 0, 0, 768, 540 };
	Sprite::GetInstance().GetSprite()->SetTransform(&boardMat);
	Sprite::GetInstance().GetSprite()->Draw(boardTex, &RcBoard, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcHead = { 0, 0, 640, 64 };
	Sprite::GetInstance().GetSprite()->SetTransform(&headCharMat);
	Sprite::GetInstance().GetSprite()->Draw(headCharTex, &rcHead, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	stage1Button->Draw();
	stage2Button->Draw();


	RECT RcSantWear = { 0, 0, 360, 560 };
	Sprite::GetInstance().GetSprite()->SetTransform(&santaWearMat);
	Sprite::GetInstance().GetSprite()->Draw(SantaWearTex, &RcSantWear, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	GetCursor.Draw();

	GetBackToTitle.Draw();
	GetSceneSwitchEffect.Draw();

	// 描画終了
	Sprite::GetInstance().GetSprite()->End();
}

bool MenuScene::Update(void)
{
	//-------------------------------------------------------------------
	//タイトルに戻る前の確認		☆一つのモジュールにする
	//-------------------------------------------------------------------
	if (BackToTitle() == true)return true;		//動作中は早期リターン


	switch (nowState)
	{
	case GAME_START:
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			GetSceneSwitcher.SwitchScene(new GameScene(selectedStage));
			return false;		//このfalse返すのシーン遷移とセットやからスマートにかけないだろうか ☆
		}
		return true;		//シーン遷移状態なら早期リターン

		break;
	case BACK_TO_TITLE_MENU:
		if (GetSceneSwitchEffect.GetFadeState() == STOP)		//シーン遷移が終わっていたら移行
		{
			GetSceneSwitcher.SwitchScene(new TitleScene());			//タイトルへ移行
			return false;
		}
		return true;
		break;
	default:
		break;
	}

	stage1Button->Update();
	stage2Button->Update();

	

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (stage1Button->GetState() == true)
		{
			GetSound.Play2D(Success_Sound);
			EndScene();
			selectedStage = 1;
			nowState = GAME_START;
		}

		if (stage2Button->GetState() == true)
		{
			GetSound.Play2D(Success_Sound);
			EndScene();
			selectedStage = 2;
			nowState = GAME_START;
		}
	}

	return true;
}

void MenuScene::BeginScene(void)
{
	GetSceneSwitchEffect.PlayFadeIn();
	GetCursor.ShowCursor(true);
	GetSound.Play2D(MenuBGM_Sound);
	nowState = IN_MENU;
}

void MenuScene::EndScene(void)
{
	GetSceneSwitchEffect.PlayFadeOut();
	GetCursor.ShowCursor(false);
	GetSound.Stop(MenuBGM_Sound);
}


bool MenuScene::BackToTitle(void)
{
	RETURN_STATE GameSceneState;
	GameSceneState = GetBackToTitle.CallBackToTitle();

	if (GameSceneState == WAITING_INPUT)return true;
	if (GameSceneState == RETURN_TITLE)
	{
		nowState = BACK_TO_TITLE_MENU;
		EndScene();
		return false;
	}

	if (GameSceneState == NOT_ACTIVE)return false;
	if (GameSceneState == CANCEL)return false;			//☆解除後カメラが移動するのを何とかする

	return false;
}
