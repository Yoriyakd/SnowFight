#pragma once
#include"main.h"
#include"commonObj/SnowBall.h"
#include"Enemy/Enemy.h"
#include"Map/MapObj.h"
#include"Player/PlayerCamera.h"
#include"Player/Player.h"
#include"Item/DecorationManager.h"
#include"GameScene/EventManager.h"

class CollisionObserver {
public:
	CollisionObserver();
	~CollisionObserver();
	//敵と雪玉の当たり判定	SnowBallManagerとEnemyManagerをポインタで渡す
	bool SnowBalltoEnemy(SnowBall *SnowBall, Enemy *Enemy);
	//雪玉とMapオブジェの当たり判定	SnowBallManagerとMapObjManagerをポインタで渡す
	bool SnowBalltoObj(SnowBall *SnowBall, MapObj *MapObj);
	//playerのマップオブジェクトに対する当たり判定
	void PlayertoObj(PlayerCamera *PlayerCam, MapObj *MapObj);
	//敵の雪玉とプレイヤーの当たり判定
	bool EnemySnowBalltoPlayer(Player *Player, SnowBall *SnowBall);
	//Mapオブジェとデコレーションの当たり判定
	void DecorationToMapObj(DecorationBase *Decoration, MapObj *MapObj, EventManager *EventManager);

private:
	void GetPolyNormal(D3DXVECTOR3 *ObjNormal ,LPD3DXMESH ObjMesh, const DWORD *PolyNo);
};