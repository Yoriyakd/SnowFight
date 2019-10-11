#include "GameScene.h"

D3DLIGHT9 Light;


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

	loadStageData->GetStageSize(&stageXtmp, &stageZtmp);		//�C���X�^���X�Ԃ̂����͂������邵���Ȃ��H
	fenceManager->SetStageSize(stageXtmp, stageZtmp);
	fenceManager->SetFence();

	for (int i = 0; i < loadStageData->GetWallNum(); i++)
	{
		wallManager->SetWall(loadStageData->GetWallData(i));
	}

	for (int i = 0; i < loadStageData->GetEnemyNum(); i++)
	{
		enemyManager->SetEnemy(loadStageData->GetEnemyData(i));			//enemyManager���C���X�^���X���쐬����
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
