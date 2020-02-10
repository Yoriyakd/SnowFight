#include "GameScene.h"
#include"../MenuScene/MenuScene.h"
#include"../TitleScene/TitleScene.h"

D3DLIGHT9 Light;

const float SnowBallGravity = -0.05f;						//重力	※必ず負の値のする

GameScene::GameScene(int StageNo): isESCKye(false), Resultime(120), isSwitchResulut(false), endSceneState(false)
{
	GetResource.GetXFILE(EnemyBody_M);
	GetResource.GetXFILE(EnemyHand_M);
	GetResource.GetXFILE(EnemyHat_M);/*1度読み込むことで軽量化*/

	srand(timeGetTime());

	GetEnemyManager.Create();
	loadStageData = new LoadStageData(StageNo);
	ground = new Ground;
	
	skyBox = new SkyBox;
	GetSnowBallManager.Create();
	mapObjManager = new MapObjManager();
	GetPlayerCam.Create();
	eventManager = new EventManager();

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


	loadStageData->SetStageMap(*mapObjManager, *eventManager, *gameObjective, *stageBorder);
	
	//-------------------------------------------------------
	GetPlayerCam.SetPos(&D3DXVECTOR3(stageBorder->Right / 2, 0, 10.0f));				//プレイヤーの初期位置

	stage1Enclosure = new Stage1Enclosure(stageBorder);


	//-----------------------------
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


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

	lpD3DDevice->SetLight(0, &Light);
	lpD3DDevice->LightEnable(0, TRUE);
	//-----------------------------
	StartScene();
}

GameScene::~GameScene()
{
	delete loadStageData;
	delete ground;
	delete skyBox;
	delete stage1Enclosure;
	GetSnowBallManager.Destroy();
	delete mapObjManager;
	GetPlayerCam.Destroy();
	delete eventManager;

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
	if (resultFlag == true)
	{
		return;		//描画しない		(インスタンスを削除する方がいいんだろうか？)☆
	}
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	GetEnemyManager.Draw();
	EnemyAnime.Draw();
	GetSnowBallManager.Draw();
	Effect.Draw();
	

	GetPlayer.Draw();		//※Zバッファクリアをしているため最後に描画する
}

void GameScene::SetCamera(void)
{
	if (resultFlag == true)
	{
		resultCam->SetCamera();				//リザルト中のカメラ
		return;
	}
	GetPlayerCam.SetCamera();
}

void GameScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);
	if (resultFlag == false)		//リザルト表示中は消す
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
	else
	{
		RECT RcResult = { 0, 0, 820, 160 };
		lpSprite->SetTransform(&resultMat);
		lpSprite->Draw(resultTex, &RcResult, &D3DXVECTOR3(820 / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT RcReturn = { 0, 0, 499, 84 };
		if (Resultime <= 0)
		{
			lpSprite->SetTransform(&returnMat);
			lpSprite->Draw(returnTex, &RcReturn, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	GetBackToTitle.Draw();
	GetSceneSwitchEffect.Draw();			//常に描画

	// 描画終了
	lpSprite->End();
}

bool GameScene::Update()
{
	static bool BackToTitleFlag = false;
	if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) || BackToTitleFlag == true)
	{
		if (isESCKye == true)
		{
			BackToTitleFlag = true;
			int State;

			State = GetBackToTitle.CallBackToTitle();
			switch (State)
			{
			case -1:
				BackToTitleFlag = false;
				isESCKye = false;		//押しっぱなし対策
				break;
			case 0:
				return true;
				break;
			case 1:
				BackToTitleFlag = false;
				EndScene();
				break;
			}
		}
	}
	else
	{
		isESCKye = true;
	}

	if (endSceneState == true)
	{
		if (GetSceneSwitchEffect.GetFadeState() == STOP)		//シーン遷移が終わっていたら移行
		{
			GetSceneSwitcher.SwitchScene(new TitleScene());			//タイトルへ移行
			return false;
		}
		return true;
	}

	//---------------------------------------------------------
	//リザルト移行
	//---------------------------------------------------------
	if (isSwitchResulut == true)
	{
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			StartResult();
		}
	}

	//---------------------------------------------------------
	//リザルト中の処理
	//---------------------------------------------------------
	if (resultFlag == true)
	{
		if (ResultUpdate() == false)			//リザルト中の処理はここに記述
		{
			GetSceneSwitcher.SwitchScene(new MenuScene());
			GetSound.AllStop();
			return false;
		}
		return true;		//リザルト表示中は早期リターンして動きを止める
	}

	//----------------------------------------------------------------------------------------------------------------
	//プレイヤーの更新	※カメラ→あたり判定→プレイヤーの順番で	プレイヤーのの位置がカメラとずれるため
	//----------------------------------------------------------------------------------------------------------------
	GetPlayerCam.Update(*stageBorder);						//プレイヤーカメラの移動

	//マップオブジェとプレイヤーの当たり判定
	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		CollisionObserver::PlayertoObj(&GetPlayerCam, mapObjManager->mapObj[i]);
	}

	GetPlayer.Update(*pickUpInstructions);		//カメラを更新してから

	AddSnowBallUI::GetInstance().Update();
	//---------------------------------------------------------


	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &GetPlayerCam.GetmView());		//カメラのアップデートの後に呼ぶ

	GetEnemyManager.Update(GetSnowBallManager, *stageBorder);

	remainingBallUI->SetRemainingBallCnt(GetPlayer.GetRemainingBalls());
	GetSnowBallManager.Update();

	Effect.SetBillBoardMat(&TmpBillBoardMat);		//※effectManagerのUpdateの前に呼ぶ
	Effect.Update();
	EnemyAnime.Updata();

	GetDecorationManager.Updata();

	//雪玉と敵の当たり判定
	for (unsigned int ei = 0; ei < GetEnemyManager.enemy.size(); ei++)
	{
		for (unsigned int sj = 0; sj < GetSnowBallManager.snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoEnemyHat(GetSnowBallManager.snowBall[sj], GetEnemyManager.enemy[ei]) == true)
			{
				if (GetEnemyManager.enemy[ei]->TakeDamage(10) == false)		//falseが返ってきたら
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime作成
					//-------------------------------------------------------------
					EnemyAnime.NewEnemyDeathAnime(*GetEnemyManager.enemy[ei], *GetSnowBallManager.snowBall[sj]);
					EnemyAnime.NewEnemyHatAnime(*GetEnemyManager.enemy[ei], *GetSnowBallManager.snowBall[sj], true);

					//死んだインスタンス削除
					GetEnemyManager.DeleteEnemyInstance(ei);
					ei--;		//きえた分詰める

					//SnowFragエフェクト呼ぶ
					Effect.NewSnowFrag(GetSnowBallManager.snowBall[sj]->GetPos());

					//死んだインスタンス削除
					GetSnowBallManager.DeleteInstance(sj);
					sj--;		//きえた分詰める

					break;
				}
				
			}

			if (CollisionObserver::SnowBalltoEnemy(GetSnowBallManager.snowBall[sj], GetEnemyManager.enemy[ei]) == true)		//命中でtrueが返ってくる
			{
				if (GetEnemyManager.enemy[ei]->TakeDamage(1) == false)		//falseが返ってきたら
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime作成
					//-------------------------------------------------------------

					EnemyAnime.NewEnemyDeathAnime(*GetEnemyManager.enemy[ei], *GetSnowBallManager.snowBall[sj]);
					EnemyAnime.NewEnemyHatAnime(*GetEnemyManager.enemy[ei], *GetSnowBallManager.snowBall[sj], false);

					//死んだインスタンス削除
					GetEnemyManager.DeleteEnemyInstance(ei);
					ei--;		//きえた分詰める
				}

				//SnowFragエフェクト呼ぶ
				Effect.NewSnowFrag(GetSnowBallManager.snowBall[sj]->GetPos());

				//死んだインスタンス削除
				GetSnowBallManager.DeleteInstance(sj);
				sj--;		//きえた分詰める

				break;
			}
		}
	}

	//雪玉とマップオブジェの当たり判定

	for (unsigned int mi = 0; mi < mapObjManager->mapObj.size(); mi++)
	{
		for (unsigned int sj = 0; sj < GetSnowBallManager.snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoObj(GetSnowBallManager.snowBall[sj], mapObjManager->mapObj[mi]))		//命中でtrueが返ってくる
			{
				//SnowFragエフェクト呼ぶ
				Effect.NewSnowFrag(GetSnowBallManager.snowBall[sj]->GetPos());

				//死んだインスタンス削除
				GetSnowBallManager.DeleteInstance(sj);
				sj--;				//きえた分詰める
			}
		}
	}

	//敵の雪玉とプレイヤーのあたり判定
	for (unsigned int si = 0; si < GetSnowBallManager.snowBall.size(); si++)
	{
		if (CollisionObserver::EnemySnowBalltoPlayer(&GetPlayer, GetSnowBallManager.snowBall[si]))
		{
			//SnowFragエフェクト呼ぶ
			Effect.NewSnowFrag(GetSnowBallManager.snowBall[si]->GetPos());
			eventManager->PlayerTakeDamage();			//HIT時のメソッドを呼ぶ
			timePenaltyUI.push_back(new TimePenaltyUI(3));		//変数化

			//Soundを呼ぶ
			GetSound.Play2D(SnowBallHit_SOUND);

			//----------------------------------------------------
			//HitEffecctの処理(Effectのクラスに変数を持たせた方がいいのでは？)
			//----------------------------------------------------
			HitEffectID ActivationID;

			ActivationID = PlayerHitEffect::CalculateHitDirection(GetSnowBallManager.snowBall[si]->GetMoveVec());

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
				for (auto PlayerHitEffect_Left: playerHitEffect_Left)
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

			//----------------------------------------------------
			GetSnowBallManager.DeleteInstance(si);
			si--;						//きえた分詰める
		}
	}

	for (auto PlayerHitEffect_Right : playerHitEffect_Right)
	{
		PlayerHitEffect_Right->Update();
	}

	for (auto PlayerHitEffect_Left : playerHitEffect_Left)
	{
		PlayerHitEffect_Left->Update();
	}

	playerHitEffect_Back->Update();

	//デコレーションとMapObjの当たり判定
	for (unsigned int i = 0; i < GetDecorationManager.decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			CollisionObserver::DecorationToMapObj(GetDecorationManager.decoration[i], mapObjManager->mapObj[j], eventManager);
		}
	}

	for (unsigned int ei = 0; ei < GetEnemyManager.enemy.size(); ei++)
	{
		for (unsigned int mj = 0; mj < mapObjManager->mapObj.size(); mj++)
		{
			CollisionObserver::EnemyToMapObj(GetEnemyManager.enemy[ei], mapObjManager->mapObj[mj]);
		}
	}
	for (unsigned int i = 0; i < timePenaltyUI.size(); i++)
	{
		if (timePenaltyUI[i]->Update() == false)
		{
			delete timePenaltyUI[i];
			timePenaltyUI.erase(timePenaltyUI.begin() + i);
			i--;
		}

	}
	GetSpawnerManager.Update(*stageBorder);
	//----------------------------------------------------------------------------------------
	//イベント処理
	//----------------------------------------------------------------------------------------
	if (eventManager->Update() == false)		//falseが返ってきたらリザルトへ移行する
	{
		SwitchResulut();
	}

	//----------------------------------------------------------------------------------------
	//時間処理
	//----------------------------------------------------------------------------------------
	timeUI->SetTime_s(eventManager->GetRemainingTime_s());		//フレームを秒に直して渡している
	timeUI->Update();

	//----------------------------------------------------------------------------------------
	//ノルマ処理
	//----------------------------------------------------------------------------------------
	bool NormState;
	NormState = eventManager->GetNormState();
	if (NormState == false)
	{
		gameObjective->SetNowNormCnt(eventManager->GetNowNormCnt());
	}
	else
	{
		gameObjective->SetNormState(eventManager->GetNormState());
	}

	return true;
}

