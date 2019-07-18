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
		Scene->Frame();			//今のシーンのフレームを実行
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
