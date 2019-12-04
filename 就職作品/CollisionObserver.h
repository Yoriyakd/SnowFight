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
	//�G�Ɛ�ʂ̓����蔻��	SnowBallManager��EnemyManager���|�C���^�œn��
	bool SnowBalltoEnemy(SnowBall *SnowBall, Enemy *Enemy);
	//��ʂ�Map�I�u�W�F�̓����蔻��	SnowBallManager��MapObjManager���|�C���^�œn��
	bool SnowBalltoObj(SnowBall *SnowBall, MapObj *MapObj);
	//player�̃}�b�v�I�u�W�F�N�g�ɑ΂��铖���蔻��
	void PlayertoObj(PlayerCamera *PlayerCam, MapObj *MapObj);
	//�G�̐�ʂƃv���C���[�̓����蔻��
	bool EnemySnowBalltoPlayer(Player *Player, SnowBall *SnowBall);
	//Map�I�u�W�F�ƃf�R���[�V�����̓����蔻��
	void DecorationToMapObj(DecorationBase *Decoration, MapObj *MapObj, EventManager *EventManager);

private:
	void GetPolyNormal(D3DXVECTOR3 *ObjNormal ,LPD3DXMESH ObjMesh, const DWORD *PolyNo);
};