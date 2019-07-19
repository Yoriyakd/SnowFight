#include "GameScene.h"

void DrawMesh(XFILE *XFile);				//Draw�͂�������Ȃ�	��ňړ�������



GameScene::GameScene()
{
	fieldMesh = resourceManager->GetXFILE("XFiles/Field.x" );
	D3DXMatrixTranslation(&fieldMat, 0, 0, 0);
}

GameScene::~GameScene()
{
	
}

void GameScene::Render3D(void)
{
	//lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &fieldMat);
	DrawMesh(&fieldMesh);
}

void GameScene::SetCamera(void)
{
	D3DXMATRIX mView, mProj;

	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&mView,
		&D3DXVECTOR3(0.0f, 10.0f, -10.0f),	// �J�����̈ʒu
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
	return true;
}
