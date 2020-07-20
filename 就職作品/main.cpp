#include<time.h>
#include<stdio.h>
#include"main.h"

#include"Window/Window.h"
#include"DirectX/Direct3D.h"
#include"DirectX/DirectSound.h"
#include"DirectX/Sprite.h"
#include"DirectX/Font.h"

#include"SceanSwitcher/SceneSwitcher.h"
#include"GameScene/GameScene.h"
#include"TitleScene/TitleScene.h"
#include"ResourceManager.h"

#include"Effect/EffectManager.h"
#include"Effect/SceneSwitchEffect.h"
#include"Sound/SoundManager.h"
#include"commonObj/BackToTitle.h"
#include"commonObj/Cursor.h"


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

//60FPS�Œ�̂��߂̏����Ƃ肠���������ɏ���
bool FPSLimiter(void)
{
	static DWORD NTlmt, BTlmt;
	static const float MIN = 1000.0f;

	//---------------------------------------------------------------------------
	//60FPS��������
	NTlmt = timeGetTime();

	if (NTlmt - BTlmt <= MIN / GAME_FPS)			//1000 / 60ms�o���Ă��Ȃ������烊�^�[���łƂ΂����Ƃ�60FPS���������
	{
		return false;
	}
	BTlmt = NTlmt;
	//---------------------------------------------------------------------------

	return true;
}

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPSTR lpszCmdParam, int nCmdshow)
{
	Window::Create();
	//Window������
	if (Window::GetInstance().InitWindow(hInst, nCmdshow) == false)		//�E�C���h�E������
	{
		return false;
	}

	Direct3D::Create();
	//�`��n������
	if (Direct3D::GetInstance().InitDirect3D() == false)
	{
		return false;
	}

	timeBeginPeriod(1);

	//DirectSound������
	DirectSound::Create();
	if (DirectSound::GetInstance().InitDirectSound() == false)
	{
		return false;
	}

	// �Q�[���Ɋւ��鏉�������� ---------------------------
	SceneSwitcher::Create();
	ResourceManager::Create();
	SceneSwitchEffect::Create();
	EffectManager::Create();
	GetSound.Create();
	GetSound.Initialize();
	BackToTitle::Create();
	GetCursor.Create();

	ShowCursor(FALSE);			//�J�[�\����\�����Ȃ�	��FALSE�̉񐔂��J�E���g���Ă���̂ŕK�v�ȏ�ɌĂ΂Ȃ�



	//�X�v���C�g�I�u�W�F�N�g�쐬
	Sprite::Create();

	//�t�H���g�I�u�W�F�N�g�쐬
	Font::Create();
	
	GetSceneSwitcher.SwitchScene(new TitleScene());

	MSG msg;

	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			if (FPSLimiter() == true)		//FPS����
			{
				GetSceneSwitcher.NowScene();
				GetSceneSwitchEffect.Update();
				GetCursor.Update();
			}
		}
	}

	// �Q�[���Ɋւ���I������ ---------------------------
	SceneSwitcher::Destroy();
	ResourceManager::Destroy();
	SceneSwitchEffect::Destroy();
	EffectManager::Destroy();
	GetSound.Destroy();
	BackToTitle::Destroy();
	GetCursor.Destroy();
	ShowCursor(TRUE);			//�J�[�\����\������	��TRUE�̉񐔂��J�E���g���Ă���̂ŕK�v�ȏ�ɌĂ΂Ȃ�	�Ǘ�����N���X�����


	Sprite::GetInstance().GetSprite()->Release();	// �X�v���C�g

	timeEndPeriod(1);

	Window::Destroy();
	Direct3D::Destroy();
	DirectSound::Destroy();

	return (int)msg.wParam;
}