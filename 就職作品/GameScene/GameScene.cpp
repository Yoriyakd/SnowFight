#include "GameScene.h"


void GameScene::CollisionDetectionS_PtoE(void)		//当たり判定用のクラスに引数でデータを渡す
{
	for (unsigned int i = 0; i < enemyManager->enemy.size(); i++)
	{
		for (unsigned int j = 0; j < snowBallManager->snowBall.size(); j++)
		{
			D3DXVECTOR3 EnemyPosTmp = enemyManager->enemy[i]->GetPos(), SnowBall_PPosTmp = snowBallManager->snowBall[j]->GetPos();

			if (CollisionDetection(EnemyPosTmp, 3, SnowBall_PPosTmp, 1.5))		//半径あとで変数化
			{
				delete enemyManager->enemy[i];
				delete snowBallManager->snowBall[j];
				snowBallManager->snowBall.erase(snowBallManager->snowBall.begin() + j);
				enemyManager->enemy.erase(enemyManager->enemy.begin() + i);
				j--;
				i--;
			}

		}
	}
}

GameScene::GameScene(int StageNo)
{
	
	setStageData = new SetStageData(StageNo);
	player = new Player;
	ground = new Ground;
	enemyManager = new EnemyManager;
	skyBox = new SkyBox;
	fenceManager = new FenceManager(15, 15, 15.0f, 15.0f);
	snowBallManager = new SnowBallManager();

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

	CollisionDetectionS_PtoE();
	return true;
}
