#include "GameScene.h"
#include"../MenuScene/MenuScene.h"
#include"../TitleScene/TitleScene.h"
#include"../DirectX/Direct3D.h"
#include"../DirectX/Sprite.h"
#include <algorithm>

D3DLIGHT9 Light;

const float SnowBallGravity = -0.05f;						//重力	※必ず負の値のする

GameScene::GameScene(int StageNo):ResulCnt(120)
{
	GetResource.GetXFILE(EnemyBody_M);
	GetResource.GetXFILE(EnemyHand_M);
	GetResource.GetXFILE(EnemyHat_M);
	GetResource.GetXFILE(Decoration_BlueBall_M);
	GetResource.GetXFILE(Decoration_RedBall_M);
	GetResource.GetXFILE(Decoration_YellowBall_M);/*1度読み込むことで軽量化*/

	srand(timeGetTime());
	GameNorm.Create();
	GetEnemyManager.Create();
	loadStageData = new LoadStageData(StageNo);
	ground = new Ground;
	
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	GetPlayerCam.Create();
	

	GetPlayer.Create();
	
	GetDecorationManager.Create();
	GetSpawnerManager.Create();

	for (auto i = 0; i < EFFECT_CNT; i++)
	{
		playerHitEffect_Right[i] = new PlayerHitEffect();
		playerHitEffect_Right[i]->Initialize_RightEffect();
	}

	for (auto i = 0; i < EFFECT_CNT; i++)
	{
		playerHitEffect_Left[i] = new PlayerHitEffect();
		playerHitEffect_Left[i]->Initialize_LeftEffect();
	}

	playerHitEffect_Back = new PlayerHitEffect();
	playerHitEffect_Back->Initialize_BackEffect();

	stageBorder = new StageBorder;
	EnemyAnime.Create();
	//-------------------------------------------------------
	//UI
	//-------------------------------------------------------
	pickUpInstructions = new PickUpInstructions();
	remainingBallUI = new RemainingBallUI();
	timeUI = new TimeUI();
	gameObjective = new GameObjective();
	AddSnowBallUI::GetInstance().Create();

	//-------------------------------------------------------
	//リザルト
	//-------------------------------------------------------
	resultTex = GetResource.GetTexture(ResultHead_Tex);
	D3DXMatrixTranslation(&resultMat, SCRW / 2, 10, 0);

	returnTex = GetResource.GetTexture(ResultReturn_Tex);
	D3DXMatrixTranslation(&returnMat, 800, 500, 0);


	loadStageData->SetStageMap(*mapObjManager, GameNorm, *gameObjective, *stageBorder);
	
	//-------------------------------------------------------
	GetPlayerCam.SetPos(&D3DXVECTOR3(stageBorder->Right / 2, 0, 10.0f));				//プレイヤーの初期位置

	stage1Enclosure = new Stage1Enclosure(stageBorder);


	//-----------------------------
	Direct3D::GetInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);


	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	Light.Diffuse.a = 1.0f;
	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;

	Light.Specular.a = 0.8f;
	Light.Specular.r = 0.8f;
	Light.Specular.g = 0.8f;
	Light.Specular.b = 0.8f;

	Light.Ambient.r = 0.3f;
	Light.Ambient.g = 0.3f;
	Light.Ambient.b = 0.3f;

	Light.Range = 1000.0f;

	Direct3D::GetInstance().GetD3DDevice()->SetLight(0, &Light);
	Direct3D::GetInstance().GetD3DDevice()->LightEnable(0, TRUE);
	//-----------------------------
	BeginScene();
}

