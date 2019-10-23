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
	virtual void EngagingMode(void);		//交戦中の行動
	virtual void FreeMode(void);			//未発見時の行動
	virtual void StageBorderProcessing(void);

	int ShootCoolTime;					//雪玉発射のクールタイム
	float MoveInterval;						//freeMode時動くまでの時間
	float freeMoveCnt;							//freeMode時動く必要のある時間の時間
	SnowBallManager *snowBallManager;		//snowBallManagerのポインタを保存する
protected:

	

public:
	Enemy(D3DXVECTOR3);
	~Enemy();
	virtual bool Update(SnowBallManager *snowBallManager);
	virtual void Draw(void);
	virtual D3DXVECTOR3 GetPos(void);
	virtual void GetCollisionSphere(CollisionSphere *CollisionSphereA, CollisionSphere *CollisionSphereB);
};