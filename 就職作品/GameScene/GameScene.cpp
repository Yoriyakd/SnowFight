#include "GameScene.h"
#include"../MenuScene/MenuScene.h"

D3DLIGHT9 Light;

const float SnowBallGravity = -0.05f;						//重力	※必ず負の値のする

GameScene::GameScene(int StageNo)
{
	srand(timeGetTime());
	sceneSwitchState = 1;		//最初は明転させる

	GetEnemyManager.Create();
	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	playerCam = new PlayerCamera();
	eventManager = new EventManager();
	
	GetDecorationManager.Create();
	GetSpawnerManager.Create();

	stageBorder = new StageBorder;
	EnemyAnime.Create();
	//-------------------------------------------------------
	//UI
	//-------------------------------------------------------
	pickUpInstructions = new PickUpInstructions();
	remainingBallUI = new RemainingBallUI();
	timeUI = new TimeUI();
	gameObjective = new GameObjective();

	//-------------------------------------------------------
	//リザルト
	//-------------------------------------------------------
	resultTex = GetResource.GetTexture(ResultHead_Tex);
	D3DXMatrixTranslation(&resultMat, SCRW / 2, 10, 0);

	returnTex = GetResource.GetTexture(ResultReturn_Tex);
	D3DXMatrixTranslation(&returnMat, 800, 500, 0);


	loadStageData->SetStageMap(*mapObjManager, *eventManager, *gameObjective, *stageBorder);
	
	//-------------------------------------------------------
	playerCam->SetPos(&D3DXVECTOR3(stageBorder->Right / 2, 0, 10.0f));				//プレイヤーの初期位置

	stage1Enclosure = new Stage1Enclosure(stageBorder);

	player->SetPlayerCamPointer(playerCam);		//プレイヤーカメラのポインタをセット

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
}

GameScene::~GameScene()
{
	delete loadStageData;
	delete ground;
	delete skyBox;
	delete stage1Enclosure;
	delete snowBallManager;
	delete mapObjManager;
	delete playerCam;
	delete eventManager;

	delete player;
	GetEnemyManager.Destroy();

	delete resultCam;

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
	snowBallManager->Draw();
	Effect.Draw();
	

	player->Draw();		//※Zバッファクリアをしているため最後に描画する
}

void GameScene::SetCamera(void)
{
	if (resultFlag == true)
	{
		resultCam->SetCamera();				//リザルト中のカメラ
		return;
	}
	playerCam->SetCamera();
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
		pickUpInstructions->Draw();
		remainingBallUI->Draw();
		timeUI->Draw();
		gameObjective->Draw();
	}
	else
	{
		RECT RcResult = { 0, 0, 820, 160 };
		lpSprite->SetTransform(&resultMat);
		lpSprite->Draw(resultTex, &RcResult, &D3DXVECTOR3(820 / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT RcReturn = { 0, 0, 420, 40 };
		lpSprite->SetTransform(&returnMat);
		lpSprite->Draw(returnTex, &RcResult, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	SceneSwitch.Draw();			//常に描画

	// 描画終了
	lpSprite->End();
}

bool GameScene::Update()
{
	//---------------------------------------------------------
	//リザルト中の処理
	//---------------------------------------------------------
	if (resultFlag == true)
	{
		if (ResultUpdate() == false)			//リザルト中の処理はここに記述
		{
			SwitcheScene.SwitchScene(new MenuScene());
			return false;
		}
		return true;		//リザルト表示中は早期リターンして動きを止める
	}


	if (sceneSwitchState == 1)				//初めに明転させる処理
	{
		if (SceneSwitch.ToBrightness() == true)
		{
			sceneSwitchState = 0;
		}
	}
	//----------------------------------------------------------------------------------------------------------------
	//プレイヤーの更新	※カメラ→あたり判定→プレイヤーの順番で	プレイヤーのの位置がカメラとずれるため
	//----------------------------------------------------------------------------------------------------------------
	playerCam->Update(*stageBorder);						//プレイヤーカメラの移動

	//マップオブジェとプレイヤーの当たり判定
	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		CollisionObserver::PlayertoObj(playerCam, mapObjManager->mapObj[i]);
	}

	player->Update(*snowBallManager, GetDecorationManager, *pickUpInstructions);		//カメラを更新してから
	//---------------------------------------------------------


	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &playerCam->GetmView());		//カメラのアップデートの後に呼ぶ

	GetEnemyManager.Update(*player, *snowBallManager, *stageBorder);

	remainingBallUI->SetRemainingBallCnt(player->GetRemainingBalls());
	//remainingBallUI->SetRemainingBallCnt(player->GetHP());		//HP確認用☆
	snowBallManager->Update();

	Effect.SetBillBoardMat(&TmpBillBoardMat);		//※effectManagerのUpdateの前に呼ぶ
	Effect.Update();
	EnemyAnime.Updata();

	GetDecorationManager.Updata();

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
		{
			if (CollisionObserver::SnowBalltoObj(snowBallManager->snowBall[sj], mapObjManager->mapObj[mi]))		//命中でtrueが返ってくる
			{
				//SnowFragエフェクト呼ぶ
				Effect.NewSnowFrag(snowBallManager->snowBall[sj]->GetPos());

				//死んだインスタンス削除
				snowBallManager->DeleteInstance(sj);
				sj--;				//きえた分詰める
			}
		}
	}

	//敵の雪玉とプレイヤーのあたり判定
	for (unsigned int si = 0; si < snowBallManager->snowBall.size(); si++)
	{
		if (CollisionObserver::EnemySnowBalltoPlayer(player, snowBallManager->snowBall[si]))
		{
			//SnowFragエフェクト呼ぶ
			Effect.NewSnowFrag(snowBallManager->snowBall[si]->GetPos());
			player->HitSnowBall();			//HIT時のメソッドを呼ぶ

			snowBallManager->DeleteInstance(si);
			si--;						//きえた分詰める
		}
	}

	for (unsigned int i = 0; i < GetDecorationManager.decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			CollisionObserver::DecorationToMapObj(GetDecorationManager.decoration[i], mapObjManager->mapObj[j], eventManager);
		}
	}

	GetSpawnerManager.Update(*stageBorder);
	//----------------------------------------------------------------------------------------
	if (eventManager->Update(GetEnemyManager, GetDecorationManager, *stageBorder) == false)		//falseが返ってきたらリザルトへ移行する
	{
		sceneSwitchState = -1;
	}

	if (sceneSwitchState == -1)
	{
		if (SceneSwitch.ToDarkness() == true)
		{
			resultFlag = true;
			resultCam = new ResultCam();
			sceneSwitchState = 1;

			//敵やエフェクトなど邪魔なものを削除する
			GetEnemyManager.AllDelete();
			Effect.AllDelete();
			snowBallManager->AllDelete();
			GetDecorationManager.DeleteToResult();
		}
	}
	//----------------------------------------------------------------------------------------
	timeUI->SetTime_s(eventManager->GetRemainingTime_s());
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

bool GameScene::ResultUpdate(void)
{
	if (sceneSwitchState == 1)				//シーン移行後明転させる処理
	{
		if (SceneSwitch.ToBrightness() == true)
		{
			sceneSwitchState = 0;
		}
	}

	resultCam->Update(&mapObjManager->GetXmasTreePos());

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		sceneSwitchState = -1;
	}

	if (sceneSwitchState == -1)
	{
		if (SceneSwitch.ToDarkness() == true)
		{
			return false;
		}
	}
	return true;
}
