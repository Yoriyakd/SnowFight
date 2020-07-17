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


////  グローバル変数宣言

LPD3DXSPRITE lpSprite;	// スプライト
LPD3DXFONT lpFont;		// フォント

bool gameFullScreen;	// フルスクリーン（true,false)
const int GameFPS = 60;		//ゲームのFPS指定


LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト
LPDIRECTSOUNDBUFFER lpSPrimary;

//60FPS固定のための処理とりあえずここに書く
bool FPSLimiter(void)
{
	static DWORD NTlmt, BTlmt;
	static const float MIN = 1000.0f;

	//---------------------------------------------------------------------------
	//60FPS制限処理
	NTlmt = timeGetTime();

	if (NTlmt - BTlmt <= MIN / GameFPS)			//1000 / 60ms経っていなかったらリターンでとばすことで60FPS上限をつける
	{
		return false;
	}
	BTlmt = NTlmt;
	//---------------------------------------------------------------------------

	return true;
}

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


//DirectX,Windowの作成は学校配布コードです

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPSTR lpszCmdParam, int nCmdshow)
{
	Window::Create();
	//Window初期化
	if (Window::GetInstance().InitWindow(hInst, nCmdshow) == false)		//ウインドウ初期化
	{
		return false;
	}

	Direct3D::Create();
	//描画系初期化
	if (Direct3D::GetInstance().InitDirect3D() == false)
	{
		return false;
	}


	timeBeginPeriod(1);

	//---------------------DirectSound関連-----------------------
	DirectSoundCreate8(NULL, &lpDSound, NULL);

	//協調レベルを設定
	lpDSound->SetCooperativeLevel(Window::GetInstance().GetHWND(), DSSCL_PRIORITY);

	// プライマリ・バッファの作成
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// プライマリ・バッファを指定
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	// バッファを作る
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

	// プライマリ・バッファのWaveフォーマットを設定
	// 　　　優先協調レベル以上の協調レベルが設定されている必要があります．
	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;		// ２チャンネル（ステレオ）
	pcmwf.nSamplesPerSec = 44100;	// サンプリング・レート　44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = 16;		// 16ビット
	lpSPrimary->SetFormat(&pcmwf);

	CoInitialize(NULL);

	// ゲームに関する初期化処理 ---------------------------
	SceneSwitcher::Create();
	ResourceManager::Create();
	SceneSwitchEffect::Create();
	EffectManager::Create();
	GetSound.Create();
	GetSound.Initialize();
	BackToTitle::Create();
	GetCursor.Create();

	ShowCursor(FALSE);			//カーソルを表示しない	※FALSEの回数をカウントしているので必要以上に呼ばない



	// スプライト作成
	D3DXCreateSprite(Direct3D::GetInstance().GetD3DDevice(), &lpSprite);
	lpSprite->OnResetDevice();

	// フォント作成
	D3DXCreateFont(Direct3D::GetInstance().GetD3DDevice(), 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "ＭＳ ゴシック", &lpFont);

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
			if (FPSLimiter() == true)		//FPS制御
			{
				GetSceneSwitcher.NowScene();
				GetSceneSwitchEffect.Update();
				GetCursor.Update();
			}
		}
	}

	// ゲームに関する終了処理 ---------------------------
	SceneSwitcher::Destroy();
	ResourceManager::Destroy();
	SceneSwitchEffect::Destroy();
	EffectManager::Destroy();
	GetSound.Destroy();
	BackToTitle::Destroy();
	GetCursor.Destroy();
	ShowCursor(TRUE);			//カーソルを表示する	※TRUEの回数をカウントしているので必要以上に呼ばない	管理するクラスを作る


	lpSprite->Release();	// スプライト
	lpFont->Release();		// フォント

	timeEndPeriod(1);

	lpSPrimary->Release();
	lpDSound->Release();

	CoUninitialize();

	Window::Destroy();
	Direct3D::Destroy();

	return (int)msg.wParam;
}