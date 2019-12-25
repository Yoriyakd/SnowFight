#pragma once
#include"../main.h"
#include"../ResourceManager.h"
#include"../Enemy/Enemy.h"
#include"../commonObj/SnowBall.h"

//-----------------------------------------------------------------------------
//敵の頭から落ちていく帽子を新しく作り落ちていくアニメーションを再生するクラス
//雪玉と敵のインスタンスを渡して使う
//コンストラクターの第3引数がtrueの場合HeadShot用のアニメを再生する
//-----------------------------------------------------------------------------

class EnemyHatAnime {
public:
	//第3引数がtrueの場合HeadShot用のアニメを再生する
	EnemyHatAnime(Enemy &Enemy, SnowBall &SnowBall, bool HeadShot);
	void Draw();
	bool Update();
private:
	XFILE mesh;
	D3DXMATRIX startRotMat, mat, rotMat;
	D3DXVECTOR3 rotAxis, moveVec;
};