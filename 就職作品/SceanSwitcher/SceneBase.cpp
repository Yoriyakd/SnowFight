#include<d3dx9.h>
#include"SceneBase.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;


SceneBase::~SceneBase()
{
}

bool SceneBase::Update(void)
{
	return true;
}

void SceneBase::Render3D(void)
{
}

void SceneBase::Render2D(void)
{
}

void SceneBase::SetCamera(void)
{
}

void SceneBase::Frame(void)
{
	//---------------------------------------------------------------------------
	//60FPS制限処理
	NTlmt = timeGetTime();

	if (NTlmt - BTlmt <= 1000.0f / 60.0f)			//1 / 60秒　経っていなかったらリターンでとばすことで60FPS上限をつける
	{
		return;
	}
	BTlmt = NTlmt;
	//---------------------------------------------------------------------------

	NTlmt = timeGetTime();
	cntFPS++;
	
	if ((NTcnt - BTcnt) >= 1000)
	{
		FPS = cntFPS;
		cntFPS = 0;				//リセット
		BTcnt = NTcnt;		//基準時間を変更
	}
	//---------------------------------------------------------------------------

	if (Update() == false)											//falseを返さないと消したシーンをが実行されるので注意
	{
		return;
	}
	lpD3DDevice->BeginScene();
	lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	SetCamera();
	Render3D();
	Render2D();
	lpD3DDevice->EndScene();
	lpD3DDevice->Present(NULL, NULL, NULL, NULL);
}