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
		//今のシーンのフレームを実行
		Scene->Frame();
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