GameScene::~GameScene()
{
	delete loadStageData;
	delete ground;
	delete skyBox;
	delete stage1Enclosure;
	GameNorm.Destroy();
	delete snowBallManager;
	delete mapObjManager;
	GetPlayerCam.Destroy();

	GetPlayer.Destroy();
	GetEnemyManager.Destroy();

	delete resultCam;

	for (auto PlayerHitEffect_Right : playerHitEffect_Right)
	{
		delete PlayerHitEffect_Right;
		
	}

	for (auto PlayerHitEffect_Left : playerHitEffect_Left)
	{
		delete PlayerHitEffect_Left;
	}

	delete playerHitEffect_Back;

	delete stageBorder;

	GetDecorationManager.Destroy();
	GetSpawnerManager.Destroy();
	EnemyAnime.Destroy();
	//-------------------------------------------------------
	//UI
	//-------------------------------------------------------
	delete pickUpInstructions;
	delete remainingBallUI;
	delete timeUI;
	delete gameObjective;
	AddSnowBallUI::GetInstance().Destroy();
}

void GameScene::Render3D(void)
{
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	skyBox->Draw();
	ground->Draw();
	stage1Enclosure->Draw();
	mapObjManager->Draw();

	GetDecorationManager.Draw();
	if (nowState== IN_RESULT)
	{
		return;		//描画しない		(インスタンスを削除する方がいいんだろうか？)☆
	}
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	if (nowState == IN_GAME)
	{
		GetEnemyManager.Draw();
		EnemyAnime.Draw();
		snowBallManager->Draw();
		Effect.Draw();

		GetPlayer.Draw();		//※Zバッファクリアをしているため最後に描画する
	}
}

void GameScene::SetCamera(void)
{
	if (nowState == IN_RESULT)
	{
		resultCam->SetCamera();				//リザルト中のカメラ
		return;
	}

	if (nowState == IN_GAME)
	{
		GetPlayerCam.SetCamera();
	}

}

void GameScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	Sprite::GetInstance().GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	if (nowState == IN_GAME)		//リザルト表示中は消す
	{
		for (auto PlayerHitEffect_Right : playerHitEffect_Right)
		{
			PlayerHitEffect_Right->Draw();
		}

		for (auto PlayerHitEffect_Left : playerHitEffect_Left)
		{
			PlayerHitEffect_Left->Draw();
		}

		playerHitEffect_Back->Draw();

		pickUpInstructions->Draw();
		remainingBallUI->Draw();
		timeUI->Draw();
		for (auto *TimePenaltyUI : timePenaltyUI)
		{
			TimePenaltyUI->Draw();
		}
		gameObjective->Draw();

		AddSnowBallUI::GetInstance().Draw();
	}
	if (nowState == IN_RESULT)
	{
		RECT RcResult = { 0, 0, 820, 160 };
		Sprite::GetInstance().GetSprite()->SetTransform(&resultMat);
		Sprite::GetInstance().GetSprite()->Draw(resultTex, &RcResult, &D3DXVECTOR3(820 / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT RcReturn = { 0, 0, 499, 84 };
		if (ResulCnt <= 0)
		{
			Sprite::GetInstance().GetSprite()->SetTransform(&returnMat);
			Sprite::GetInstance().GetSprite()->Draw(returnTex, &RcReturn, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	GetBackToTitle.Draw();
	GetSceneSwitchEffect.Draw();			//常に描画

	// 描画終了
	Sprite::GetInstance().GetSprite()->End();
}

bool GameScene::Update()
{
	//-------------------------------------------------------------------
	//タイトルに戻る前の確認		☆一つのモジュールにする
	//-------------------------------------------------------------------
	if (BackToTitle() == true)return true;		//動作中は早期リターン


	//------------------------------------------------------
	//とりあえず実装
	//------------------------------------------------------
	switch (nowState)
	{
	case IN_GAME:
		break;
	case SWITCH_RESULT:

		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			BeginResult();
		}
		return true;
		break;

	case IN_RESULT:
		ResultUpdate();
		break;

	case END_RESULT:
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			GetSceneSwitcher.SwitchScene(new MenuScene());
			GetSound.Stop(InGameBGM_Sound);
			return false;
		}
		return true;
		break;

	case TIME_UP_EFFECT:
		break;

	case BACK_TO_TITLE_GAME:
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

	if (addUpdate != nullptr)
	{
		GameSceneState NextState;
		NextState = addUpdate->AddUpdate();

		if (NextState != nowState)
		{
			delete addUpdate;
			addUpdate = nullptr;

			switch (NextState)
			{
			case IN_GAME:
				break;
			case SWITCH_RESULT:		//リザルト移行
				SwitchResult();
				break;
			case IN_RESULT:			//リザルト中の処理
				BeginResult();
				break;
			case END_RESULT:
				
				break;
			case TIME_UP_EFFECT:	//終了時の演出再生
				BeginTimeUpEffect();
				break;
			default:
				break;
			}
		}
	}

	//------------------------------------------------------
	//とりあえず実装ここまで
	//------------------------------------------------------

	Collision();

	//----------------------------------------------------------------------------------------------------------------
	//プレイヤーの更新	※カメラ→あたり判定→プレイヤーの順番で	プレイヤーのの位置がカメラとずれるため
	//----------------------------------------------------------------------------------------------------------------
	GetPlayerCam.Update(*stageBorder);						//プレイヤーカメラの移動

	//マップオブジェとプレイヤーの当たり判定
	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		CollisionObserver::PlayertoObj(&GetPlayerCam, mapObjManager->mapObj[i]);
	}

	GetPlayer.Update(*pickUpInstructions, this);		//カメラを更新してから

	AddSnowBallUI::GetInstance().Update();
	//---------------------------------------------------------


	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &GetPlayerCam.GetmView());		//カメラのアップデートの後に呼ぶ

	GetEnemyManager.Update(this);

	remainingBallUI->SetRemainingBallCnt(GetPlayer.GetRemainingBalls());
	snowBallManager->Update();

	Effect.SetBillBoardMat(&TmpBillBoardMat);		//※effectManagerのUpdateの前に呼ぶ
	Effect.Update();
	EnemyAnime.Updata();

	GetDecorationManager.Updata();

	

	//--------------------------------------------------------
	//HitEffect
	//--------------------------------------------------------

	for (auto PlayerHitEffect_Right : playerHitEffect_Right)
	{
		PlayerHitEffect_Right->Update();
	}

	for (auto PlayerHitEffect_Left : playerHitEffect_Left)
	{
		PlayerHitEffect_Left->Update();
	}

	playerHitEffect_Back->Update();

	GetSpawnerManager.Update(*stageBorder);

	//----------------------------------------------------------------------------------------
	//時間処理
	//----------------------------------------------------------------------------------------
	for (unsigned int i = 0; i < timePenaltyUI.size(); i++)
	{
		if (timePenaltyUI[i]->Update() == false)
		{
			delete timePenaltyUI[i];
			timePenaltyUI.erase(timePenaltyUI.begin() + i);
			i--;
		}
	}
	//timeUI->SetTime_s(GameNormManager->GetRemainingTime_s());		//フレームを秒に直して渡している
	timeUI->SetTime_s(GameTime::GetRemainingTime_s());		//フレームを秒に直して渡している
	timeUI->Update();

	//----------------------------------------------------------------------------------------
	//ノルマ処理
	//----------------------------------------------------------------------------------------
	bool NormState;
	NormState = GameNorm.GetNormState();
	if (NormState == false)
	{
		gameObjective->SetNowNormCnt(GameNorm.GetNowNormCnt());		//現在の数を渡す
	}
	else
	{
		gameObjective->SetNormState(GameNorm.GetNormState());			//現在のノルマ状況を渡す		//☆改善の余地あり
	}

	return true;
}

SnowBallManager& GameScene::GetSnowBallManager()
{
	return *snowBallManager;
}

StageBorder& GameScene::GetStageBorder()
{
	return *stageBorder;
}

void GameScene::BeginScene()
{
	nowState = IN_GAME;
	addUpdate = new GameTime();
	GetSound.Play2D(InGameBGM_Sound);
	GetSceneSwitchEffect.PlayFadeIn();
}

void GameScene::EndScene()
{
	nowState = BACK_TO_TITLE_GAME;
	GetSceneSwitchEffect.PlayFadeOut();
	GetSound.Stop(InGameBGM_Sound);										//サウンドを再生停止
	GetSound.Stop(Clock_Sound);										//サウンドを再生停止(移行時に止めるサウンドをまとめた関数作成)
}

void GameScene::Collision()
{
	//雪玉と敵の当たり判定
	for (unsigned int ei = 0; ei < GetEnemyManager.enemy.size(); ei++)
	{
		for (unsigned int sj = 0; sj < snowBallManager->snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoEnemyHat(snowBallManager->snowBall[sj], GetEnemyManager.enemy[ei]) == true)
			{
				if (GetEnemyManager.enemy[ei]->TakeDamage(10) == false)		//falseが返ってきたら
				{
					//-------------------------------------------------------------
					//HeadShoot用サウンド再生
					//-------------------------------------------------------------
					GetSound.Play2D(HeadShoot_Sound);
					//-------------------------------------------------------------
					//EnemyDeathAnime作成
					//-------------------------------------------------------------
					EnemyAnime.NewEnemyDeathAnime(*GetEnemyManager.enemy[ei], *snowBallManager->snowBall[sj]);
					EnemyAnime.NewEnemyHatAnime(*GetEnemyManager.enemy[ei], *snowBallManager->snowBall[sj], true);

					//死んだインスタンス削除
					GetEnemyManager.DeleteEnemyInstance(ei);
					ei--;		//きえた分詰める

					//SnowFragエフェクト呼ぶ
					Effect.NewSnowFrag(snowBallManager->snowBall[sj]->GetPos());

					//死んだインスタンス削除
					snowBallManager->DeleteInstance(sj);
					sj--;		//きえた分詰める

					break;
				}

			}

			if (CollisionObserver::SnowBalltoEnemy(snowBallManager->snowBall[sj], GetEnemyManager.enemy[ei]) == true)		//命中でtrueが返ってくる
			{
				if (GetEnemyManager.enemy[ei]->TakeDamage(1) == false)		//falseが返ってきたら
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime作成
					//-------------------------------------------------------------

					EnemyAnime.NewEnemyDeathAnime(*GetEnemyManager.enemy[ei], *snowBallManager->snowBall[sj]);
					EnemyAnime.NewEnemyHatAnime(*GetEnemyManager.enemy[ei], *snowBallManager->snowBall[sj], false);

					//死んだインスタンス削除
					GetEnemyManager.DeleteEnemyInstance(ei);
					ei--;		//きえた分詰める
				}

				GetSound.Play2D(Damage_Sound);

				//SnowFragエフェクト呼ぶ
				Effect.NewSnowFrag(snowBallManager->snowBall[sj]->GetPos());

				//死んだインスタンス削除
				snowBallManager->DeleteInstance(sj);
				sj--;		//きえた分詰める

				break;
			}
		}
	}

	//雪玉とマップオブジェの当たり判定

	for (unsigned int mi = 0; mi < mapObjManager->mapObj.size(); mi++)
	{
		for (unsigned int sj = 0; sj < snowBallManager->snowBall.size(); sj++)
			if (CollisionObserver::SnowBalltoObj(snowBallManager->snowBall[sj], mapObjManager->mapObj[mi]))		//命中でtrueが返ってくる
			{
				//SnowFragエフェクト呼ぶ
				Effect.NewSnowFrag(snowBallManager->snowBall[sj]->GetPos());

				//サウンド
				GetSound.Play2D(SnowBallBreak_Sound);

				//死んだインスタンス削除
				snowBallManager->DeleteInstance(sj);
				sj--;
			}
	}

	//敵の雪玉とプレイヤーのあたり判定
	for (unsigned int si = 0; si < snowBallManager->snowBall.size(); si++)
	{
		if (CollisionObserver::EnemySnowBalltoPlayer(&GetPlayer, snowBallManager->snowBall[si]))
		{
			//SnowFragエフェクト呼ぶ
			Effect.NewSnowFrag(snowBallManager->snowBall[si]->GetPos());

			//サウンド
			GetSound.Play2D(Damage_Sound);

			//GameNormManager->PlayerTakeDamage();			//HIT時のメソッドを呼ぶ
			GameTime::PlayerTakeDamage(3);
			timePenaltyUI.push_back(new TimePenaltyUI(3));		//変数化

			//----------------------------------------------------
			//HitEffecctの処理(Effectのクラスに変数を持たせた方がいいのでは？)
			//----------------------------------------------------
			HitEffectID ActivationID;

			ActivationID = PlayerHitEffect::CalculateHitDirection(snowBallManager->snowBall[si]->GetMoveVec());

			switch (ActivationID)
			{
			case Right:
				for (auto PlayerHitEffect_Right : playerHitEffect_Right)
				{
					if (PlayerHitEffect_Right->GetActiveState() == false)
					{
						PlayerHitEffect_Right->Active();
						break;
					}
				}
				break;
			case Left:
				for (auto PlayerHitEffect_Left : playerHitEffect_Left)
				{
					if (PlayerHitEffect_Left->GetActiveState() == false)
					{
						PlayerHitEffect_Left->Active();
						break;
					}
				}
				break;
			case Back:
				playerHitEffect_Back->Active();
				break;
			}

			snowBallManager->DeleteInstance(si);
			si--;						//きえた分詰める
		}
	}

	//デコレーションとMapObjの当たり判定
	for (unsigned int i = 0; i < GetDecorationManager.decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			CollisionObserver::DecorationToMapObj(GetDecorationManager.decoration[i], mapObjManager->mapObj[j]);
		}
	}

	//敵とMapObjの判定
	for (unsigned int ei = 0; ei < GetEnemyManager.enemy.size(); ei++)
	{
		for (unsigned int mj = 0; mj < mapObjManager->mapObj.size(); mj++)
		{
			CollisionObserver::EnemyToMapObj(GetEnemyManager.enemy[ei], mapObjManager->mapObj[mj]);
		}
	}
}

