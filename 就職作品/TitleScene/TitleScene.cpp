#include "TitleScene.h"
#include"../GameScene/GameScene.h"
#include"../MenuScene/MenuScene.h"

TitleScene::TitleScene():ESCFlag(false)
{
	logoTex = GetResource.GetTexture(TitleLogo_Tex);
	D3DXMatrixTranslation(&logoMat, SCRW / 2, 0, 0);

	backTex = GetResource.GetTexture(TitleBack_Tex);
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	kyeInstructionTex = GetResource.GetTexture(TitleInstructions_Tex);
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

	GetSceneSwitchEffect.Draw();


	// �`��I��
	lpSprite->End();
}

bool TitleScene::Update(void)
{
	//if (GetAsyncKeyState(VK_RBUTTON || VK_LBUTTON) & 0x8000)		�ł��Ȃ�����
	//{
	//	sceneSwitchState = true;
	//}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (ESCFlag == true)
		{
			PostQuitMessage(0);		//�I������
			return false;
		}
	}
	else
	{
		ESCFlag = true;
	}

	if (sceneSwitchState == false)
	{
		
		if (GetAsyncKeyState(VK_RBUTTON) & 0x8000 || GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			if (clickFlag == true)
			{
				GetSound.Play2D(Success_Sound);
				sceneSwitchState = true;
			}
		}
		else
		{
			clickFlag = true;
		}
	}

	if (sceneSwitchState == true)
	{
		if (GetSceneSwitchEffect.ToDarkness() == true)		//�^���ÂɂȂ�����ڍs
		{
			GetSceneSwitcher.SwitchScene(new MenuScene());
			return false;
		}
	}
	return true;
}
