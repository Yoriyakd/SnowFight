#pragma once
#include"SceneBase.h"
class SceneSwitcher
{
public:
	SceneSwitcher();
	~SceneSwitcher();
	void NowScene(void);
	//�ς����̃V�[����new���ē����
	void SwitchScene(SceneBase *NowScene);

private:
	SceneBase *Scene;
};
//�V�[����؂�ς���Ƃ��ɌĂ�	main.cpp�Ő錾
extern SceneSwitcher sceneSwitcher;