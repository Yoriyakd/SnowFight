#pragma once
#include<vector>
#include"../main.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBallManager.h"
class Enemy {
private:
	XFILE mesh;
	D3DXMATRIX mat, rotMat;
	virtual void ShootSnowBall(float TragetAng);
	virtual void EngagingMode(void);		//��풆�̍s��
	virtual void FreeMode(void);			//���������̍s��
	virtual void StageBorderProcessing(void);

	int ShootCoolTime;					//��ʔ��˂̃N�[���^�C��
	float MoveInterval;						//freeMode�������܂ł̎���
	float freeMoveCnt;							//freeMode�������K�v�̂��鎞�Ԃ̎���
	SnowBallManager *snowBallManager;		//snowBallManager�̃|�C���^��ۑ�����
protected:

	

public:
	Enemy(D3DXVECTOR3);
	~Enemy();
	virtual bool Update(SnowBallManager *snowBallManager);
	virtual void Draw(void);
	virtual D3DXVECTOR3 GetPos(void);
	virtual void GetCollisionSphere(CollisionSphere *CollisionSphereA, CollisionSphere *CollisionSphereB);
};