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

//60FPS固定のための処理とりあえずここに書く
bool FPSLimiter(void)
{
	static DWORD NTlmt, BTlmt;
	static const float MIN = 1000.0f;

	//---------------------------------------------------------------------------
	//60FPS制限処理
	NTlmt = timeGetTime();

	if (NTlmt - BTlmt <= MIN / GAME_FPS)			//1000 / 60ms経っていなかったらリターンでとばすことで60FPS上限をつける
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

	//DirectSound初期化
	DirectSound::Create();
	if (DirectSound::GetInstance().InitDirectSound() == false)
	{
		return false;
	}

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



	//スプライトオブジェクト作成
	Sprite::Create();

	//フォントオブジェクト作成
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


	Sprite::GetInstance().GetSprite()->Release();	// スプライト

	timeEndPeriod(1);

	Window::Destroy();
	Direct3D::Destroy();
	DirectSound::Destroy();

	return (int)msg.wParam;
}