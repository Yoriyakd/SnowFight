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
	//変える先のシーンをnewして入れる
	void SwitchScene(SceneBase *NowScene);
};
