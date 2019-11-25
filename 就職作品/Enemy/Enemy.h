#pragma once
#include<vector>
#include"../main.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBallManager.h"
#include<vector>
class Enemy {
public:
	Enemy(D3DXVECTOR3);
	~Enemy();
	virtual bool Update(SnowBallManager *snowBallManager);
	virtual void Draw(void);
	virtual D3DXVECTOR3 GetPos(void);
	virtual D3DXMATRIX GetMat(void);
	virtual XFILE GetMesh(void);
	virtual void GetCollisionSphere(CollisionSphere *CollisionSphereA, CollisionSphere *CollisionSphereB);
	void CheckOverlapEnemies(D3DXVECTOR3*);
	bool TakeDamage(int Damage);

protected:
	int HP;		//�̗�	���1����1����

private:
	XFILE mesh;
	D3DXMATRIX mat, rotMat, transMat;
	virtual void ShootSnowBall(float TragetAng);
	virtual void EngagingMode(void);		//��풆�̍s��
	virtual void FreeMode(void);			//���������̍s��
	virtual void StageBorderProcessing(void);

	int ShootCoolTime;					//��ʔ��˂̃N�[���^�C��
	float MoveInterval;						//freeMode�������܂ł̎���
	float freeMoveCnt;							//freeMode�������K�v�̂��鎞�Ԃ̎���
	SnowBallManager *snowBallManager;		//snowBallManager�̃|�C���^��ۑ�����

	float searchRange;						//���G�͈�
	const float maxLength = 40.0f, minLength = 15.0f;						//��펞�̋����̍ő�ŏ��͈�
	float limitLength;		//��펞��鋗��
	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//��펞�̈ړ�		�����ˎ��͎~�܂�悤�ɂ���

};