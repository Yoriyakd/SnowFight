#include "MenuScene.h"
#include"../GameScene/GameScene.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Render3D(void)
{
}

void MenuScene::SetCamera(void)
{
}

void MenuScene::Render2D(void)
{
}

bool MenuScene::Update(void)
{
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		sceneSwitcher.SwitchScene(new GameScene(1));
		return false;
	}
	return true;
}
