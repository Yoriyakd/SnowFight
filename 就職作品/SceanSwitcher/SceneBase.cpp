#include<d3dx9.h>
#include"SceneBase.h"
#include"../Sound/SoundManager.h"
#include"../Effect/SceneSwitchEffect.h"
#include"../DirectX/Direct3D.h"



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
	Direct3D::GetInstance().GetD3DDevice()->BeginScene();
	Direct3D::GetInstance().GetD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	SetCamera();
	Render3D();
	Render2D();
	Direct3D::GetInstance().GetD3DDevice()->EndScene();
	Direct3D::GetInstance().GetD3DDevice()->Present(NULL, NULL, NULL, NULL);
}

