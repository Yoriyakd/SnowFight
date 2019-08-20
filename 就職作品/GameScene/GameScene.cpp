#include "GameScene.h"



void DrawMesh(XFILE *XFile);		//TEST:

Player *player;
StageCreater *stageCreater;

//XFILE TestMesh;
//D3DXMATRIX TestMat;



GameScene::GameScene()
{
	player = new Player();
	stageCreater = new StageCreater();
	//TestMesh = resourceManager->GetXFILE("XFiles/EnemyBody.x");
}

GameScene::~GameScene()
{
	
}

void GameScene::Render3D(void)
{
	stageCreater->Draw();
	player->Draw();
}

void GameScene::SetCamera(void)
{
	D3DXMATRIX mView, mProj;

	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(0.0f, 5.0f, -5.0f),	// カメラの位置
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);


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
