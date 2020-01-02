#pragma once
#include"SceneBase.h"
#include"../SingletonBase.h"

#define SwitcheScene SceneSwitcher::GetInstance()

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

SceneSwitcher* SingletonBase<SceneSwitcher>::instance = nullptr;