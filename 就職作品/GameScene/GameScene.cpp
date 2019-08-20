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

	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(0.0f, 5.0f, -5.0f),	// �J�����̈ʒu
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// �J�����̎��_
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// �J�����̓��̕���
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//�s��ݒ�
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
