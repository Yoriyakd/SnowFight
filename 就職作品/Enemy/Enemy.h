#pragma once
#include<vector>
#include"../main.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBallManager.h"
#include"../Player/Player.h"
#include<vector>
#include"EnemyState/EnemyStateBase.h"
#include"EnemyState/PlayerSearchState.h"
class Enemy {
public:
	Enemy(D3DXVECTOR3);
	~Enemy();
	virtual bool Update(SnowBallManager &SnowBallManager, StageBorder &StageBorder);
	virtual void Draw(void);
	//--------------------------------------------
	//Getter
	//--------------------------------------------
	virtual const D3DXVECTOR3 GetPos(void);
	virtual const D3DXMATRIX GetMat(void);
	virtual void GetCollisionSphere(CollisionSphere *CollisionSphereA, CollisionSphere *CollisionSphereB);
	bool GetJumpState();		//�W�����v���Ă��邩
	D3DXVECTOR3 GetPlayerVec();		//player�Ƃ̃x�N�g����Ԃ�
	float GetToPlayerAng();
	void PushedObj(const D3DXVECTOR3 &PushVec);

	D3DXMATRIX GetHatMat(void);
	float GetHatRadius(void);
	float GetHatHight(void);

	float CalculateEnemyToPlayerAng();

	//�n���ꂽ�p�x�����W�����v������
	void Spin(float AtOneceAng);
	virtual void Jump(void);
	virtual void FrontJump(void);
	virtual void BackJump(void);
	virtual void ShootSnowBall();

	void CheckOverlapEnemies(const D3DXVECTOR3*);

	bool TakeDamage(int Damage);



protected:
	int HP;		//�̗�	���1����1����

private:
	EnemyStateBase *nowState;
	XFILE bodyMesh, handMesh;
	D3DXMATRIX mat, rotMat, transMat;

	//------------------------------------------------
	XFILE hatMesh;
	D3DXMATRIX hatMat, hatOffsetMat, hatRotMat;

	const float hatRadius = 1.0f, hatHight = 2.0f;
	//------------------------------------------------

	virtual void StageBorderProcessing(StageBorder &StageBorder);

	bool jumpState;

	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//��펞�̈ړ�		�����ˎ��͎~�܂�悤�ɂ���

	const float SphereRadiusHead = 1.3f;
	const float SphereRadiusBody = 2.0f;

};