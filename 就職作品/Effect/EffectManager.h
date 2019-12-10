#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"
#include"../Player/PlayerCamera.h"
#include"EnemyDeathAnime.h"

//---------------------------------------------------------------------------------
//エフェクトのインスタンスが入っている配列を複数持つクラス
//マネージャーのインスタンスにアクセスして、新しいエフェクトを作り配列に入れる役割
//---------------------------------------------------------------------------------

class EffectManager {
private:
	PlayerCamera *pPlayerCam;	//プレイヤーカメラのポインタ
	D3DXMATRIX billBoardMat;
public:
	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;
	std::vector<EnemyDeathAnime*> enemyDeathAnime;

	EffectManager();
	~EffectManager();
	void AllDelete(void);
	void Draw(void);
	void Update(void);
	void SetBillBoardMat(D3DXMATRIX *BillBoardMat);
};

extern EffectManager *effectManager;	//mainで宣言
