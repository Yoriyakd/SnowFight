#include "TitleScene.h"
#include"../GameScene/GameScene.h"
#include"../MenuScene/MenuScene.h"

TitleScene::TitleScene()
{
	logoTex = GetResource.GetTexture("TitleLogo.png", logoTexX, 170, NULL);
	D3DXMatrixTranslation(&logoMat, SCRW / 2, 0, 0);

	backTex = GetResource.GetTexture("BackTex.jpg", SCRW, SCRH, NULL);		//���̔w�i�T�C�Y���傫������
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	kyeInstructionTex = GetResource.GetTexture("TitleInstructions.png", kyeInstructionX, 116, NULL);
	D3DXMatrixTranslation(&kyeInstructionMat, SCRW / 2, 500, 0);

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

	RECT RcKyeInstruction = { 0, 0, kyeInstructionX, 116 };
	lpSprite->SetTransform(&kyeInstructionMat);
	lpSprite->Draw(kyeInstructionTex, &RcKyeInstruction, &D3DXVECTOR3((float)kyeInstructionX / 2, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	sceneSwitchEffect->Draw();


	// �`��I��
	lpSprite->End();
}

bool TitleScene::Update(void)
{
	//if (GetAsyncKeyState(VK_RBUTTON || VK_LBUTTON) & 0x8000)		�ł��Ȃ�����
	//{
	//	sceneSwitchState = true;
	//}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		sceneSwitchState = true;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		sceneSwitchState = true;
	}

	if (sceneSwitchState == true)
	{
		if (sceneSwitchEffect->ToDarkness() == true)		//�^���ÂɂȂ�����ڍs
		{
			sceneSwitcher.SwitchScene(new MenuScene());
			return false;
		}
	}
	return true;
}
