
#include "GameScene.h"

EnemyManager *enemyManager;
Player *player;
D3DLIGHT9 Light;
float StageBorderOffsetX = 15.0f;			//外周までの距離
float StageBorderOffsetZ = 15.0f;			//外周までの距離

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

	int FenceCntX = 15, FenceCntY = 15;		//自動的に求められるようにする

	loadStageData->GetStageSize(&stageSizeX, &stageSizeZ);

	stageBorder.Top = stageSizeZ + StageBorderOffsetZ;
	stageBorder.Bottom = -1 * StageBorderOffsetZ;
	stageBorder.Left = -1 * StageBorderOffsetX;
	stageBorder.Right = stageSizeX + StageBorderOffsetX;

	fenceManager = new FenceManager(FenceCntX, FenceCntY, StageBorderOffsetX, StageBorderOffsetZ);		//ステージの境界データをもらうよう変更する
	fenceManager->SetStageSize(stageSizeX, stageSizeZ);
	fenceManager->SetFence();		//フェンスを配置

	player->SetStageBorder(stageBorder);
	setEnemies->SetStageSize(stageSizeX, stageSizeZ);
	

	for (int i = 0; i < loadStageData->GetWallNum(); i++)
	{
		mapObjManager->SetWall(loadStageData->GetWallData(i));
	}

	mapObjManager->SetTree(D3DXVECTOR3(50, 0, 50));

	for (int i = 0; i <  loadStageData->GetEnemyNum(); i++)
	{
		enemyManager->SetEnemy(loadStageData->GetEnemyData(i));			//enemyManagerがインスタンスを作成する
	}

	//-----------------------------k
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
	player->SetCamera();
}

void GameScene::Render2D(void)
{
}

bool GameScene::Update()
{
	if (GetAsyncKeyState('P') & 0x8000)		//条件を変えて本実装
	{
		setEnemies->SetEnemy();
	}
	enemyManager->Update(snowBallManager);
	player->Update(snowBallManager);
	snowBallManager->Update();
	effectManager->Update();

	collisionObserver->SnowBalltoEnemy(snowBallManager, enemyManager);
	collisionObserver->SnowBalltoObj(snowBallManager, mapObjManager);
	return true;
}
