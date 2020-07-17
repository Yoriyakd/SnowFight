#include<time.h>
#include<stdio.h>
#include"main.h"

#include"Window/Window.h"
#include"DirectX/Direct3D.h"

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


D3DPRESENT_PARAMETERS d3dpp;


////  �O���[�o���ϐ��錾

LPD3DXSPRITE lpSprite;	// �X�v���C�g
LPD3DXFONT lpFont;		// �t�H���g

bool gameFullScreen;	// �t���X�N���[���itrue,false)
const int GameFPS = 60;		//�Q�[����FPS�w��


LPDIRECTSOUND8 lpDSound;	//DirectSound�I�u�W�F�N�g
LPDIRECTSOUNDBUFFER lpSPrimary;

//60FPS�Œ�̂��߂̏����Ƃ肠���������ɏ���
bool FPSLimiter(void)
{
	static DWORD NTlmt, BTlmt;
	static const float MIN = 1000.0f;

	//---------------------------------------------------------------------------
	//60FPS��������
	NTlmt = timeGetTime();

	if (NTlmt - BTlmt <= MIN / GameFPS)			//1000 / 60ms�o���Ă��Ȃ������烊�^�[���łƂ΂����Ƃ�60FPS���������
	{
		return false;
	}
	BTlmt = NTlmt;
	//---------------------------------------------------------------------------

	return true;
}

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


//DirectX,Window�̍쐬�͊w�Z�z�z�R�[�h�ł�

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

	//---------------------DirectSound�֘A-----------------------
	DirectSoundCreate8(NULL, &lpDSound, NULL);

	//�������x����ݒ�
	lpDSound->SetCooperativeLevel(Window::GetInstance().GetHWND(), DSSCL_PRIORITY);

	// �v���C�}���E�o�b�t�@�̍쐬
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// �v���C�}���E�o�b�t�@���w��
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	// �o�b�t�@�����
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

	// �v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	// �@�@�@�D�拦�����x���ȏ�̋������x�����ݒ肳��Ă���K�v������܂��D
	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;		// �Q�`�����l���i�X�e���I�j
	pcmwf.nSamplesPerSec = 44100;	// �T���v�����O�E���[�g�@44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = 16;		// 16�r�b�g
	lpSPrimary->SetFormat(&pcmwf);

	CoInitialize(NULL);

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



	// �X�v���C�g�쐬
	D3DXCreateSprite(Direct3D::GetInstance().GetD3DDevice(), &lpSprite);
	lpSprite->OnResetDevice();

	// �t�H���g�쐬
	D3DXCreateFont(Direct3D::GetInstance().GetD3DDevice(), 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "�l�r �S�V�b�N", &lpFont);

	lpFont->OnResetDevice();

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


	lpSprite->Release();	// �X�v���C�g
	lpFont->Release();		// �t�H���g

	timeEndPeriod(1);

	lpSPrimary->Release();
	lpDSound->Release();

	CoUninitialize();

	Window::Destroy();
	Direct3D::Destroy();

	return (int)msg.wParam;
}