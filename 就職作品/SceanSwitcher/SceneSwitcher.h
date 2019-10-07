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
//シーンを切る変えるときに呼ぶ	main.cppで宣言
extern SceneSwitcher sceneSwitcher;