#pragma once
#include"SceneBase.h"
#include"../SingletonBase.h"

#define SwitcheScene SceneSwitcher::GetInstance()

class SceneSwitcher : public SingletonBase<SceneSwitcher>
{
	friend class SingletonBase<SceneSwitcher>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	void NowScene(void);
	//�ς����̃V�[����new���ē����
	void SwitchScene(SceneBase *NowScene);

private:
	SceneSwitcher();
	~SceneSwitcher();
	SceneBase *Scene;
};

SceneSwitcher* SingletonBase<SceneSwitcher>::instance = nullptr;