#include "GameScene.h"



Player *player;
Stage *stage;




GameScene::GameScene()
{
	player = new Player();
	stage = new Stage(1);
	//TestMesh = resourceManager->GetXFILE("XFiles/EnemyBody.x");

	
}

GameScene::~GameScene()
{
	delete player;
	delete stage;
	
}

void GameScene::Render3D(void)
{
	stage->Draw();
	player->Draw();
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
	player->Update();
	
	return true;
}
