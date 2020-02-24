#include "MenuScene.h"
#include"../GameScene/GameScene.h"
#include"../TitleScene/TitleScene.h"

MenuScene::MenuScene() : endSceneState(false)
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
	//カーソル
	//---------------------------------------
	cursorTex = GetResource.GetTexture(MenuCursor_Tex);

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
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);


	RECT RcBack = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcBoard = { 0, 0, 768, 540 };
	lpSprite->SetTransform(&boardMat);
	lpSprite->Draw(boardTex, &RcBoard, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcHead = { 0, 0, 640, 64 };
	lpSprite->SetTransform(&headCharMat);
	lpSprite->Draw(headCharTex, &rcHead, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	stage1Button->Draw();
	stage2Button->Draw();


	RECT RcSantWear = { 0, 0, 360, 560 };
	lpSprite->SetTransform(&santaWearMat);
	lpSprite->Draw(SantaWearTex, &RcSantWear, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcCursor = { 0, 0, 64, 64 };
	lpSprite->SetTransform(&cursorMat);
	lpSprite->Draw(cursorTex, &RcCursor, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	GetSceneSwitchEffect.Draw();

	// 描画終了
	lpSprite->End();
}

bool MenuScene::Update(void)
{
	if (endSceneState == true)
	{
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			GetSceneSwitcher.SwitchScene(new GameScene(selectedStage));
			return false;		//このfalse返すのシーン遷移とセットやからスマートにかけないだろうか☆
		}
		return true;		//シーン遷移状態なら早期リターン
	}

	stage1Button->Update();
	stage2Button->Update();

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		GetSceneSwitcher.SwitchScene(new TitleScene());				//エフェクトと確認を入れる☆
		return false;
	}
	

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (stage1Button->GetState() == true)
		{
			GetSound.Play2D(Success_Sound);
			EndScene();
			selectedStage = 1;
		}

		if (stage2Button->GetState() == true)
		{
			GetSound.Play2D(Success_Sound);
			EndScene();
			selectedStage = 2;
		}
	}

	//--------------------------------------------
	//カーソル移動
	//--------------------------------------------
	POINT Pt;

	GetCursorPos(&Pt);					//現在のカーソルの位置をいれる
	ScreenToClient(hwnd, &Pt);		//スクリーン座標に変換

	D3DXMatrixTranslation(&cursorMat, (float)Pt.x, (float)Pt.y, 0);

	return true;
}

void MenuScene::BeginScene(void)
{
	GetSceneSwitchEffect.PlayFadeIn();
}

void MenuScene::EndScene(void)
{
	GetSceneSwitchEffect.PlayFadeOut();
	endSceneState = true;
}
