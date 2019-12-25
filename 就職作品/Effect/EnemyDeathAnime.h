#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include"../commonObj/SnowBall.h"
#include"../Enemy/Enemy.h"

//-------------------------------------------------------------------------
//倒れている敵を新しく作り倒れるアニメーションを再生するクラス
//雪玉と敵のインスタンスを渡して使う
//-------------------------------------------------------------------------

class EnemyDeathAnime{
public:
	//行列とXFILEと雪玉の方向ベクトルを渡す
	EnemyDeathAnime(Enemy &Enemy, SnowBall &SnowBall);
	~EnemyDeathAnime();
	void Draw(void);
	//Anime終了でfalseを返す
	bool Update(void);
private:
	XFILE mesh;
	D3DXMATRIX startMat, mat, rotMat;
	float nowAng;
	D3DXVECTOR3 rotAxis;		//回転軸
};