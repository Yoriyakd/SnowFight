#pragma once
#include<d3d9.h>
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"../Player/Player.h"
#include<vector>
#include"../Map/LoadStageData.h"
#include"../Map/Ground.h"
#include"../Map/WallManager.h"
#include"../Enemy/EnemyManager.h"
#include"../Enemy/SetEnemies.h"
#include"../commonObj/SkyBox.h"
#include"../Map/FenceManager.h"
#include"../commonObj/SnowBallManager.h"
#include"../CollisionObserver.h"
#include"../Effect/EffectManager.h"


class GameScene : public SceneBase {
private:
	LoadStageData *loadStageData;
	;
	Ground *ground;
	Player *player;
	SkyBox *skyBox;
	FenceManager *fenceManager;
	SnowBallManager *snowBallManager;
	WallManager *wallManager;
	CollisionObserver *collisionObserver;
	SetEnemies *setEnemies;

	StageBorder stageBorder;

	float stageSizeX, stageSizeZ;
public:
	GameScene(int);
	~GameScene();
	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);
};

extern EnemyManager *enemyManager;