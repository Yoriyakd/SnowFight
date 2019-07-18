#include "SceneSwitcher.h"

SceneSwitcher::SceneSwitcher()
{
	Scene = nullptr;
}

SceneSwitcher::~SceneSwitcher()
{
	if (Scene != nullptr)
	{
		delete Scene;
	}
}

void SceneSwitcher::NowScene(void)
{
	if (Scene != nullptr)
	{
		Scene->Frame();			//���̃V�[���̃t���[�������s
	}
}

void SceneSwitcher::SwitchScene(SceneBase * NowScene)
{
	if (Scene != nullptr)
	{
		delete Scene;
	}
	Scene = NowScene;
}
