#pragma once
#include"SceneBase.h"
class SceneSwitcher
{
public:
	SceneSwitcher();
	~SceneSwitcher();
	void NowScene(void);
	//変える先のシーンをnewして入れる
	void SwitchScene(SceneBase *NowScene);

private:
	SceneBase *Scene;
};
//シーンを切る変えるときに呼ぶ	main.cppで宣言
extern SceneSwitcher sceneSwitcher;