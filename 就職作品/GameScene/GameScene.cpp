#include "GameScene.h"
#include"../MenuScene/MenuScene.h"

D3DLIGHT9 Light;

const float SnowBallGravity = -0.05f;						//重力	※必ず負の値のする

GameScene::GameScene(int StageNo)
{
	srand(timeGetTime());
	sceneSwitchState = 1;		//最初は明転させる

	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	playerCam = new PlayerCamera();
	eventManager = new EventManager();
	decorationManager = new DecorationManager();
	stageBorder = new StageBorder;
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
	resultTex = resourceManager->GetTexture("Result.png", 820, 160, NULL);
	D3DXMatrixTranslation(&resultMat, SCRW / 2, 10, 0);

	returnTex = resourceManager->GetTexture("Click_To_Return.png", 420, 40, NULL);
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
	delete enemyManager;

	delete resultCam;
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

	decorationManager->Draw();
	if (resultFlag == true)
	{
		return;		//描画しない		(インスタンスを削除する方がいいんだろうか？)☆
	}
	//-------------------------------------------------------
	//
	//-------------------------------------------------------
	enemyManager->Draw();
	snowBallManager->Draw();
	effectManager->Draw();
	

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

	sceneSwitchEffect->Draw();			//常に描画

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
			sceneSwitcher.SwitchScene(new MenuScene());
			return false;
		}
		return true;		//リザルト表示中は早期リターンして動きを止める
	}

	
	if (sceneSwitchState == 1)				//初めに明転させる処理
	{
		if (sceneSwitchEffect->ToBrightness() == true)
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

	player->Update(*snowBallManager, *decorationManager, *pickUpInstructions);		//カメラを更新してから
	//---------------------------------------------------------


	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &playerCam->GetmView());		//カメラのアップデートの後に呼ぶ

	enemyManager->Update(*player, *snowBallManager, *stageBorder);

	remainingBallUI->SetRemainingBallCnt(player->GetRemainingBalls());
	//remainingBallUI->SetRemainingBallCnt(player->GetHP());		//HP確認用☆
	snowBallManager->Update();

	effectManager->SetBillBoardMat(&TmpBillBoardMat);		//※effectManagerのUpdateの前に呼ぶ
	effectManager->Update();

	decorationManager->Updata();

	//雪玉と敵の当たり判定
	for (unsigned int ei = 0; ei < enemyManager->enemy.size(); ei++)
	{
		for (unsigned int sj = 0; sj < snowBallManager->snowBall.size(); sj++)
		{
			if (CollisionObserver::SnowBalltoEnemy(snowBallManager->snowBall[sj], enemyManager->enemy[ei]) == true)		//命中でtrueが返ってくる
			{
				//SnowFragエフェクト呼ぶ
				effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[sj]->GetPos()));

				if (enemyManager->enemy[ei]->TakeDamage(1) == false)		//falseが返ってきたら
				{
					//-------------------------------------------------------------
					//EnemyDeathAnime再生開始
					//-------------------------------------------------------------
					//引数として渡す変数を一時的に宣言
					D3DXMATRIX TmpAnimeMat;
					XFILE TmpAnimeMesh;
					D3DXVECTOR3 SnowBallVec;

					TmpAnimeMat = enemyManager->enemy[ei]->GetMat();		//行列
					TmpAnimeMesh = enemyManager->enemy[ei]->GetMesh();	//Mesh
					SnowBallVec = snowBallManager->snowBall[sj]->GetMoveVec();	//雪玉の移動ベクトルをもらう

					effectManager->enemyDeathAnime.push_back(new EnemyDeathAnime(TmpAnimeMat, TmpAnimeMesh, SnowBallVec));

					//死んだインスタンス削除
					delete enemyManager->enemy[ei];
					enemyManager->enemy.erase(enemyManager->enemy.begin() + ei);
					ei--;		//きえた分詰める
				}
				//死んだインスタンス削除
				delete snowBallManager->snowBall[sj];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + sj);
				sj--;		//きえた分詰める
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
				effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[sj]->GetPos()));

				//死んだインスタンス削除
				delete snowBallManager->snowBall[sj];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + sj);
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
			effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[si]->GetPos()));
			player->HitSnowBall();			//HIT時のメソッドを呼ぶ

			delete snowBallManager->snowBall[si];
			snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + si);
			si--;						//きえた分詰める
		}
	}

	for (unsigned int i = 0; i < decorationManager->decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			CollisionObserver::DecorationToMapObj(decorationManager->decoration[i], mapObjManager->mapObj[j], eventManager);
		}
	}
	//----------------------------------------------------------------------------------------
	if (eventManager->Update(*enemyManager, *decorationManager, *stageBorder) == false)		//falseが返ってきたらリザルトへ移行する
	{
		sceneSwitchState = -1;
	}

	if (sceneSwitchState == -1)
	{
		if (sceneSwitchEffect->ToDarkness() == true)
		{
			resultFlag = true;
			resultCam = new ResultCam();
			sceneSwitchState = 1;

			//敵やエフェクトなど邪魔なものを削除する
			enemyManager->AllDelete();
			effectManager->AllDelete();
			snowBallManager->AllDelete();
			decorationManager->DeleteToResult();
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
		if (sceneSwitchEffect->ToBrightness() == true)
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
		if (sceneSwitchEffect->ToDarkness() == true)
		{
			return false;
		}
	}
	return true;
}
