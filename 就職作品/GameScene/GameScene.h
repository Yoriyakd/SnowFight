#pragma once
#include<d3d9.h>
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"../Player/Player.h"
#include<vector>
#include"../Map/SetStageData.h"
#include"../Map/Ground.h"
#include"../Map/Wall.h"
#include"../Enemy/Enemy.h"
#include"../Enemy/EnemyManager.h"
#include"../commonObj/SkyBox.h"
#include"../Map/FenceManager.h"

//enum objType { EMPTY, WALL, ENEMY = 5 };

class GameScene : public SceneBase {
private:
	
	

	std::vector <Wall*> wall;		//wallマネージャー作る

	SetStageData *setStageData;
	EnemyManager *enemyManager;
	Ground *ground;
	Player *player;
	SkyBox *skyBox;
	FenceManager *fenceManager;

	
	void CollisionDetectionS_PtoE(void);



public:
	GameScene(int);
	~GameScene();
	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);
};
