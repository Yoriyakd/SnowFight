#include "TitleScene.h"
#include"../GameScene/GameScene.h"
#include"../MenuScene/MenuScene.h"

TitleScene::TitleScene()
{
	logoTex = resourceManager->GetTexture("TitleLogo.png", logoTexX, 170, NULL);
	D3DXMatrixTranslation(&logoMat, SCRW / 2, 0, 0);

	backTex = resourceManager->GetTexture("BackTex.jpg", SCRW, SCRH, NULL);		//���̔w�i�T�C�Y���傫������
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	kyeInstructionTex = resourceManager->GetTexture("PushSpase.png", kyeInstructionX, 128, NULL);
	D3DXMatrixTranslation(&kyeInstructionMat, SCRW / 2, 500, 0);

	sceneSwitchEffectAlpha = 0;
	switchEffectTex = resourceManager->GetTexture("SceneSwitchEffect.png", 32, 32, NULL);
	D3DXMatrixTranslation(&switchEffectMat, 0, 0, 0);
}

TitleScene::~TitleScene()
{
}

void TitleScene::Render3D(void)
{
}

void TitleScene::SetCamera(void)
{
}

void TitleScene::Render2D(void)
{
	//////////////////////////////////////////////////
	///	�X�v���C�g�̕`�揈��
	//////////////////////////////////////////////////
	// �`��J�n
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT RcBack = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcLogo = { 0, 0, logoTexX, 170 };
	lpSprite->SetTransform(&logoMat);
	lpSprite->Draw(logoTex, &RcLogo, &D3DXVECTOR3((float)logoTexX / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcKyeInstruction = { 0, 0, 548, 128 };
	lpSprite->SetTransform(&kyeInstructionMat);
	lpSprite->Draw(kyeInstructionTex, &RcKyeInstruction, &D3DXVECTOR3((float)kyeInstructionX / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcSwitchEffect = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&switchEffectMat);
	lpSprite->Draw(switchEffectTex, &RcSwitchEffect, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(sceneSwitchEffectAlpha, 255, 255, 255));

	// �`��I��
	lpSprite->End();
}

bool TitleScene::Update(void)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		sceneSwitchFlag = true;
	}

	if (sceneSwitchFlag == true)
	{
		sceneSwitchEffectAlpha += 20;
		if (sceneSwitchEffectAlpha > 255)		//�A���t�@�l��255�ȏ�ŃV�[���J��
		{
			sceneSwitcher.SwitchScene(new MenuScene());
			return false;
		}
	}
	return true;
}
