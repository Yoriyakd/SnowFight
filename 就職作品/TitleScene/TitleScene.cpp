#include "TitleScene.h"
#include"../GameScene/GameScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Render3D(void)
{
}

void TitleScene::SetCamera(void)
{
}

void TitleScene::Render2D(void)
{
}

bool TitleScene::Update(void)
{
	if (GetAsyncKeyState('P') & 0x8000)
	{
		sceneSwitcher.SwitchScene(new GameScene(1));
		return false;
	}
	return true;
}
