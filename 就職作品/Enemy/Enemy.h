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
	//ジャンプしているか
	bool IsJump();		
	//playerとのベクトルを返す
	D3DXVECTOR3 GetPlayerVec();		
	//渡されたPosとのベクトルを返す
	D3DXVECTOR3 GetPlayerVec(D3DXVECTOR3 &Offset);
	//playerとの角度を返す
	float GetToPlayerAng();
	//playerとの角度を返す渡されたPosと
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

	//渡された角度分回るジャンプをする
	void Spin(float AtOneceAng);
	virtual void Jump(void);
	virtual void FrontJump(void);
	virtual void BackJump(void);
	virtual void ShootSnowBall(GameScene* GameScene);

	void CheckOverlapEnemies(const D3DXVECTOR3*);

	bool TakeDamage(int Damage);



protected:
	static const int DEFAULT_HP;
	int nowHP;		//体力	雪玉1発で1減少

private:
	EnemyStateBase *nowState;
	XFILE bodyMesh, handMesh;
	D3DXMATRIX mat, rotMat, transMat;

	XFILE hatMesh;
	D3DXMATRIX hatMat, hatOffsetMat, hatRotMat;

	bool isShoot = false;		//trueなら雪玉を投げる別な方法を考えたい
	//------------------------------------------------
	//定数
	//------------------------------------------------
	const static float HAT_RADIUS, HAT_HIGHT;
	const static float SENSING_LENGTH;
	//------------------------------------------------

	virtual void StageBorderProcessing(const StageBorder &StageBorder);

	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//交戦時の移動		球発射時は止まるようにする

	const static float SPHERE_RADIUS_HEAD;
	const static float SPHER_RADIUS_BODY;

};