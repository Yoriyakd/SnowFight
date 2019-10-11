#include "GameScene.h"




GameScene::GameScene(int StageNo)
{
	
	loadStageData = new LoadStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	skyBox = new SkyBox;
	fenceManager = new FenceManager(15, 15, 15.0f, 15.0f);
	snowBallManager = new SnowBallManager();
	wallManager = new WallManager();
	collisionObserver = new CollisionObserver();

	float stageXtmp, stageZtmp;

	loadStageData->GetStageSize(&stageXtmp, &stageZtmp);		//インスタンス間のやり取りはこうするしかない？
	fenceManager->SetStageSize(stageXtmp, stageZtmp);
	fenceManager->SetFence();

	for (int i = 0; i < loadStageData->GetWallNum(); i++)
	{
		wallManager->SetWall(loadStageData->GetWallData(i));
	}

	for (int i = 0; i < loadStageData->GetEnemyNum(); i++)
	{
		enemyManager->SetEnemy(loadStageData->GetEnemyData(i));			//enemyManagerがインスタンスを作成する
	}
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
	delete wallManager;
	delete collisionObserver;
}

void GameScene::Render3D(void)
{
	skyBox->Draw();
	ground->Draw();
	fenceManager->Draw();
	wallManager->Draw();
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

	enemyManager->Update();
	player->Update(snowBallManager);
	snowBallManager->Update();
	effectManager->Update();

	collisionObserver->SnowBalltoEnemy(snowBallManager, enemyManager);
	collisionObserver->SnowBalltoWall(snowBallManager, wallManager);
	return true;
}
