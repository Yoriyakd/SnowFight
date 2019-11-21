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
	playerCam = new PlayerCamera(SCRW, SCRH, hwnd);
	eventManager = new EventManager();
	decorationManager = new DecorationManager();
	pickUpInstructions = new PickUpInstructions();


	decorationManager->decoration.push_back(new Decoration_Ball(&D3DXVECTOR3(80, 0, 50), RED_BALL));		//test☆

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
	stageBorder->Right = StageSizeX ;
	//-------------------------------------------------------
	playerCam->SetPos(&D3DXVECTOR3(StageSizeX / 2, 0, 10.0f));				//プレイヤーの初期位置

	//fenceManager = new FenceManager(FenceCntX, FenceCntY, stageSizeX, stageSizeZ);		//ステージの境界データをもらうよう変更する
	//fenceManager->SetStageSize(stageSizeX, stageSizeZ);
	//fenceManager->SetFence();		//フェンスを配置

	player->SetPlayerCamPointer(playerCam);		//プレイヤーカメラのポインタをセット
	effectManager->SetPlayerCamPointer(playerCam);	//プレイヤーカメラのポインタをセット
	
	//-----------------------------
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);


	Light.Type = D3DLIGHT_DIRECTIONAL;

	Light.Direction = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	Light.Diffuse.a = 1.0f;
	Light.Diffuse.r = 1.0f;
	Light.Diffuse.g = 1.0f;
	Light.Diffuse.b = 1.0f;

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
	//delete fenceManager;
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
	//fenceManager->Draw();
	mapObjManager->Draw();
	enemyManager->Draw();
	player->Draw();
	snowBallManager->Draw();
	effectManager->Draw();
	decorationManager->Draw();
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
	// 描画終了
	lpSprite->End();
}

bool GameScene::Update()
{
	enemyManager->Update(snowBallManager);
	playerCam->Update();
	player->Update(snowBallManager);		//カメラを更新してから
	snowBallManager->Update();
	effectManager->Update();
	eventManager->Update();
	decorationManager->Updata();

	collisionObserver->SnowBalltoEnemy(snowBallManager, enemyManager);
	collisionObserver->SnowBalltoObj(snowBallManager, mapObjManager);
	collisionObserver->PlayertoObj(playerCam, mapObjManager);
	return true;
}
