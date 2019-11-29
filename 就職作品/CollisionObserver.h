#pragma once
#include"main.h"
#include"commonObj/SnowBallManager.h"
#include"Enemy/EnemyManager.h"
#include"Map/MapObjManager.h"
#include"Effect/EffectManager.h"
#include"Player/Player.h"
#include"Player/PlayerCamera.h"
#include"Item/DecorationManager.h"
class CollisionObserver {
public:
	CollisionObserver();
	~CollisionObserver();
	//敵と雪玉の当たり判定	SnowBallManagerとEnemyManagerをポインタで渡す
	void SnowBalltoEnemy(SnowBallManager *SnowBallManager, EnemyManager *EnemyManager);
	//雪玉とMapオブジェの当たり判定	SnowBallManagerとMapObjManagerをポインタで渡す
	void SnowBalltoObj(SnowBallManager *SnowBallManager, MapObjManager *MapObjManager);
	//playerのマップオブジェクトに対する当たり判定
	void PlayertoObj(PlayerCamera *PlayerCam, MapObjManager *MapObjManager);
	//敵の雪玉とプレイヤーの当たり判定
	void EnemySnowBalltoPlayer(Player *Player, SnowBallManager *SnowBallManager);
	//Mapオブジェとデコレーションの当たり判定
	void DecorationToMapObj(DecorationManager *DecorationManager, MapObjManager *MapObjManager);
};