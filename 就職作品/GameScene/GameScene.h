#pragma once
#include<d3d9.h>
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../Func.h"



class GameScene : public SceneBase {
private:
	XFILE fieldMesh;
	D3DXMATRIX fieldMat;

public:
	GameScene();
	~GameScene();
	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update();
};
