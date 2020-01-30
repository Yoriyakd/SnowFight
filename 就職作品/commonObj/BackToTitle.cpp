#include "BackToTitle.h"
#include"../TitleScene/TitleScene.h"

BackToTitle::BackToTitle() : ESCKyeFlag(true)
{
	tex = GetResource.GetTexture(BackToTitle_Tex);
	D3DXMatrixTranslation(&mat, 0, 0, 0);

	YesButton = new ButtonBase(1);
	NoButton = new ButtonBase(2);
}

BackToTitle::~BackToTitle()
{
}

void BackToTitle::Draw()
{
	if (calledState == true)		//�^�C�g���o�b�N�m�F��ʂ��Ă΂�Ă���Ԃ̂ݕ`��
	{
		RECT RectTmp = { 0, 0, 1280, 720 };
		lpSprite->SetTransform(&mat);
		lpSprite->Draw(tex, &RectTmp, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		YesButton->Draw();
		NoButton->Draw();
	}
}

int BackToTitle::CallBackToTitle()
{
	static bool CursorFlag = false;		//���O�̃J�[�\���ɕύX���遙
	if (CursorFlag == false)
	{
		CursorFlag = true;
		ShowCursor(true);		//����
	}
	calledState = true;

	YesButton->Update();
	NoButton->Update();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (YesButton->GetState() == true)
		{
			GetSound.Play2D(Success_Sound);
			calledState = false;
			GetSceneSwitcher.SwitchScene(new TitleScene());
			ShowCursor(false);		//����
			CursorFlag = false;

			ESCKyeFlag = true;

			return 1;
		}
		if (NoButton->GetState() == true) 
		{
			calledState = false;
			ShowCursor(false);		//����
			CursorFlag = false;
			ESCKyeFlag = true;
			return -1;
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (ESCKyeFlag == true)
		{
			return 0;
		}
		calledState = false;
		GetSceneSwitcher.SwitchScene(new TitleScene());
		ShowCursor(false);		//����(�S�̂ŊǗ����������悳�����J�[�\���g���Ȃ�)
		CursorFlag = false;

		ESCKyeFlag = true;

		return 1;
	}
	else
	{
		ESCKyeFlag = false;
	}

	return 0;
}
