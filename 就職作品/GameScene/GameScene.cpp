#include "GameScene.h"

EnemyManager *enemyManager;
Player *player;
D3DLIGHT9 Light;
StageBorder *stageBorder;
DecorationManager *decorationManager;
PickUpInstructions *pickUpInstructions;
const float SnowBallGravity = -0.05f;						//重力	※必ず負の値のする

GameScene::GameScene(int StageNo)
{
	srand(timeGetTime());
	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	collisionObserver = new CollisionObserver();
	playerCam = new PlayerCamera();
	eventManager = new EventManager();
	decorationManager = new DecorationManager();
	pickUpInstructions = new PickUpInstructions();
	remainingBallUI = new RemainingBallUI();


	decorationManager->decoration.push_back(new Decoration_RedBall(&D3DXVECTOR3(80, 0, 50)));		//test☆
	decorationManager->decoration.push_back(new Decoration_BlueBall(&D3DXVECTOR3(80, 0, 60)));		//test☆
	decorationManager->decoration.push_back(new Decoration_YellowBall(&D3DXVECTOR3(80, 0, 70)));		//test☆

	loadStageData->SetStageMap(mapObjManager);
	//-------------------------------------------------------
	//ステージの境界を求める
	//-------------------------------------------------------
	float StageSizeX, StageSizeZ;		//ステージのサイズ	stageボーダーだけでよさそう
	loadStageData->GetStageSize(&StageSizeX, &StageSizeZ);
	stageBorder = new StageBorder;

	stageBorder->Top = StageSizeZ;
	stageBorder->Bottom = 0;
	stageBorder->Left = 0;
	stageBorder->Right = StageSizeX;
	//-------------------------------------------------------
	playerCam->SetPos(&D3DXVECTOR3(StageSizeX / 2, 0, 10.0f));				//プレイヤーの初期位置

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
	delete player;
	delete ground;
	delete enemyManager;
	delete skyBox;
	delete stage1Enclosure;
	delete snowBallManager;
	delete mapObjManager;
	delete collisionObserver;
	delete eventManager;
	delete pickUpInstructions;
}

void GameScene::Render3D(void)
{
	skyBox->Draw();
	ground->Draw();
	stage1Enclosure->Draw();
	mapObjManager->Draw();
	enemyManager->Draw();
	snowBallManager->Draw();
	effectManager->Draw();
	decorationManager->Draw();

	player->Draw();		//※Zバッファクリアをしているため最後に描画する
}

void GameScene::SetCamera(void)
{
	playerCam->SetCamera();
}

void GameScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	スプライトの描画処理
	//////////////////////////////////////////////////
	// 描画開始
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	pickUpInstructions->Draw();
	remainingBallUI->Draw();

	// 描画終了
	lpSprite->End();
}

bool GameScene::Update()
{
	playerCam->Update();
	//マップオブジェとプレイヤーの当たり判定
	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		collisionObserver->PlayertoObj(playerCam, mapObjManager->mapObj[i]);
	}

	D3DXMATRIX TmpBillBoardMat;
	MakeBillBoardMat(&TmpBillBoardMat, &playerCam->GetmView());		//カメラのアップデートの後に呼ぶ

	enemyManager->Update(snowBallManager);

	player->Update(snowBallManager);		//カメラを更新してから
	remainingBallUI->SetRemainingBallCnt(player->GetRemainingBalls());
	//remainingBallUI->SetRemainingBallCnt(player->GetHP());		//HP確認用☆
	snowBallManager->Update();

	effectManager->SetBillBoardMat(&TmpBillBoardMat);		//※effectManagerのUpdateの前に呼ぶ
	effectManager->Update();

	eventManager->Update();
	decorationManager->Updata();

	//雪玉と敵の当たり判定
	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		for (unsigned int j = 0; j < snowBallManager->snowBall.size(); j++)
		{
			if (snowBallManager->snowBall[j]->GetID() == PLAYER_ID)		//プレイヤーの球なら実行
			{
				if (collisionObserver->SnowBalltoEnemy(snowBallManager->snowBall[j], enemyManager->enemy[i]) == true)		//命中でtrueが返ってくる
				{
					//SnowFragエフェクト呼ぶ
					effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[j]->GetPos()));

					if (enemyManager->enemy[i]->TakeDamage(1) == false)		//falseが返ってきたら
					{
						//-------------------------------------------------------------
						//EnemyDeathAnime再生開始
						//-------------------------------------------------------------
						//引数として渡す変数を一時的に宣言
						D3DXMATRIX TmpAnimeMat;
						XFILE TmpAnimeMesh;
						D3DXVECTOR3 SnowBallVec;

						TmpAnimeMat = enemyManager->enemy[i]->GetMat();		//行列
						TmpAnimeMesh = enemyManager->enemy[i]->GetMesh();	//Mesh
						SnowBallVec = snowBallManager->snowBall[j]->GetMoveVec();	//雪玉の移動ベクトルをもらう

						effectManager->enemyDeathAnime.push_back(new EnemyDeathAnime(TmpAnimeMat, TmpAnimeMesh, SnowBallVec));

						//死んだインスタンス削除
						delete enemyManager->enemy[i];
						enemyManager->enemy.erase(enemyManager->enemy.begin() + i);
						i--;		//きえた分詰める
					}
					//死んだインスタンス削除
					delete snowBallManager->snowBall[j];
					snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
					j--;		//きえた分詰める
				}
			}
		}
	}

	//雪玉とマップオブジェの当たり判定

	for (unsigned int i = 0; i < mapObjManager->mapObj.size(); i++)
	{
		for (unsigned int j = 0; j < snowBallManager->snowBall.size(); j++)
		{
			if (collisionObserver->SnowBalltoObj(snowBallManager->snowBall[j], mapObjManager->mapObj[i]))		//命中でtrueが返ってくる
			{
				//SnowFragエフェクト呼ぶ
				effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[j]->GetPos()));

				//死んだインスタンス削除
				delete snowBallManager->snowBall[j];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
				j--;				//きえた分詰める
			}
		}
	}

	//敵の雪玉とプレイヤーのあたり判定
	for (unsigned int i = 0; i < snowBallManager->snowBall.size(); i++)
	{
		if (snowBallManager->snowBall[i]->GetID() == ENEMY_ID)		//敵の球なら実行
		{
			if (collisionObserver->EnemySnowBalltoPlayer(player, snowBallManager->snowBall[i]))
			{
				//SnowFragエフェクト呼ぶ
				effectManager->snowFrag.push_back(new SnowFrag(snowBallManager->snowBall[i]->GetPos()));
				player->HitSnowBall();			//HIT時のメソッドを呼ぶ

				delete snowBallManager->snowBall[i];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + i);
				i--;						//きえた分詰める
			}
		}
	}

	for (unsigned int i = 0; i < decorationManager->decoration.size(); i++)
	{
		for (unsigned int j = 0; j < mapObjManager->mapObj.size(); j++)
		{
			collisionObserver->DecorationToMapObj(decorationManager->decoration[i], mapObjManager->mapObj[j]);
		}
	}

	return true;
}
