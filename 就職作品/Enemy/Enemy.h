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
	bool GetJumpState();		//ジャンプしているか
	D3DXVECTOR3 GetPlayerVec();		//playerとのベクトルを返す
	float GetToPlayerAng();
	void PushedObj(const D3DXVECTOR3 &PushVec);

	D3DXMATRIX GetHatMat(void);
	float GetHatRadius(void);
	float GetHatHight(void);

	float CalculateEnemyToPlayerAng();

	//渡された角度分回るジャンプをする
	void Spin(float AtOneceAng);
	virtual void Jump(void);
	virtual void FrontJump(void);
	virtual void BackJump(void);
	virtual void ShootSnowBall();

	void CheckOverlapEnemies(const D3DXVECTOR3*);

	bool TakeDamage(int Damage);



protected:
	int HP;		//体力	雪玉1発で1減少

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

	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//交戦時の移動		球発射時は止まるようにする

	const float SphereRadiusHead = 1.3f;
	const float SphereRadiusBody = 2.0f;

};