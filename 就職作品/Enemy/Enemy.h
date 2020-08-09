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
	virtual bool Update(GameScene* _GameScene);
	virtual void Draw(void);
	//--------------------------------------------
	//Getter
	//--------------------------------------------
	virtual const D3DXVECTOR3 GetPos(void);
	virtual const D3DXMATRIX GetMat(void);
	virtual void GetCollisionSphere(CollisionSphere *CollisionSphereA, CollisionSphere *CollisionSphereB);
	float GetRadisu(void);
	//�W�����v���Ă��邩
	bool IsJump();		
	//player�Ƃ̃x�N�g����Ԃ�
	D3DXVECTOR3 GetPlayerVec();		
	//�n���ꂽPos�Ƃ̃x�N�g����Ԃ�
	D3DXVECTOR3 GetPlayerVec(D3DXVECTOR3 &Offset);
	//player�Ƃ̊p�x��Ԃ�
	float GetToPlayerAng();
	//player�Ƃ̊p�x��Ԃ��n���ꂽPos��
	float GetToPlayerAng(D3DXVECTOR3 &Pos);

	D3DXMATRIX GetHatMat(void);
	float GetHatRadius(void);
	float GetHatHight(void);
	float GetSensingLength(void);
	//--------------------------------------------
	//Setter
	//--------------------------------------------
	void SetMat(D3DXMATRIX &_Mat);
	void SetShootFlag(bool flag);
	void PushedObj(const D3DXVECTOR3 &PushVec);

	float CalculateEnemyToPlayerAng();

	//�n���ꂽ�p�x�����W�����v������
	void Spin(float AtOneceAng);
	virtual void Jump(void);
	virtual void FrontJump(void);
	virtual void BackJump(void);
	virtual void ShootSnowBall(GameScene* GameScene);

	void CheckOverlapEnemies(const D3DXVECTOR3*);

	bool TakeDamage(int Damage);



protected:
	static const int DEFAULT_HP;
	int nowHP;		//�̗�	���1����1����

private:
	EnemyStateBase *nowState;
	XFILE bodyMesh, handMesh;
	D3DXMATRIX mat, rotMat, transMat;

	XFILE hatMesh;
	D3DXMATRIX hatMat, hatOffsetMat, hatRotMat;

	bool isShoot = false;		//true�Ȃ��ʂ𓊂���ʂȕ��@���l������
	//------------------------------------------------
	//�萔
	//------------------------------------------------
	const static float HAT_RADIUS, HAT_HIGHT;
	const static float SENSING_LENGTH;
	//------------------------------------------------

	virtual void StageBorderProcessing(const StageBorder &StageBorder);

	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//��펞�̈ړ�		�����ˎ��͎~�܂�悤�ɂ���

	const static float SPHERE_RADIUS_HEAD;
	const static float SPHER_RADIUS_BODY;

};