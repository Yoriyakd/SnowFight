#include "MenuScene.h"
#include"../GameScene/GameScene.h"

MenuScene::MenuScene()
{
	//---------------------------------------
	//�؂�ւ��G�t�F�N�g
	//---------------------------------------
	sceneSwitchEffectAlpha = 255;
	switchEffectTex = resourceManager->GetTexture("SceneSwitchEffect.png", 32, 32, NULL);
	D3DXMatrixTranslation(&switchEffectMat, 0, 0, 0);

	//---------------------------------------
	//�w�i
	//---------------------------------------
	backTex = resourceManager->GetTexture("Menuback.jpeg", 1280, 720, NULL);
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	//---------------------------------------
	//�X�e�[�W�Z���N�g�{�[�h
	//---------------------------------------
	boardTex = resourceManager->GetTexture("StageSelect.png", 768, 540, NULL);
	D3DXMatrixTranslation(&boardMat, 370, 100, 0);

	stage1Button = new Stage1Button();
}

MenuScene::~MenuScene()
{
	delete stage1Button;
}

void MenuScene::Render3D(void)
{
}

void MenuScene::SetCamera(void)
{
}

void MenuScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//RECT RCRightArrow = {};

	RECT RcBack = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcBoard = { 0, 0, 768, 540 };
	lpSprite->SetTransform(&boardMat);
	lpSprite->Draw(boardTex, &RcBoard, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	stage1Button->Draw();

	RECT RcSwitchEffect = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&switchEffectMat);
	lpSprite->Draw(switchEffectTex, &RcSwitchEffect, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(sceneSwitchEffectAlpha, 255, 255, 255));


	// �`��I��
	lpSprite->End();
}

bool MenuScene::Update(void)
{
	sceneSwitchEffectAlpha -= 20;
	if (sceneSwitchEffectAlpha < 0)
	{
		sceneSwitchEffectAlpha = 0;
	}

	stage1Button->Update();

	
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (stage1Button->GetState() == true)
		{
			sceneSwitcher.SwitchScene(new GameScene(1));
			return false;
		}
	}
	return true;
}
