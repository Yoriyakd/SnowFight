#pragma once
#include"SceneBase.h"
class SceneSwitcher
{
private:
	SceneBase *Scene;
public:
	SceneSwitcher();
	~SceneSwitcher();
	void NowScene(void);
	void SwitchScene(SceneBase *NowScene);
};
