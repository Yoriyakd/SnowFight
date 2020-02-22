#include "BackToTitle.h"
#include"../TitleScene/TitleScene.h"

BackToTitle::BackToTitle() : nowState(false)
{
	tex = GetResource.GetTexture(BackToTitle_Tex);
	D3DXMatrixTranslation(&mat, 0, 0, 0);

	YesButton = new BackToTitleButton();
	ButtonData TmpData;
	TmpData.Pos = D3DXVECTOR2(440, 300);
	TmpData.BoxSize = D3DXVECTOR2(132, 132);
	YesButton->Initialize(TmpData, GetResource.GetTexture(YesButton_Tex));		//CSV����ǂݍ��ނ悤�ɕύX���遙
	
	NoButton = new BackToTitleButton();
	TmpData.Pos = D3DXVECTOR2(740, 300);
	TmpData.BoxSize = D3DXVECTOR2(132, 132);
	NoButton->Initialize(TmpData, GetResource.GetTexture(NoButton_Tex));
}

BackToTitle::~BackToTitle()
{
}

void BackToTitle::Draw()
{
	if (nowState == true)		//�^�C�g���o�b�N�m�F��ʂ��Ă΂�Ă���Ԃ̂ݕ`��
	{
		RECT RectTmp = { 0, 0, 1280, 720 };
		lpSprite->SetTransform(&mat);
		lpSprite->Draw(tex, &RectTmp, &D3DXVECTOR3(0, 0, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		YesButton->Draw();
		NoButton->Draw();
	}
}

RETURN_STATE BackToTitle::CallBackToTitle()
{
	static bool CursorFlag = false;		//���O�̃J�[�\���ɕύX���遙

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		if (isESCKey == true)
		{
			if (nowState == true)
			{
				//�J�[�\��
				ShowCursor(false);
				CursorFlag = false;

				nowState = false;
				isESCKey = false;	//ESC��A�����ĉ����Ȃ��悤��
				return CANCEL;
			}
			else
			{
				nowState = true;
				isESCKey = false;	//���sESC��A�����ĉ����Ȃ��悤��
			}
		}
	}
	else
	{
		isESCKey = true;
	}
	
	if (nowState == false)return NOT_ACTIVE;

	if (CursorFlag == false)		//����(�S�̂ŊǗ����������悳�����J�[�\���g���Ȃ�)	//�J�[�\���������Ȃ��Ȃ猩����悤�ɂ���
	{
		CursorFlag = true;
		ShowCursor(true);		//����
	}

	YesButton->Update();
	NoButton->Update();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (YesButton->GetState() == true)
		{
			GetSound.Play2D(Success_Sound);
			nowState = false;
			ShowCursor(false);		//����
			CursorFlag = false;

			nowState = false;

			return RETURN_TITLE;
		}
		if (NoButton->GetState() == true) 
		{
			nowState = false;
			ShowCursor(false);		//����
			CursorFlag = false;
			nowState = false;
			return CANCEL;
		}
	}

	return WAITING_INPUT;
}
