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
	//�ς����̃V�[����new���ē����
	void SwitchScene(SceneBase *NowScene);
};
//�V�[����؂�ς���Ƃ��ɌĂ�	main.cpp�Ő錾
extern SceneSwitcher sceneSwitcher;