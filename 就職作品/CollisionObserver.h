#pragma once
#include"main.h"
#include"commonObj/SnowBall.h"
#include"Enemy/Enemy.h"
#include"Map/MapObj.h"
#include"Player/PlayerCamera.h"
#include"Player/Player.h"
#include"Item/DecorationManager.h"
#include"GameScene/EventManager.h"
#include"Sound/SoundManager.h"

class CollisionObserver {
public:
	//�G�̖X�q�Ɛ�ʂ̓����蔻��	SnowBallManager��EnemyManager���|�C���^�œn��
	static bool SnowBalltoEnemyHat(SnowBall *SnowBall, Enemy *Enemy);
	//�G�Ɛ�ʂ̓����蔻��	SnowBallManager��EnemyManager���|�C���^�œn��
	static bool SnowBalltoEnemy(SnowBall *SnowBall, Enemy *Enemy);
	//��ʂ�Map�I�u�W�F�̓����蔻��	SnowBallManager��MapObjManager���|�C���^�œn��
	static bool SnowBalltoObj(SnowBall *SnowBall, MapObj *MapObj);
	//player�̃}�b�v�I�u�W�F�N�g�ɑ΂��铖���蔻��
	static void PlayertoObj(PlayerCamera *PlayerCam, MapObj *MapObj);
	//�G�̐�ʂƃv���C���[�̓����蔻��
	static bool EnemySnowBalltoPlayer(Player *Player, SnowBall *SnowBall);
	//Map�I�u�W�F�ƃf�R���[�V�����̓����蔻��
	static void DecorationToMapObj(DecorationBase *Decoration, MapObj *MapObj, GameNormManager *GameNormManager);
	//Map�I�u�W�F�ƓG�̓����蔻��
	static void EnemyToMapObj(Enemy *Enemy, MapObj *MapObj);

private:
	CollisionObserver();
	~CollisionObserver();
	static void GetPolyNormal(D3DXVECTOR3 *ObjNormal ,LPD3DXMESH ObjMesh, const DWORD *PolyNo);
};