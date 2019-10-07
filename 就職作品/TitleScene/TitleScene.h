#pragma once
#include<d3d9.h>
#include"../main.h"
//#include"../ResourceManager.h"
//#include"../GameScene/GameScene.h"

class TitleScene : public SceneBase {

public:
	TitleScene();
	~TitleScene();

	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);

};
