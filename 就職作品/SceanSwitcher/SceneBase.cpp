#include<d3dx9.h>
#include"SceneBase.h"
#include"../Sound/SoundManager.h"
#include"../Effect/SceneSwitchEffect.h"

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
	if (Update() == false)											//false‚ð•Ô‚³‚È‚¢‚ÆÁ‚µ‚½ƒV[ƒ“‚ð‚ªŽÀs‚³‚ê‚é‚Ì‚Å’ˆÓ
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