void GameScene::SwitchResult()
{
	nowState = SWITCH_RESULT;
	GetSceneSwitchEffect.PlayFadeOut();
}

void GameScene::BeginResult(void)
{
	nowState = IN_RESULT;
	//敵やエフェクトなど邪魔なものを削除する
	GetEnemyManager.AllDelete();
	Effect.AllDelete();
	snowBallManager->AllDelete();
	GetDecorationManager.DeleteToResult();

	GetSceneSwitchEffect.PlayFadeIn();
	resultCam = new ResultCam();
}

void GameScene::EndResult(void)
{
	nowState = END_RESULT;
	GetSceneSwitchEffect.PlayFadeOut();
}

//この辺りはリファクタリングの必要あり
bool GameScene::ResultUpdate(void)
{
	resultCam->Update(&mapObjManager->GetXmasTreePos());

	ResulCnt--;

	if (ResulCnt <= 0)//一定時間入力をうけつけない
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)		//右クリックが押されるとシーン遷移
		{
			GetSound.Play2D(Success_Sound);
			EndResult();
		}
	}
	return true;
}

bool GameScene::BackToTitle(void)
{
	RETURN_STATE GameSceneState;
	GameSceneState = GetBackToTitle.CallBackToTitle();

	if (GameSceneState == WAITING_INPUT)return true;
	if (GameSceneState == RETURN_TITLE)
	{
		EndScene();
		return false;
	}

	if (GameSceneState == NOT_ACTIVE)return false;
	if (GameSceneState == CANCEL)
	{
		PlayerStateIdle::LimitKeepPushShootKey();
		return false;			//☆解除後カメラが移動するのを何とかする
	}
	
	return false;
}

void GameScene::BeginTimeUpEffect()
{
	nowState = TIME_UP_EFFECT;
	GetSound.Stop(Clock_Sound);
	GetSound.Play2D(EndWhistle_Sound);
	addUpdate = new TimeUpEffect();
}
