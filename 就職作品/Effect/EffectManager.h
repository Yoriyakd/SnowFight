#pragma once
#include"../main.h"
#include<vector>
#include"../ResourceManager.h"
#include"SnowFrag.h"
#include"Locus.h"
#include"../Player/PlayerCamera.h"


//---------------------------------------------------------------------------------
//エフェクトのインスタンスが入っている配列を複数持つクラス
//マネージャーのインスタンスにアクセスして、新しいエフェクトを作り配列に入れる役割
//---------------------------------------------------------------------------------

class EffectManager {
public:
	EffectManager();
	~EffectManager();
	void AllDelete(void);

	void NewSnowFrag(const D3DXVECTOR3 &Pos);
	void NewSnowLocus(const D3DXMATRIX &SnowBallMat);

	void Draw(void);
	void Update(void);
	void SetBillBoardMat(D3DXMATRIX *BillBoardMat);

private:
	PlayerCamera *pPlayerCam;	//プレイヤーカメラのポインタ
	D3DXMATRIX billBoardMat;

	std::vector<SnowFrag*> snowFrag;
	std::vector<SnowLocus*> snowLocus;
};

extern EffectManager *effectManager;	//mainで宣言
