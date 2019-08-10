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
	//•Ï‚¦‚éæ‚ÌƒV[ƒ“‚ğnew‚µ‚Ä“ü‚ê‚é
	void SwitchScene(SceneBase *NowScene);
};
