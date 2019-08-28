#include "GameScene.h"



void DrawMesh(XFILE *XFile);		//TEST:

Player *player;
Stage *stage;

//XFILE TestMesh;
//D3DXMATRIX TestMat;



GameScene::GameScene()
{
	player = new Player();
	stage = new Stage(1);
	//TestMesh = resourceManager->GetXFILE("XFiles/EnemyBody.x");

	
}

GameScene::~GameScene()
{
	
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
	//D3DXMatrixTranslation(&TestMat, 0, 0, 0);		//TEST:
	player->Update();
	
	return true;
}
