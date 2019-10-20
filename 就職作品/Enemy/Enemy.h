#pragma once
#include<vector>
#include"../main.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBallManager.h"
class Enemy {
private:
	XFILE mesh;
	D3DXMATRIX mat, rotMat, transMat;
	virtual void ShootSnowBall(float TragetAng);
	virtual void EngagingMode(void);		//åêÌíÜÇÃçsìÆ
	virtual void FreeMode(void);			//ñ¢î≠å©éûÇÃçsìÆ
	SnowBallManager *snowBallManager;
protected:

	

public:
	Enemy(D3DXVECTOR3);
	~Enemy();
	virtual bool Update(SnowBallManager *snowBallManager);
	virtual void Draw(void);
	virtual D3DXVECTOR3 GetPos(void);
	virtual void GetCollisionSphere(CollisionSphere *CollisionSphereA, CollisionSphere *CollisionSphereB);
};