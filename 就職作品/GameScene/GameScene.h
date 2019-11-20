#pragma once
#include<d3d9.h>
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"
#include"../Player/Player.h"
#include<vector>
#include"../Map/LoadStageData.h"
#include"../Map/Ground.h"
#include"../Map/MapObjManager.h"
#include"../Enemy/EnemyManager.h"
#include"../commonObj/SkyBox.h"
#include"../Map/FenceManager.h"
#include"../commonObj/SnowBallManager.h"
#include"../CollisionObserver.h"
#include"../Effect/EffectManager.h"
#include"EventManager.h"
#include"../Item/ItemManager.h"


class GameScene : public SceneBase {
public:
	GameScene(int);
	~GameScene();
	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);

private:
	LoadStageData *loadStageData;
	Ground *ground;
	SkyBox *skyBox;
	//FenceManager *fenceManager;
	SnowBallManager *snowBallManager;
	MapObjManager *mapObjManager;
	CollisionObserver *collisionObserver;	
	PlayerCamera *playerCam;
	EventManager *eventManager;
};

extern EnemyManager *enemyManager;
extern Player *player;
extern StageBorder *stageBorder;
extern ItemManager *itemManager;
extern const float Gravity;