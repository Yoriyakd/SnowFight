
#include "GameScene.h"

EnemyManager *enemyManager;
Player *player;
D3DLIGHT9 Light;
StageBorder stageBorder;
const float StageBorderOffsetX = 15.0f;			//外周までの距離
const float StageBorderOffsetZ = 15.0f;			//外周までの距離
const float Gravity = -0.05f;						//重力	※必ず負の値のする

GameScene::GameScene(int StageNo)
{
	srand(timeGetTime());
	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	setEnemies = new SetEnemies();
	skyBox = new SkyBox;
	snowBallManager = new SnowBallManager();
	mapObjManager = new MapObjManager();
	collisionObserver = new CollisionObserver();
	playerCam = new PlayerCamera(SCRW, SCRH, hwnd);

	int FenceCntX = 15, FenceCntY = 15;		//自動的に求められるようにする		そもそもフェンス以外を設置する☆

	loadStageData->GetStageSize(&stageSizeX, &stageSizeZ);

	//-------------------------------------------------------
	//ステージの境界を求める
	//-------------------------------------------------------
	stageBorder.Top = stageSizeZ + StageBorderOffsetZ;
	stageBorder.Bottom = -1 * StageBorderOffsetZ;
	stageBorder.Left = -1 * StageBorderOffsetX;
	stageBorder.Right = stageSizeX + StageBorderOffsetX;
	//-------------------------------------------------------

	fenceManager = new FenceManager(FenceCntX, FenceCntY, StageBorderOffsetX, StageBorderOffsetZ);		//ステージの境界データをもらうよう変更する
	fenceManager->SetStageSize(stageSizeX, stageSizeZ);
	fenceManager->SetFence();		//フェンスを配置

	playerCam->SetStageBorder(stageBorder);		//ステージの境界データをセット
	player->SetPlayerCamPointer(playerCam);		//プレイヤーカメラのポインタをセット
	effectManager->SetPlayerCamPointer(playerCam);	//プレイヤーカメラのポインタをセット
	setEnemies->SetStageSize(stageSizeX, stageSizeZ);
	
	mapObjManager->SetTree(D3DXVECTOR3(50, 0, 50));		//test ☆
	mapObjManager->SetBench(D3DXVECTOR3(30, 0, 80));		//test　☆

	for (int i = 0; i <  loadStageData->GetEnemyNum(); i++)
	{
		enemyManager->SetEnemy(loadStageData->GetEnemyData(i));			//enemyManagerがインスタンスを作成する
	}

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
	delete fenceManager;
	delete snowBallManager;
	delete mapObjManager;
	delete collisionObserver;
}

void GameScene::Render3D(void)
{
	skyBox->Draw();
	ground->Draw();
	fenceManager->Draw();
	mapObjManager->Draw();
	enemyManager->Draw();
	player->Draw();
	snowBallManager->Draw();
	effectManager->Draw();
}

void GameScene::SetCamera(void)
{
	playerCam->SetCamera();
}

void GameScene::Render2D(void)
{
}

bool GameScene::Update()
{
	if (GetAsyncKeyState('P') & 0x8000)		//条件を変えて本実装☆
	{
		setEnemies->SetEnemy();
	}
	enemyManager->Update(snowBallManager);
	playerCam->Update();
	player->Update(snowBallManager);		//カメラを更新してから
	snowBallManager->Update();
	effectManager->Update();

	collisionObserver->SnowBalltoEnemy(snowBallManager, enemyManager);
	collisionObserver->SnowBalltoObj(snowBallManager, mapObjManager);
	collisionObserver->PlayertoObj(playerCam, mapObjManager);
	return true;
}
