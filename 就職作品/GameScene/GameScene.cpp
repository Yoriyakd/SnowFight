#include "GameScene.h"




GameScene::GameScene(int StageNo)
{
	
	setStageData = new SetStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	skyBox = new SkyBox;
	fenceManager = new FenceManager(15, 15, 15.0f, 15.0f);
	snowBallManager = new SnowBallManager();
	collisionObserver = new CollisionObserver();

	float stageXtmp, stageZtmp;

	setStageData->GetStageSize(&stageXtmp, &stageZtmp);		//インスタンス間のやり取りはこうするしかない？
	fenceManager->SetStageSize(stageXtmp, stageZtmp);
	fenceManager->SetFence();

	for (int i = 0; i < setStageData->GetWallNum(); i++)
	{
		wall.push_back(new Wall(setStageData->GetWallData(i)));
	}

	for (int i = 0; i < setStageData->GetEnemyNum(); i++)
	{
		enemyManager->SetEnemy(setStageData->GetEnemyData(i));			//enemyManagerがインスタンスを作成する

	}
}

GameScene::~GameScene()
{
	delete player;
	
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		delete wall[i];

	}
	wall.clear();

	delete enemyManager;
	delete setStageData;
	delete fenceManager;
	delete snowBallManager;
}

void GameScene::Render3D(void)
{
	skyBox->Draw();
	ground->Draw();
	fenceManager->Draw();
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		wall[i]->Draw();
	}

	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		enemyManager->enemy[i]->Draw();
	}
	player->Draw();
	
	for (unsigned int i = 0; i < snowBallManager->snowBall.size(); i++)
	{
		snowBallManager->snowBall[i]->Draw();
	}
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
	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		enemyManager->enemy[i]->Update();
	}
	player->Update(snowBallManager);

	for (unsigned int i = 0; i < snowBallManager->snowBall.size(); i++)
	{
		if (snowBallManager->snowBall[i]->Update() == false)
		{
			delete snowBallManager->snowBall[i];
			snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + i);
			i--;
		}
	}

	collisionObserver->SnowBalltoEnemy(snowBallManager, enemyManager);
	return true;
}
