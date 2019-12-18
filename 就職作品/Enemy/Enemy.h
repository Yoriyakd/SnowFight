#pragma once
#include<vector>
#include"../main.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBallManager.h"
#include"../Player/Player.h"
#include<vector>
class Enemy {
public:
	Enemy(D3DXVECTOR3);
	~Enemy();
	virtual bool Update(Player &Player, SnowBallManager &SnowBallManager, StageBorder &StageBorder);
	virtual void Draw(void);
	//--------------------------------------------
	//Getter
	//--------------------------------------------
	virtual D3DXVECTOR3 GetPos(void);
	virtual D3DXMATRIX GetMat(void);
	virtual XFILE GetMesh(void);
	virtual void GetCollisionSphere(CollisionSphere *CollisionSphereA, CollisionSphere *CollisionSphereB);

	D3DXMATRIX GetHatMat(void);
	float GetHatRadius(void);
	float GetHatHight(void);

	void CheckOverlapEnemies(D3DXVECTOR3*);

	bool TakeDamage(int Damage);

protected:
	int HP;		//�̗�	���1����1����

private:
	XFILE bodyMesh;
	D3DXMATRIX mat, rotMat, transMat;

	//------------------------------------------------
	XFILE hatMesh;
	D3DXMATRIX hatMat, hatOffsetMat, hatRotMat;

	const float hatRadius = 1.0f, hatHight = 2.0f;
	//------------------------------------------------

	virtual void ShootSnowBall(float TragetAng, SnowBallManager &snowBallManager);
	virtual void EngagingMode(const D3DXVECTOR3 TragetPos, SnowBallManager &snowBallManager);		//��풆�̍s��
	virtual void FreeMode(void);			//���������̍s��
	virtual void StageBorderProcessing(StageBorder &StageBorder);

	int ShootCoolTime;					//��ʔ��˂̃N�[���^�C��
	float MoveInterval;						//freeMode�������܂ł̎���
	float freeMoveCnt;							//freeMode�������K�v�̂��鎞�Ԃ̎���

	float searchRange;						//���G�͈�
	const float maxLength = 40.0f, minLength = 15.0f;						//��펞�̋����̍ő�ŏ��͈�
	float limitLength;		//��펞��鋗��
	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//��펞�̈ړ�		�����ˎ��͎~�܂�悤�ɂ���

	const float SphereRadiusHead = 1.3f;
	const float SphereRadiusBody = 2.0f;

};