#include "MenuScene.h"
#include"../GameScene/GameScene.h"
#include"../TitleScene/TitleScene.h"

MenuScene::MenuScene()
{
	sceneSwitchState = 1;		//1�ŏ��͖��]������

	//---------------------------------------
	//�w�i
	//---------------------------------------
	backTex = GetResource.GetTexture(MenuBack_Tex);
	D3DXMatrixTranslation(&backMat, 0, 0, 0);

	//---------------------------------------
	//�X�e�[�W�Z���N�g�{�[�h
	//---------------------------------------
	boardTex = GetResource.GetTexture(MenuBoard_Tex);
	D3DXMatrixTranslation(&boardMat, 370, 100, 0);

	//---------------------------------------
	//�X�e�[�W�Z���N�g����
	//---------------------------------------
	headCharTex = GetResource.GetTexture(MenuHeadChar_Tex);
	D3DXMatrixTranslation(&headCharMat, 430, 100, 0);

	//---------------------------------------
	//�J�[�\��
	//---------------------------------------
	cursorTex = GetResource.GetTexture(MenuCursor_Tex);

	stage1Button = new ButtonBase(1);
	stage2Button = new ButtonBase(2);
}

MenuScene::~MenuScene()
{
	delete stage1Button;
	delete stage2Button;
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


	RECT RcBack = { 0, 0, SCRW, SCRH };
	lpSprite->SetTransform(&backMat);
	lpSprite->Draw(backTex, &RcBack, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT RcBoard = { 0, 0, 768, 540 };
	lpSprite->SetTransform(&boardMat);
	lpSprite->Draw(boardTex, &RcBoard, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcHead = { 0, 0, 640, 64 };
	lpSprite->SetTransform(&headCharMat);
	lpSprite->Draw(headCharTex, &rcHead, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	stage1Button->Draw();
	stage2Button->Draw();

	RECT RcCursor = { 0, 0, 64, 64 };
	lpSprite->SetTransform(&cursorMat);
	lpSprite->Draw(cursorTex, &RcCursor, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	GetSceneSwitchEffect.Draw();

	// �`��I��
	lpSprite->End();
}

bool MenuScene::Update(void)
{
	stage1Button->Update();
	stage2Button->Update();

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		GetSceneSwitcher.SwitchScene(new TitleScene());				//�G�t�F�N�g�Ɗm�F�����遙
		return false;
	}
	
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (stage1Button->GetState() == true)
		{
			sceneSwitchState = -1;
			selectedStage = 1;
		}
	}
	
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (stage2Button->GetState() == true)
		{
			sceneSwitchState = -1;
			selectedStage = 2;
		}
	}

	if (sceneSwitchState == -1)
	{
		if (GetSceneSwitchEffect.ToDarkness() == true)			//�Ó]������
		{
			GetSceneSwitcher.SwitchScene(new GameScene(selectedStage));
			return false;
		}
	}

	if (sceneSwitchState == 1)
	{
		if (GetSceneSwitchEffect.ToBrightness() == true)
		{
			sceneSwitchState = 0;
		}
	}

	//--------------------------------------------
	//�J�[�\���ړ�
	//--------------------------------------------
	POINT Pt;

	GetCursorPos(&Pt);					//���݂̃J�[�\���̈ʒu�������
	ScreenToClient(hwnd, &Pt);		//�X�N���[�����W�ɕϊ�

	D3DXMatrixTranslation(&cursorMat, (float)Pt.x, (float)Pt.y, 0);

	return true;
}