void GameScene::StartScene()
{
	GetSound.Play2D(InGameBGM_SOUND);
	GetSceneSwitchEffect.PlayFadeIn();
}

void GameScene::EndScene()
{
	GetSceneSwitchEffect.PlayFadeOut();
	GetSound.AllStop();										//サウンドを再生停止
	endSceneState = true;
}

void GameScene::SwitchResulut()
{
	GetSceneSwitchEffect.PlayFadeOut();
	isSwitchResulut = true;
}

void GameScene::StartResult(void)
{
	//敵やエフェクトなど邪魔なものを削除する
	GetEnemyManager.AllDelete();
	Effect.AllDelete();
	GetSnowBallManager.AllDelete();
	GetDecorationManager.DeleteToResult();

	resultFlag = true;
	isSwitchResulut = false;
	GetSceneSwitchEffect.PlayFadeIn();
	resultFlag = true;
	resultCam = new ResultCam();
}

void GameScene::EndResult(void)
{
	GetSceneSwitchEffect.PlayFadeOut();
	endResultState = true;
}

//この辺りは作り直しの必要あり
bool GameScene::ResultUpdate(void)
{
	resultCam->Update(&mapObjManager->GetXmasTreePos());

	Resultime--;

	if (Resultime <= 0)//一定時間入力をうけつけない
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)		//右クリックが押されるとシーン遷移
		{
			EndResult();
		}
	}

	if (endResultState == true)		//リザルト終了フラグが立っている状態でフェードが終了するとシーン遷移
	{
		if (GetSceneSwitchEffect.GetFadeState() == STOP)
		{
			return false;
		}
	}
	return true;
}
