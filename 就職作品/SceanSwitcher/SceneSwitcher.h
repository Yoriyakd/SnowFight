#pragma once
#include"SceneBase.h"
#include"../SingletonBase.h"

#define GetSceneSwitcher SceneSwitcher::GetInstance()

class SceneSwitcher : public SingletonBase<SceneSwitcher>
{
	friend class SingletonBase<SceneSwitcher>;			//SingletonBaseでのインスタンス作成削除は許可
public:
	void NowScene(void);
	//変える先のシーンをnewして入れる
	void SwitchScene(SceneBase *NowScene);

private:
	SceneSwitcher();
	~SceneSwitcher();
	SceneBase *Scene;
};